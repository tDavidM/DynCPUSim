;Library with exemples of code and structure

;Stack in RAM

;Push $9 (uses 1 slot of CPU stack)
;Inline, ErrCD 0x01
;[PUSH_INLN_RAM

;Pop $9 (uses 1 slot of CPU stack)
;Inline, ErrCD 0x02
;[POP_INLN_RAM

;Push $9 (uses 1 slot of CPU stack) return using $7,$8 (H,L)
;Jump, ErrCD 0x01
;:PUSH_JMP_RAM

;Pop $9 (uses 1 slot of CPU stack) return using $7,$8 (H,L)
;Jump, ErrCD 0x02
;:POP_JMP_RAM

;Push $9 (uses 1 slot of CPU stack) uses $6,$7,$8
;Jump macro, ErrCD 0x01
;[PUSH_JMP_RAM

;Pop $9 (uses 1 slot of CPU stack) uses $6,$7,$8
;Jump macro, ErrCD 0x02
;[POP_JMP_RAM


; =============================================================================
;Initialisation
; =============================================================================
                        SET   0xFF,   $A         ; Init the stack pointer


; =============================================================================
;Stack full error handling routine
; =============================================================================
[STACK_FULL_ERR         
                        SET   0x01,   $9         ; Put stack full error code in $9
                        RAISE                    ; Raise the error code
]

; =============================================================================
;Stack full error handling routine
; =============================================================================
[STACK_EMPTY_ERR         
                        SET   0x02,   $9         ; Put stack full error code in $9
                        RAISE                    ; Raise the error code
]

; =============================================================================
;Push $9 (uses 1 slot of CPU stack)
;Inline macro, ErrCD 0x01
; =============================================================================
[PUSH_INLN_RAM
                        PUSH  $B                 ; Stash current RAM page
                        SET   0x00, $B           ; Switch to RAM page zero
                        SETR  @$A,  $9           ; Write user value at stack pointer addr
                        SEQ   $A,   $F           ; Check if stack pointer at limit 0x80
                        JMPA  :STACK_OK_PUSH     ; When ok
                        %STACK_FULL_ERR          ; Call the error handling macro
                        JMPA  :STACK_DONE_PUSH   ; Skip the decrement
:STACK_OK_PUSH          DEC   $A                 ; Decrement stack pointer
:STACK_DONE_PUSH        POP   $B                 ; Reset RAM page
]

; =============================================================================
;Pop $9 (uses 1 slot of CPU stack)
;Inline macro, ErrCD 0x02
; =============================================================================
[POP_INLN_RAM
                        PUSH  $B                 ; Stash current RAM page
                        SET   0x00, $B           ; Switch to RAM page zero
                        SETR  $A,   $9           ; Write user value at stack pointer addr
                        SEQ   $A,   $C           ; Check if stack pointer at starting value 0xFF
                        JMPA  :STACK_OK_POP      ; When ok
                        %STACK_EMPTY_ERR         ; Call the error handling macro
                        JMPA  :STACK_DONE_POP    ; Skip the decrement
:STACK_OK_POP           INC   $A                 ; Increment stack pointer
                        GETR  @$A,    $9         ; Read value at stack pointer
:STACK_DONE_POP         POP   $B                 ; Reset RAM page
]

; =============================================================================
;Push $9 (uses 1 slot of CPU stack) return using $7,$8 (H,L)
;Jump, ErrCD 0x01
; =============================================================================
:PUSH_JMP_RAM
                        %POP_INLN_RAM            ;
                        WJMPR $7, $8             ; Return to caller

; =============================================================================
;Pop $9 (uses 1 slot of CPU stack) return using $7,$8 (H,L)
;Jump, ErrCD 0x02
; =============================================================================
:POP_JMP_RAM
                        %POP_INLN_RAM            ;
                        WJMPR $7, $8             ; Return to caller

; =============================================================================
;Push $9 (uses 1 slot of CPU stack) uses $6,$7,$8
;Jump macro, ErrCD 0x01
; =============================================================================
[PUSH_JMP_RAM
                        SET   ::PUSH_JMP_RAM_RETURN, $7 ; Set Return H value
                        SET   :*PUSH_JMP_RAM_RETURN, $8 ; Set Return L value
                        SET   ::PUSH_JMP_RAM, $6        ; Set target L value
                        WJMPV $6, :*PUSH_JMP_RAM        ;
:PUSH_JMP_RAM_RETURN
]

; =============================================================================
;Pop $9 (uses 1 slot of CPU stack) uses $6,$7,$8
;Jump macro, ErrCD 0x02
; =============================================================================
[POP_JMP_RAM
                        SET   ::POP_JMP_RAM_RETURN, $7 ; Set Return H value
                        SET   :*POP_JMP_RAM_RETURN, $8 ; Set Return L value
                        SET   ::POP_JMP_RAM, $6        ; Set target L value
                        WJMPV $6, :*POP_JMP_RAM        ; 
:POP_JMP_RAM_RETURN
]

