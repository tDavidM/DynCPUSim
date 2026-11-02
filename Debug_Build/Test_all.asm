;TEST Demo Loading from ASM File, shows a file that can test every circuits of the CPU

;Default debug value register
#DEFINE DBG_REG $3                                    

;Define for the registers outputing a fixed value   
#DEFINE REG_VAL_00 $C
#DEFINE REG_VAL_01 $D
#DEFINE REG_VAL_FF $E
#DEFINE REG_VAL_80 $F

;MACRO to print a debug value to the Terminal (input $3, uses $9)
[PRINT_DBG                                            
                        SET   "0x03", $9              ;Set command to PrintDbgVal
                        WIOB  :%DBG_REG               ;Set the debug value
                        WIOA  $9                      ;Send command plus value
]

;Test 0, basic test on WideJump and NoOp
:START_OVER             NOP
                        NOP
;                        WJMP  :.SKIP_FIRST_HALT               ;Make sure WideJump works as it's used a lot for error handling
                        WJMP   :.TEST_NO_25B                  ;Alternatively, bypass to a latter test
                        NOP
                        HALT                                  ;If this run, there's an issue
                        NOP
:SKIP_FIRST_HALT        NOP
;Test 1, SET and SkipEqual as well as register $0 and $E tests 
:TEST_NO_1              SET   "0x01",         :%DBG_REG       ;Keep track of where it halts, if it does
                        %PRINT_DBG                                                    ;Print Debug value
                        SET   "0xFF",         $0              ;Test if $0 stores a value and if SET instruction outputs on bus C correctly 
                        SEQ   $0,             :%REG_VAL_FF    ;Test that $0 outputs correctly on Bus A, that $E outputs 0xFF on Bus B, and SkipEqual works
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        SEQ   :%REG_VAL_FF,   $0              ;Test that $0 outputs correctly on Bus B, that $E outputs 0xFF on Bus A, and SkipEqual works
                        WJMP  :.HALT_ON_ERR                   ;If Error
;Test 2, JumpAddr and more $0 and $E tests
:TEST_NO_2              SET   "0x02",         :%DBG_REG       ;Keep track of where it halts, if it does
                        %PRINT_DBG                                                    ;Print Debug value
                        SET   "0x00",         $0              ;
                        SEQ   $0,             :%REG_VAL_FF    ;Test that SkipEqual works when not equal
                        JMPA  :TEST_NO_2A                     ;Test that JumpAddr works forward
                        NOP
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        NOP
                        NOP
:TEST_NO_2B             JMPA  :TEST_NO_3                      ;Test that JumpAddr works
                        NOP
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        NOP
:TEST_NO_2A             JMPA  :TEST_NO_2B                     ;Test that JumpAddr works backward
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        NOP
;Test 3, register $C and more $0 and SkipEqual tests
:TEST_NO_3              SET   "0x03",         :%DBG_REG       ;
                        %PRINT_DBG
                        SET   "0x00",         $0              ;
                        SEQ   $0,             :%REG_VAL_01    ;Test that SkipEqual works when not equal
                        SEQ   :%REG_VAL_00,   $0              ;Test that $C outputs 0x00 on Bus A
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        SEQ   $0,             :%REG_VAL_80    ;Test that SkipEqual works when not equal
                        SEQ   $0,             :%REG_VAL_00    ;Test that $C outputs 0x00 on Bus B
                        WJMP  :.HALT_ON_ERR                   ;If Error
;Test 4, register $1 tests
:TEST_NO_4              SET   "0x04",         :%DBG_REG       ;
                        %PRINT_DBG
                        SET   "0x00",         $0              ;
                        SET   "0x00",         $1              ;
                        SEQ   $0,             $1              ;Test if $1 and $0 both output correctly on Bus A and B
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        SEQ   $1,             $0              ;Test if $1 and $0 both output correctly on Bus A and B
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        SET   "0xFF",         $0              ;
                        SET   "0xFF",         $1              ;Test if $1 stores a value
                        SEQ   $0,             $1              ;Test if $1 and $0 both output correctly on Bus A and B
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        SEQ   $1,             $0              ;Test if $1 and $0 both output correctly on Bus A and B
                        WJMP  :.HALT_ON_ERR                   ;If Error
;Test 5, AND and register $2 and more $1 tests
:TEST_NO_5              SET   "0x05",         :%DBG_REG       ;
                        %PRINT_DBG
                        AND   $0,     $1,     $2              ;Test if AND works and if $2 stores a value
                        SEQ   :%REG_VAL_00,   $2              ;Test if $2 outputs correctly on Bus B
                        SEQ   $1,             $2              ;
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        SEQ   $2,             :%REG_VAL_00    ;Test if $2 outputs correctly on Bus A
                        SEQ   $2,             $1              ;
                        WJMP  :.HALT_ON_ERR                   ;If Error
;Test 6, SkipIfZero, IfNotZero, IfZero and more AND
:TEST_NO_6              SET   "0x06",         :%DBG_REG       ;
                        %PRINT_DBG
                        JMPA  #:TEST_NO_6A                    ;An other test that JumpAddr works

:TEST_NO_6A             SIFZ  :%REG_VAL_00                    ;Test SkipIfZero on $C
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        IFNZ  :%REG_VAL_00,   :TEST_6_ERR_JMP ;Test IfNotZero should not follow that jump
                        IFZ   :%REG_VAL_00,   :TEST_6_OK_JMP  ;Test IfZero should follow that jump
                        NOP
:TEST_6_ERR_JMP         WJMP  :.HALT_ON_ERR                   ;If Error                       
:TEST_6_OK_JMP          AND   :%REG_VAL_00, :%REG_VAL_FF, $2  ;Test AND with 0x00 & 0xFF
                        SIFZ  $2                              ;Sould be 0x00
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        AND   :%REG_VAL_FF, :%REG_VAL_00, $2  ;Test AND with 0xFF & 0x00
                        SIFZ  $2                              ;Sould be 0x00
                        WJMP  :.HALT_ON_ERR                   ;If Error
                        IFNZ  :%REG_VAL_01,   :TEST_6_OK_JMP2 ;Test IfNotZero should follow that jump
                        WJMP  :.HALT_ON_ERR                   ;If Error
:TEST_6_OK_JMP2         IFZ   :%REG_VAL_01,   :TEST_6_ERR_JMP ;Test IfZero should not follow that jump
;Test 7, SkipIf and real cases for WideJump
:TEST_NO_7              SET   "0x07",         :%DBG_REG       ;
                        %PRINT_DBG
                        NOP
                        WJMP  :.TEST_WIDEJMP1                 ;Should make a small jump foward
                        NOP
                        WJMP  :.HALT_ON_ERR                   ;
                        NOP
:TEST_WIDEJMP3          NOP                                   ;This is actually part of Test 18, an other WideJump test
                        SET   0x01,           $0
                        WJMP  :.TEST_WIDEJMP4                 ;  going back and foward over the limit of a relative jmp
                        WJMP  :.HALT_ON_ERR
:TEST_WIDEJMP5          SET   0x02,           $0
                        WJMP  :.TEST_WIDEJMP6
                        NOP
                        NOP
                        WJMP  :.HALT_ON_ERR                   ;
:TEST_WIDEJMP2          SIF   :%REG_VAL_FF,   0x00            ;Test SkipIf (no skip)
                        SIF   :%REG_VAL_FF,   0xFF            ;Test SkipIf (skip)
                        WJMP  :.HALT_ON_ERR                   ;
                        SIF   :%REG_VAL_00,   0x01            ;Test SkipIf (no skip)
                        SIF   :%REG_VAL_00,   0x00            ;Test SkipIf (skip)
                        WJMP  :.HALT_ON_ERR                   ;
                        SIF   :%REG_VAL_01,   0x00            ;Test SkipIf (no skip)
                        SIF   :%REG_VAL_01,   0x01            ;Test SkipIf (skip)
                        WJMP  :.HALT_ON_ERR                   ;
                        SIF   :%REG_VAL_FF,   0x01            ;Test SkipIf (no skip)
                        SIF   :%REG_VAL_80,   0x80            ;Test SkipIf (skip)
                        WJMP  :.HALT_ON_ERR                   ;                      
                        SIF   :%REG_VAL_80,   0x00            ;Test SkipIf (no skip)
                        SIF   :%REG_VAL_FF,   0xFF            ;Test SkipIf (skip)
:TEST_WIDEJMP1          WJMP  :.TEST_WIDEJMP2                 ;Should make a small jump backward
;Test 8, NOT, OR and XOR
:TEST_NO_8              SET   "0x08",         :%DBG_REG       ;
                        %PRINT_DBG
                        NOT   :%REG_VAL_FF,   $0              ;Test seting $0 to !0xFF
                        NOT   :%REG_VAL_00,   $1              ;Test seting $1 to !0x00
                        AND   $0,     $1,     $2              ;Test AND with 0x00 & 0xFF
                        SEQ   $0,             $2              ;Both should be 0x00
                        WJMP  :.HALT_ON_ERR                   ;
                        SIF   $1,             0xFF            ;Should be 0xFF
                        WJMP  :.HALT_ON_ERR                   ;
                        OR    $1,   :%REG_VAL_FF,   $0        ;Test OR with 0xFF | 0xFF
                        OR    $0,   :%REG_VAL_00,   $1        ;Test OR with 0xFF | 0x00
                        SEQ   $0,             $1              ;Both should be 0xFF
                        WJMP  :.HALT_ON_ERR                   ;
                        OR    :%REG_VAL_00, :%REG_VAL_00, $0  ;Test OR with 0x00 | 0x00
                        OR    :%REG_VAL_00, :%REG_VAL_FF, $1  ;Test OR with 0x00 | 0xFF
                        SIF   $1,             0xFF            ;$1 should be == to 0xFF
                        WJMP  :.HALT_ON_ERR                   ;
                        SIF   $0,             0x00            ;$0 should be == to 0x00
                        WJMP  :.HALT_ON_ERR                   ;
                        XOR   $0,     $1,     $2              ;Test XOR with 0x00 ^ 0xFF
                        XOR   $1,     $2,     $0              ;Test XOR with 0xFF ^ 0xFF
                        XOR   $2,     $0,     $1              ;Test XOR with 0xFF ^ 0x00
                        XOR   $0,   :%REG_VAL_00,   $2        ;Test XOR with 0x00 ^ 0x00
                        SEQ   $0,             $2              ;After those 4 XOR, $0 and $2 should be 0x00
                        WJMP  :.HALT_ON_ERR                   ;
;Test 9, SkipIfNotZero, JumpReg and IfZeroReg
:TEST_NO_9              SET   "0x09",         :%DBG_REG       ;
                        %PRINT_DBG
                        SET   #0x82,          $2              ;Set $2 for testing IfZeroReg, relative addr from where it's going to be used
                        IFZR  $0,             #$2             ;Test IfZeroReg, $0 should be 0x00 (See previous XORs)
                        WJMP  :.HALT_ON_ERR
                        WJMP  :.HALT_ON_ERR
                        SIFNZ $1                              ;Test SkipIfNotZero with $1 that is != 0x00 (See previous XORs)
                        WJMP  :.HALT_ON_ERR
                        SET   #0x7F,          $2              ;Set $2 for testing IfZeroReg, relative addr from where it's going to be used
                        SET   #0x83,          $0              ;Set $0 for testing JumpReg, relative addr from where it's going to be used                
                        SIFNZ :%REG_VAL_00                    ;Test SkipIfNotZero with $C that is == 0x00
                        JMPR  #$0                             ;Test JumpReg
                        NOP
                        NOP
                        WJMP  :.HALT_ON_ERR
                        IFZR  $1,             #$2             ;Test IfZeroReg, $1 should not be 0x00
;Test 10, SkipGreater
:TEST_NO_10             SET   "0x0A",         :%DBG_REG
                        %PRINT_DBG
                        SET   0x00,           $0
                        SET   0x01,           $1
                        SGRT  $0,             $1              ;Test SkipFGreater 0x00 > 0x01
                        SGRT  $1,             $0              ;Test SkipFGreater 0x01 > 0x00
                        WJMP  :.HALT_ON_ERR
                        SET   0x55,           $0
                        SET   0xAA,           $1
                        SGRT  $0,             $1              ;Test SkipFGreater 0x55 > 0xAA
                        SGRT  $1,             $0              ;Test SkipFGreater 0xAA > 0x55
                        WJMP  :.HALT_ON_ERR
                        SET   0x00,   $0
                        SET   0xFF,   $1
                        SGRT  $0,             $1              ;Test SkipFGreater 0x00 > 0xFF
                        SGRT  $1,             $0              ;Test SkipFGreater 0xFF > 0x00
                        WJMP  :.HALT_ON_ERR
;Test 11, Greatest (instruction removed)
;:TEST_NO_11             SET   "0x0B",         :%DBG_REG
;                        %PRINT_DBG
;                        GRT   $0,      $1,      $2      ;Test Greater with 0x00 and 0xFF
;                        GRT   $2, :%REG_VAL_01, $1      ;Test Greater with 0xff and 0x01
;                        SIF   $1,               0xFF    ;$1 should be == to 0xFF
;                        WJMP  :.HALT_ON_ERR
;                        SET   0x55,             $0
;                        SET   0xAA,             $1
;                        GRT   $0,      $1,      $2      ;Test Greater with 0x55 and 0xAA
;                        GRT   $2, :%REG_VAL_80, $2      ;Test Greater with 0xAA and 0x80
;                        SIF   $2,               0xAA    ;$1 should be == to 0xAA
;                        WJMP  :.HALT_ON_ERR
;Test 12, Add and carry flag
:TEST_NO_12             SET   "0x0C",         :%DBG_REG
                        %PRINT_DBG
                        ADD   :%REG_VAL_00, :%REG_VAL_01, $0  ;Test Add with 0x00 + 0x01
                        SIFC                                  ;Test SkipCarry, sould not skip
                        SIFNC                                 ;Test SkipIfNoCarry
                        WJMP  :.HALT_ON_ERR
                        SEQ   $0,             :%REG_VAL_01    ;Check that $0 is == 0x01
                        WJMP  :.HALT_ON_ERR
                        ADD   $0,   :%REG_VAL_01,   $0        ;Test Add with 0x01 + 0x01
                        SIF   $0,             0x02            ;Check that $0 is == 0x02
                        WJMP  :.HALT_ON_ERR
                        SET   0x55,           $0
                        SET   0xAA,           $1
                        ADD   $1,     $0,     $0              ;Test Add with 0xAA + 0x55
                        SIF   $0,             0xFF            ;Check that $0 is == 0xFF
                        WJMP  :.HALT_ON_ERR
                        ADD   $0,   :%REG_VAL_01,   $0        ;Test Add with 0xFF + 0x01
                        SIFC                                  ;Test SkipCarry
                        WJMP  :.HALT_ON_ERR
                        SIFNC                                 ;Test SkipIfNoCarry, sould not skip
                        SIFZ  $0                              ;Sould be 0x00, so skip
                        WJMP  :.HALT_ON_ERR
                        CFLG  $1                              ;Save Carry Flag to $1
                        CLCR                                  ;Clear Carry Flag
                        SIF   $1,             0x01            ;Check that $1 is == 0x01
                        WJMP  :.HALT_ON_ERR
                        CFLG  $1                              ;Save Carry Flag to $1
                        SIFZ  $1                              ;Check that $1 is == 0x00
                        WJMP  :.HALT_ON_ERR
                        ADD   :%REG_VAL_00,   $0,   $0        ;Test Add with 0x00 + 0x00
                        SIFZ  $0                              ;Check that $0 is == 0x00
                        WJMP  :.HALT_ON_ERR
;Test 13, Subtract, Increment, Decrement and 
:TEST_NO_13             SET   "0x0D",         :%DBG_REG
                        %PRINT_DBG
                        SUB   :%REG_VAL_80, :%REG_VAL_01, $0  ;Test SUB with 0x80 - 0x01
                        SET   0x0F,           $1
                        SUB   $0,     $1,     $0              ;Test SUB with 0x7F - 0x0F
                        SET   0x50,           $1
                        SUB   $0,     $1,     $0              ;Test SUB with 0x70 - 0x50
                        SET   0x1F,   $1
                        SUB   $0,     $1,     $0              ;Test SUB with 0x20 - 0x1F
                        SIF   $0,             0x01            ;Check that $0 is == 0x01
                        WJMP  :.HALT_ON_ERR
                        SIFC                                  ;Test SkipIfCarry, after subtract, the carry flag represents a borrow flag
                        SIFNC                                 ;Test SkipIfNoCarry,
                        WJMP  :.HALT_ON_ERR
                        SET   0x02,           $1
                        SUB   $0,     $1,     $0              ;Test SUB with 0x01 - 0x02
                        SEQ   $0,             :%REG_VAL_FF    ;Check that $0 is == 0xFF or -0x01
                        WJMP  :.HALT_ON_ERR
                        SIFNC                                 ;Test SkipIfNoCarry, a borrow should have occured
                        SIFC                                  ;Test SkipIfCarry,
                        WJMP  :.HALT_ON_ERR

                        INC   $0                              ;Test Increment on $0 from 0xFF to 0x00
                        INC   $0                              ;Increment to 0x01
                        INC   $0                              ;Increment
                        SIF   $0,             0x02            ;Check that $0 is == 0x02
                        WJMP  :.HALT_ON_ERR
                        DEC   $0                              ;Test Decrement on $0
                        SEQ   $0,             :%REG_VAL_01    ;Check that $0 is == 0x01
                        WJMP  :.HALT_ON_ERR
                        DEC   $0
                        DEC   $0
                        SEQ   $0,             :%REG_VAL_FF    ;Check that $0 is == 0xFF or -0x01
                        WJMP  :.HALT_ON_ERR
;Test 14, AddCarry, Compare
:TEST_NO_14             SET   "0x0E",         :%DBG_REG
                        %PRINT_DBG
                        ADD   :%REG_VAL_80, :%REG_VAL_80, $0  ;Cause an overflow
                        ADDC  $0,   :%REG_VAL_01,   $0        ;Add 0x00(with carry) + 0x01
                        SIF   $0,             0x02            ;Check that $0 is == 0x02
                        WJMP  :.HALT_ON_ERR
                        ADDC  $0,   :%REG_VAL_01,   $0        ;Add 0x02(no carry) + 0x01
                        SIF   $0,             0x03            ;Check that $0 is == 0x03
                        WJMP  :.HALT_ON_ERR

                        CMP   :%REG_VAL_01,   $0,   $1        ;Set the difference in $1 (carry flag set if $B<$C)
                        SIFC                                  ;It should as 0x01 < 0x03
                        WJMP  :.HALT_ON_ERR
                        SIF   $1,             0xFE            ;Check that $1 is == -2 (0xFE) (difference between 0x01 and 0x03)
                        WJMP  :.HALT_ON_ERR
                        SET   0x02,           $1
                        CMP   $0,     $1,     $1              ;Difference between 0x03 and 0x02
                        SIFNC                                 ;It should as 0x03 !< 0x02
                        WJMP  :.HALT_ON_ERR
                        SIF   $1,             0x01            ;Check that $1 is == 0x01 (difference between 0x03 and 0x02)
                        WJMP  :.HALT_ON_ERR
;Test 15, DecSkipZero and DecSkipNotZero
:TEST_NO_15             SET   "0x0F",         :%DBG_REG
                        %PRINT_DBG
                        SET   0x00,           $0
:TEST_NO_15_LOOP_INC    INC   $0                              ;Increment $0, looping until == 0x10
                        SIF   $0,             0x10            ;Quit when $0 == 0x10
                        JMPA  :TEST_NO_15_LOOP_INC            ;Loop to INC $0
                        SET   0xFF,           $0
:TEST_NO_15_LOOP_DEC    DEC   $0                              ;Decrement $0, looping until == 0xEF
                        SIF   $0,             0xEF            ;Quit when $0 == 0xEF
                        JMPA  :TEST_NO_15_LOOP_DEC            ;Loop to DEC $0
                        
                        SET   0x10,           $0
:TEST_NO_15_LOOP_DSIZ   NOP                                   ;Here would be instructions to run in a loop
                        DSIZ  $0                              ;Test DecSkipZero :-) my favorite instruction
                        JMPA  :TEST_NO_15_LOOP_DSIZ           ;Loop to DSIZ $0
                        SIFZ  $0                              ;$0 Should be zero by now
                        WJMP  :.HALT_ON_ERR
                        
                        SET   0x10,           $0
:TEST_NO_15_LOOP_DSINZ  DSINZ $0                              ;Test DecSkipNotZero
                        JMPA  :TEST_NO_15_END                 ;quit Loop when $0 == 0x00
                        NOP                                   ;Here would be instructions to run in a loop
                        JMPA  :TEST_NO_15_LOOP_DSINZ          ;Loop to DSINZ $0
:TEST_NO_15_END         SIFZ  $0                              ;$0 Should be zero by now
                        WJMP  :.HALT_ON_ERR
;Test 16, Right and Left Shift plus Carry Flag for the dropped bits
:TEST_NO_16             SET   "0x10",         :%DBG_REG
                        %PRINT_DBG
                        CPY   :%REG_VAL_01,   $0              ;CPY is an alias for OR with 0x00
                        LSHT  $0,             $0              ;Test LeftShift with 0x01
                        SIF   $0,             0x02            ;Check that $0 is == 0x02
                        WJMP  :.HALT_ON_ERR

                        RSHT  $0,             $0              ;Test LeftShift with 0x01
                        SIF   $0,             0x01            ;Check that $0 is == 0x01
                        WJMP  :.HALT_ON_ERR

                        SET   0x55,           $0
                        LSHT  $0,             $0              ;Test LeftShift with 0b0101 0101
                        SIF   $0,             0xAA            ;Check that $0 is == 0b1010 1010
                        WJMP  :.HALT_ON_ERR
                        SIFNC                                 ;Test that carry bit is zero
                        WJMP  :.HALT_ON_ERR

                        RSHT  $0,             $0              ;Test RightShift with 0xAA (0b1010 1010)
                        SIF   $0,             0x55            ;Check that $0 is == 0x55 (0b0101 0101)
                        WJMP  :.HALT_ON_ERR
                        SIFNC                                 ;Test that carry bit is zero
                        WJMP  :.HALT_ON_ERR

                        CLCR                                  ;Clear Carry Flag
                        CPY   :%REG_VAL_FF,   $0              
                        LSHT  $0,             $0              ;Test LeftShift with 0xFF
                        SIF   $0,             0xFE            ;Check that $0 is == 0xFE (0b1111 1110)
                        WJMP  :.HALT_ON_ERR
                        SIFC                                  ;Test that carry bit is one
                        WJMP  :.HALT_ON_ERR
;Test 17, Arithmetic Right Shift plus Carry Flag for the dropped bits
:TEST_NO_17             SET   "0x11",         :%DBG_REG
                        %PRINT_DBG
                        CPY   :%REG_VAL_FF,   $0
                        RSHT  $0,             $0              ;Test RightShift with 0xFF
                        SIFC                                  ;Test that carry bit is one
                        WJMP  :.HALT_ON_ERR
                        SIF   $0,             0x7F            ;Check that $0 is == 0x7F (0b0111 1111)
                        WJMP  :.HALT_ON_ERR

                        CLCR                                  ;Clear Carry Flag
                        CPY   :%REG_VAL_FF,   $0
                        RSHTA $0,             $0              ;Test RightArSht with 0xFF
                        SIF   $0,             0xFF            ;Check that $0 is == 0xFF
                        WJMP  :.HALT_ON_ERR
                        SIFC                                  ;Test that carry bit is one
                        WJMP  :.HALT_ON_ERR

                        CPY   :%REG_VAL_80,   $0
                        RSHTA $0,             $0              ;Test RightArSht with 0b1000 0000
                        SIF   $0,             0xC0            ;Check that $0 is == 0b1100 0000
                        WJMP  :.HALT_ON_ERR
                        SIFNC                                 ;Test that carry bit is zero
                        WJMP  :.HALT_ON_ERR
;Test 18, Left and Right Rotate
:TEST_NO_18             SET   "0x12",         :%DBG_REG
                        %PRINT_DBG
                        CLCR                                  ;Clear Carry Flag
                        SET   0xAA,           $0
                        LROT  $0,             $0              ;Test LeftRotate with 0xAA
                        SIFNC                                 ;Test that carry bit is zero
                        WJMP  :.HALT_ON_ERR
                        SIF   $0,             0x55            ;Check that $0 is == 0x55
                        WJMP  :.HALT_ON_ERR

                        LROT  $0,             $0              ;Test LeftRotate with 0x55
                        SIFNC                                 ;Test that carry bit is zero
                        WJMP  :.HALT_ON_ERR
                        SIF   $0,             0xAA            ;Check that $0 is == 0xAA
                        WJMP  :.HALT_ON_ERR

                        RROT  $0,             $0              ;Test RightRotate with 0xAA
                        SIFNC                                 ;Test that carry bit is zero
                        WJMP  :.HALT_ON_ERR
                        SIF   $0,             0x55            ;Check that $0 is == 0x55
                        WJMP  :.HALT_ON_ERR

                        RROT  $0,             $0              ;Test RightRotate with 0x55
                        SIFNC                                 ;Test that carry bit is zero
                        WJMP  :.HALT_ON_ERR
                        SIF   $0,             0xAA            ;Check that $0 is == 0xAA
                        WJMP  :.HALT_ON_ERR

                        SET   0xFF,           $0
                        LROT  $0,             $0              ;Test LeftRotate with 0xFF
                        RROT  $0,             $0              ;Test RightRotate with 0xFF
                        SIF   $0,             0xFF            ;Check that $0 is == 0xFF
                        WJMP  :.HALT_ON_ERR
;Test 19, Left and Right Carry Rotate
:TEST_NO_19             SET   "0x13",         :%DBG_REG
                        %PRINT_DBG
                        CLCR                                  ;Clear Carry Flag
                        SET   0b10101010,     $0
                        LROTC $0,             $0              ;Test LeftCarryRotate with 0xAA
                        SIFC                                  ;Test that carry bit is one
                        WJMP  :.HALT_ON_ERR
                        SIF   $0,             0b01010100      ;Check that $0 is == 0x54
                        WJMP  :.HALT_ON_ERR
                        
                        LROTC $0,             $0              ;Test LeftCarryRotate with 0x54 (0b0101 0100)
                        SIFNC                                 ;Test that carry bit is zero
                        WJMP  :.HALT_ON_ERR
                        SIF   $0,             0b10101001      ;Check that $0 is == 0xA9 (0b1010 1001)
                        WJMP  :.HALT_ON_ERR

                        CLCR                                  ;Clear Carry Flag
                        RROTC $0,             $0              ;Test RightCarryRotate with 0xA9 (0b1010 1001)
                        SIFC                                  ;Test that carry bit is one
                        WJMP  :.HALT_ON_ERR
                        SIF   $0,             0x54            ;Check that $0 is == 0x54
                        WJMP  :.HALT_ON_ERR

                        RROTC $0,             $0              ;Test RightCarryRotate with 0x54 (0b0101 0100)
                        SIFNC                                 ;Test that carry bit is zero
                        WJMP  :.HALT_ON_ERR
                        SIF   $0,             0xAA            ;Check that $0 is == 0xAA (0b1010 1010)
                        WJMP  :.HALT_ON_ERR

                        RSHT  :%REG_VAL_01,   $0              ;Set Carry Flag to one
                        SET   0xFF,           $0
                        LROTC $0,             $0              ; L, L
                        LROTC $0,             $0              ;
                        RROTC $0,             $0              ; R, R
                        RROTC $0,             $0              ;
                        SIF   $0,             0xFF            ;Check that $0 is == 0xFF
                        WJMP  :.HALT_ON_ERR
                        
;Test 20, Random number, first pass
:TEST_NO_20             SET   "0x14",         :%DBG_REG
                        %PRINT_DBG
                        SET   0xFF,           $B              ;Prepare the seed for the RNG
                        SRNG                                  ;Set RngSeed
                        SET   0x00,           $B
                        SET   0x20,           $1 
                        NOP                                   ;Give the RNG some time to shift 
                        NOP
                        NOP
                        NOP
                        NOP
                        NOP
                        NOP
                        NOP
:TEST_NO_20A            RND   $0                              ;Get a random number in $0
                        SETR  @$1,            $0              ;Write that number to RAM @ $1
                        INC   $1
                        SIF   $1,             0x30            ;Stop the loop after 16 iteration
                        JMPA  :TEST_NO_20A                    ;Go get an other random number
;Test 21, All other Registers beyond the main 3 used so far
:TEST_NO_21             SET   "0x15",         :%DBG_REG
                        %PRINT_DBG
                        CPY   :%REG_VAL_FF,   $3              ;Set $3 to 0xFF, testing writing to it
                        AND   $3,     $3,     $4              ;Test that $3 outputs to Bus A and B and testing writing to $4
                        AND   $4,     $4,     $5              ;Test that $4 outputs to Bus A and B and testing writing to $5
                        AND   $5,     $5,     $6              ;Test that $5 outputs to Bus A and B and testing writing to $6
                        AND   $6,     $6,     $7              ;Test that $6 outputs to Bus A and B and testing writing to $7
                        AND   $7,     $7,     $8              ;Test that $7 outputs to Bus A and B and testing writing to $8
                        AND   $8,     $8,     $9              ;Test that $8 outputs to Bus A and B and testing writing to $9
                        AND   $9,     $9,     $A              ;Test that $9 outputs to Bus A and B and testing writing to $A
                        AND   $A,     $A,     $B              ;Test that $A outputs to Bus A and B and testing writing to $B
                        AND   $B,     $B,     $0              ;Test that $B outputs to Bus A and B
                        SIF   $0,             0xFF            ;Check that $0 is == 0xFF
                        WJMP  :.HALT_ON_ERR
                        CPY   :%REG_VAL_00,   $3              ;Set $3 to 0x00, testing writing to it
                        OR    $3,     $3,     $4              ;Test that $3 outputs to Bus A or B and testing writing to $4
                        OR    $4,     $4,     $5              ;Test that $4 outputs to Bus A or B and testing writing to $5
                        OR    $5,     $5,     $6              ;Test that $5 outputs to Bus A or B and testing writing to $6
                        OR    $6,     $6,     $7              ;Test that $6 outputs to Bus A or B and testing writing to $7
                        OR    $7,     $7,     $8              ;Test that $7 outputs to Bus A or B and testing writing to $8
                        OR    $8,     $8,     $9              ;Test that $8 outputs to Bus A or B and testing writing to $9
                        OR    $9,     $9,     $A              ;Test that $9 outputs to Bus A or B and testing writing to $A
                        OR    $A,     $A,     $B              ;Test that $A outputs to Bus A or B and testing writing to $B
                        OR    $B,     $B,     $0              ;Test that $B outputs to Bus A or B
                        SIFZ  $0                              ;Check that $0 is == 0x00
                        WJMP  :.HALT_ON_ERR
;Test 22, All Read and Write to RAM
:TEST_NO_22             SET   "0x16",         :%DBG_REG
                        %PRINT_DBG
                        SET   0xFF,           $B              ;Change RAM page to [0xFF]
                        SETA  @0x00,          :%REG_VAL_01    ;write 0x01 to RAM @ 0x00[0xFF]
                        SETA  @0x01,          :%REG_VAL_80    ;write 0x80 to RAM @ 0x01[0xFF]
                        SETA  @0x02,          :%REG_VAL_FF    ;write 0xFF to RAM @ 0x02[0xFF]

                        SET   0x00,           $B              ;Change RAM page back to [0x00]
                        SET   0xFF,           $0
                        SETA  @0x00,          $0              ;write 0xFF to RAM @ 0x00[0x00]
                        SET   0x00,           $0
                        GETA  @0x00,          $0              ;read RAM @ 0x00[0x00] to $0
                        SIF   $0,             0xFF            ;Check that $0 is == 0xFF
                        WJMP  :.HALT_ON_ERR

                        SET   0x01,           $1
                        SET   0xFF,           $0
                        SETR  @$1,            $0              ;write 0xFF to RAM @ 0x01[0x00]
                        SET   0x00,           $0
                        GETR  @$1,            $0              ;read RAM @ 0x01[0x00] to $0
                        SIF   $0,             0xFF            ;Check that $0 is == 0xFF
                        WJMP  :.HALT_ON_ERR

                        INC   $1
                        SETV  @$1,            0xFF            ;write 0xFF to RAM @ 0x02[0x00]
                        SET   0x00,           $0
                        GETR  @$1,            $0              ;read RAM @ 0x02[0x00] to $0
                        SIF   $0,             0xFF            ;Check that $0 is == 0xFF
                        WJMP  :.HALT_ON_ERR

                        SET   0xFF,           $B              ;Change RAM page to 0xFF, check that writing at page 0x00 didn't affect page 0xFF
                        GETA  @0x00,          $0              ;read RAM @ 0x00[0xFF] to $0
                        SIF   $0,             0x01            ;Check that $0 is == 0x01
                        WJMP  :.HALT_ON_ERR
                        GETA  @0x01,          $0              ;read RAM @ 0x01[0xFF] to $0
                        SIF   $0,             0x80            ;Check that $0 is == 0x00
                        WJMP  :.HALT_ON_ERR
                        GETA  @0x02,          $0              ;read RAM @ 0x02[0xFF] to $0
                        SIF   $0,             0xFF            ;Check that $0 is == 0x00
                        WJMP  :.HALT_ON_ERR
                        SET   0x00,           $B              ;Change RAM page back to 0x00
;Test 23, WideJump Val and Reg
:TEST_NO_23             SET   "0x17",         :%DBG_REG
                        %PRINT_DBG
                        SET   :*TEST_WIDEJMP3, $1             ;Set $1 with the most significant bits of that Label
                        SET   :.TEST_WIDEJMP3, $2             ;Set $2 with the least significant bits of that Label
                        WJMPR $1,              $2             ;Test WideJumpReg to :TEST_WIDEJMP3
                        WJMP  :.HALT_ON_ERR
:TEST_WIDEJMP4          SEQ   $0,             :%REG_VAL_01    ;If the test worked, $0 should be set to 0x01
                        WJMP  :.HALT_ON_ERR
                        SET   :*TEST_WIDEJMP5, $1             ;Set $1 with the most significant bits of that Label
                        WJMPV $1,             :.TEST_WIDEJMP5 ;Test WideJumpVal to :TEST_WIDEJMP5
                        WJMP  :.HALT_ON_ERR
:TEST_WIDEJMP6          SIF   $0,             0x02            ;If the test worked, $0 should be set to 0x02
                        WJMP  :.HALT_ON_ERR

;Test 24, Random number, second pass, same seed
:TEST_NO_24             SET   "0x18",         :%DBG_REG
                        %PRINT_DBG
                        SET   0xFF,           $B              ;Prepare the seed for the RNG
                        SRNG                                  ;Set RngSeed
                        SET   0x00,           $B
                        SET   0x40,           $1 
                        NOP                                   ;Give the RNG some time to shift 
                        NOP
                        NOP
                        NOP
                        NOP
                        NOP
                        NOP
                        NOP
:TEST_NO_24_GEN         RND   $0                              ;Get a random number in $0
                        SETR  @$1,            $0              ;Write that number to RAM @ $1
                        INC   $1
                        SIF   $1,             0x50            ;Stop the loop after 16 iterations
                        JMPA  :TEST_NO_24_GEN                 ;Go get an other random number
                        
                        SET   0x20,           $1
                        SET   0x40,           $2 
:TEST_NO_24_CHECK       GETR  @$1,            $3              ;Read a number from RAM @ $1
                        GETR  @$2,            $4              ;Read a number from RAM @ $2  
                        INC   $1
                        INC   $2
                        SEQ   $3, $4                          ;Is the value from test 20 the same a this time
                        WJMP  :.HALT_ON_ERR
                        SIF   $2,             0x50            ;Stop the loop after 16 iterations
                        JMPA  :TEST_NO_24_CHECK               ;Go fetch an other number
;Test 25, Push and Pop
:TEST_NO_25             SET   "0x19",         :%DBG_REG
                        %PRINT_DBG
                        SET   0xFF,           $0              ;Test value
                        SET   0x10,           $1              ;Set for 16 iterations
:TEST_NO_25_PUSH        PUSH  $0                              ;Fill CPU stack with 0xFF
                        DEC   $1
                        IFNZ  $1,            :TEST_NO_25_PUSH ;IfNotZero, goto Push

                        SET   0x00,           $0
                        SET   0x0F,           $1              ;Set for 16 iterations
:TEST_NO_25_POP         POP   $0                              ;Retrive the values from CPU stack
                        SIF   $0,             0xFF            ;Check that $0 is == 0xFF
                        WJMP  :.HALT_ON_ERR
                        DSIZ  $1                              ;Decrement $1 until zero
                        JMPA  :TEST_NO_25_POP                 ;Go Pop an other value

                        POP   $0                              ;Poping beyond the max depth of the stack should return zero
                        SIFZ  $0                              ;Check that $0 is == 0x00
                        WJMP  :.HALT_ON_ERR
                        
:TEST_NO_25B            PUSH  :%REG_VAL_FF                    ;Place a test value in the stack
                        SET   0x55,           $1              ;Preprare more test values to follow
                        SET   0xAA,           $2              ;
                        SET   0x07,           $0              ;Set for 7 iterations
:TEST_NO_25B_PUSH       DSINZ $0                              ;Decrement $0 until zero
                        JMPA  :TEST_NO_25B_END                ;If End of Loop at Zero
                        PUSH  $1
                        PUSH  $2
                        JMPA  :TEST_NO_25B_PUSH               ;Loop back
:TEST_NO_25B_END        PUSH  :%REG_VAL_FF                    ;Place one last test value in the stack

                        POP   $0
                        SIF   $0,             0xFF            ;Check that last value is == 0xFF
                        WJMP  :.HALT_ON_ERR
                        SET   0x06,           $0              ;Set for 7 iterations (6+1)
:TEST_NO_25C_POP        POP   $2
                        POP   $1
                        SIF   $2,             0xAA            ;Check that 0xAA was poped out of the stack
                        WJMP  :.HALT_ON_ERR
                        SIF   $1,             0x55            ;Check that 0x55 was poped out of the stack
                        WJMP  :.HALT_ON_ERR
                        DSIZ  $0                              ;Decrement $0 until zero
                        JMPA  :TEST_NO_25C_POP                ;Loop back
                        POP   $0
                        SIF   $0,             0xFF            ;Check that the first 0xFF was poped out of the stack
                        WJMP  :.HALT_ON_ERR
                        
                        POP   $0
                        SIFZ  $0                              ;Check that the stack is empty
                        WJMP  :.HALT_ON_ERR
;Test 26, FlushStack and Reset
:TEST_NO_26             SET   "0x1A",         :%DBG_REG
%PRINT_DBG
                        PUSH  :%REG_VAL_FF                    ;Add back some values to the stack
                        PUSH  :%REG_VAL_01
                        PUSH  $1
                        PUSH  :%REG_VAL_80
                        PUSH  $2
                        PUSH  :%REG_VAL_FF
                        PUSH  :%REG_VAL_00
                        SET   0xFF,           $0
                        
                        FLUSH                                 ;In order to test the Flush instruction
                        SET   0x08,           $1              ;Set for 8 iterations
:TEST_NO_26A            POP   $0
                        SIFZ  $0                              ;Must be 0x00
                        WJMP  :.HALT_ON_ERR
                        DEC   $1
                        IFNZ  $1,             :TEST_NO_26A    ;IfNotZero, goto Push
                        
                        SET   0xFF,           $0              ;Set $0 for the next test
                        RST   $0                              ;Reset that register
                        SIFZ  $0                              ;Check that it is 0x00
                        WJMP  :.HALT_ON_ERR
;Test 27, Error handling with Raise and GoBack
:TEST_NO_27             SET   "0x1B",         :%DBG_REG
                        %PRINT_DBG

                        SERRH :*ERROR_HANDLING                ;Init the High bits of the Error handling routine
                        SERTL :.ERROR_HANDLING                ;Init the Low bits of the Error handling routine
                        SET   0x80,           $1  
                        RAISE                                 ;Trigger Error Handler
                        SIF   $0,             0xFF            ;That register should have been set by the error routine
                        WJMP  :.HALT_ON_ERR
                        POP   $0                              ;As well as the first entry in the CPU stack
                        SIF   $0,             0xFF
                        WJMP  :.HALT_ON_ERR
;Test 28, Interrupt handling with Interrupt and Return
:TEST_NO_28             SET   "0x1D",         :%DBG_REG
                        %PRINT_DBG

                        SINTH :*INTERRUPT_HANDLING            ;Init the High bits of the Interrupt handling routine
                        SINTL :.INTERRUPT_HANDLING            ;Init the Low bits of the Interrupt handling routine
                        SET   0x80,           $1              ;Signal it was a soft interrupt
                        INT                                   ;Trigger Interrupt
                        SIF   $0,             0xFF            ;That register should have been set by the interrupt routine
                        WJMP  :.HALT_ON_ERR
                        POP   $0                              ;As well as the first entry in the CPU stack
                        SIF   $0,             0xFF
                        WJMP  :.HALT_ON_ERR

;Test 29, Read and Write with CPU I/O (also test Hardware Interrupt, Halt and NoInt/OkInt)
:TEST_NO_29             SET   "0x1F",         :%DBG_REG
                        %PRINT_DBG

                        NOINT                                 ;Disable interrupts
                        SET   0x01, $1                        ;Set command to UserDisplay
                        SET   0x01, $2                        ;Set value to SetBusyIndicator
                        WIOB  $2                              ;Set the output value
                        WIOA  $1                              ;Send command plus value
                        SET   0xFF,           $4

                        HALT                                  ;Trigger a Debug Halt
                                                              ;At this time the user must clear the Halt condition
                                                              ;   after having triggered a hardware interrupt by pressing a key

                        SET   0x02,           $2              ;Set value to ClearBusyIndicator
                        WIOB  $2                              ;Set the output value
                        WIOA  $1                              ;Send command plus value                  
                        OKINT                                 ;Enable interrputs
                        
                        SET   0x01,           $4              ;Signal it was an interrupt from the idle loop
                        SET   0x00,           $2              ;Exit condition
:IDLE_LOOP              INC   $0
                        SIFNZ $2                              ;In this loop the user must again press a key to exit
                        JMPA  :IDLE_LOOP


; Error and Interrupt handling routine
                        WJMP  :*INTERRUPT_ERROR_END           ;Skip over the Interrupt and Error handling code
                        SET   "0xF0",         :%DBG_REG
                        %PRINT_DBG
                        WJMP  :.HALT_ON_ERR

:INTERRUPT_HANDLING     NOINT                                 ;Disable interrupts
                        SEQ   $1,             :%REG_VAL_80    ;If triggered by software
                        JMPA  :INTERRUPT_HARDWARE
                        SET   0xFF,           $0              ;Set values for the test
                        SET   0xFF,           $1
                        PUSH  $1
                        SET   "0x1E",         :%DBG_REG
                        %PRINT_DBG
                        JMPA  :INTERRUPT_HANDLING_END
                        
:INTERRUPT_HARDWARE     SEQ   $4,             :%REG_VAL_FF    ;If triggered around the Halt
                        JMPA  :INTERRUPT_LOOP
                        RIOA  $1                              ;There should be an I/O value awaiting
                        RIOB  $2
                        RIOD                                  ;Mark the I/O as Done
                        SIF   $1,             0x01            ;The commande should be 0x01 for KeyPress
                        WJMP  :.HALT_ON_ERR
                        SETA  @0xFF,          $2
                        JMPA  :INTERRUPT_HANDLING_END
                        
:INTERRUPT_LOOP         SET   "0x20",         :%DBG_REG       ;If the trigger was in the loop
                        %PRINT_DBG
                        SET   0x01,           $2              ;set the exit condition for the idle loop

:INTERRUPT_HANDLING_END OKINT                                 ;Enable interrputs
                        RET                                   ;Returns 

                        NOP                                   ;This should never run
                        SET   "0xF4",         :%DBG_REG
                        %PRINT_DBG
                        WJMP  :.HALT_ON_ERR
                        NOP

:ERROR_HANDLING         SIF   $1,             0x80            ;That register should have been set by the calling routine
                        WJMP  :.HALT_ON_ERR
                        SET   0xFF,           $0              ;Set values for the test
                        SET   0xFF,           $1
                        PUSH  $1
                        SET   "0x1C",         :%DBG_REG
                        %PRINT_DBG
                        GOBCK                                 ;Return to the calling code
                        SET   "0xF6",         :%DBG_REG
                        %PRINT_DBG
                        WJMP  :.HALT_ON_ERR
:INTERRUPT_ERROR_END
     
;End of test routine                        
                        NOP
                        HALT                                 ;SUCCESS !!!
                        NOP
                        WJMP  :*START_OVER
                        NOP
:HALT_ON_ERR            HALT                                 ;NOT HOORAY :(
                        NOP

