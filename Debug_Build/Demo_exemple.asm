#INCLUDE "Library_init.asm"

; TEST Demo Loading from ASM File, shows a file that can successfully be parsed
; Comment lines and blank lines are removed by the assembler

;; Comment on empty lines with a double semicolon at the start are kept, adding a NOP instruction (visible in the ROM inspector)

; The first 24 columns are for labels only, followed by 1 space, then 5 fixed columns for the instructio/opcode followed by a final 1 space
; A second label can be set on the same line if a space is left between

#DEFINE CONST 0x01                                         ; Constant may be define this way, with a simple NAME VALUE structure, nothing more, no param
#DEFINE TARGET_REG $D                                      ; Register ID may be used as well, a simple replace will be done using the name when found 

:PROGRAM_START :BEGIN   SET   0xFF,  $0                    ; Comments at the end of an instruction line are kept after import (visible in the ROM inspector)
                        ; Unlike instructions, comments don't have to follow a precise position (but it looks nicer when all alligned)
                        
:PROGRAM_HEAD                                              ; Labels defined on a line with no instruction will point to the next valid instruction
                                                           ; Comments not set at the end of an instruction are discarded
:PROGRAM_BEGIN_HEAD_START_HERE/SET   0x08,  $1             ; Very long labels can exceed 24 char by using the / to mark the end/start of the label/instruction (no space)  
                                                           ; Labels are not case sensitive, up to 2 per line, used for relative adresse with :
                                                           ; Labels can only use A-Z 0-9 and _
                                                           ; Labels are always defined with a single : (left side)

                        SET   0x01,      $2                ; Each parameter is seperated by , and spaces are optional and the number may vary to help align/indent the params
                        SUB   $0 - $1 =  $3                ; The , may be substitute with the following + - = == & | ^ > -> >> < <- << ? for readablity
                        ADD   $3 + $2 -> $3                ; Those 3 ADD lines are strictly equivalent
                        ADD   $3,  $2,   $3                
                        ADD   $3,$2,$3                            

; ######################

:LOOP_START             INC   $3                            
                        SIF   $3 == "0x09"                 ; In addition to the list of symbols that are replaced by , the following ( ) " # @ ! are discarded entirely 
                        JMPA  #:LOOP_START                 ; Those characters may be used for readablity, the only reserved chars are $ : / * 
                        SET   "0b00000000"->$3             ; Beside hexadecimal values prefixed with 0x (non significant zeros are optional)
                        SET   (255)->$3                    ; The prefix 0b followed by a binary value may be used, ss well as decimal values

; ######################

                        JMPA  :RELATIVE_JMP                ; When used (inside an instruction), a single : mean relative address (8 bits)
                        NOP                                ; Those are limited to +/- 127 instructions forward or backward between source and destination
:RELATIVE_JMP           NOP                                ; Under the hood, 0x80 points to the next line following the current instruction
                        NOP                                ; The assembler will replace the previous call to :RELATIVE_JMP in JMPA with 0x81 to jump forward by 2
                        NOP                                ; However, from this very line, 0x7E would be used to jump back by 2 to :RELATIVE_JMP 
                                                           ; Relative tags are easier to use for short range jump

                        SET   :*ABSOLUTE_JMP1 , $0         ; To jump to a location further away, an absolute address (16 bits) is required (called WideJump)
                        SET   :.ABSOLUTE_JMP1 , $1         ; But it's length requires 2 parts (8 bits each), a High and a Low value, respectively accessed by :* and :.
                        WJMPR $0, $1                       ; Using :: provides the most significant bits and :* the least significant bits of an absolute addr
                        NOP
                        NOP
:ABSOLUTE_JMP1          WJMP  #:.ABSOLUTE_JMP2             ; If an instruction (exemple WJMP) takes a wider data portion (12 bits for WJMP), :. outputs the lower 12 bits
                        NOP
                        NOP
:ABSOLUTE_JMP2          NOP


; ==========================================================
[MACRO_EXEMPLE
                        SET   3, $2 
]
; ==========================================================

                        %MACRO_TEST                        ; Macro can be called before or after the definition but NOT within it's own definition (no recursion)
                        NOP                                ; Calling one takes the same place as an instruction, the code will be inserted inline
                        NOP                                ; Labels and Macros cannot be redefined, names must be unique

; ==========================================================
[MACRO_TEST                                                ; The definition starts with [NAME and end with ] each on their own empty line     
                        SET   5, $2                        ; 
:MACRO_LOOP             DSIZ  $2                           ; Labels inside a macro should not be called from outside as they get renamed at import (for when the same macro is used multiple times)
                        JMPA  :MACRO_LOOP                  ; Every time a macro is used, the labels receive the suffix _MACRO_* where * starts at zero and is incremented each time
                        NOP                                   
                        %MACRO_EXEMPLE                     ; Calling a different Macro within a definition is valid
                        SET   :%CONST, $1                  ; Using a constant requires the :% prefix
]
; ==========================================================

                        %MACRO_TEST    
                        SEQ   :%TARGET_REG == $D           ; On that CPU, the 4 last registers are readonly, they always return fixed values 
                        HALT                               ; $C->0x00  $D->0x01  $E->0xFF  $F->0X80 (0x80 is == 0b10000000)
                        JMPA  :PROGRAM_START               ; Unless something is done, at the very last instruction the CPU loops back to the very first                      
                                                           ; Included files are simply concatenated at that location
                                                           ; Making the very first instruction something inside the included files in this exemple
                                                           
; When a .asm file is imported, the controls at the bottom of the ROM window are disabled
; Editing can only be done by pressing Clear then re-importing the .asm file



;  CHECK ??
; Labels must also be terminated by a : when used (inside an instruction)

