#include "dbg.h"
#include "stm32f2xx.h"
#include "nvic/nvic.h"

extern void lua_main(void);
int main(void)
{
	nvic_global_init();
	dbg_init();
	dbp("\n\n%s %s\n", __DATE__, __TIME__);
	dbp("APP=stm32f207vet6\n");

	//lua_main();
	while(1);
}

