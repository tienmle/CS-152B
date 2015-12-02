

#ifndef IMAGE_DISPLAY_H__
#define IMAGE_DISPLAY_H

#include <xio.h>
#include "xparamaters.h"


void SetPixel(u32 xVal, u32 yVal, u32 pixelVal);
void GetPixel(u32 xVal, u32 yVal, u32* PixelVal);
void FillScreen(u32 xStartVal, u32 yStartVal, u32 xEndVal, u32 yEndVal, u32 PixelVal);
void WriteChar(u32 CharValue, u32 ColStartVal, u32 RowStartVal, u32 FgColor, u32 BgColor);
void WriteString(const u32 *CharValue, int startX, int startY);


#endif