;Library with exemples of code and structure

;Multiplication

;Multiply $0 * $1 -> $2  (uses $3 and $4)
;Inline, Unsigned, No check
;[MULT_INL_U_NC

;Multiply $0 * $1 -> $2  , return $3$4 (uses $5 and $6)
;Jump, Unsigned, No check
;:MULT_JMP_U_NC

;Multiply $0 * $1 -> $2  , return Stack HL (uses $3 and $4)
;Jump, Unsigned, No check
;:MULT_STK_U_NC

;Multiply $0 * $1 -> $2  (uses $3, $4 ) $5 == 0x01 if Overflow
;Inline, Unsigned, Carry check
;[MULT_INL_U_CC

;Multiply $0 * $1 -> $2  , return $3$4 (uses $5, $6 ) $7 == 0x01 if Overflow
;Jump, Unsigned, Carry check
;:MULT_JMP_U_CC

;Multiply $0 * $1 -> $2  , return Stack HL (uses $3, $4 ) $5 == 0x01 if Overflow
;Jump, Unsigned, No check
;:MULT_STK_U_CC



;Multiply $0 * $1 -> $2  (uses $3 and $4)
;Inline, Unsigned, No check
[MULT_INL_U_NC
                        SET   0x00,   $2              ; Init accumulator
                        SET   0x07,   $4              ; Counter for 8 iterations
:AND_MULT_INL_U_NC      AND   $0,     $D,     $3      ; Parity mask on $0
                        SIF   $3,     0x01            ; Check for parity
                        ADD   $1,     $2,     $2      ; Add if $0 is odd
                        RSHT  $0,     $0              
                        LSHT  $1,     $1              
                        DSIN  $4                      ; Loop counter
                        JMPA  :AND_MULT_INL_U_NC      ; Back to parity check
]

;Multiply $0 * $1 -> $2  , return $3$4 (uses $5 and $6)
;Jump, Unsigned, No check
:MULT_JMP_U_NC          SET   0x00,   $2              ; Init accumulator
                        SET   0x07,   $6              ; Counter for 8 iterations
:AND_MULT_JMP_U_NC      AND   $0,     $D,     $5      ; Parity mask on $0
                        SIF   $5,     0x01            ; Check for parity
                        ADD   $1,     $2,     $2      ; Add if $0 is odd
                        RSHT  $0,     $0              
                        LSHT  $1,     $1              
                        DSIN  $6                      ; Loop counter
                        JMPA  :AND_MULT_JMP_U_NC      ; Back to parity check
                        WJMPR $3,     $4
            
            
;Multiply $0 * $1 -> $2  , return Stack HL (uses $3 and $4)
;Jump, Unsigned, No check
:MULT_STK_U_NC          SET   0x00,   $2              ; Init accumulator
                        SET   0x07,   $4              ; Counter for 8 iterations
:AND_MULT_JMP_U_NC      AND   $0,     $D,     $3      ; Parity mask on $0
                        SIF   $3,     0x01            ; Check for parity
                        ADD   $1,     $2,     $2      ; Add if $0 is odd
                        RSHT  $0,     $0              
                        LSHT  $1,     $1              
                        DSIN  $4                      ; Loop counter
                        JMPA  :AND_MULT_JMP_U_NC      ; Back to parity check
                        POP   $4
                        POP   $3
                        WJMPR $3,     $4


;Multiply $0 * $1 -> $2  (uses $3, $4 ) $5 == 0x01 if Overflow
;Inline, Unsigned, Carry check
[MULT_INL_U_CC
                        SET   0x00,   $2              ; Init accumulator
                        SET   0x07,   $4              ; Counter for 8 iterations
                        SET   0x00,   $5              ; Init Overflow Flag
                        RSTC                          ; Reset Carry Flag
:AND_MULT_INL_U_CC      AND   $0,     $D,     $3      ; Parity mask on $0
                        SIF   $3,     0x01            ; Check for parity
                        ADD   $1,     $2,     $2      ; Add if $0 is odd
                        SIFNC                         ;
                        SET   0x01,   $5              ; Flags an Overflow
                        RSHT  $0,     $0              
                        LSHT  $1,     $1   
                        SIFNC
                        SET   0x01,   $5              ; Flags an Overflow
                        DSIN  $4                      ; Loop counter
                        JMPA  :AND_MULT_INL_U_CC      ; Back to parity check
]

;Multiply $0 * $1 -> $2  , return $3$4 (uses $5, $6 ) $7 == 0x01 if Overflow
;Jump, Unsigned, Carry check
:MULT_JMP_U_CC          SET   0x07,   $6              ; Counter for 8 iterations
                        SET   0x00,   $2              ; Init accumulator
                        RSTC                          ; Reset Carry Flag
:AND_MULT_JMP_U_CC      AND   $0,     $D,     $5      ; Parity mask on $0
                        SIF   $5,     0x01            ; Check for parity
                        ADD   $1,     $2,     $2      ; Add if $0 is odd
                        SIFNC
                        SET   0x01,   $5              ; Flags an Overflow
                        RSHT  $0,     $0              
                        LSHT  $1,     $1              
                        SIFNC
                        SET   0x01,   $5              ; Flags an Overflow
                        DSIN  $6                      ; Loop counter
                        JMPA  :AND_MULT_JMP_U_CC      ; Back to parity check
                        WJMPR $3,     $4              ; Return to caller
                        

;Multiply $0 * $1 -> $2  , return Stack HL (uses $3, $4 ) $5 == 0x01 if Overflow
;Jump, Unsigned, No check
:MULT_STK_U_CC          SET   0x07,   $4              ; Counter for 8 iterations
                        SET   0x00,   $2              ; Init accumulator
                        RSTC                          ; Reset Carry Flag
:AND_MULT_JMP_U_NC      AND   $0,     $D,     $3      ; Parity mask on $0
                        SIF   $3,     0x01            ; Check for parity
                        ADD   $1,     $2,     $2      ; Add if $0 is odd
                        SIFNC
                        SET   0x01,   $5              ; Flags an Overflow
                        RSHT  $0,     $0              
                        LSHT  $1,     $1            
                        SIFNC
                        SET   0x01,   $5              ; Flags an Overflow
                        DSIN  $4                      ; Loop counter
                        JMPA  :AND_MULT_JMP_U_NC      ; Back to parity check
                        POP   $4                      ; Inverse order of PUSH $3, PUSH $4
                        POP   $3
                        WJMPR $3,     $4              ; Return to caller
                        
