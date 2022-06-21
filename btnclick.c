#include <REGX52.H>
#include "btnclick.h"

char button_last_state = 255;

void (*k1_click_handler)();
void (*k2_click_handler)();
void (*k3_click_handler)();
void (*k4_click_handler)();
void (*anyk_click_handler)(int);

void on_k1_click(void (*handler)()) { k1_click_handler = handler; }
void on_k2_click(void (*handler)()) { k2_click_handler = handler; }
void on_k3_click(void (*handler)()) { k3_click_handler = handler; }
void on_k4_click(void (*handler)()) { k4_click_handler = handler; }
void on_anyk_click(void (*handler)(int)) { anyk_click_handler = handler; }

typedef struct {
	char (*checker)();
	void (**handler)();
} ButtonCheckInfo;

char k1checker() { return TXD; }
char k2checker() { return RXD; }
char k3checker() { return P3 & 4; }
char k4checker() { return P3 & 8; }

ButtonCheckInfo btns[4] = {
	{ k1checker, &k1_click_handler },
	{ k2checker, &k2_click_handler },
	{ k3checker, &k3_click_handler },
	{ k4checker, &k4_click_handler }
};

void btnclick_loop() {
	char i = 0;
	char mask = 0;
	char click = 0;
	while (i < 4) {
		mask = 1 << i;
		
		if (btns[i].checker()) {
			click = !(button_last_state & mask);
			button_last_state |= mask;
		} else {
			button_last_state &= ~mask;
		}
		
		if (click) {
			if (*btns[i].handler != 0)
				(*(btns[i].handler))();
			if (anyk_click_handler != 0)
				anyk_click_handler(i);
		}
		
		i++;
	}
}