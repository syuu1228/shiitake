#ifndef MIPS_H
#define MIPS_H

#define SR_CU_MASK	0xf0000000	/* Coproc Usable */
#define SR_CU3		0x80000000	/* Coprocessor 3 usable */
#define SR_CU2		0x40000000	/* Coprocessor 2 usable */
#define SR_CU1		0x20000000	/* Coprocessor 1 usable */
#define SR_CU0		0x10000000	/* Coprocessor 0 usable */
#define SR_BEV		0x00400000	/* Boot Exception Vectors */
#define SR_TS			0x00200000	/* TLB shutdown */
#define SR_PE			0x00100000	/* Parity Error (cache) */
#define SR_CM			0x00080000	/* Cache Miss */
#define SR_PZ			0x00040000	/* Parity Zero (cache) */
#define SR_SwC		0x00020000	/* Swap Caches */
#define SR_IsC		0x00010000	/* Isolate (data) Cache */
#define SR_INT_MASK	0x0000ff00	/* Interrupt Mask (1=enable)*/
#define INT_LEV8		0x00000000	/* Interrupt level 8 */
#define INT_LEV7		0x00008000	/* Interrupt level 7 */
#define INT_LEV6		0x0000c000	/* Interrupt level 6 */
#define INT_LEV5		0x0000e000	/* Interrupt level 5 */
#define INT_LEV4		0x0000f000	/* Interrupt level 4 */
#define INT_LEV3		0x0000f800	/* Interrupt level 3 */
#define INT_LEV2		0x0000fc00	/* Interrupt level 2 */
#define INT_LEV1		0x0000fe00	/* Interrupt level 1 */
#define INT_LEV0		0x0000ff00	/* Interrupt level 0 */
#define SR_KUo		0x00000020	/* old  mode (1 => user) */
#define SR_KUp		0x00000008	/* previous mode */
#define SR_KUo_SHIFT	5
#define SR_KUp_SHIFT	3
#define SR_KUc		0x00000002	/* currrent mode */
#define SR_IEo		0x00000010	/* old IntEn (1 => enable) */
#define SR_IEp		0x00000004	/* previous IntEn */
#define SR_IEc		0x00000001	/* Current IntEn */

#define	CAUSE_BD		0x80000000	/* Branch Delay */
#define	CAUSE_CE_MASK		0x30000000	/* Coprocessor Error */
#define	CAUSE_CE_SHIFT		28
#define	CAUSE_IP_MASK		0x0000ff00	/* Interrupts Pending */
#define	CAUSE_IP_SHIFT		8
#define	IP_NLEV		8		/* No. of Interrupt Levels */
#define	IP_LEV7		0x00008000	/* Hardware level 7 pending */
#define	IP_LEV6		0x00004000	/* Hardware level 6 pending */
#define	IP_LEV5		0x00002000	/* Hardware level 5 pending */
#define	IP_LEV4		0x00001000	/* Hardware level 4 pending */
#define	IP_LEV3		0x00000800	/* Hardware level 3 pending */
#define	IP_LEV2		0x00000400	/* Hardware level 2 pending */
#define	IP_LEV1		0x00000200	/* Software level 1 pending */
#define	IP_LEV0		0x00000100	/* Software level 0 pending */
#define	CAUSE_EXC_MASK		0x0000003c	/* Exc Code */
#define	CAUSE_EXC_SHIFT		2
#define	EXC_INT		0x00000000	/* Interrupt */
#define	EXC_MOD		0x00000004	/* TLB mod */
#define	EXC_TLBL	0x00000008	/* TLB Miss (Load) */
#define	EXC_TLBS	0x0000000c	/* TLB Miss (Store) */
#define	EXC_ADEL	0x00000010	/* Address Error (Load) */
#define	EXC_ADES	0x00000014	/* Address Error (Store) */
#define	EXC_IBE		0x00000018	/* Bus Error (Instruction) */
#define	EXC_DBE		0x0000001c	/* Bus Error (Data) */
#define	EXC_SYS		0x00000020	/* Syscall */
#define	EXC_BP		0x00000024	/* Breakpoint */
#define	EXC_RI		0x00000028	/* Reserved Instruction */
#define	EXC_CU		0x0000002c	/* Coprocessor Unusable */
#define	EXC_OVF		0x00000030	/* Arithmetic Overflow */

#define THREAD_PREV     0
#define THREAD_NEXT     4
#define THREAD_STATUS   8
#define THREAD_MSS      12
#define THREAD_STACK_AREA       176
#define THREAD_MSS_TLB_LO       12
#define THREAD_MSS_TLB_HI       16
#define THREAD_MSS_TLB_INX      20
#define THREAD_MSS_TLB_CTX      24
#define THREAD_MSS_AT   28
#define THREAD_MSS_V0   32
#define THREAD_MSS_V1   36
#define THREAD_MSS_A0   40
#define THREAD_MSS_A1   44
#define THREAD_MSS_A2   48
#define THREAD_MSS_A3   52
#define THREAD_MSS_T0   56
#define THREAD_MSS_T1   60
#define THREAD_MSS_T2   64
#define THREAD_MSS_T3   68
#define THREAD_MSS_T4   72
#define THREAD_MSS_T5   76
#define THREAD_MSS_T6   80
#define THREAD_MSS_T7   84
#define THREAD_MSS_S0   88
#define THREAD_MSS_S1   92
#define THREAD_MSS_S2   96
#define THREAD_MSS_S3   100
#define THREAD_MSS_S4   104
#define THREAD_MSS_S5   108
#define THREAD_MSS_S6   112
#define THREAD_MSS_S7   116
#define THREAD_MSS_T8   120
#define THREAD_MSS_T9   124
#define THREAD_MSS_K0   128
#define THREAD_MSS_K1   132
#define THREAD_MSS_GP   136
#define THREAD_MSS_SP   140
#define THREAD_MSS_FP   144
#define THREAD_MSS_RA   148
#define THREAD_MSS_SR   152
#define THREAD_MSS_LO   156
#define THREAD_MSS_HI   160
#define THREAD_MSS_BAD  164
#define THREAD_MSS_CAUSE        168
#define THREAD_MSS_PC   172
#define THREAD_MSS_PROCESSOR_ID 176
#define THREAD_MSS_TLB_RANDOM 180
#define THREAD_MSS_TLB_BAD 184
#define THREAD_MSS_ZERO 188
#ifdef __ASSEMBLY__
#define zero $0
#define at $1
#define v0 $2
#define v1 $3
#define a0 $4
#define a1 $5
#define a2 $6
#define a3 $7
#define t0 $8
#define t1 $9
#define t2 $10
#define t3 $11
#define t4 $12
#define t5 $13
#define t6 $14
#define t7 $15
#define s0 $16
#define s1 $17
#define s2 $18
#define s3 $19
#define s4 $20
#define s5 $21
#define s6 $22
#define s7 $23
#define t8 $24
#define t9 $25
#define k0 $26
#define k1 $27
#define gp $28
#define sp $29
#define fp $30
#define ra $31
#define c0_tlbhi	$10		/* EntryHi Register */
#define c0_tlblo	$2		/* Entry Lo Register */
#define c0_tlbind	$0		/* Index Register */
#define c0_tlbrnd	$1		/* Random Register */
#define c0_tlbcxt	$4		/* Context Register */
#define c0_tlbbad	$8		/* BadVAddr Register */
#define c0_status	$12		/* Status Register */
#define c0_cause	$13		/* Cause Register */
#define c0_epc	$14		/* ExceptionPC Register */
#define c0_prid	$15		/* Processor Id Register */
#else 
typedef struct
{
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
}registers;
#endif
#endif /* #ifndef MIPS_H */
