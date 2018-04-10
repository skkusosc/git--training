#include <sys/syscall.h>

#define SYSCALL_NUMBER 333
int main(void)
{
	syscall(SYSCALL_NUMBER);
	return 0;
}
