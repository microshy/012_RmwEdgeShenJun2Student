#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "bmpFile.h"
#include "RmwEdgeDetect.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//     从彩色图像中选择一个位面
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
//     测试
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void test1()
{
	clock_t t1,t2;
	int width,height;

	BYTE *pRGBImg=RmwRead24BitBmpFile2Img("Dune.bmp",&width,&height);
	BYTE *pGryImg=new BYTE [width*height];
	BYTE *pResImg=new BYTE [width*height];
	BYTE *pTmpImg=new BYTE [width*height];
	
	RmwExtractOneChannelFromRGB(pRGBImg,width,height,0,pGryImg);
	RmwWriteByteImg2BmpFile(pGryImg,width,height,"Dune_Blue.bmp");

	RmwGradientGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"Dune_Gradient.bmp");

	RmwRobertGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"Dune_Robert.bmp");

	RmwSobelGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"Dune_Sobel.bmp");

	RmwGradientByPrewitt(pGryImg,width,height,1,1,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"Dune_Prewitt.bmp");

	RmwGradientByPrewitt(pGryImg,width,height,2,2,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"Dune_Prewitt5x5.bmp");


	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.3,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"Dune_Shenjun3.bmp");

	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.7,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"Dune_Shenjun7.bmp");

	delete pRGBImg;
	delete pGryImg;
	delete pResImg;
	delete pTmpImg;
	return;
}

void test2()
{
	clock_t t1,t2;
	int width,height;

	BYTE *pGryImg=RmwRead8BitBmpFile2Img("rice.bmp",&width,&height);
	BYTE *pResImg=new BYTE [width*height];
	BYTE *pTmpImg=new BYTE [width*height];
	
	RmwGradientGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Gradient.bmp");

	RmwRobertGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Robert.bmp");

	RmwSobelGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Sobel.bmp");

	RmwGradientByPrewitt(pGryImg,width,height,1,1,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Prewitt.bmp");

	RmwGradientByPrewitt(pGryImg,width,height,2,2,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Prewitt5x5.bmp");


	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.3,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Shenjun3.bmp");

	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.7,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Shenjun7.bmp");

	delete pGryImg;
	delete pResImg;
	delete pTmpImg;
	return;
}
 
void test3()
{
	clock_t t1,t2;
	int width,height;

	//BYTE *pGryImg=RmwRead8BitBmpFile2Img("rice.bmp",&width,&height);
	BYTE *pGryImg=RmwRead8BitBmpFile2Img("D:\\FJ4.bmp",&width,&height);
	BYTE *pResImg=new BYTE [width*height];
	BYTE *pTmpImg=new BYTE [width*height];

	RmwGradientGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\rice__Gradient.bmp");

	RmwRobertGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\rice__Robert.bmp");

	RmwSobelGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\rice__Sobel.bmp");

	RmwGradientByPrewitt(pGryImg,width,height,1,1,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\rice__Prewitt.bmp");

	RmwGradientByPrewitt(pGryImg,width,height,2,2,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\rice__Prewitt5x5.bmp");


	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.3,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\rice__Shenjun3.bmp");

	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.7,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\rice__Shenjun7.bmp");

	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.5,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\rice__Shenjun5.bmp");

	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.9,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\rice__Shenjun9.bmp");

	delete pGryImg;
	delete pResImg;
	delete pTmpImg;
	return;
}


void test4()
{
	clock_t t1,t2;
	int width,height;

	BYTE *pGryImg=RmwRead8BitBmpFile2Img("frame0110.bmp",&width,&height);
	BYTE *pResImg=new BYTE [width*height];
	BYTE *pTmpImg=new BYTE [width*height];

	RmwGradientGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Gradient.bmp");

	RmwRobertGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Robert.bmp");

	RmwSobelGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Sobel.bmp");

	RmwGradientByPrewitt(pGryImg,width,height,1,1,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Prewitt.bmp");

	RmwGradientByPrewitt(pGryImg,width,height,2,2,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Prewitt5x5.bmp");


	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.1,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Shenjun3.bmp");

	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.9,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"rice_Shenjun7.bmp");

	delete pGryImg;
	delete pResImg;
	delete pTmpImg;
	return;
}


void test5()
{
	clock_t t1,t2;
	int width,height;

	BYTE *pRGBImg=RmwRead24BitBmpFile2Img("D:\\D09.bmp",&width,&height);
	BYTE *pGryImg=new BYTE [width*height];
	BYTE *pResImg=new BYTE [width*height];
	BYTE *pTmpImg=new BYTE [width*height];
	BYTE *pPreWitt=new BYTE [width*height];
	
	RmwExtractOneChannelFromRGB(pRGBImg,width,height,0,pGryImg);
	RmwWriteByteImg2BmpFile(pGryImg,width,height,"D:\\Dune_Blue.bmp");

	RmwGradientGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\Dune_Gradient.bmp");

	RmwRobertGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\Dune_Robert.bmp");

	RmwSobelGrayImage(pGryImg,width,height,pResImg);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\Dune_Sobel.bmp");

	RmwGradientByPrewitt(pGryImg,width,height,1,1,pPreWitt);
	RmwWriteByteImg2BmpFile(pPreWitt,width,height,"D:\\Dune_Prewitt.bmp");

	RmwGradientByPrewitt(pGryImg,width,height,2,2,pPreWitt);
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\Dune_Prewitt5x5.bmp");


	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.10,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\Dune_Shenjun01.bmp");

	for(int i=0;i<width*height;i++)
	{
		if ( *(pPreWitt+i)<12*4)  *(pResImg+i)=0;
	}
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\Dune_Shenjun01_del.bmp");


	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.3,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\Dune_Shenjun03.bmp");

	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.5,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\Dune_Shenjun05.bmp");

	RmwShenJunEdge(pGryImg,pTmpImg,width,height,0.05,pResImg); 
	RmwWriteByteImg2BmpFile(pResImg,width,height,"D:\\Dune_Shenjun005.bmp");

	delete pRGBImg;
	delete pGryImg;
	delete pResImg;
	delete pPreWitt;
	delete pTmpImg;
	return;
}

void main()
{
	//test1();
	//test2();
	test3();
	//test4();
	//test5();
	return;
}

