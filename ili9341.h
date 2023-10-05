#ifndef  _ILI9341_H_
#definir  _ILI9341_H_

#incluir  <avr/io.h>
#incluir  <util/delay.h>
#incluir  <avr/pgmspace.h>
#incluir  <límites.h>
#incluir  <tiposint.h>

#definir  puerto de control PORTB
#definir  controlddr DDRB
#definir  pin de control PINB
#definir  primer puerto PORTD
#definir  primer DDRD
#definir  PIND de primer pin
#definir  CC 0
#definir  cs 1
#definir  primero 7
#definir  ILI9341_TFTHEIGHT 240
#definir  ILI9341_TFTWIDTH 320

#definir  NEGRO        0x0000      
#definir  MARINO         0x000F      
#definir  VERDE OSCURO    0x03E0      
#define  CIAN OSCURO     0x03EF      
#definir  GRANATE       0x7800      
#definir  PÚRPURA       0x780F      
#definir  OLIVA        0x7BE0      
#definir  GRIS CLARO    0xC618      
#define  GRIS OSCURO     0x7BEF      
#definir  AZUL         0x001F      
#definir  VERDE        0x07E0      
#definir  CIAN         0x07FF      
#definir  ROJO          0xF800     
#definir  MAGENTA      0xF81F      
#definir  AMARILLO       0xFFE0      
#definir  BLANCO        0xFFFF      
#definir  NARANJA       0xFD20      
#define  VERDEAMARILLO 0xAFE5     
#definir  ROSA         0xF81F

vacío  ili9341_hard_init ( vacío );
vacío  ili9341_spi_init ( vacío );
void  ili9341_spi_send ( char spi_data sin firmar  );
anular  ili9341_writecommand8 ( uint8_t  com );
anular  ili9341_writedata8 ( datos uint8_t  );
void  ili9341_setaddress ( uint16_t  x1 , uint16_t  y1 , uint16_t  x2 , uint16_t  y2 );
anular  ili9341_hard_reset ( anular );
vacío  ili9341_init ( vacío );
void  ili9341_pushcolor ( color uint16_t  );
anular  ili9341_clear ( color uint16_t  );
void  ili9341_drawpixel ( uint16_t  x3 , uint16_t  y3 , uint16_t  color1 );
void  ili9341_drawvline ( uint16_t  x , uint16_t  y , uint16_t  h , uint16_t  color );
void  ili9341_drawhline ( uint16_t  x , uint16_t  y , uint16_t  w , uint16_t  color );
void  ili9341_fillrect ( uint16_t  x , uint16_t  y , uint16_t  w , uint16_t  h , uint16_t  color );
void  ili9341_setRotation ( uint8_t  x );

#terminara si
