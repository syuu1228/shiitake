#ifndef MIPS_ASM_H_
#define MIPS_ASM_H_

#define COP0_TLB_INX $0
#define COP0_TLB_LO $2
#define COP0_TLB_CTX $4
#define COP0_BAD $8
#define COP0_TLB_HI $10
#define COP0_STATUS $12
#define COP0_CAUSE $13

#define THREAD_MD_TLB_LO 0
#define THREAD_MD_TLB_HI 4
#define THREAD_MD_TLB_INX 8
#define THREAD_MD_TLB_CTX 12
#define THREAD_MD_AT 16
#define THREAD_MD_V0   20
#define THREAD_MD_V1   24
#define THREAD_MD_A0   28
#define THREAD_MD_A1   32
#define THREAD_MD_A2   36
#define THREAD_MD_A3   40
#define THREAD_MD_T0   44
#define THREAD_MD_T1   48
#define THREAD_MD_T2   52
#define THREAD_MD_T3   56
#define THREAD_MD_T4   60
#define THREAD_MD_T5   64
#define THREAD_MD_T6   68
#define THREAD_MD_T7   72
#define THREAD_MD_S0   76
#define THREAD_MD_S1   80
#define THREAD_MD_S2   84
#define THREAD_MD_S3   88
#define THREAD_MD_S4   92
#define THREAD_MD_S5   96
#define THREAD_MD_S6   100
#define THREAD_MD_S7   104
#define THREAD_MD_T8   108
#define THREAD_MD_T9   112
#define THREAD_MD_K0   116
#define THREAD_MD_K1   120
#define THREAD_MD_GP   124
#define THREAD_MD_SP   128
#define THREAD_MD_FP   132
#define THREAD_MD_RA   136
#define THREAD_MD_SR   140
#define THREAD_MD_LO   144
#define THREAD_MD_HI   148
#define THREAD_MD_BAD  152
#define THREAD_MD_CAUSE        156
#define THREAD_MD_PC   160
#define THREAD_MD_PROCESSOR_ID 164
#define THREAD_MD_TLB_RANDOM 168
#define THREAD_MD_TLB_BAD 172
#define THREAD_MD_ZERO 176

#endif
