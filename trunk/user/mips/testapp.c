
int syscall1(int a, int b, int c, int d)
{
	asm volatile("li $v0, 0x1\n"
		     "syscall");
}

int main(void)
{
	syscall1(0x10, 0x20, 0x30, 0x40);
	return 10;
}
