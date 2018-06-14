#ifndef XSY_EDGE_DETECT_H
#define XSY_EDGE_DETECT_H

	//void XsySetImageBoundary(BYTE *BinImg, int width, int height, BYTE Color);
	//void RmwGradientGrayImage(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
	//void RmwRobertGrayImage(BYTE *pGryImg, int width, int height, BYTE *pRbImg);
	//void RmwSobelGrayImage(BYTE *pGryImg, int width, int height, BYTE *pSbImg);
	void XsyShenJun(BYTE *pGryImg, BYTE *pTmpImg, int width, int height, double alpha, BYTE *pResImg);
	void XsyGradientPrewitt(BYTE *pGryImg, int width, int height, BYTE *pGrImg);
	void XsyEdgSharp(BYTE *pGryImg, int width, int height, BYTE *pGrImg);

#endif#pragma once
