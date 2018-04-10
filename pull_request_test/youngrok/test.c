/*******************************************************
 * Copyright (C) 2018 SKKU Embedded Software Lab.
 * 
 * This file is part of OS Project 1.
 * 
 * This file can not be copied and/or distributed without the express
 * permission of ESLAB
 *******************************************************/

#include <sys/syscall.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

#define SYSCALL_NUMBER 333

enum {
	OPT_PS = 0,
	OPT_CPU_INFO,
	OPT_SIBLING,
	OPT_CHILDREN,
	OPT_VMA,
};

int isPositiveInteger(char *str) {
	int i = 0;
	while (isdigit(str[i]))
		i++;

	if (str[i] == '\0')
		return 1;
	return 0;
}

char *options[][2] = {"-C", "print CPU information",
	"-s", "print sibling (need -p option)",
	"-c", "print children (need -p option)",
	"-v", "print vma information",
	"-p <pid>", "set pid value (default=1)",
	"-h", "print usage",
	NULL};
	
void printHelp(void) {
	int i;
	printf("Usage:\n");
	printf("./sysps [OPTION]\n\n");
	printf("Options:\n");
	for (i=0; options[i][0]!=NULL; i++)
		printf("  %-10s%s\n", options[i][0], options[i][1]);
}

int main(int argc, char *argv[]) {
	int opt, pid = 1;
	int flag_C = 0, flag_s = 0, flag_c = 0, flag_v = 0, flag_p = 0;

	int c;
	while ( (c = getopt(argc, argv, "Cscvp:h")) != -1) {
		switch (c) {
			case 'C':
				flag_C = 1;
				break;
			case 's':
				flag_s = 1;
				break;
			case 'c':
				flag_c = 1;
				break;
			case 'v':
				flag_v = 1;
				break;
			case 'p':
				flag_p = 1;
				if (isPositiveInteger(optarg))
					pid = atoi(optarg);
				else {
					printf("pid is not integer\n");
					exit(1);
				}
				break;
			case '?':
				printf("Invalid option\n");
			case 'h':
				printHelp();
				exit(1);
		}
	}

	if (!(flag_C || flag_s || flag_c || flag_v))
		syscall(SYSCALL_NUMBER, OPT_PS, pid);
	else {
		if (flag_C) syscall(SYSCALL_NUMBER, OPT_CPU_INFO, pid);
		if (flag_s) syscall(SYSCALL_NUMBER, OPT_SIBLING, pid);
		if (flag_c) syscall(SYSCALL_NUMBER, OPT_CHILDREN, pid);
		if (flag_v) syscall(SYSCALL_NUMBER, OPT_VMA, pid);
	}

	execl("/usr/bin/sudo", "sudo", "dmesg", "-tc", NULL);

        return 0;
}
