#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "RmwEdgeDetect.h"


void XsyFilAvg(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {
	int x, y, sum;
	int a = 3, weight = 5;
	int T[3][3] = { 0,1,0,
					1,1,1,
					0,1,0 };
	int i, j;
	BYTE *pGry, *pGr;
	
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
			*pGr = sum / weight;
		}
	}
	XsySetImageBoundary(pGrImg, width, height, 0);
}

void XsyFilGauss(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {
	float pi = 3.1415926;
	float sigma = 2.3;//7/3
	float p[15];

	int x, y, sum;
	int i, j;
	int a = 15, weight = 2;
	float T[15][15];
	BYTE *pGry, *pGr;
	for (i = 0; i < 15; i++) {
		j = i - 7;
		p[i] = (1 / sqrt(2 * pi*sigma *sigma))*exp(-j*j/ (2 * sigma *sigma));
		printf("%f\n", p[i]);
	}
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			if (j == a / 2) {
				T[i][j] = p[i];
			}
			else if (i == a / 2) {
				T[i][j] = p[j];
			}
			else T[i][j] = 0;
			//printf("%f\n", T[i][j]);
		}
	}
	
	for (i = a/2; i < height-a / 2; i++) {
		pGry = pGryImg + i*width+a / 2;
		pGr = pGrImg + i*width+a / 2;
		for (j = a / 2; j < width-a / 2; pGry++, pGr++, j++) {
			sum = 0;
			for (x = -a / 2; x < (a + 1) / 2; x++) {
				for (y = -a / 2; y < (a + 1) / 2; y++) {
					sum += *(pGry + x*width + y)*T[a / 2 + x][a / 2 + y];
				}
			}
			*pGr = sum / weight;
		}
	}
	XsySetImageBoundary(pGrImg, width, height, 0);
}

void XsyFilMedi(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {
	int sum;
	int i, j, x, y, g;
	BYTE *pGry, *pGr;
	unsigned long hist[256];
	int a = 3;
	//采用a*a的窗口,若要采用1*a的窗口则只需将x循环语句注释即可
	XsySetImageBoundary(pGrImg, width, height, 0);

	for (i = a / 2; i < height- a / 2; i++) {
		pGry = pGryImg + a / 2 + i*width;
		pGr = pGrImg + a / 2 + i*width;
		for (j = a / 2; j < width - a / 2; pGry++, pGr++, j++) {
			memset(hist, 0, sizeof(unsigned long) * 256);//初始化直方图
			for (x = -a / 2; x < (a + 1) / 2; x++) {
				for (y = -a / 2; y < (a + 1) / 2; y++) {
					hist[*(pGry+x*width+y)]++;
				}				
			}
			for (g = sum = 0; g < 256; g++) {
				sum += hist[g];
				if (sum >= a*a / 2)break;
			}
			*pGr = g;
		}
	}
}

void XsyFilMin(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {
	int sum;
	int i, j, x, y, g;
	BYTE *pGry, *pGr;
	unsigned long hist[256];
	int a = 13;
	//采用a*a的窗口,若要采用1*a的窗口则只需将x循环语句注释即可

	
/**/	
	for (i = a / 2; i < height - a / 2; i++) {
		pGry = pGryImg + a / 2 + i*width;
		pGr = pGrImg + a / 2 + i*width;
		for (j = a / 2; j < width - a / 2; pGry++, pGr++, j++) {
			memset(hist, 0, sizeof(unsigned long) * 256);//初始化直方图
			for (x = -a / 2; x < (a + 1) / 2; x++) {
				for (y = -a / 2; y < (a + 1) / 2; y++) {
					hist[*(pGry + x*width + y)]++;
				}
			}
			for (g = 0; g < 256; g++) {
				if (hist[g])break;
			}
			*pGr = g;
		}
	}
	XsySetImageBoundary(pGrImg, width, height, 0);
}

void XsyFilMax(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {
	int sum;
	int i, j, x, y, g;
	BYTE *pGry, *pGr;
	unsigned long hist[256];
	int a = 3;
	//采用a*a的窗口,若要采用1*a的窗口则只需将x循环语句注释即可
	XsySetImageBoundary(pGrImg, width, height, 0);

	for (i = a / 2; i < height - a / 2; i++) {
		pGry = pGryImg + a / 2 + i*width;
		pGr = pGrImg + a / 2 + i*width;
		for (j = a / 2; j < width - a / 2; pGry++, pGr++, j++) {
			memset(hist, 0, sizeof(unsigned long) * 256);//初始化直方图
			for (x = -a / 2; x < (a + 1) / 2; x++) {
				for (y = -a / 2; y < (a + 1) / 2; y++) {
					hist[*(pGry + x*width + y)]++;
				}
			}
			for (g = 255; g >=0; g--) {
				if (hist[g])break;
			}
			*pGr = g;
		}
	}
}

void XsyFilOverMedi(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {
	int sum;
	int i, j, x, y, g, cur;
	BYTE *pGry, *pGr;
	unsigned long hist[256];
	int a = 3;
	int t = 3;
	//采用a*a的窗口,若要采用1*a的窗口则只需将x循环语句注释即可
	XsySetImageBoundary(pGrImg, width, height, 0);

	for (i = a / 2; i < height - a / 2; i++) {
		pGry = pGryImg + a / 2 + i*width;
		pGr = pGrImg + a / 2 + i*width;
		for (j = a / 2; j < width - a / 2; pGry++, pGr++, j++) {
			memset(hist, 0, sizeof(unsigned long) * 256);//初始化直方图
			for (x = -a / 2; x < (a + 1) / 2; x++) {
				for (y = -a / 2; y < (a + 1) / 2; y++) {
					hist[*(pGry + x*width + y)]++;
				}
			}
			for (g = sum = 0; g < 256; g++) {
				sum += hist[g];
				if (sum >= a*a / 2)break;
			}
			cur = g;//超限部分代码如下，其他滤波也可用这种形式的超限算法。
			if (abs(*pGry - g) < t) {
				*pGr = *pGry;
			}
			else {
				*pGr = g;
			}
		}
	}
}

void XsyFilAbst(BYTE *pGryImg, BYTE *pTmpImg, int width, int height, BYTE *pGrImg) {
	BYTE *pGry, *pTmp, *pGr;
	int ImgSize = width*height;
	int i;
	
	for (pGry = pGryImg, pTmp = pTmpImg, pGr = pGrImg, i = 0; i < ImgSize; pGry++, pTmp++, pGr++, i++) {
		*pGr = *pGry - *pTmp;
	}
	XsySetImageBoundary(pGrImg, width, height, 0);
}

void XsyFil2(BYTE *pGryImg, int width, int height, BYTE *pGrImg) {
	int LUT[256];
	BYTE *pGry, *pGr;;
	int i,T=75;
	int ImgSize = width*height;
	for (i = 0; i < 256; i++) {
		if (i < T)LUT[i] = 0;
		else LUT[i] = 255;
	}
	XsySetImageBoundary(pGrImg, width, height, 0);
	for (pGry = pGryImg, pGr = pGrImg, i = 0; i < ImgSize; pGry++, pGr++, i++) {
		*pGr = LUT[*pGry];
	}
	XsySetImageBoundary(pGrImg, width, height, 0);
}