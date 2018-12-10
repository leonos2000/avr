/*
 *  main.c
 *
 *  Created on: 5 gru 2018
 * 		Author: Leon Czajka
 *
 */

#include <avr/io.h>
#include <util/delay.h>

#define WS_PORT PORTB
#define WS_DDR DDRB
#define WS_PIN 4

uint8_t wsBuffer[3];
uint8_t wsPin;

void wsInit() {
	WS_DDR |= (1 << WS_PIN);
	wsPin = (1 << WS_PIN);
}

void wsSend() {
	uint8_t databyte = 0, cnt, pinLO = ~wsPin;
	uint8_t dataLen = 3;

	asm volatile(
			"		lds		%[cnt],%[ws_port]	\n\t"
			"		or		%[pinHI],%[cnt]		\n\t"
			"		and		%[pinLO],%[cnt]		\n\t"
			"mPTL%=:subi	%A6,1				\n\t"
			"		sbci	%B6,0				\n\t"
			"		brcs	exit%=				\n\t"
			"		ld		%[databyte],X+		\n\t"
			"		ldi		%[cnt],8			\n\t"
			"oPTL%=:sts		%[ws_port],	%[pinHI]\n\t"
			"		lsl		%[databyte]			\n\t"
			"		brcs	.+2					\n\t"
			"		sts		%[ws_port],	%[pinLO]\n\t"
			"		dec		%[cnt]				\n\t"
			"		sts		%[ws_port],	%[pinLO]\n\t"
			"		breq	mPTL%=				\n\t"
			"		rjmp	oPTL%=				\n\t"
			"exit%=:							\n\t"
			: [cnt]"=&d" (cnt)
			: [databyte]"r" (databyte), [ws_port]"M" (_SFR_MEM_ADDR(WS_PORT)), [pinHI]"r" (wsPin),
			[pinLO]"r" (pinLO), [data]"x" (wsBuffer), [datlen]"r" (dataLen)
	);
}

inline void hsvToRgb(uint8_t h) {
	if (h < 40) {
		wsBuffer[1] = 240;
		wsBuffer[0] = h * 6;
		wsBuffer[2] = 0;
	} else if (h < 80) {
		wsBuffer[1] = (40 - (h - 40)) * 6;
		wsBuffer[0] = 240;
		wsBuffer[2] = 0;
	} else if (h < 120) {
		wsBuffer[1] = 0;
		wsBuffer[0] = 240;
		wsBuffer[2] = (h - 80) * 6;
	} else if (h < 160) {
		wsBuffer[1] = 0;
		wsBuffer[0] = (40 - (h - 120)) * 6;
		wsBuffer[2] = 240;
	} else if (h < 200) {
		wsBuffer[1] = (h - 160) * 6;
		wsBuffer[0] = 0;
		wsBuffer[2] = 240;
	} else {
		wsBuffer[1] = 240;
		wsBuffer[0] = 0;
		wsBuffer[2] = (40 - (h - 200)) * 6;
	}
}

int main(void) {
	wsInit();

	uint16_t buf;

	while (1) {
		for (uint8_t i = 0; i < 20; i++) {
			for (uint8_t j = 0; j < 240; j++) {
				for (uint8_t k = 0; k < 35; k++) {
					buf = j + k * 7;
					if (buf > 240)
						buf -= 240;
					hsvToRgb((uint8_t) buf);
					wsSend();
				}
				_delay_ms(10);
			}
		}
		for (uint8_t i = 0; i < 5; i++) {
			for (uint8_t j = 0; j < 35; j++) {
				for (uint8_t k = 0; k < 35; k++) {
					if (k == j) {
						wsBuffer[0] = 240;
						wsBuffer[1] = 240;
						wsBuffer[2] = 240;
					} else {
						wsBuffer[0] = 0;
						wsBuffer[1] = 0;
						wsBuffer[2] = 0;
					}
					wsSend();
				}
				_delay_ms(100);
			}
			_delay_ms(10);
		}
		for (uint8_t i = 0; i < 6; i++) {
			for (uint8_t j = 0; j < 35; j++) {
				for (uint8_t k = 0; k < 35; k++) {
					if ((i % 2) ? (k > j) : (k < j)) {
						wsBuffer[0] = 240;
						wsBuffer[1] = 240;
						wsBuffer[2] = 240;
					} else {
						wsBuffer[0] = 0;
						wsBuffer[1] = 0;
						wsBuffer[2] = 0;
					}
					wsSend();
				}
				_delay_ms(100);
			}
		}
		for (uint8_t i = 0; i < 7; i++) {
			for (uint8_t j = 0; j < 240; j++) {
				for (uint8_t k = 0; k < 35; k++) {
					hsvToRgb(j);
					wsSend();
				}
				_delay_ms(30);
			}
		}
		for (uint16_t i = 0; i < 200; i++) {
			for (uint8_t k = 0; k < 35; k++) {
				if ((k + (i % 2)) % 2) {
					wsBuffer[0] = 240;
					wsBuffer[1] = 240;
					wsBuffer[2] = 240;
				} else {
					wsBuffer[0] = 0;
					wsBuffer[1] = 0;
					wsBuffer[2] = 0;
				}
				wsSend();
			}
			_delay_ms(100);
		}
		for (uint8_t i = 0; i < 5; i++) {
			for (uint8_t j = 0; j < 255; j++) {
				for (uint8_t k = 0; k < 35; k++) {
					if (i % 2) {
						wsBuffer[0] = j;
						wsBuffer[1] = j;
						wsBuffer[2] = j;
					} else {
						wsBuffer[0] = 255 - j;
						wsBuffer[1] = 255 - j;
						wsBuffer[2] = 255 - j;
					}
					wsSend();
				}
				_delay_ms(10);
			}
		}
	}
}
