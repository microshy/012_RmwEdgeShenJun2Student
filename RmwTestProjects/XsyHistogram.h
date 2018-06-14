
#ifndef XSY_HISTOGRAM_H
#define XSY_HISTOGRAM_H

void XsyHistogram(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
void XsyHistMin(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
void XsyHistMax(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
void XsyHistMedi(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
void XsyHistBriCon(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
void XsyHistRegular(BYTE *pGryImg, int width, int height, BYTE *pGrImg);

#endif