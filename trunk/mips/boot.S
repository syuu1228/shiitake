#include <mips/asm.h>
	
      .text
      .globl _start
      .ent   _start	
_start:	
      .set noreorder
      /* Disable interrupt */
      mtc0	$zero, COP0_STATUS
      /* Setup sp and gp */
      la    $gp, _gp
      la    $sp, _sp
      /* Clear bss */
      la    $t0, _fbss	/* First address */
      la    $t1, _end	/* Last  address */
      addu  $t1, 3
      li    $t2, ~3
      and   $t1, $t2
1:
      sw    $zero, 0($t0)
      bne   $t0, $t1, 1b
      addiu $t0, 4
      /* Get ready to jump to main */
      move  $s0, $ra
      la    $t0, arch_init
      /* Jump to main */
      jal   $t0
      nop
      jal   main
      nop
die:
      j	    die
      nop
      .set reorder
      .end   _start
