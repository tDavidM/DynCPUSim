;TEST Demo Loading from ASM File, shows a file that can test every circuits of the CPU

:START_OVER             SET   "0xFF", $0              ;Test if $0 stores a value and if SET instruction outputs on bus C correctly 
						SEQ   $0,     $E              ;Test that $0 outputs correctly on Bus A, that $E outputs 0xFF on Bus B, and SkipEqual works
						WJMP  #:*HALT_ON_ERR:         ;If Error
						SEQ   $E,     $0              ;Test that $0 outputs correctly on Bus B, that $E outputs 0xFF on Bus A, and SkipEqual works
						WJMP  #:*HALT_ON_ERR:         ;If Error
                        
                        SET   "0x00", $0              ;
                        SEQ   $0,     $E              ;Test that SkipEqual works when not equal
                        JMPA  #:TEST_NO_3:            ;Test that JumpAddr works
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        
:TEST_NO_3              SEQ   $C,     $0              ;Test that $C outputs 0x00 on Bus A
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SEQ   $0,     $C              ;Test that $C outputs 0x00 on Bus B
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        
                        SET   "0xFF", $0              ;
                        SET   "0xFF", $1              ;Test if $1 stores a value
						SEQ   $0,     $1              ;Test if $1 and $0 both output correctly on Bus A and B
						WJMP  #:*HALT_ON_ERR:         ;If Error
						SEQ   $1,     $0              ;Test if $1 and $0 both output correctly on Bus A and B
						WJMP  #:*HALT_ON_ERR:         ;If Error
						
                        AND   $0,     $1,     $2      ;Test if AND works and if $2 stores a value
						SEQ   $1,     $2              ;Test if $2 outputs correctly on Bus B
						WJMP  #:*HALT_ON_ERR:         ;If Error
						SEQ   $2,     $1              ;Test if $2 outputs correctly on Bus A
						WJMP  #:*HALT_ON_ERR:         ;If Error
                        JMPA  #:TEST_NO_6:            ;An other test that JumpAddr works
                        
:TEST_NO_6              SIFZ  $C                      ;Test SkipIfZero on $C
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        IFNZ  $C,     #:TEST_6_ERR_JMP: ;Test IfNotZero should not follow that jump
                        IFZ   $C,     #:TEST_6_OK_JMP:;Test IfZero should follow that jump
:TEST_6_ERR_JMP         WJMP  #:*HALT_ON_ERR:         ;If Error                       
:TEST_6_OK_JMP          AND   $C,     $E,     $2      ;Test AND with 0x00 & 0xFF
                        SIFZ  $2                      ;Sould be 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        IFNZ  $D,     #:TEST_6_OK_JMP2:;Test IfNotZero should follow that jump
                        WJMP  #:*HALT_ON_ERR:         ;If Error
:TEST_6_OK_JMP2         IFZ   $D,     #:TEST_6_ERR_JMP:;Test IfZero should not follow that jump

                        NOP
                        WJMP  #:*TEST_WIDEJMP1:       ;Should make a small jump foward
                        NOP
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        
:TEST_WIDEJMP2          SIF   $E,     0xFF            ;Test SkipIf
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $C,     0x00            ;Test SkipIf
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $D,     0x01            ;Test SkipIf
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $C,     0x01            ;Test SkipIf
                        SIF   $D,     0x00            ;Test SkipIf
                        SIF   $E,     0x00            ;Test SkipIf
                        SIF   $E,     0x01            ;Test SkipIf
                        SIF   $F,     0x80            ;Test SkipIf
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $F,     0x00            ;Test SkipIf
                        SIF   $F,     0x01            ;Test SkipIf
                        SIF   $F,     0xFF            ;Test SkipIf
:TEST_WIDEJMP1          WJMP  #:*TEST_WIDEJMP1:       ;Should make a small jump backward
                        
                        
                        
                        SET   "0xFF", $1              
                        SET   @$0,    $1 
                        ADD   $0,     $D,     $0      ;
                        ADD   $1,     $D,     $1
                        SEQ   $1,     $E
                        JMPA  #"0x7C"
                        SET   "0xFF", $E



                        WJMP  #:*START_OVER:
:HALT_ON_ERR            HALT



 ; GETA      
 ; SETA            
 ; ADD       
 ; SUB       
 ; OR        
 ; XOR       
 ; SETV      
 ; GRT       
 ; WJMPV     
 ; NOT       
 ; LSHT      
 ; LROT      
 ; RSHT      
 ; RROT      
 ; GETR      
 ; SETR      
 ; SGRT      
 ; IFZR      
 ; WJMPR     
 ; LROTC     
 ; RROTC
 ; RSHTA     
 ; JMPR      
 ; CFLG      
 ; RSTC      
 ; SETC
 ; INC   
 ; DEC   
 ; RND   
 ; SIFNZ 
 ; SIFNC 
 ; DSINZ 

