#include "humble.h"
#include "dbg.h"
#include "stm32f2xx.h"
#include "nvic/nvic.h"
#include "shell/shell.h"
#include "systimer/systimer.h"
#include "netconf/netconf.h"

#include "udptest/udptest.h"
#include "tcptest/tcptest.h"

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
	LwIP_Init();
	udptest_server_init();
	udptest_client_init();
	tcptest_server_init();
	tcptest_client_init();
	shell_init();
	while(1){
		/* handle periodic timers for LwIP */
		LwIP_Periodic_Handle(LocalTime);
		
		if((LocalTime - currenttime0) >= 500){
			//dbp("0.5s\n");
			currenttime0 = LocalTime;
		}
		if((LocalTime - currenttime1) >= 1000){
			currenttime1 = LocalTime;
			udptest_send_data();
			check_tcp_connected();
			tcptest_send_data();
			//dbp("1s\n");
		}
		
	}
}
