#include "humble.h"
#include "dbg.h"
#include "stm32f2xx.h"
#include "nvic/nvic.h"
#include "shell/shell.h"
#include "systimer/systimer.h"
#include "eth/eth.h"


typedef  void (*pFunction)(void);

int main(void)
{
	u32 currenttime0 = 0;
	u32 currenttime1 = 0;
	
	pFunction Jump2App = (pFunction)(*(vu32*) (APP_Address + 4));
	nvic_global_init();
	systimer_init();
	
	dbg_init();
	
	/* Test if user code is programmed starting from address "APP_Address" */
	if (((*(vu32*)APP_Address) & 0x2FFE0000 ) == 0x20000000){
		/* Jump to user application */
		dbp("Jump to user application\n");
		/* Initialize user application's Stack Pointer */
		__set_MSP(*(vu32*) APP_Address);
		Jump2App();
	}
	
	dbp("\n\n%s %s\n", __DATE__, __TIME__);
	dbp("BOOT = stm32f207vet6\n");
	//zq_eth_init();
	shell_init();
	while(1){
		if((LocalTime - currenttime0) == 5000){
			dbp("5s\n");
			currenttime0 = LocalTime;
		}
		if((LocalTime - currenttime1) == 10000){
			currenttime1 = LocalTime;
			dbp("10\n");
		}
	}
}