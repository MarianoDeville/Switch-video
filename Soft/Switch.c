/********************************************************************************/
/*								*/
/*				Revisión:				1.00									*/
/*				PIC:					PIC16F873A								*/
/*				Compilador:				MPLAB IDE 8.53 - HI-TECH 9.60			*/
/*				Checksum:				0x8851									*/
/*				Fecha de creación:		28/10/2011								*/
/*				Autor:					Mariano Ariel Deville					*/
/********************************************************************************/
/*								MACROS											*/
/*..............................................................................*/
#define		PIC_CLK		20000000	// 20Mhz.									*/
#define		ENTRADA		1			//											*/
#define		SALIDA		0			//											*/
/*------------------------------------------------------------------------------*/
/*				Defino los nombres de los pines de E/S							*/
/*..............................................................................*/
#define		BOTON_4		RA0		// Botón para cambiar la imagen en la salida 1.	*/
#define		BOTON_3		RA1		// Botón para cambiar la imagen en la salida 2.	*/
#define		BOTON_2		RA2		// Botón para cambiar la imagen en la salida 2.	*/
#define		BOTON_1		RA3		// Botón para cambiar la imagen en la salida 2.	*/
#define		S2			RB0
#define		S6			RB1
#define		S3			RB2
#define		S7			RB3
#define		S4			RB4
#define		S8			RB5
#define		S1			RC6
#define		S5			RC7
#define		BARRIDO		RC4
/********************************************************************************/
/*							ARCHIVOS CABECERA									*/
/*..............................................................................*/
#include	"htc.h"				// Necesario para el compilador.				*/
#include	"Delay.c"			// Rutinas de demoras.							*/
/********************************************************************************/
/*						PROTOTIPO DE FUNCIONES									*/
/*..............................................................................*/
void Cambiar_Entrada(unsigned char canal);

__CONFIG(DEBUGDIS & UNPROTECT & LVPDIS & BOREN & PWRTEN & WDTEN & HS);	//		*/
/********************************************************************************/
void main(void)
{
	unsigned char canal;
	ADCON1=0B00000110;						// Todos los pines digitales.
	PORTA=0xff;
	PORTB=0xff;
	PORTC=0xff;
/********************************************************************************/
/*				Configuración de los puertos									*/
/*..............................................................................*/
	TRISA0=ENTRADA;			// Botón para cambiar la entrada de la salida 1.	*/
	TRISA1=ENTRADA;			// Botón para cambiar la entrada de la salida 2.	*/
	TRISA2=ENTRADA;			// Botón para cambiar la entrada de la salida 3.	*/
	TRISA3=ENTRADA;			// Botón para cambiar la entrada de la salida 4.	*/
	TRISA4=SALIDA;			// Sin uso.											*/
	TRISA5=SALIDA;			// Sin uso.											*/
/*..............................................................................*/
	TRISB0=SALIDA;			// 								*/
	TRISB1=SALIDA;			// 								*/
	TRISB2=SALIDA;	   		// 								*/
	TRISB3=SALIDA;   		// 								*/
	TRISB4=SALIDA; 	  		// 								*/
	TRISB5=SALIDA;   		// 								*/
	TRISB6=ENTRADA;   		// Sin uso - PGC.									*/
	TRISB7=ENTRADA;   		// Sin uso - PGD.									*/
/*..............................................................................*/
	TRISC0=SALIDA;			// Sin uso.											*/
	TRISC1=SALIDA;			// Sin uso.											*/
	TRISC2=SALIDA;			// Sin uso.											*/
	TRISC3=SALIDA;			// Sin uso.											*/
	TRISC4=ENTRADA;			// Botón para cambiar a modo barrido automático.	*/
	TRISC5=SALIDA;			// Sin uso.											*/
	TRISC6=SALIDA;			// 								*/
	TRISC7=SALIDA;			//								*/
/********************************************************************************/
/*			TIMER 0 - NO UTILIZADO												*/
/*..............................................................................*/
	T0CS=0;					// Oscilador interno.								*/
	T0SE=0;					// Flanco ascendente.								*/
	PSA=1;					// Asigno el preescaler al WDT.						*/
	PS0=1;					// Configuro el Preescaler 1/128.					*/
	PS1=1;					// 													*/
	PS2=1;					// 													*/
	TMR0=0;					//													*/
	TMR0IF=0;				// Bajo la bandera de la interrupción.				*/
/********************************************************************************/
/*			TIMER 1 - NO UTILIZADO												*/
/*..............................................................................*/
	T1CKPS0=1; 				// Preescaler TMR1 a 1:8.							*/
	T1CKPS1=1; 				//													*/
	T1SYNC=0;				// No sincronizo con clock externo.					*/
	T1OSCEN=0;				// Oscilador deshabilitado.							*/
	TMR1CS=0;  				// Reloj interno Fosc/4.							*/
	TMR1IF=0;				// Bajo la bandera de la interrupción.				*/
	TMR1ON=0;				// Enciendo el TMR1.								*/
	TMR1H=0;				// Configuro el tiempo que tarda en generar			*/
	TMR1L=0;				// la interrupcion (100 mseg).						*/
/********************************************************************************/
/*			TIMER 2 - NO UTILIZADO												*/
/*..............................................................................*/
	TMR2ON=0;				// Timer 2 apagado.									*/
	TOUTPS0=0;				// Postscale.										*/
	TOUTPS1=0;				// Postscale.										*/
	TOUTPS2=0;				// Postscale.										*/
	TOUTPS3=0;				// Postscale.										*/
	T2CKPS0=1;				// Configuro el Preescaler.							*/
	T2CKPS1=1;				// 													*/
	TMR2=5;					// Configuro el desborde.							*/
	TMR2IF=0;				// Bajo la bandera de la interrupción.				*/
/********************************************************************************/
/*			Configuración de las interrupciones									*/
/*..............................................................................*/
	GIE=0;					// No utilizo interrupciones.						*/
	PEIE=0;					// Interrupcion externa deshabilitada.				*/
	INTE=0;					// Interrupcion RB0/INT deshabilitada.				*/
	TMR0IE=0;				// Interrupcion desborde TMR0 deshabilitada.		*/
	TMR1IE=0;				// Interrupcion desborde TMR1 deshabilitada.		*/
	TMR2IE=0;				// Interrupcion desborde TMR2 deshabilitada.		*/
	CCP1IE=0;				// CCP1 Interrupt disable.							*/
	CCP2IE=0;				// CCP2 Interrupt disable.							*/
	EEIE=0;					// EEPROM Write Operation Interrupt disable.		*/
	SSPIE=0;				// Interrupcion por comunicacion I2C.				*/
	BCLIE=0;				// Bus Collision Interrupt disable.					*/
	ADIE=0;					// Interrupcion del conversor AD deshabilitada.		*/
	RBIE=0;					// Interrupcion por RB deshabilitada.				*/
	RCIE=0;					// Interrupcion recepcion USART deshabilitada.		*/
 	INTEDG=1;				// Interrupcion en el flanco descendente de RB0.	*/
	RBPU=1;					// RB pull-ups estan deshabilitadas.				*/
/********************************************************************************/
	for(;;)							// Bloque principal del programa.
	{
		CLRWDT();
		if(BOTON_1)
			canal=1;
		if(BOTON_2)
			canal=2;
		if(BOTON_3)
			canal=3;
		if(BOTON_4)
			canal=4;
		while(BOTON_1||BOTON_2||BOTON_3||BOTON_4)
			CLRWDT();
		Cambiar_Entrada(canal);
		canal=0;
		while(BARRIDO)				// Barrido automático de entradas.
		{
			Cambiar_Entrada(1);
			Cambiar_Entrada(2);
			Cambiar_Entrada(3);
			Cambiar_Entrada(4);
			DelayS(4);
		}
		DelayMs(50);
	}
}
/********************************************************************************/
/*		Cambio entre las distintas entradas para cada canal.					*/
/*..............................................................................*/
void Cambiar_Entrada(unsigned char canal)
{
	switch(canal)
	{
		case 0:
			return;
		case 1:
		{
			if(S1)
			{
				S1=0;
				S5=1;
				return;
			}
			if(!S1&&S5)
			{
				S1=0;
				S5=0;
				return;
			}
			if(!S5)
			{
				S1=1;
				S5=1;
				return;
			}
		}
		case 2:
		{
			if(S2)
			{
				S2=0;
				S6=1;
				return;
			}
			if(!S2&&S6)
			{
				S2=0;
				S6=0;
				return;
			}
			if(!S6)
			{
				S2=1;
				S6=1;
				return;
			}
		}
		case 3:
		{
			if(S3)
			{
				S3=0;
				S7=1;
				return;
			}
			if(!S3&&S7)
			{
				S3=0;
				S7=0;
				return;
			}
			if(!S7)
			{
				S3=1;
				S7=1;
				return;
			}
		}
		case 4:
		{
			if(S4)
			{
				S4=0;
				S8=1;
				return;
			}
			if(!S4&&S8)
			{
				S4=0;
				S8=0;
				return;
			}
			if(!S8)
			{
				S4=1;
				S8=1;
				return;
			}
		}
	}
	return;
}
