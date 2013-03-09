// POB-Technology 2009
//
// File : Functions.c
// Author : Foucault Alisson
//
// This file includes functions such as Pob-proto initialization and printing on LCD screen 
//


#include "pad.h"
#include "math.h"
#include "bitmap.h"



//array for display the graphic interface
static GraphicBuffer LCD_Buffer_Video;
static UInt8         LCD_Buffer[LCD_WIDTH*LCD_HEIGHT*BITS];
static UInt8		 ASCII_Buffer[LCD_WIDTH*LCD_HEIGHT*BITS]; // Buffer to stock the ascii table in bitmap format

// Set the bitmap  picture of the first 127 ASCII Char in ASCII_GRAPHIC_BUFFER
// ASCII_GRAPHIC_BUFFER will be used to get the pictures of characters to display on the LCD

void InitAsciiBuffer() 
{
	GraphicBuffer ASCII_GRAPHIC_BUFFER;
	
	InitGraphicBuffer(&ASCII_GRAPHIC_BUFFER,LCD_WIDTH,LCD_HEIGHT,ONE_BIT,ASCII_Buffer); 
	ClearGraphicBuffer(&ASCII_GRAPHIC_BUFFER);
	DrawBitmap(0,0, IDB_ASCII,bitmap,&ASCII_GRAPHIC_BUFFER); //bitmap is an array built by pob-tools
}
	
/****************************************************************************************************************************
* PrintTextOnPobLCD : displays a string in the screen buffer
*
* row : LCD display Row of the first char
* col :  LCD display column of the first char
* string : string to display, Use 'sprintf' function to build a string including floats and intergers
* Screen_Bufffer : Screen buffer to display
*
* ASCII_Buffer is the buffer oh the fisrt 127 chars of the ASCII table. Each char is 8x8 pixels, it is possible to display 16 char per row and 8 columns
*****************************************************************************************************************************/

void PrintTextOnPobLCD(int row, int col, char *string, UInt8 *Screen_Buffer)
{
	int i,j,k=0; // i = ascii char starting buffer; j = 0 to 7 (8 times 8 points)

	while(*string) 
	{
		// starting point in the ASCII_Buffer of the char to display,128 (16charx8lines of pixels) is a complete row of text
		i = (string[0]/16)*128 + (string[0]%16); 	
		// display char on Screen_Buffer, 8 bytes
		for (j=0; j<8; j++) 
		{		
			// 8 intergers to define a bitmap of a char
			Screen_Buffer[col+row*128+k*16]=ASCII_Buffer[i+j*16];
			k++;
		}
		string++; 	
		k=0;
		// 1 byte right
		col+=1; 					
		if (col%16==0) 
		{ 			
			// Manages end of line and go to the next line on the left
			row++; 
			col=0;
			// Go to the top of the screen if the bottom is reached
			if (row%8 == 0) row=0; 	
		}
	}
}


