#include "main.h"

void EntryPoint()
{
	printf("Test library started.\n");
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
	while (true)
	{
		printf("Test library sleeping for 2 seconds.\n");
		sleep(2);
	}
#pragma clang diagnostic pop
}