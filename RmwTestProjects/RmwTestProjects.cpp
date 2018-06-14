// RmwTestProjects.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "bmpFile.h"
#include "RmwEdgeDetect.h"
#include "XsyEnhance.h"
#include "XsyHistogram.h"
#include "XsyFilter.h"
#include "XsyEdgeDetect.h"
#include "XsyRGB2Gry.h"
//#include "RmwFastSobelShenJun.h"

#include "RmwChainFilter.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//     �Ӳ�ɫͼ����ѡ��һ��λ��
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RmwExtractOneChannelFromRGB(BYTE *pRGBImg,
								 int width,int height,
								 int R2B0G1,BYTE *pResImg)
{   
	BYTE *pRgbCur,*pResCur;
    int i,ImgSize=width*height;


    pRgbCur=pRGBImg+R2B0G1;
	pResCur=pResImg;
	for(i=0;i<ImgSize;i++,pRgbCur+=3) *(pResCur++)=*pRgbCur;
	return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//     ����
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test_rice()
{
//	clock_t t1,t2;
	int width,height;

	BYTE *pRGBImg = RmwRead24BitBmpFile2Img("..//BmpOrgFile//sk.bmp", &width, &height);
//	BYTE *pGryImg=RmwRead8BitBmpFile2Img("..//BmpOrgFile//sk1_GRY.bmp",&width,&height);
//	BYTE *pGryImg=RmwRead8BitBmpFile2Img("..//BmpResFile//Lena_Filter_Over_Medi.bmp", &width, &height);
	BYTE *pResImg=new BYTE [width*height];
	BYTE *pTmpImg=new BYTE [width*height];
	
	//�˲���-��ֵ����˹����ֵ����С����󣬳�����ֵ
/*	XsyFilAvg(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//Lena_Filter_Average.bmp");
	XsyFilGauss(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//Lena_Filter_Gaussian.bmp");
	XsyFilMedi(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//Lena_Filter_Medium.bmp");
	XsyFilMin(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//Lena_Filter_Min.bmp");
	XsyFilMax(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//Lena_Filter_Max.bmp");
	XsyFilOverMedi(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//Lena_Filter_Over_Medi.bmp");*/

  //RGBת�Ҷ�ͼ��
/*	
	XsyRGBImg2GryImg0(pRGBImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpOrgFile//sk1_GRY.bmp");*/


	BYTE *pGryImg = RmwRead8BitBmpFile2Img("..//BmpOrgFile//1.bmp", &width, &height);

	//ֱ��ͼ-ֱ��ͼ���������ȶԱȶȣ����棬��Сֵ�����ֵ����ֵ
/*	XsyHistogram(pGryImg, width, height, pResImg);
	XsyHistBriCon(pGryImg, width, height, pResImg);
	XsyHistRegular(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//Lena_Regular.bmp");*/

	//ͼ����ǿ
/*	
	XsyPicEnhance(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//Lena_Enhance.bmp");*/

	//��Ե���-Prewitt��ShenJun���ݶȷ���Robert����Sobel������rmw�ĸо���ࣩ10
/**/	
	XsyGradientPrewitt(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//sk_Prewitt1.bmp");
	XsyShenJun(pGryImg, pTmpImg, width, height, 0.1, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//sk_Shenjun_3.bmp");

	//��Ե������ಿ��
/*
	RmwGradientByPrewitt(pGryImg,width,height,1,1,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"..//BmpResFile//Lena_Prewitt.bmp");
	RmwGradientGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"..//BmpResFile//Lena_Gradient.bmp");

	RmwRobertGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"..//BmpResFile//Lena_Robert.bmp");

	RmwSobelGrayImage(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"..//BmpResFile//Lena_Sobel.bmp");
	
	RmwGradientByPrewitt(pGryImg,width,height,2,2,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"..//BmpResFile//Lena_Prewitt5x5.bmp");

	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.3,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"..//BmpResFile//Lena_Shenjun3.bmp");*/

	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.7,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"..//BmpResFile//Lena_Shenjun7.bmp");

	//��Ե��
/*	XsyEdgSharp(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//Lena_Edge_Sharpen.bmp");*/

	//clock
/*	t1=clock();
    for(int k=0;k<100;k++)
	{
		RmwShenJunEdge(pGryImg, pTmpImg, width, height, 0.3, pResImg);
	}
	t2=clock();
    printf("\nRmwShenJunEdge()=%d ms ",t2-t1);
	 
	t1=clock();
	for(int k=0;k<100;k++)
	{
		XsyShenJun(pGryImg, pTmpImg, width, height, 0.3, pResImg);
	}
	t2=clock();
    printf("\nXsyShenJun()=%d ms ",t2-t1);

	RmwShenJunEdgeFast( pGryImg,pTmpImg,width,height,0.7,12,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"..//BmpResFile//rice_Shenjun7_12.bmp");

	RmwShenJunEdgeFast( pGryImg,pTmpImg,width,height,0.3,20,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"..//BmpResFile//rice_Shenjun7_20.bmp");*/

	
	delete pGryImg;
	delete pRGBImg;	
	delete pResImg;
	delete pTmpImg;

//	printf("\nPress any key to exit!");

//	getchar();

	return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//     main()
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{
	//	clock_t t1,t2;
	int width, height;

//	BYTE *pRGBImg = RmwRead24BitBmpFile2Img("..//BmpOrgFile//sk.bmp", &width, &height);
	BYTE *pGryImg=RmwRead8BitBmpFile2Img("..//BmpOrgFile//sk1_GRY.bmp",&width,&height);
//	BYTE *pGryImg=RmwRead8BitBmpFile2Img("..//BmpResFile//Lena_Filter_Over_Medi.bmp", &width, &height);
	BYTE *pResImg = new BYTE[width*height];
	BYTE *pTmpImg = new BYTE[width*height];

	XsyGradientPrewitt(pGryImg, width, height, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//sk_Prewitt1.bmp");
	XsyShenJun(pGryImg, pTmpImg, width, height, 0.1, pResImg);
	RmwWriteByteImg2BmpFile(pResImg, width, height, "..//BmpResFile//sk_Shenjun_3.bmp");

	delete pGryImg;
	delete pRGBImg;
	delete pResImg;
	delete pTmpImg;

	getchar();
	
 	return 0;
}


