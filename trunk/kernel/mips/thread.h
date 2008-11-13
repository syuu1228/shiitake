#ifndef MIPS_THREAD_H_
#define MIPS_THREAD_H_

typedef struct {
	unsigned tlb_low; /* TLB (partial) state, for KDB */
	unsigned tlb_high; /* EntryHi Register */
	unsigned tlb_index; /* Entry Lo Register */
	unsigned tlb_context; /* Context Register */
	unsigned at; /* assembler temporary */
	unsigned v0; /* return value 0 */
	unsigned v1; /* return value 1 */
	unsigned a0; /* argument 0 */
	unsigned a1; /* argument 1 */
	unsigned a2; /* argument 2 */
	unsigned a3; /* argument 3 */
	unsigned t0; /* caller saved 0 */
	unsigned t1; /* caller saved 1 */
	unsigned t2; /* caller saved 2 */
	unsigned t3; /* caller saved 3 */
	unsigned t4; /* caller saved 4 */
	unsigned t5; /* caller saved 5 */
	unsigned t6; /* caller saved 6 */
	unsigned t7; /* caller saved 7 */
	unsigned s0; /* callee saved 0 */
	unsigned s1; /* callee saved 1 */
	unsigned s2; /* callee saved 2 */
	unsigned s3; /* callee saved 3 */
	unsigned s4; /* callee saved 4 */
	unsigned s5; /* callee saved 5 */
	unsigned s6; /* callee saved 6 */
	unsigned s7; /* callee saved 7 */
	unsigned t8; /* code generator 0 */
	unsigned t9; /* code generator 1 */
	unsigned k0; /* kernel temporary 0 */
	unsigned k1; /* kernel temporary 1 */
	unsigned gp; /* global pointer */
	unsigned sp; /* stack pointer */
	unsigned fp; /* frame pointer */
	unsigned ra; /* return address */
	unsigned sr; /* status register */
	unsigned mdlo; /* low mult result */
	unsigned mdhi; /* high mult result */
	unsigned bad_address; /* bad virtual address */
	unsigned cause; /* cause register */
	unsigned pc; /* program counter */
	unsigned processor_id; /* Processor Id Register */
	unsigned tlb_random; /* Random Register */
	unsigned tlb_bad; /* BadVAddr Register */
	unsigned zero;
} md_thread_t;

#endif
