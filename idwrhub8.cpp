#include <idwrhub8.h>
#include <avr/pgmspace.h>
#include "arduino.h"

idwrhub8::idwrhub8(uint8_t en_pin,uint8_t a_pin,uint8_t b_pin,uint8_t c_pin,uint8_t d_pin){
  en_latch_pin=en_pin;
  a_latch_pin=a_pin;
  b_latch_pin=b_pin;
  c_latch_pin=c_pin;
  d_latch_pin=d_pin;
  
  pinMode(en_pin,OUTPUT); //led
  pinMode(a_pin,OUTPUT); //d.6
  pinMode(b_pin,OUTPUT); //d.7
  pinMode(c_pin,OUTPUT); //c.1
  pinMode(d_pin,OUTPUT); //c.0
}

void idwrhub8::teks_hub(char *teks) {
  unsigned char a, b;
  char masuk;
  char isi_teks[8];
  a = 0;
  
//  while (k = *teks++) {
//    isi_teks[a] = k; a++;
//  }

  for(a=0;a<8;a++){
    masuk=*teks;
    if(masuk>31 && masuk<128)isi_teks[a] = masuk;
    else if(masuk!=0)        isi_teks[a] = 0x20;
    else                     break;
    teks++;
  }
  
  for (b = a; b < 8; b++)isi_teks[b] = ' ';
  
  for (b = 0; b < 8; b++) {
    for (a = 0; a < 16; a++) {
      matrix_tampil[a][b] = pgm_read_byte(&(font[a + (isi_teks[b] - 32) * 16]));
    }
  }

}

void idwrhub8::display_dmd_hub8() {
  int i, j;
  for (i = 0; i < 16; i++) {
    posisi_hub8(i);
    digitalWrite(ss_latch_pin, LOW);
    for (j = 0; j < 8; j++)data_matrix(matrix_tampil[i][j]);
    digitalWrite(ss_latch_pin, HIGH);
    digitalWrite(en_latch_pin, LOW);
    delayMicroseconds(500);
    digitalWrite(en_latch_pin, HIGH);
  }
}

void idwrhub8::posisi_hub8(unsigned char posisi) {
  switch (posisi) {
    case 0: digitalWrite(d_latch_pin,LOW); digitalWrite(c_latch_pin,LOW); digitalWrite(b_latch_pin,LOW); digitalWrite(a_latch_pin,LOW); break;
    case 1: digitalWrite(d_latch_pin,LOW); digitalWrite(c_latch_pin,LOW); digitalWrite(b_latch_pin,LOW); digitalWrite(a_latch_pin,HIGH); break;
    case 2: digitalWrite(d_latch_pin,LOW); digitalWrite(c_latch_pin,LOW); digitalWrite(b_latch_pin,HIGH); digitalWrite(a_latch_pin,LOW); break;
    case 3: digitalWrite(d_latch_pin,LOW); digitalWrite(c_latch_pin,LOW); digitalWrite(b_latch_pin,HIGH); digitalWrite(a_latch_pin,HIGH); break;
    case 4: digitalWrite(d_latch_pin,LOW); digitalWrite(c_latch_pin,HIGH); digitalWrite(b_latch_pin,LOW); digitalWrite(a_latch_pin,LOW); break;
    case 5: digitalWrite(d_latch_pin,LOW); digitalWrite(c_latch_pin,HIGH); digitalWrite(b_latch_pin,LOW); digitalWrite(a_latch_pin,HIGH); break;
    case 6: digitalWrite(d_latch_pin,LOW); digitalWrite(c_latch_pin,HIGH); digitalWrite(b_latch_pin,HIGH); digitalWrite(a_latch_pin,LOW); break;
    case 7: digitalWrite(d_latch_pin,LOW); digitalWrite(c_latch_pin,HIGH); digitalWrite(b_latch_pin,HIGH); digitalWrite(a_latch_pin,HIGH); break;
    case 8: digitalWrite(d_latch_pin,HIGH); digitalWrite(c_latch_pin,LOW); digitalWrite(b_latch_pin,LOW); digitalWrite(a_latch_pin,LOW); break;
    case 9: digitalWrite(d_latch_pin,HIGH); digitalWrite(c_latch_pin,LOW); digitalWrite(b_latch_pin,LOW); digitalWrite(a_latch_pin,HIGH); break;
    case 10: digitalWrite(d_latch_pin,HIGH); digitalWrite(c_latch_pin,LOW); digitalWrite(b_latch_pin,HIGH); digitalWrite(a_latch_pin,LOW); break;
    case 11: digitalWrite(d_latch_pin,HIGH); digitalWrite(c_latch_pin,LOW); digitalWrite(b_latch_pin,HIGH); digitalWrite(a_latch_pin,HIGH); break;
    case 12: digitalWrite(d_latch_pin,HIGH); digitalWrite(c_latch_pin,HIGH); digitalWrite(b_latch_pin,LOW); digitalWrite(a_latch_pin,LOW); break;
    case 13: digitalWrite(d_latch_pin,HIGH); digitalWrite(c_latch_pin,HIGH); digitalWrite(b_latch_pin,LOW); digitalWrite(a_latch_pin,HIGH); break;
    case 14: digitalWrite(d_latch_pin,HIGH); digitalWrite(c_latch_pin,HIGH); digitalWrite(b_latch_pin,HIGH); digitalWrite(a_latch_pin,LOW); break;
    case 15: digitalWrite(d_latch_pin,HIGH); digitalWrite(c_latch_pin,HIGH); digitalWrite(b_latch_pin,HIGH); digitalWrite(a_latch_pin,HIGH); break;
  }
}

void idwrhub8::data_matrix(unsigned char data) {
  SPDR = data;
  while (!(SPSR & (1 << 7)));
}

void idwrhub8::hardware_spi_init(uint8_t ss_pin){
  ss_latch_pin=ss_pin;
  
  pinMode(11,OUTPUT);	//MOSI
  pinMode(13,OUTPUT);	//SCK
  pinMode(ss_pin, OUTPUT); //ss
  
  //pokoke max speed
  SPCR = (1 << 6) | (1 << 4);
  SPCR = 0x50;
  SPSR = 0x01;
}

void idwrhub8::pilihfont(const uint8_t * Font){
    this->font = Font;
}

