

	  struct segment_descriptor_table idtr;
	  get_idtr(&idtr);
	  printf("idtr limit:%x base:%p\n",
		 idtr.limit, idtr.base);
	  int len = idtr.limit / sizeof(struct segment_descriptor);
	  int i;
	  for(i = 0; i <= len; i++) {
		  struct gate_descriptor *desc = &idtr.base.gate_descriptor[i];
		  printf("idt[%d]\n", i);
		  printf("offset_l:%x ", desc->offset_l);
		  printf("segment_selector:%x ", desc->segment_selector);
		  printf("stack_copy_count:%x ", desc->stack_copy_count);
		  printf("type:%x dpl:%x p:%x ", desc->type, desc->dpl, desc->p);
		  printf("offset_h:%x\n", desc->offset_h);
	  }

  unsigned tr;
  asm volatile ("str %0" : "=m"(tr));
  printf("tr: %x\n", tr);

  int i;
  for(i = 0; i < 256; i++)
	  init_gate_descriptor(&idt[i], 0x8, interrupt_handler, 0x0, GATE_TYPE_32BIT_TRAP, 0, 1);
//  init_gate_descriptor(&idt[0xd], 0x8, gpe_fault, 0x0, GATE_TYPE_32BIT_TRAP, 0x1, 0x3, 0x1);
  idtr.limit = 256 * sizeof(struct gate_descriptor);
  idtr.base.gate_descriptor = idt;
  set_idtr(&idtr);
  printf("idt initialized\n");
  asm volatile ("sti");
  printf("interrupt enabled\n");
