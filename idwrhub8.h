#ifndef idwrhub8_h
#define idwrhub8_h

#include <avr/pgmspace.h>
#include "arduino.h"

class idwrhub8{
	public:
	
	idwrhub8(uint8_t en_pin,uint8_t a_pin,uint8_t b_pin,uint8_t c_pin,uint8_t d_pin);
	
	void hardware_spi_init(uint8_t ss_pin);
	
	void display_dmd_hub8();
	
	uint8_t matrix_tampil[16][8]; // [y][x]
	
	void data_matrix(unsigned char data);
	
	void posisi_hub8(unsigned char posisi);
	
	void teks_hub(char *teks);
	
	void pilihfont(const uint8_t * Font);
	
	//uint8_t spi_mosi;
	//uint8_t spi_clk;
	const uint8_t* font;
	uint8_t ss_latch_pin;
	uint8_t en_latch_pin;
	uint8_t a_latch_pin;
	uint8_t b_latch_pin;
	uint8_t c_latch_pin;
	uint8_t d_latch_pin;
	
};

#endif
	