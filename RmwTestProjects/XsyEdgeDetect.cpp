#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "RmwEdgeDetect.h"


/*//边界处理
void XsySetImageBoundary(BYTE *BinImg, int width, int height, BYTE Color)
{
	BYTE *pCur1, *pCur2;
	int x, y;

	for (x = 0, pCur1 = BinImg, pCur2 = BinImg + (height - 1L)*width; x<width; x++) *(pCur1++) = *(pCur2++) = Color;
	for (y = 0, pCur1 = BinImg, pCur2 = BinImg + width - 1; y<height; y++, pCur1 += width, pCur2 += width) *pCur1 = *pCur2 = Color;
}*/
//Prewitt法
void XsyGradientPrewitt(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {
	int x, y;
	int a = 3;
	int T0[3][3] = { 1,1,1,0,0,0,-1,-1,-1 };
	int T90[3][3] = { 1,0,-1,1,0,-1,1,0,-1 };
	int T45[3][3] = { 1,1,0,1,0,-1,0,-1,-1 };
	int T135[3][3] = { 0,1,1,-1,0,1,-1,-1,0 };
	int sum0, sum45, sum90, sum135;
	int i, j;
	BYTE *pGry, *pGr;
	XsySetImageBoundary(pGrImg, width, height, 0);
	for (i = a / 2; i < height - a / 2; i++) {
		pGry = pGryImg + a / 2 + i*width;
		pGr = pGrImg + a / 2 + i*width;
		for (j = a / 2; j < width - a / 2; pGry++, pGr++, j++) {
			sum0 = sum45 = sum90 = sum135 = 0;
			for (x = -a / 2; x < (a + 1) / 2; x++) {
				for (y = -a / 2; y < (a + 1) / 2; y++) {
					sum0 += *(pGry + x*width + y)*T0[a / 2 + x][a / 2 + y];
					sum45 += *(pGry + x*width + y)*T45[a / 2 + x][a / 2 + y];
					sum90 += *(pGry + x*width + y)*T90[a / 2 + x][a / 2 + y];
					sum135 += *(pGry + x*width + y)*T135[a / 2 + x][a / 2 + y];
				}
			}
			*pGr = min(255, max(max(abs(sum0), abs(sum45)), max(abs(sum90), abs(sum135))));
		}
	}
}
//shenjun
void XsyShenJun(BYTE *pGryImg, BYTE *pTmpImg, int width, int height, double alpha, BYTE *pResImg) {
	int i, x, y,ImgSize = width*height;
	double gLUT[512], *LUT;
	BYTE *cur, *pBuf1, *pBuf2, BLUT[256];

	alpha = max(0.01, min(0.99, alpha));
	// 1. step.1---------------------Shen Filter Image--------------------------------------//
	// init LUT
	for (i = 0; i<512; i++) gLUT[i] = alpha*(i - 256);//构造查找表
	LUT = gLUT + 256;
	// copy image
	//memcpy(pResImg, pGryImg, width*height);
	memcpy(pTmpImg, pGryImg, ImgSize);
	pBuf1 = pGryImg;
	pBuf2 = pTmpImg;
	for (y = 0; y < height; y++) {
		cur = pTmpImg + y*width + 1;//left
		for (x = 1; x < width; x++, cur++) {
			*cur = *(cur - 1) + LUT[*cur - *(cur - 1)];
		}
		cur = pTmpImg + y*width - 2;//right
		for (x = width - 1; x >= 0; x--, cur++) {
			*cur = *(cur + 1) + LUT[*cur - *(cur + 1)];
			if (y > 0) {//down
				*cur = *(cur - width) + LUT[*cur - *(cur - width)];
			}
		}
/*		if (y > 0) {//down
			cur = pTmpImg + y*width;
			for (x = 0; x < width; x++, cur++) {
				*cur = *(cur - width) + LUT[*cur - *(cur - width)];
			}
		}*/
	}
	for (y = height - 2; y >= 0; y--) {//up
		cur = pTmpImg + y*width;
		for (x = 0; x < width; x++, cur++) {
			*cur = *(cur + width) + LUT[*cur - *(cur + width)];
		}
	}
	//-----------------------------------------------------------
	cur = pResImg;
	for (i = 0; i < ImgSize; i++, pBuf1++, pBuf2++,cur++) {
		if (*pBuf1 > *pBuf2) *cur = 255;
		else *cur = 0;
	}
	for (y = 1; y < height - 1; y++) {
		cur = pResImg + y*width + 1;//left
		for (x = 1; x < width - 1; x++, cur++) {
			if (*cur) {
				if ((*(cur - 1) == 0) || (*(cur + 1) == 0) || (*(cur - width) == 0) || (*(cur + width) == 0)) {
					*cur = 128;
				}
			}
		}
	}
	for (i = 0; i<256; i++) BLUT[i] = 0;
	BLUT[128] = 255;
	for (cur = pResImg, i = 0; i < ImgSize; i++, cur++) *cur = BLUT[*cur];
	XsySetImageBoundary(pResImg, width, height, 0);
}

//边缘锐化
void XsyEdgSharp(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {
	int x, y, sum, cur;
	int a = 3, weight = 5;
	int T[3][3] = { 0,1,0,
		1,1,1,
		0,1,0 };
	int i, j,N=1;
	BYTE *pGry, *pGr;
	XsySetImageBoundary(pGrImg, width, height, 0);
	for (i = a / 2; i < height - a / 2; i++) {
		pGry = pGryImg + a / 2 + i*width;
		pGr = pGrImg + a / 2 + i*width;
		for (j = a / 2; j < width - a / 2; pGry++, pGr++, j++) {
			sum = 0;
			for (x = -a / 2; x < (a + 1) / 2; x++) {
				for (y = -a / 2; y < (a + 1) / 2; y++) {
					sum += *(pGry + x*width + y)*T[a / 2 + x][a / 2 + y];
				}
			}
			cur = sum / weight;
			*pGr = *pGry + N*(*pGry - cur);
		}
	}
}