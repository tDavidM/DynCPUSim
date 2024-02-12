;TEST Demo Loading from ASM File, shows a file that can test every circuits of the CPU

;Test 1, SET and SkipEqual as well as register $0 and $E tests 
:START_OVER             SET   "0xFF", $0              ;Test if $0 stores a value and if SET instruction outputs on bus C correctly 
                        SEQ   $0,     $E              ;Test that $0 outputs correctly on Bus A, that $E outputs 0xFF on Bus B, and SkipEqual works
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SEQ   $E,     $0              ;Test that $0 outputs correctly on Bus B, that $E outputs 0xFF on Bus A, and SkipEqual works
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 2, JumpAddr and more $0 and $E tests
                        SET   "0x01", $3              ;Keep track of where it halts, if it does
                        SET   "0x00", $0              ;
                        SEQ   $0,     $E              ;Test that SkipEqual works when not equal
                        JMPA  #:TEST_NO_3:            ;Test that JumpAddr works
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 3, register $C and more $0 tests
                        SET   "0x02", $3              ;Keep track of where it halts, if it does
:TEST_NO_3              SEQ   $C,     $0              ;Test that $C outputs 0x00 on Bus A
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SEQ   $0,     $C              ;Test that $C outputs 0x00 on Bus B
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 4, register $1 tests
                        SET   "0x03", $3              ;Keep track of where it halts, if it does
                        SET   "0xFF", $0              ;
                        SET   "0xFF", $1              ;Test if $1 stores a value
                        SEQ   $0,     $1              ;Test if $1 and $0 both output correctly on Bus A and B
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SEQ   $1,     $0              ;Test if $1 and $0 both output correctly on Bus A and B
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 5, AND and register $2 and more $1 tests
                        SET   "0x04", $3              ;Keep track of where it halts, if it does
                        AND   $0,     $1,     $2      ;Test if AND works and if $2 stores a value
                        SEQ   $1,     $2              ;Test if $2 outputs correctly on Bus B
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SEQ   $2,     $1              ;Test if $2 outputs correctly on Bus A
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   "0x05", $3              ;Keep track of where it halts, if it does
                        JMPA  #:TEST_NO_6:            ;An other test that JumpAddr works
;Test 6, SkipIfZero, IfNotZero, IfZero and more AND
:TEST_NO_6              SIFZ  $C                      ;Test SkipIfZero on $C
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        IFNZ  $C,     #:TEST_6_ERR_JMP: ;Test IfNotZero should not follow that jump
                        IFZ   $C,     #:TEST_6_OK_JMP:;Test IfZero should follow that jump
:TEST_6_ERR_JMP         WJMP  #:*HALT_ON_ERR:         ;If Error                       
:TEST_6_OK_JMP          AND   $C,     $E,     $2      ;Test AND with 0x00 & 0xFF
                        SET   "0x06", $3              ;Keep track of where it halts, if it does
                        SIFZ  $2                      ;Sould be 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        AND   $E,     $C,     $2      ;Test AND with 0xFF & 0x00
                        SIFZ  $2                      ;Sould be 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        IFNZ  $D,     #:TEST_6_OK_JMP2:;Test IfNotZero should follow that jump
                        WJMP  #:*HALT_ON_ERR:         ;If Error
:TEST_6_OK_JMP2         IFZ   $D,     #:TEST_6_ERR_JMP:;Test IfZero should not follow that jump
;Test 7, SkipIf and real cases for WideJump
                        SET   "0x07", $3              ;Keep track of where it halts, if it does
                        NOP
                        WJMP  #:*TEST_WIDEJMP1:       ;Should make a small jump foward
                        NOP
:TEST_WIDEJMP3          NOP                           ;This is actually part of Test 18, an other WideJump test
                        SET   0x01,   $0
                        WJMP  #:*TEST_WIDEJMP4:       ;  going back and foward over the limit of a relative jmp
:TEST_WIDEJMP5          SET   0x02,   $0
                        WJMP  #:*TEST_WIDEJMP6:     
                        NOP
                        NOP
                        WJMP  #:*HALT_ON_ERR:         ;If Error
:TEST_WIDEJMP2          SIF   $E,     0x00            ;Test SkipIf (no skip)
                        SIF   $E,     0xFF            ;Test SkipIf (skip)
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $C,     0x01            ;Test SkipIf (no skip)
                        SIF   $C,     0x00            ;Test SkipIf (skip)
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $D,     0x00            ;Test SkipIf (no skip)
                        SET   "0x08", $3              ;Keep track of where it halts, if it does
                        SIF   $D,     0x01            ;Test SkipIf (skip)
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $E,     0x01            ;Test SkipIf (no skip)
                        SIF   $F,     0x80            ;Test SkipIf (skip)
                        WJMP  #:*HALT_ON_ERR:         ;If Error                      
                        SIF   $F,     0x00            ;Test SkipIf (no skip)
                        SIF   $E,     0xFF            ;Test SkipIf (skip)
:TEST_WIDEJMP1          WJMP  #:*TEST_WIDEJMP2:       ;Should make a small jump backward
;Test 8, NOT, OR, XOR and IfZeroReg
                        SET   "0x09", $3              ;Keep track of where it halts, if it does
                        NOT   $E,     $0              ;Test seting $0 to !0xFF
                        NOT   $C,     $1              ;Test seting $1 to !0x00
                        AND   $0,     $C,     $2      ;Test AND with 0x00 & 0x00
                        SEQ   $0,     $2              ;Both should be 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $1,     0xFF            ;Should be 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        OR    $1,     $E,     $0      ;Test OR with 0xFF | 0xFF
                        OR    $0,     $C,     $1      ;Test OR with 0xFF | 0x00
                        SEQ   $0,     $1              ;
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        OR    $C,     $C,     $0      ;Test OR with 0x00 | 0x00
                        OR    $C,     $E,     $1      ;Test OR with 0x00 | 0xFF
                        SIF   $1,     0xFF            ;$1 should be == to 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   "0x0A", $3              ;Keep track of where it halts, if it does
                        SIF   $0,     0x00            ;$0 should be == to 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        XOR   $0,     $1,     $2      ;Test XOR with 0x00 ^ 0xFF
                        XOR   $1,     $2,     $0      ;Test XOR with 0xFF ^ 0xFF
                        XOR   $2,     $0,     $1      ;Test XOR with 0xFF ^ 0x00
                        XOR   $0,     $C,     $2      ;Test XOR with 0x00 ^ 0x00
                        SEQ   $0,     $2              ;After those 4 XOR, $0 and $2 should be 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 9, SkipIfNotZero and JumpReg (with more IfZeroReg)
                        SET   "0x0B", $3              ;Keep track of where it halts, if it does
                        SET   0x82,   $2              ;Set $2 for testing IfZeroReg, relative addr from where it's going to be used
                        IFZR  $0,     $2              ;Test IfZeroReg, $0 should be 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        WJMP  #:*HALT_ON_ERR:         ;
                        SIFNZ $1                      ;Test SkipIfNotZero with $1 that is != 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   0x7F,   $2              ;Set $2 for testing IfZeroReg, relative addr from where it's going to be used
                        SET   0x81,   $0              ;Set $0 for testing JumpReg, relative addr from where it's going to be used                
                        SIFNZ $C                      ;Test SkipIfNotZero with $C that is == 0x00
                        JMPR  $0                      ;Test JumpReg
:TEST_NO_9B             WJMP  #:*HALT_ON_ERR:         ;If Error
:TEST_NO_9C             IFZR  $1,     $2              ;Test IfZeroReg, $1 should not be 0x00
;Test 10, SkipGreater
                        SET   "0x0C", $3              ;Keep track of where it halts, if it does
                        SET   0x00,   $0
                        SET   0x01,   $1
                        SGRT  $0,     $1              ;Test SkipFGreater 0x00 > 0x01
                        SGRT  $1,     $0              ;Test SkipFGreater 0x01 > 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   0x55,   $0
                        SET   0xAA,   $1
                        SET   "0x0D", $3              ;Keep track of where it halts, if it does
                        SGRT  $0,     $1              ;Test SkipFGreater 0x55 > 0xAA
                        SGRT  $1,     $0              ;Test SkipFGreater 0xAA > 0x55
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   0x00,   $0
                        SET   0xFF,   $1
                        SGRT  $0,     $1              ;Test SkipFGreater 0x00 > 0xFF
                        SGRT  $1,     $0              ;Test SkipFGreater 0xFF > 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 11, Greatest 
                        SET   "0x0E", $3              ;Keep track of where it halts, if it does
                        GRT   $0,     $1,     $2      ;Test Greater with 0x00 and 0xFF
                        GRT   $2,     $D,     $1      ;Test Greater with 0xff and 0x01
                        SIF   $1,     0xFF            ;$1 should be == to 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   0x55,   $0
                        SET   0xAA,   $1
                        GRT   $0,     $1,     $2      ;Test Greater with 0x55 and 0xAA
                        GRT   $2,     $E,     $2      ;Test Greater with 0xAA and 0xFF
                        SIF   $2,     0xFF            ;$1 should be == to 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 12, Add and carry flag
                        SET   "0x0F", $3              ;Keep track of where it halts, if it does
                        ADD   $C,     $D,     $0      ;Test Add with 0x00 + 0x01
                        SIFNC                         ;Test SkipIfNoCarry
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SEQ   $0,     $D              ;Check that $0 is == 0x01
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        ADD   $0,     $D,     $0      ;Test Add with 0x01 + 0x01
                        SIF   $0,     0x02            ;Check that $0 is == 0x02
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   "0x10", $3              ;Keep track of where it halts, if it does
                        SET   0x55,   $0
                        SET   0xAA,   $1
                        ADD   $1,     $0,     $0      ;Test Add with 0xAA + 0x55
                        SIF   $0,     0xFF            ;Check that $0 is == 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        ADD   $0,     $D,     $0      ;Test Add with 0xFF + 0x01
                        SIFNC                         ;Test SkipIfNoCarry, sould not skip
                        SIFZ  $0                      ;Sould be 0x00, so skip
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   "0x11", $3              ;Keep track of where it halts, if it does
                        CFLG  $1                      ;Save Carry Flag to $1
                        RSTC                          ;Reset Carry Flag
                        SIF   $1,     0x01            ;Check that $1 is == 0x01
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        CFLG  $1                      ;Save Carry Flag to $1
                        SIFZ  $1                      ;Check that $1 is == 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        ADD   $C,     $0,     $0      ;Test Add with 0x00 + 0x00
                        SIFZ  $0                      ;Check that $0 is == 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 13, Substract, Increment, Decrement and DecSkipNotZero
                        SET   "0x12", $3              ;Keep track of where it halts, if it does
                        SUB   $F,     $D,     $0      ;Test SUB with 0x80 - 0x01
                        SET   0x0F,   $1
                        SUB   $0,     $1,     $0      ;Test SUB with 0x7F - 0x0F
                        SET   0x50,   $1
                        SUB   $0,     $1,     $0      ;Test SUB with 0x70 - 0x50
                        SET   0x1F,   $1
                        SUB   $0,     $1,     $0      ;Test SUB with 0x20 - 0x1F
                        SIF   $0,     0x01            ;Check that $0 is == 0x01
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   "0x13", $3              ;Keep track of where it halts, if it does
                        SETC                          ;Test SetCarryFlag
                        SIFNC                         ;Test SkipIfNoCarry, sould not skip
                        INC   $0                      ;Test Increment on $0
                        SIF   $0,     0x02            ;Check that $0 is == 0x02
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        DEC   $0                      ;Test Decrement on $0
                        SEQ   $0,     $D              ;Check that $0 is == 0x01
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   "0x14", $3              ;Keep track of where it halts, if it does
:TEST_NO_13_LOOP_INC    INC   $0                      ;Increment $0, looping until == 0x10
                        SIF   $0,     0x10            ;Quit when $0 == 0x10
                        JMPA  #:TEST_NO_13_LOOP_INC:  ;Loop to INC $0
                        SET   0xFF,   $0
:TEST_NO_13_LOOP_DEC    DEC   $0                      ;Decrement $0, looping until == 0xEF
                        SIF   $0,     0xEF            ;Quit when $0 == 0xEF
                        JMPA  #:TEST_NO_13_LOOP_DEC:  ;Loop to DEC $0
                        SET   0x10,   $0
                        SET   "0x15", $3              ;Keep track of where it halts, if it does
:TEST_NO_13_LOOP_DSIZ   DSIZ  $0                      ;Test DecSkipZero :-) my favorite instruction
                        JMPA  #:TEST_NO_13_LOOP_DSIZ: ;Loop to DEC $0
                        SIFZ  $0                      ;$0 Should be zero by now
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   0x10,   $0
:TEST_NO_13_LOOP_DSINZ  DSINZ $0                      ;Test DecSkipNotZero
                        JMPA  #:TEST_NO_14:           ;quit Loop when $0 == 0x00
                        JMPA  #:TEST_NO_13_LOOP_DSINZ:;Loop to DEC $0    
;Test 14, Basic Left and Right Shift
:TEST_NO_14             SIFZ  $0                      ;$0 Should be zero by now
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        CPY   $D,     $0              ;CPY is an alias for OR with 0x00
                        SET   "0x16", $3              ;Keep track of where it halts, if it does
                        LSHT  $0,     $0              ;Test LeftShift with 0x01
                        SIF   $0,     0x02            ;Check that $0 is == 0x02
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   0x55,   $0
                        LSHT  $0,     $0              ;Test LeftShift with 0x55
                        SIF   $0,     0xAA            ;Check that $0 is == 0xAA
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        RSHT  $0,     $0              ;Test RightShift with 0xAA
                        SIF   $0,     0x55            ;Check that $0 is == 0x55
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 15, Arithmetic Right Shift and that the Carry Flag gets the droped bits
                        SET   "0x17", $3              ;Keep track of where it halts, if it does
                        SIFNC                         ;Test SkipIfNoCarry, sould skip
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        RSTC                          ;Reset Carry Flag
                        CPY   $E,     $0              ;CPY is an alias for OR with 0x00
                        RSHT  $0,     $0              ;Test RightShift with 0xFF
                        SIF   $0,     0x7F            ;Check that $0 is == 0x7F
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        CFLG  $1                      ;Save Carry Flag to $1
                        SIF   $1,     0x01            ;Check that $1 is == 0x01
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        
                        SET   "0x18", $3              ;Keep track of where it halts, if it does
                        RSTC                          ;Reset Carry Flag
                        CPY   $E,     $0              ;CPY is an alias for OR with 0x00
                        LSHT  $0,     $0              ;Test LeftShift with 0xFF
                        SIF   $0,     0xFE            ;Check that $0 is == 0xFE
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        CFLG  $1                      ;Save Carry Flag to $1
                        SIF   $1,     0x01            ;Check that $1 is == 0x01
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        
                        SET   "0x19", $3              ;Keep track of where it halts, if it does
                        RSTC                          ;Reset Carry Flag
                        CPY   $E,     $0              ;CPY is an alias for OR with 0x00
                        RSHTA $0,     $0              ;Test RightArSht with 0xFF
                        SIF   $0,     0xFF            ;Check that $0 is == 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        CFLG  $1                      ;Save Carry Flag to $1
                        SIF   $1,     0x01            ;Check that $1 is == 0x01
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 16, Left and Right Rotate
                        SET   "0x1A", $3              ;Keep track of where it halts, if it does
                        RSTC                          ;Reset Carry Flag
                        SET   0xAA,   $0
                        LROT  $0,     $0              ;Test LeftRotate with 0xAA
                        SIFNC                         ;Test SkipIfNoCarry, sould skip
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $0,     0x55            ;Check that $0 is == 0x55
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   "0x1B", $3              ;Keep track of where it halts, if it does
                        RROT  $0,     $0              ;Test LeftRotate with 0x55
                        SIF   $0,     0xAA            ;Check that $0 is == 0xAA
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   0xFF,   $0
                        LROT  $0,     $0              ;Test LeftRotate with 0xFF
                        RROT  $0,     $0              ;Test LeftRotate with 0xFF
                        SIF   $0,     0xFF            ;Check that $0 is == 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 17, Left and Right Carry Rotate
                        SET   "0x1C", $3              ;Keep track of where it halts, if it does
                        RSTC                          ;Reset Carry Flag
                        SET   0xAA,   $0
                        LROTC $0,     $0              ;Test LeftCarryRotate with 0xAA
                        CFLG  $1                      ;Save Carry Flag to $1
                        SIF   $1,     0x01            ;Check that $1 is == 0x01
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $0,     0x54            ;Check that $0 is == 0x54
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   "0x1D", $3              ;Keep track of where it halts, if it does
                        RSTC                          ;Reset Carry Flag
                        RROTC $0,     $0              ;Test RightCarryRotate with 0x54
                        CFLG  $1                      ;Save Carry Flag to $1
                        SIF   $1,     0x00            ;Check that $1 is == 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $0,     0x2A            ;Check that $0 is == 0x2A
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   "0x1E", $3              ;Keep track of where it halts, if it does
                        SETC                          ;Set Carry Flag
                        SET   0xFF,   $0
                        LROTC $0,     $0              ;Test LeftCarryRotate with 0xFF
                        LROTC $0,     $0              ;Test LeftCarryRotate with 0xFF
                        RROTC $0,     $0              ;Test RightCarryRotate with 0xFF
                        RROTC $0,     $0              ;Test RightCarryRotate with 0xFF
                        SIF   $0,     0xFF            ;Check that $0 is == 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 18, All Read and Write to RAM
                        SET   "0x1F", $3              ;Keep track of where it halts, if it does
                        SET   0xFF,   $B              ;Change RAM page to 0xFF
                        SETA  @0x00,  $C              ;write 0x00 to RAM @ 0x00[0xFF]
                        SETA  @0x01,  $C              ;write 0x00 to RAM @ 0x01[0xFF]
                        SETA  @0x02,  $C              ;write 0x00 to RAM @ 0x02[0xFF]
                        
                        SET   0x00,   $B              ;Change RAM page back to 0x00
                        SETA  @0x00,  $0              ;write 0xFF to RAM @ 0x00
                        GETA  @0x00,  $0              ;read RAM @ 0x00 to $0
                        SIF   $0,     0xFF            ;Check that $0 is == 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   "0x20", $3              ;Keep track of where it halts, if it does
                        INC   $1
                        SETR  @$1,    $0              ;write 0xFF to RAM @ 0x01
                        GETR  @$1,    $0              ;read RAM @ 0x01 to $0
                        SIF   $0,     0xFF            ;Check that $0 is == 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        INC   $1
                        SETV  @$1,    0xFF            ;write 0xFF to RAM @ 0x02
                        GETR  @$1,    $0              ;read RAM @ 0x02 to $0
                        SIF   $0,     0xFF            ;Check that $0 is == 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        
                        SET   "0x21", $3              ;Keep track of where it halts, if it does
                        SET   0xFF,   $B              ;Change RAM page to 0xFF, check that writing at page 0x00 didn't affect page 0xFF
                        GETA  @0x00,  $0              ;read RAM @ 0x00[0xFF] to $0
                        SIFZ  $0                      ;Check that $0 is == 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        GETA  @0x01,  $0              ;read RAM @ 0x01[0xFF] to $0
                        SIFZ  $0                      ;Check that $0 is == 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        GETA  @0x02,  $0              ;read RAM @ 0x02[0xFF] to $0
                        SIFZ  $0                      ;Check that $0 is == 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   0x00,   $B              ;Change RAM page back to 0x00
;Test 19, WideJump Val and Reg
                        SET   "0x22", $3              ;Keep track of where it halts, if it does
                        SET   ::TEST_WIDEJMP3:,   $1  ;Set $1 with the most significant bits of that Label
                        SET   :*TEST_WIDEJMP3:,   $2  ;Set $2 with the least significant bits of that Label
                        WJMPR $1,     $2              ;Test WideJumpReg to :TEST_WIDEJMP3
:TEST_WIDEJMP4          SEQ   $0,     $D              ;If the test worked, $0 should be set to 0x01
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SET   ::TEST_WIDEJMP5:,   $1  ;Set $1 with the most significant bits of that Label
                        WJMPV $1,     :*TEST_WIDEJMP5:;Test WideJumpVal to :TEST_WIDEJMP5
:TEST_WIDEJMP6          SIF   $0,     0x02            ;If the test worked, $0 should be set to 0x02
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 20, All other Registers beyond the main 3 used so far
                        CPY   $E,     $3              ;Set $3 to 0xFF, testing writing to it
                        AND   $3,     $3,     $4      ;Test that $3 outputs to Bus A and B and testing writing to $4
                        AND   $4,     $4,     $5      ;Test that $4 outputs to Bus A and B and testing writing to $5
                        AND   $5,     $5,     $6      ;Test that $5 outputs to Bus A and B and testing writing to $6
                        AND   $6,     $6,     $7      ;Test that $6 outputs to Bus A and B and testing writing to $7
                        AND   $7,     $7,     $8      ;Test that $7 outputs to Bus A and B and testing writing to $8
                        AND   $8,     $8,     $9      ;Test that $8 outputs to Bus A and B and testing writing to $9
                        AND   $9,     $9,     $A      ;Test that $9 outputs to Bus A and B and testing writing to $A
                        AND   $A,     $A,     $B      ;Test that $A outputs to Bus A and B and testing writing to $B
                        AND   $B,     $B,     $0      ;Test that $B outputs to Bus A and B
                        SIF   $0,     0xFF            ;Check that $0 is == 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        CPY   $C,     $3              ;Set $3 to 0x00, testing writing to it
                        OR    $3,     $3,     $4      ;Test that $3 outputs to Bus A or B and testing writing to $4
                        OR    $4,     $4,     $5      ;Test that $4 outputs to Bus A or B and testing writing to $5
                        OR    $5,     $5,     $6      ;Test that $5 outputs to Bus A or B and testing writing to $6
                        OR    $6,     $6,     $7      ;Test that $6 outputs to Bus A or B and testing writing to $7
                        OR    $7,     $7,     $8      ;Test that $7 outputs to Bus A or B and testing writing to $8
                        OR    $8,     $8,     $9      ;Test that $8 outputs to Bus A or B and testing writing to $9
                        OR    $9,     $9,     $A      ;Test that $9 outputs to Bus A or B and testing writing to $A
                        OR    $A,     $A,     $B      ;Test that $A outputs to Bus A or B and testing writing to $B
                        OR    $B,     $B,     $0      ;Test that $B outputs to Bus A or B
                        SIFZ  $0,                     ;Check that $0 is == 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
;Test 21, Random number
                        SET   "0x24", $3              ;Keep track of where it halts, if it does
                        SET   0x10,   $1              ;
:TEST_NO_21             RND   $0                      ;Get a random number in $0
                        SETR  @$1,    $0              ;Write that number to RAM @ $1
                        INC   $1
                        SIF   $0,     0x1F            ;Stop the loop after 16 iteration
                        JMPA  #:TEST_NO_21:           ;Go get an other random number
;Test 22, Push and Pop
                        SET   "0x25", $3              ;Keep track of where it halts, if it does
                        SET   0xFF,   $0              ;
                        SET   0x0F,   $1              ;Set for 16 iterations
:TEST_NO_22_PUSH        PUSH  $0
                        DEC   $1
                        IFNZ  $1,     :TEST_NO_22_PUSH:;IfNotZero, goto Push
                        SET   "0x26", $3              ;Keep track of where it halts, if it does
                        SET   0xAA,   $0              ;Filler
                        SET   0x0F,   $1              ;Set for 16 iterations
:TEST_NO_22_POP         POP   $0
                        SIF   $0,     0xFF            ;Check that $0 is == 0xFF
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        DSINZ $1                      ;Decrement $1 until zero
                        JMPA  #:TEST_NO_22_END:       ;If End of Loop at Zero
                        JMPA  #:TEST_NO_22_POP:       ;Go Pop an other value
:TEST_NO_22_END         SET   "0x27", $3              ;Keep track of where it halts, if it does
                        POP   $0                      ;Poping beyond the max depth of the stack should return zero
                        SIFZ  $0                      ;Check that $0 is == 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        
                        PUSH  $E
                        SET   0x55,   $1              ;
                        SET   0xAA,   $2              ;
                        SET   0x07,   $0              ;Set for 7 iterations
:TEST_NO_22B_PUSH       DSINZ $0                      ;Decrement $0 until zero
                        JMPA  #:TEST_NO_22B_END:      ;If End of Loop at Zero
                        PUSH  $1
                        PUSH  $2
                        JMPA  #:TEST_NO_22B_PUSH:     ;Loop back
:TEST_NO_22B_END        PUSH  $E
                        SET   "0x28", $3              ;Keep track of where it halts, if it does
                        POP   $0
                        SET   0x07,   $0              ;Set for 7 iterations
:TEST_NO_22C_POP        DSINZ $0                      ;Decrement $0 until zero
                        JMPA  #:TEST_NO_22C_END:      ;If End of Loop at Zero
                        POP   $2
                        POP   $1
                        SIF   $2,     0xAA            ;Check that 0xAA was poped out of the stack
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        SIF   $1,     0x55            ;Check that 0x55 was poped out of the stack
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        JMPA  #:TEST_NO_22C_POP:      ;Loop back
:TEST_NO_22C_END        SET   "0x29", $3              ;Keep track of where it halts, if it does
                        POP   $0
                        SIF   $0,     0xFF            ;Check that 0xFF was poped out of the stack
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        POP   $0
                        SIFZ  $0                      ;Check that $0 is == 0x00
                        WJMP  #:*HALT_ON_ERR:         ;If Error
                        
                        SET   "0x30", $3              ;Keep track of where it halts, if it does
                        WJMP  #:*START_OVER:
:HALT_ON_ERR            HALT

 

 



 



