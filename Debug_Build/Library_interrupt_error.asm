;Library with exemples of code and structure

;Interrupt and Error Handling

;Interrupt handling routine uses 1 slot of CPU stack
;Error handling routine uses 1 slot of CPU stack


; =============================================================================
;Initialisation
; =============================================================================
                        SINTH :*INTERRUPT_HANDLING       ; Init the High bits of the Interrupt handling routine
                        SINTL :.INTERRUPT_HANDLING       ; Init the Low bits of the Interrupt handling routine
                        SERRH :*ERROR_HANDLING           ; Init the High bits of the Error handling routine
                        SERTL :.ERROR_HANDLING           ; Init the Low bits of the Error handling routine

                        SET   :*INTERRUPT_ERROR_END, $9  ; Set Addr for Jmp
                        WJMPV $9, :.INTERRUPT_ERROR_END  ; Skip over the Interrupt and Error handling code

; =============================================================================
;Interrupt handling routine
; =============================================================================
:INTERRUPT_HANDLING      NOINT                    ; Disable interrupts
                        
                        
                        PUSH  $9                 ; Push that value in the CPU stack
                        NOP
                        POP   $9                 ; Push that value in the CPU stack
                        
:INTERRUPT_HANDLING_END OKINT                    ; Enable interputs
                        RET                      ; Returns 

; =============================================================================
;Error handling routine
; =============================================================================
:ERROR_HANDLING         SGRT  $9, $C               ; Check that the error code is > 0
                        JMPA  :ERROR_HANDLING_DONE ; Skip to the end
                        PUSH  $8                   ; Push that value in the CPU stack
                        SET   0x02,  $8            ; Init $8
                        SGRT  $8,    $9            ; Check that the error code is > 2
                        JMPA  :ERROR_STACK_FULL    ; When error code equal 1
                        INC   $8
                        SGRT  $8,    $9            ; Check that the error code is > 3
                        JMPA  :ERROR_STACK_EMPTY   ; When error code equal 2
                        INC   $8
                        SGRT  $8,    $9            ; Check that the error code is > 4
                        JMPA  :ERROR_DIVIDE_ZERO   ; When error code equal 3
                        JMPA  :ERROR_UNHANDLED
                        
:ERROR_STACK_FULL
:ERROR_STACK_EMPTY  
:ERROR_DIVIDE_ZERO   
:ERROR_UNHANDLED        HALT                       ; Call the adult in the room
                                             

:ERROR_HANDLING_DONE    POP   $9                   ; Push that value in the CPU stack
                        GOBCK                      ; Return to the calling code


:INTERRUPT_ERROR_END    