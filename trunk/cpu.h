#ifndef CPU_H
#define CPU_H

#include <types.h>

struct eflags {
	uint8_t carry_flag:1;
	uint8_t __unused1:1;
	uint8_t parity_flag:1;
	uint8_t __unused2:1;
	uint8_t auxiliary_carry_flag:1;
	uint8_t __unused3:1;
	uint8_t zero_flag:1;
	uint8_t sign_flag:1;
	uint8_t trap_flag:1;
	uint8_t interrupt_enable_flag:1;
	uint8_t direction_flag:1;
	uint8_t overflow_flag:1;
	uint8_t io_privilege_level:2;
	uint8_t nested_task:1;
	uint8_t __unused4:1;
	uint8_t resume_flag:1;
	uint8_t virtual8086_mode:1;
	uint8_t alignment_check:1;
	uint8_t virtual_interrupt_flag:1;
	uint8_t virtual_interrupt_pending:1;
	uint8_t id_flag:1;
	uint16_t __unused5:10;
} __attribute__ ((__packed__));
#endif
