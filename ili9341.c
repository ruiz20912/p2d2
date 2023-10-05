#incluir  "ili9341.h"

volátil  uint16_t  LCD_W = ILI9341_TFTWIDTH ;
volátil  uint16_t  LCD_H = ILI9341_TFTHEIGHT ;

void  ili9341_hard_init ( void ) //iniciar hardware
{
	primeraddr = 0xFF ; //salida para restablecer
	primer puerto |=( 1 << primer ); //tire alto para funcionamiento normal
	controlddr |=( 1 << corriente continua ); //D/C como salida
}

void  ili9341_spi_init ( void ) //establecer la velocidad y la configuración de spi
{
	DDRB |=( 1 << 1 )|( 1 << 2 )|( 1 << 3 )|( 1 << 5 ); //CS,SS,MOSI,SCK como salida (aunque SS no se utilizará durante todo el programa)
	SPCR = ( 1 << SPE )|( 1 << MSTR ); //modo 0,fosc/4
	SPSR |=( 1 << SPI2X ); //duplicar velocidad de spi.es decir, velocidad de spi final-fosc/2
	PUERTO |=( 1 << 1 ); //cs apagado durante el inicio
}

void  ili9341_spi_send ( unsigned char  spi_data ) //enviar datos spi para mostrar
{
	SPDR = datos_spi ; //mueve datos a spdr
	mientras (!( SPSR  & ( 1 << SPIF ))); //espera hasta que finalice la transmisión
}

void  ili9341_writecommand8 ( uint8_t  com ) //comando de escritura
{
	puerto de control &=~(( 1 << dc )|( 1 << cs )); //dc y cs ambos bajos para enviar el comando
	_delay_us ( 5 ); //pequeño retraso
	ili9341_spi_send ( com );
	puerto de control |=( 1 << cs ); //tirar alto cs
}

void  ili9341_writedata8 ( uint8_t  datos ) //escritura de datos
{
	puerto de control |=( 1 << dc ); //establecer CC alta para datos
	_delay_us ( 1 ); //demora
	puerto de control &=~( 1 << cs ); //establecer cs bajo para la operación
	ili9341_spi_send ( datos );
	puerto de control |=( 1 << cs );
}

void  ili9341_setaddress ( uint16_t  x1 , uint16_t  y1 , uint16_t  x2 , uint16_t  y2 ) //establecer coordenadas para impresión u otra función
{
	ili9341_writecommand8 ( 0x2A );
	ili9341_writedata8 ( x1 >> 8 );
	ili9341_writedata8 ( x1 );
	ili9341_writedata8 ( x2 >> 8 );
	ili9341_writedata8 ( x2 );

	ili9341_writecommand8 ( 0x2B );
	ili9341_writedata8 ( y1 >> 8 );
	ili9341_writedata8 ( y1 );
	ili9341_writedata8 ( y2 );
	ili9341_writedata8 ( y2 );

	ili9341_writecommand8 ( 0x2C ); // escritura de memoria
}

void  ili9341_hard_reset ( void ) //pantalla de restablecimiento completo
{
	primer puerto |=( 1 << primer ); //tira hacia arriba si anteriormente estaba bajo
	_delay_ms ( 200 );
	primer puerto &=~( 1 << primer ); //bajo para restablecer
	_delay_ms ( 200 );
	primer puerto |=( 1 << primer ); //nuevamente tire alto para operación normal
	_delay_ms ( 200 );
}

void  ili9341_init ( void ) //configurar la pantalla usando una secuencia de comandos predefinida
{
	ili9341_hard_init ();
	ili9341_spi_init ();
	ili9341_hard_reset ();
	ili9341_writecommand8 ( 0x01 ); //reinicio suave
	_delay_ms ( 1000 );

	//control de potencia A
	ili9341_writecommand8 ( 0xCB );
	ili9341_writedata8 ( 0x39 );
	ili9341_writedata8 ( 0x2C );
	ili9341_writedata8 ( 0x00 );
	ili9341_writedata8 ( 0x34 );
	ili9341_writedata8 ( 0x02 );

	//control de potencia B
	ili9341_writecommand8 ( 0xCF );
	ili9341_writedata8 ( 0x00 );
	ili9341_writedata8 ( 0xC1 );
	ili9341_writedata8 ( 0x30 );

	//control de sincronización del conductor A
	ili9341_writecommand8 ( 0xE8 );
	ili9341_writedata8 ( 0x85 );
	ili9341_writedata8 ( 0x00 );
	ili9341_writedata8 ( 0x78 );

	//control de sincronización del conductor B
	ili9341_writecommand8 ( 0xEA );
	ili9341_writedata8 ( 0x00 );
	ili9341_writedata8 ( 0x00 );

	//encendido control de secuencia
	ili9341_writecommand8 ( 0xED );
	ili9341_writedata8 ( 0x64 );
	ili9341_writedata8 ( 0x03 );
	ili9341_writedata8 ( 0x12 );
	ili9341_writedata8 ( 0x81 );

	//control de relación de bomba
	ili9341_writecommand8 ( 0xF7 );
	ili9341_writedata8 ( 0x20 );

	//control de potencia,VRH[5:0]
	ili9341_writecommand8 ( 0xC0 );
	ili9341_writedata8 ( 0x23 );

	//Control de potencia,SAP[2:0];BT[3:0]
	ili9341_writecommand8 ( 0xC1 );
	ili9341_writedata8 ( 0x10 );

	// control vcm
	ili9341_writecommand8 ( 0xC5 );
	ili9341_writedata8 ( 0x3E );
	ili9341_writedata8 ( 0x28 );

	// control vcm 2
	ili9341_writecommand8 ( 0xC7 );
	ili9341_writedata8 ( 0x86 );

	//control de acceso a la memoria
	ili9341_writecommand8 ( 0x36 );
	ili9341_writedata8 ( 0x48 );

	//formato de píxeles
	ili9341_writecommand8 ( 0x3A );
	ili9341_writedata8 ( 0x55 );

	//control de frameración, modo normal a todo color
	ili9341_writecommand8 ( 0xB1 );
	ili9341_writedata8 ( 0x00 );
	ili9341_writedata8 ( 0x18 );

	//mostrar control de función
	ili9341_writecommand8 ( 0xB6 );
	ili9341_writedata8 ( 0x08 );
	ili9341_writedata8 ( 0x82 );
	ili9341_writedata8 ( 0x27 );

	// función 3gamma deshabilitada
	ili9341_writecommand8 ( 0xF2 );
	ili9341_writedata8 ( 0x00 );

	//curva gamma seleccionada
	ili9341_writecommand8 ( 0x26 );
	ili9341_writedata8 ( 0x01 );

	//establecer corrección gamma positiva
	ili9341_writecommand8 ( 0xE0 );
	ili9341_writedata8 ( 0x0F );
	ili9341_writedata8 ( 0x31 );
	ili9341_writedata8 ( 0x2B );
	ili9341_writedata8 ( 0x0C );
	ili9341_writedata8 ( 0x0E );
	ili9341_writedata8 ( 0x08 );
	ili9341_writedata8 ( 0x4E );
	ili9341_writedata8 ( 0xF1 );
	ili9341_writedata8 ( 0x37 );
	ili9341_writedata8 ( 0x07 );
	ili9341_writedata8 ( 0x10 );
	ili9341_writedata8 ( 0x03 );
	ili9341_writedata8 ( 0x0E );
	ili9341_writedata8 ( 0x09 );
	ili9341_writedata8 ( 0x00 );

	//establecer corrección de gamma negativa
	ili9341_writecommand8 ( 0xE1 );
	ili9341_writedata8 ( 0x00 );
	ili9341_writedata8 ( 0x0E );
	ili9341_writedata8 ( 0x14 );
	ili9341_writedata8 ( 0x03 );
	ili9341_writedata8 ( 0x11 );
	ili9341_writedata8 ( 0x07 );
	ili9341_writedata8 ( 0x31 );
	ili9341_writedata8 ( 0xC1 );
	ili9341_writedata8 ( 0x48 );
	ili9341_writedata8 ( 0x08 );
	ili9341_writedata8 ( 0x0F );
	ili9341_writedata8 ( 0x0C );
	ili9341_writedata8 ( 0x31 );
	ili9341_writedata8 ( 0x36 );
	ili9341_writedata8 ( 0x0F );

	//salir del sueño
	ili9341_writecommand8 ( 0x11 );
	_delay_ms ( 120 );
	//mostrar en
	ili9341_writecommand8 ( 0x29 );
}

//establecer color para dibujar
vacío  ili9341_pushcolor ( color uint16_t  )
{
	ili9341_writedata8 ( color >> 8 );
	ili9341_writedata8 ( color );
}

//borrar lcd y llenar de color
vacío  ili9341_clear ( color uint16_t  )
{
	uint16_ti  , j ; _
	ili9341_setaddress ( 0 , 0 , LCD_W - 1 , LCD_H - 1 );

	para ( yo = 0 ; yo < LCD_W ; yo ++ )
	{
		para ( j = 0 ; j < LCD_H ; j ++ )
		{
			ili9341_pushcolor ( color );
		}
	}
}

//dibujar píxel
void  ili9341_drawpixel ( uint16_t  x3 , uint16_t  y3 , uint16_t  colour1 ) //los píxeles siempre se contarán desde el lado derecho.x representa el ancho de la pantalla LCD, que siempre será menor que 240.Y representa la altura de la pantalla LCD, que siempre será menor que 320
{
	si (( x3  <  0 ) || ( x3 >= LCD_W ) || ( y3  <  0 ) || ( y3 >= LCD_H ))
	{
		volver ;
	}

	ili9341_setaddress ( x3 , y3 , x3 + 1 , y3 + 1 );
	ili9341_pushcolor ( color1 );
}

//dibuja una línea vertical
void  ili9341_drawvline ( uint16_t  x , uint16_t  y , uint16_t  h , uint16_t  color ) //básicamente veremos esta línea horizontal si vemos la pantalla 320*240
{
	si (( x >= LCD_W ) || ( y >= LCD_H ))
	{
		volver ;
	}

	si (( y + h - 1 ) >= LCD_H )
	{
		h = LCD_H - y ;
	}

	ili9341_setaddress ( x , y , x , y + h - 1 );

	mientras ( h- ) _
	{
		ili9341_pushcolor ( color );
	}
}


//dibuja una línea horizontal

void  ili9341_drawhline ( uint16_t  x , uint16_t  y , uint16_t  w , uint16_t  color )
{
	si (( x >= LCD_W ) || ( y >= LCD_H ))
	{
		volver ;
	}

	si (( x + w - 1 ) >= LCD_W )
	{
		w = LCD_W - x ;
	}

	ili9341_setaddress ( x , y , x + w - 1 , y );

	mientras ( w- ) _
	{
		ili9341_pushcolor ( color );
	}
}


//dibuja un rectángulo relleno de color
void  ili9341_fillrect ( uint16_t  x , uint16_t  y , uint16_t  w , uint16_t  h , uint16_t  color )
{
	si (( x >= LCD_W ) || ( y >= LCD_H ))
	{
		volver ;
	}

	si (( x + w - 1 ) >= LCD_W )
	{
		w  =  LCD_W - x ;
	}

	si (( y + h - 1 ) >= LCD_H )
	{
		h  =  LCD_H - y ;
	}

	ili9341_setaddress ( x , y , x + w - 1 , y + h - 1 );

	para ( y = h ; y > 0 ; y -- )
	{
		para ( x = w ; x > 0 ; x -- )
		{
			ili9341_pushcolor ( color );
		}
	}
}
//girar la pantalla en la orientación deseada
vacío  ili9341_setRotation ( uint8_t  m )
{
	uint8_t  rotación ;

	ili9341_writecommand8 ( 0x36 );
	rotación = m % 4 ;

	interruptor ( rotación )
	{
		caso  0 :
			ili9341_writedata8 ( 0x40 | 0x08 );
			LCD_W  =  240 ;
			LCD_H  =  320 ;
			romper ;
		caso  1 :
			ili9341_writedata8 ( 0x20 | 0x08 );
			LCD_W   =  320 ;
			LCD_H  =  240 ;
			romper ;
		caso  2 :
			ili9341_writedata8 ( 0x80 | 0x08 );
			LCD_W   =  240 ;
			LCD_H  =  320 ;
			romper ;
		caso  3 :
			ili9341_writedata8 ( 0x40 | 0x80 | 0x20 | 0x08 );
			LCD_W   =  320 ;
			LCD_H  =  240 ;
			romper ;
	}
}
