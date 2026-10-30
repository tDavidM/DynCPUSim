;Library with exemples of code and structure

;Generic first include for a program

#INCLUDE "Library_interrupt_error.asm"
#INCLUDE "Library_stack.asm"

#INCLUDE "Library_mult.asm"
#INCLUDE "Library_div_mod.asm"

#DEFINE RNG_SEED_VAL 0x2A ;

                        SET   :%RNG_SEED_VAL, :%RNG_SEED_REG  ; Prepare a seed for the RNG 
                        SRNG                                  ; Set RngSeed
                        SET   0x00, :%RAM_PAGE                ; Init the RAM page
   
;Define for the registers outputing a fixed value   
#DEFINE REG_FIXVAL_00 $C
#DEFINE REG_FIXVAL_01 $D
#DEFINE REG_FIXVAL_FF $E
#DEFINE REG_FIXVAL_80 $F

;Define for the register that holds the RAM page
#DEFINE RAM_PAGE $B

;Define for the register that holds the RNG Seed
#DEFINE RNG_SEED_REG $B
