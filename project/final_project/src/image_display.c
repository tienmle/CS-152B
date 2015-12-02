/* 
	image_display.c
	12/1/2015

	Functionality to write to the screen
*/

#include "image_display.h"
#include "xparamaters.h"
#include "charset.h"

#define CHAR_HEIGHT		24
#define CHAR_WIDTH		16
#define DEF_COLVAL		0x0
#define ASCII_OFFSET	32

#define BG_COLOR     0xffffffff//0xF0F04012
#define TEXT_COLOR   0x00000000

/*  
	SetPixel 

	Write to a single pixel at (x,y) with the specified pixel value
	
	The default value for the memory location is XPAR_DDR2_SDRAM_MPMC_BASEADDR,
	check if this breaks later if new peripherals are added.
*/
void SetPixel(u32 xVal, u32 yVal, u32 pixelVal) {

	XIO_Out32(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2*((xVal*2560) + yVal), pixelVal) 

}

/*
	GetPixel

	Read from a single pixel at (x,y) and sets the passed pointer to that value

*/
void GetPixel(u32 xVal, u32 yVal, u32* PixelVal) {

	*PixelVal = XIO_In32(XPAR_DDR2_SDRAM_MPMC_BASEADDR + 2 * ((xVal * 2560) + yVal))
}

/*
	FillScreen

	Fills the square from xStart,yStart to xEnd,yEnd with solid pixel color
*/
void FillScreen(u32 xStartVal, u32 yStartVal, u32 xEndVal, u32 yEndVal, u32 PixelVal) {

	u32 x, y;
	for (x = xStartVal; x <= xEndVal; x++) {
		for (y = yStartVal; y <= yEndVal; y++)
			SetPixel(x, y, PixelVal);
	}

}

/*
	WriteChar

	Function writes a particular character onto the screen using the character bitmap values

	* @param	InstancePtr is a pointer to the XTft instance.
	* @param	CharValue is the value of the ASCII character.
	* @param	ColStartVal is the value of the starting column. The valid
	*		values are 0 to (XTFT_DISPLAY_WIDTH - 1).
	* @param	RowStartVal is the value of the starting row. The valid
	*		values are 0 to (XTFT_DISPLAY_HEIGHT - 1).
	* @param	FgColor is the value with which the pixels will be filled
	*		to highlight the character.
	* @param	BgColor is the value with which the pixels will be filled
	*		with a different color from foreground.
*/

void WriteChar(u32 CharValue, u32 ColStartVal, u32 RowStartVal, u32 FgColor, u32 BgColor) {
	u32 RowIndex;
	u32 ColIndex;
	u32 PixelVal;
	u8 BitMapVal;

	/*
	* Gets the 12 bit value from the character array defined in
	* charcode.c file and regenerates the bitmap of that character.
	* It draws that character on screen by setting the pixel either
	* with the foreground or background color depending on
	* whether value is 1 or 0.
	*/

	for (RowIndex = 0; RowIndex < CHAR_HEIGHT; RowIndex++) {
		BitMapVal = VidChars[(u32) CharValue - ASCII_OFFSET][RowIndex / 2];
		for (ColIndex = 0; ColIndex < CHAR_WIDTH; ColIndex++) {
			if (BitMapVal & (1 << (CHAR_WIDTH / 2 - ColIndex / 2 - 1))) {
				PixelVal = FgColor;
			}
			else {
				PixelVal = BgColor;
			}

			SetPixel(ColStartVal + ColIndex, RowStartVal + RowIndex, PixelVal);
		}

	}

}

void WriteString(const u32 *CharValue, int startX, int startY) {
	int character = 0;
	while (*CharValue != 0) {
		WriteChar(*CharValue, startX + character, startY, TEXT_COLOR, BG_COLOR);
		CharValue++;
		character += 40;
}