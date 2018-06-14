#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "RmwEdgeDetect.h"

void XsyHistogram(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {//直方图输出
	int i, g, ImgSize = width*height;
	BYTE *pGry, *pGr;
	unsigned long hist[256];

	memset(hist, 0, sizeof(unsigned long) * 256);
	XsySetImageBoundary(pGrImg, width, height, 0);

	for (i = 0, pGry = pGryImg; i < ImgSize; i++, pGry++) {
		hist[*pGry]++;
	}
	for (g = 0; g < 256; g++) {
		printf("hist[%d]=%u\n", g, hist[g]);
	}
}

void XsyHistMin(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {	//求最小亮度
	int minGray;
	int i, g, ImgSize = width*height;
	BYTE *pGry, *pGr;
	unsigned long hist[256];

	memset(hist, 0, sizeof(unsigned long) * 256);
	XsySetImageBoundary(pGrImg, width, height, 0);

	for (i = 0, pGry = pGryImg; i < ImgSize; i++, pGry++) {
		hist[*pGry]++;
	}

	for (g = 0; g < 256; g++) {
		if (hist[g]) break;
	}
	minGray = g;

	printf("mingray=%d\n", minGray);
}

void XsyHistMax(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {	//求最大亮度
	int maxGray;
	int i, g, ImgSize = width*height;
	BYTE *pGry, *pGr;
	unsigned long hist[256];

	memset(hist, 0, sizeof(unsigned long) * 256);
	XsySetImageBoundary(pGrImg, width, height, 0);

	for (i = 0, pGry = pGryImg; i < ImgSize; i++, pGry++) {
		hist[*pGry]++;
	}
	for (g = 255; g >= 0; g--) {
		if (hist[g]) break;
	}
	maxGray = g;

	printf("maxgray=%d\n", maxGray);
}

void XsyHistMedi(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {	//求亮度中值
	int sum, mediGray;
	int i, g, ImgSize = width*height;
	BYTE *pGry, *pGr;
	unsigned long hist[256];

	memset(hist, 0, sizeof(unsigned long) * 256);
	XsySetImageBoundary(pGrImg, width, height, 0);

	for (i = 0, pGry = pGryImg; i < ImgSize; i++, pGry++) {
		hist[*pGry]++;
	}
	for (g = sum = 0; g < 256; g++) {
		sum += hist[g];
		if (sum >= ImgSize*0.5)break;
	}
	mediGray = g;

	printf("medigray=%d\n", mediGray);
}

void XsyHistBriCon(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {	//求亮度和对比度
	double sum,brightness,contrast;
	int i, g, ImgSize = width*height;
	BYTE *pGry, *pGr;
	unsigned long hist[256];

	memset(hist, 0, sizeof(unsigned long) * 256);
	XsySetImageBoundary(pGrImg, width, height, 0);

	for (i = 0, pGry = pGryImg; i < ImgSize; i++, pGry++) {
		hist[*pGry]++;
	}
	for (g = sum = 0; g < 256; g++) {
		sum += g*hist[g];
	}
	brightness = sum / ImgSize;
	for (g = 0, sum = 0; g < 256; g++) {
		sum += (g - brightness)*(g - brightness)*hist[g];
	}
	contrast = sqrt(sum / ImgSize);
	
	printf("brightness=%f\n", brightness);
	printf("contrast=%f\n", contrast);
}

void XsyHistRegular(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {
	int sum,LUT[256];//累计函数
	int i, g, ImgSize = width*height;
	BYTE *pGry, *pGr;
	unsigned long hist[256];

	memset(hist, 0, sizeof(unsigned long) * 256);
	XsySetImageBoundary(pGrImg, width, height, 0);

	for (i = 0, pGry = pGryImg; i < ImgSize; i++, pGry++) {
		hist[*pGry]++;
	}

	for (g = 0, sum = 0; g < 256; g++) {
		sum += hist[g];
		LUT[g] = 255 * sum / ImgSize;
	}

	for (i = 0, pGry = pGryImg, pGr = pGrImg; i < ImgSize; i++, pGry++, pGr++) {
		*pGr = LUT[*pGry];
	}
}