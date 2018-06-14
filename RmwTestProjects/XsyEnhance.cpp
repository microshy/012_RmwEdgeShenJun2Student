#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "RmwEdgeDetect.h"

void XsyPicEnhance(BYTE *pGryImg, int width, int height, BYTE *pGrImg)
{
	int LUT[256];
	int i, g, ImgSize = width*height;
	BYTE *pGry, *pGr;
	XsySetImageBoundary(pGrImg, width, height, 0);
	for (g = 0; g < 256; g++) {
		LUT[g] = max(min(g + 30, 255), 0);
	}
	for (i = 0, pGry = pGryImg, pGr = pGrImg; i < ImgSize; i++, pGry ++, pGr ++) {
		*pGr = LUT[*pGry];
	}
}