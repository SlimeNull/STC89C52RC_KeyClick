#include <REGX52.H>

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
	int (*checker)();
	void (**handler)();
	char mask;
} ButtonCheckInfo;

int k1checker() { return TXD; }
int k2checker() { return RXD; }
int k3checker() { return P3 & 4; }
int k4checker() { return P3 & 8; }

ButtonCheckInfo btns[4] = {
	{ k1checker, &k1_click_handler, 128 },
	{ k2checker, &k2_click_handler, 64 },
	{ k3checker, &k3_click_handler, 32 },
	{ k4checker, &k4_click_handler, 16 }
};

void button_loop() {
	char i = 0;
	while (i < 4) {
		if (btns[i].checker()) {
			if (!(button_last_state & btns[i].mask)) {
				if (*btns[i].handler != 0)
					(*(btns[i].handler))();
				if (anyk_click_handler != 0)
					anyk_click_handler(i);
			}
			button_last_state |= btns[i].mask;
		} else {
			button_last_state &= ~btns[i].mask;
		}
		i++;
	}
}