#include <mips/interrupt.h>
#include <mips/syscall.h>
#include <mips/cpu.h>
#include <mips/thread.h>

#define DPRINTF (printf("[%s:%s:%d] ", __FILE__, __FUNCTION__, __LINE__), printf)
//#define DPRINTF(...) do{}while(0)

static inline void
dump_frame(md_thread_t *frame)
{
	printf("tlb_low:%x tlb_high:%x tlb_index:%x tlb_context:%x\n"
	       "at:%x v0:%x v1:%x a0:%x\n"
	       "a1:%x a2:%x a3:%x t0:%x\n"
	       "t1:%x t2:%x t3:%x t4:%x\n"
	       "t5:%x t6:%x t7:%x s0:%x\n"
	       "s1:%x s2:%x s3:%x s4:%x\n"
	       "s5:%x s6:%x s7:%x t8:%x\n"
	       "t9:%x k0:%x k1:%x gp:%x\n"
	       "sp:%x fp:%x ra:%x sr:%x\n"
	       "mdlo:%x mdhi:%x bad_address:%x cause:%x\n"
	       "pc:%x processor_id:%x tlb_random:%x tlb_bad:%x\n"
	       "zero:%x\n",
	       frame->tlb_low, frame->tlb_high, frame->tlb_index, frame->tlb_context,
	       frame->at, frame->v0, frame->v1, frame->a0,
	       frame->a1, frame->a2, frame->a3, frame->t0,
	       frame->t1, frame->t2, frame->t3, frame->t4,
	       frame->t5, frame->t6, frame->t7, frame->s0,
	       frame->s1, frame->s2, frame->s3, frame->s4,
	       frame->s5, frame->s6, frame->s7, frame->t8,
	       frame->t9, frame->k0, frame->k1, frame->gp,
	       frame->sp, frame->fp, frame->ra, frame->sr,
	       frame->mdlo, frame->mdhi, frame->bad_address, frame->cause,
	       frame->pc, frame->processor_id, frame->tlb_random, frame->tlb_bad,
	       frame->zero);
}

void 
trap(unsigned status, unsigned cause, unsigned epc, 
     md_thread_t *frame)
{
	const int exc = cause & CAUSE_EXC_MASK;
	DPRINTF("status:%x cause:%x epc:%x exc:%x\n",
		status, cause, epc, exc);
	switch(exc) {
	case EXC_INT:
		interrupt_handle(cause & CAUSE_IP_MASK);
		break;
	case EXC_SYS:
		syscall_handle(status, cause, epc, frame);
		break;
	default:
		printf("[general exception]\n");
		dump_frame(frame);
		while(1)
			;
	}
}

void
trap_reset(unsigned status, unsigned cause, unsigned epc,
		       md_thread_t *frame)
{
	printf("status:%x cause:%x epc:%x\n"
	       "[reset exception]\n",
	       status, cause, epc);
	dump_frame(frame);
	while(1)
		;
}

void
trap_cache_error(unsigned status, unsigned cause, unsigned epc,
		 md_thread_t *frame)
{
	printf("status:%x cause:%x epc:%x\n"
	       "[utlb exception]\n",
	       status, cause, epc);
	dump_frame(frame);
	while(1)
		;
}
