#include "main.h"

int main(int argc, char *argv[])
{
	printf("Test application started.\n");
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
	while (true)
	{
		printf("Test application sleeping for 4 seconds.\n");
		sleep(4);
	}
#pragma clang diagnostic pop
}