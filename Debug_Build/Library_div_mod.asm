;Library with exemples of code and structure

;Division and Modulo

;Divide $0 / $1 -> $2 reminder $3 (uses $4, $5, $6, $7, $8 )
;Inline, Unsigned
;[DIVMOD_INL_U

;Divide $0 / $1 -> $2 reminder $3 , return $4$5 (uses $6, $7, $8, $9, $A )
;Jump, Unsigned
;:DIVMOD_JMP_U

;Divide $0 / $1 -> $2 reminder $3 , return Stack HL (uses $4, $5, $6, $7, $8 )
;Jump, Unsigned
;:DIVMOD_STK_U



;Divide by zero handling routine
;TBD !!!
:DIVMOD_DIVZERO_ERR     SET   0xFF,   $2              ; Init quotient
                        SET   0xFF,   $3              ; Init remainder


;Divide $0 / $1 -> $2 reminder $3 (uses $4, $5, $6, $7, $8 )
;Inline, Unsigned
[DIVMOD_INL_U
                        SIFNZ $1                      ; Check for 0 as divisor
                        NOP                           ; Divide by 0 handling, TBD!
                        SET   0x00,   $2              ; Init quotient
                        SET   0x00,   $3              ; Init remainder
                        SET   0x06,   $4              ; Counter i for 7 iterations (n bit-1)
                        SET   0b10000000, $5          ; BitMask for (i)th bit  , could use $F to set
                        SET   0b11111110, $6          ; BitMask for !(0)th bit
:LSHT_DIVMOD_INL_U      LSHT  $3,     $3              ; Left Shift remainder
                        AND   $0,     $5,     $7      ; Take (i)th bit from numerator
                        
                        CPY   $4,     $8              ; Copy current i to loop on
:RSHT_DIVMOD_INL_U      RSHT  $7,     $7              ; Bring (i)th bit down to (0)bit
                        DSIN  $8                      ; Loop until zero
                        JMPA  :RSHT_DIVMOD_INL_U
                        
;                       NOT   $D,     $6              ; Idea to reduce usage of Registers by 1, not needing $8
                        AND   $3,     $6,     $3      ; Remove the least-significant bit from remainder
                        AND   $3,     $7,     $3      ; Set the remainder least-significant bit with the one taken from numerator
                        SGRT  $1,     $3              ; Skip unless remainder >= divisor
                        JMPA  :DSIN_DIVMOD_INL_U
                        
                        SUB   $3,     $1,     $3      ; Substract divisor from remainder
                        AND   $2,     $5,     $2      ; Set (i)th bit from quotient to 1
                        
                        RSHT  $5,     $5              ; Right Shift BitMask for (i)th bit                              
:DSIN_DIVMOD_INL_U      DSIN  $4                      ; Loop i until zero
                        JMPA  :LSHT_DIVMOD_INL_U      ;
]

;Divide $0 / $1 -> $2 reminder $3 , return $4$5 (uses $6, $7, $8, $9, $A )
;Jump, Unsigned
:DIVMOD_JMP_U           SIFNZ $1                      ; Check for 0 as divisor
                        NOP                           ; Divide by 0 handling, TBD!
                        SET   0x00,   $2              ; Init quotient
                        SET   0x00,   $3              ; Init remainder
                        SET   0x06,   $6              ; Counter i for 7 iterations (n bit-1)
                        SET   0b10000000, $7          ; BitMask for (i)th bit  , could use $F to set
                        SET   0b11111110, $8          ; BitMask for !(0)th bit , could use !$D to set
:LSHT_DIVMOD_JMP_U      LSHT  $3,     $3              ; Left Shift remainder
                        AND   $0,     $7,     $9      ; Take (i)th bit from numerator
                        
                        CPY   $6,     $A              ; Copy current i to loop on
:RSHT_DIVMOD_JMP_U      RSHT  $9,     $9              ; Bring (i)th bit down to (0)bit
                        DSIN  $A                      ; Loop until zero
                        JMPA  :RSHT_DIVMOD_JMP_U
                        
;                       NOT   $D,     $8              ; Idea to reduce usage of Registers by 1, not needing $A
                        AND   $3,     $8,     $3      ; Remove the least-significant bit from remainder
                        AND   $3,     $9,     $3      ; Set the remainder least-significant bit with the one taken from numerator
                        SGRT  $1,     $3              ; Skip unless remainder >= divisor
                        JMPA  :DSIN_DIVMOD_JMP_U
                        
                        SUB   $3,     $1,     $3      ; Substract divisor from remainder
                        AND   $2,     $7,     $2      ; Set (i)th bit from quotient to 1
                        
                        RSHT  $7,     $7              ; Right Shift BitMask for (i)th bit                              
:DSIN_DIVMOD_JMP_U      DSIN  $6                      ; Loop i until zero
                        JMPA  :LSHT_DIVMOD_JMP_U      ;
                        WJMPR $4,     $5


;Divide $0 / $1 -> $2 reminder $3 , return Stack HL (uses $4, $5, $6, $7, $8 )
;Jump, Unsigned
:DIVMOD_STK_U           SIFNZ $1                      ; Check for 0 as divisor
                        NOP                           ; Divide by 0 handling, TBD!
                        SET   0x00,   $2              ; Init quotient
                        SET   0x00,   $3              ; Init remainder
                        SET   0x06,   $4              ; Counter i for 7 iterations (n bit-1)
                        SET   0b10000000, $5          ; BitMask for (i)th bit  , could use $F to set
                        SET   0b11111110, $6          ; BitMask for !(0)th bit
:LSHT_DIVMOD_STK_U      LSHT  $3,     $3              ; Left Shift remainder
                        AND   $0,     $5,     $7      ; Take (i)th bit from numerator
                        
                        CPY   $4,     $8              ; Copy current i to loop on
:RSHT_DIVMOD_STK_U      RSHT  $7,     $7              ; Bring (i)th bit down to (0)bit
                        DSIN  $8                      ; Loop until zero
                        JMPA  :RSHT_DIVMOD_STK_U
                        
;                       NOT   $D,     $6              ; Idea to reduce usage of Registers by 1, not needing $8
                        AND   $3,     $6,     $3      ; Remove the least-significant bit from remainder
                        AND   $3,     $7,     $3      ; Set the remainder least-significant bit with the one taken from numerator
                        SGRT  $1,     $3              ; Skip unless remainder >= divisor
                        JMPA  :DSIN_DIVMOD_STK_U
                        
                        SUB   $3,     $1,     $3      ; Substract divisor from remainder
                        AND   $2,     $5,     $2      ; Set (i)th bit from quotient to 1
                        
                        RSHT  $5,     $5              ; Right Shift BitMask for (i)th bit                              
:DSIN_DIVMOD_STK_U      DSIN  $4                      ; Loop i until zero
                        JMPA  :LSHT_DIVMOD_STK_U      ;
                        POP   $5
                        POP   $4
                        WJMPR $4,     $5

