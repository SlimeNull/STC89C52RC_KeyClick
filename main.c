#include <REGX52.H>
#include "btnclick.h"

void switch_led(int index) {
	P2 ^= ((1 << (index * 2)) + (1 << (index * 2 + 1)));
}

void main()
{
	on_anyk_click(switch_led);
	
	while(1)
	{
		btnclick_loop();
	}
}