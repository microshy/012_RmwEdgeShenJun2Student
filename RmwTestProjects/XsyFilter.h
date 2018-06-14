#ifndef XSY_FILTER_H
#define XSY_FILTER_H

void XsyFilAvg(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
void XsyFilGauss(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
void XsyFilMedi(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
void XsyFilMin(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
void XsyFilMax(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
void XsyFilOverMedi(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
void XsyFilAbst(BYTE *pGryImg,BYTE *pTmpImg,int width,int height,BYTE *pResImg);
void XsyFil2(BYTE *pGryImg, int width, int height, BYTE *pGrImg);

#endif // XSY_FIL_AVG

