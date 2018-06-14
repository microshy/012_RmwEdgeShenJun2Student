#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "bmpFile.h"

void XsyRGBImg2GryImg0(BYTE *pRGBImg, int width, int height, BYTE *pGryImg)
{
	BYTE *pRGB, *pGry, *pEnd = pRGBImg + 3 * width*height;
	double LUTR[256], LUTG[256], LUTB[256], gry;
	//double LUTX[256];
	int i;
	for (i = 0; i<256; i++)
	{
		//LUTX[i] = 0;
		LUTR[i] = i*0.114; //B
		LUTG[i] = i*0.587; //G
		LUTB[i] = i*0.299; //R
/*		LUTR[i] = i*0; //B
		LUTG[i] = i*0; //G
		LUTB[i] = i*1; //R*/
	}
	for (pRGB = pRGBImg, pGry = pGryImg; pRGB<pEnd;)
	{
		//gry = 0 * LUTX[*(pRGB++)];
		gry = LUTB[*(pRGB++)];
		gry += LUTG[*(pRGB++)];
		gry += LUTR[*(pRGB++)];
		*(pGry++) = (int)(gry);
	}
	return;

}

void XsyRGBImg2GryImg1(BYTE *pRGBImg, int width, int height, BYTE *pGryImg)
{
	BYTE *pRGB, *pGry, *pEnd = pRGBImg + 3 * width*height;
	double LUTR[256], LUTG[256], LUTB[256], gry;
	int i;

	for (i = 0; i<256; i++)
	{
		LUTR[i] = 0.299*i;
		LUTG[i] = 0.587*i;
		LUTB[i] = 0.114*i;
	}
	for (pRGB = pRGBImg, pGry = pGryImg; pRGB<pEnd;)
	{
		gry = LUTB[*(pRGB++)];
		gry += LUTG[*(pRGB++)];
		gry += LUTR[*(pRGB++)];
		*(pGry++) = (int)(gry);
	}
	return;
}

void XsyRGBImg2GryImg2(BYTE *pRGBImg, int width, int height, BYTE *pGryImg)
{
	BYTE *pRGB, *pGry, *pEnd = pRGBImg + 3 * width*height;
	int LUTR[256], LUTG[256], LUTB[256];
	int i, gry;

	for (i = 0; i<256; i++)
	{
		LUTR[i] = (int)(0.299*i * 1000);
		LUTG[i] = (int)(0.587*i * 1000);
		LUTB[i] = (int)(0.114*i * 1000);
	}
	for (pRGB = pRGBImg, pGry = pGryImg; pRGB<pEnd;)
	{
		gry = LUTB[*(pRGB++)];
		gry += LUTG[*(pRGB++)];
		gry += LUTR[*(pRGB++)];
		*(pGry++) = gry / 1000;
	}
	return;
}

void XsyRGBImg2GryImg3(BYTE *pRGBImg, int width, int height, BYTE *pGryImg)
{
	BYTE *pRGB, *pGry, *pEnd = pRGBImg + 3 * width*height;
	int LUTR[256], LUTG[256], LUTB[256];
	int i, gry;

	for (i = 0; i<256; i++)
	{
		LUTR[i] = (int)(0.299*i * 1024);
		LUTG[i] = (int)(0.587*i * 1024);
		LUTB[i] = (int)(0.114*i * 1024);
	}
	for (pRGB = pRGBImg, pGry = pGryImg; pRGB<pEnd;)
	{
		gry = LUTB[*(pRGB++)];
		gry += LUTG[*(pRGB++)];
		gry += LUTR[*(pRGB++)];
		*(pGry++) = gry >> 10;
	}
	return;
}