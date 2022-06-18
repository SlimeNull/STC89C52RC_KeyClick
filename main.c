#include <REGX52.H>
extern void button_loop();
extern void on_k1_click(void (*handler)());
extern void on_k2_click(void (*handler)());
extern void on_k3_click(void (*handler)());
extern void on_k4_click(void (*handler)());
extern void on_anyk_click(void (*handler)(int));

void switch_led(int index) {
	P2 ^= ((1 << (index * 2)) + (1 << (index * 2 + 1)));
}

void main()
{
	on_anyk_click(switch_led);
	
	while(1)
	{
		button_loop();
	}
}