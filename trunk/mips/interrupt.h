#ifndef MIPS_INTERRUPT_H_
#define MIPS_INTERRUPT_H_

void interrupt_init(void);
void interrupt_handle(int level);

#endif
