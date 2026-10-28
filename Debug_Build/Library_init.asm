;Library with exemples of code and structure

;Generic first include for a project

#INCLUDE "Library_interrupt_error.asm"
#INCLUDE "Library_stack.asm"

#DEFINE RAM_PAGE $B

                        SET   0x00, :%RAM_PAGE   ; Init the RAM page
                        
#DEFINE REG_FIXVAL_00 $C
#DEFINE REG_FIXVAL_01 $D
#DEFINE REG_FIXVAL_FF $E
#DEFINE REG_FIXVAL_80 $F
