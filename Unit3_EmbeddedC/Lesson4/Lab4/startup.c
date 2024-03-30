#include <stdint.h>

extern int main(void);
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text;

void Reset_Handler (void)
{
	unsigned int DATA_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA;
	unsigned char* P_src = (unsigned char*)&_E_text;
	unsigned char* P_dst = (unsigned char*)&_S_DATA;
	int i;
	for ( i = 0; i < DATA_size; i++)
	{
		*((unsigned char*)P_dst++) = *((unsigned char*)P_src++);
	}

	unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
	P_dst = (unsigned char*)&_S_bss;
	for ( i = 0; i < bss_size; i++)
	{
		*((unsigned char*)P_dst++) = (unsigned char)0;
	}

	main();
}

void Default_handler()
{
	Reset_Handler();
}
void NMI_Handler() __attribute__ ((weak,alias("Default_handler")));
void H_fault_Handler() __attribute__ ((weak,alias("Default_handler")));

// book 1024byte located by .bss through un intialized array of int 256 elment
static unsigned int Stack_top[256];

void (* const g_p_fn_Vectors[])() __attribute__((section(".vectors")))={
	(void (*)()) ((unsigned long)Stack_top + sizeof(Stack_top)),
	 &Reset_Handler,
	 &NMI_Handler,
	 &H_fault_Handler
};