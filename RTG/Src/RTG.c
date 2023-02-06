/*
 * RTG.c
 *
 */
#include "RTG.h"

void rtg_main()
{
	while (TRUE)
	{
		// Handles the actual reception of bytes from the network interface
		ethernetif_input(&gnetif);
		// Handle which checks timeout expiration
		sys_check_timeouts();
	}
}

