#include <common.h>

int board_early_init_f(void)
{
	return 0;
}

int checkboard(void)
{
	printf("BOARD: %s\n", CONFIG_BOARD_NAME);
	return 0;
}

phys_size_t initdram(int board_type)
{
	return 0;
}
