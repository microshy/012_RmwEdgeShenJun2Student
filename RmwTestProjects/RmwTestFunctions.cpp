#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define OFFSETX static int offsetx[8]={1, 1, 0,-1,-1,-1, 0, 1}
#define OFFSETY static int offsety[8]={0,-1,-1,-1, 0, 1, 1, 1}

void RmwGetHistogram(BYTE *pGryImg,int width,int height,int *histogram)
{   
	int i;
	BYTE *pCur;
	
	// reset histogram
	for(i=0;i<256;i++) histogram[i]=0;
	// Get Histogam
	for(pCur=pGryImg;pCur<pGryImg+width*height;) histogram[*(pCur++)]++;
	return;
}

int RmwGetThresholdByRatio(int *Histogram,double wRatio)
{	int i;
	int sum,count;

	for(i=255,sum=0;i>=0;i--) sum+=Histogram[i];
	sum=(int)(sum*wRatio);
    for(i=255,count=0;i>=0;i--) 
	{ count+=Histogram[i];
	  if (count>=sum) break;
	}
	return i;
}

void RmwThreshold(BYTE *pGryImg,int width,int height,int thre,BYTE *pResImg)
{   
	BYTE LUT[256],*pRes,*pCol;
    int i,imgSize;

	// init LUT-look up table
	for(i=0;i<thre;i++) LUT[i]=0;
	for(i=thre;i<256;i++) LUT[i]=255;
	// Threshold
    pRes=pResImg;
	pCol=pGryImg;
	imgSize=width*height;
	for(i=0;i<imgSize;i++) *(pRes++)=LUT[*(pCol++)];
	//return
	return;
}

void RmwDrawGryRect(BYTE *pGryImg,int width,int height,int x1,int x2,int y1,int y2,int color)
{	
	int y,i;
	BYTE *p1,*p2;

	if (x1<0) x1=0;
	if (x1>width-1) x1=width-1;
	if (x2<0) x2=0;
	if (x2>width-1) x2=width-1;
	if (x1>x2) { i=x2; x2=x1; x1=i; }
	
	if (y1<0) y1=0;
	if (y1>height-1) y1=height-1;
	if (y2<0) y2=0;
	if (y2>height-1) y2=height-1;
	if (y1>y2) { i=y2; y2=y1; y1=i; }

	memset(pGryImg+y1*width+x1,color,x2-x1+1);
	memset(pGryImg+y2*width+x1,color,x2-x1+1);
	for (y=y1,p1=pGryImg+y1*width+x1,p2=pGryImg+y1*width+x2;y<=y2;y++,p1+=width,p2+=width)
	{	
		*(p1)=color;  
		*(p2)=color;
	}
	return;
}

void RmwRealAreaAndPerimeter(BYTE *code,int N,int *Area,int *Perimeter)
{
    int Label[8]={0,1,0,1,0,1,0,1};
	int PointKindLUT[8][8]={1,1,1,3,3,2,2,1,//0
    /*[inCode][outCode]*/   1,1,1,3,3,3,2,1,//1
    /*0-下边界   1-上边界*/ 2,2,2,0,0,0,0,2,//2
    /*2-无用边界 3-尖点*/   2,2,2,0,0,0,0,3,//3
                            3,2,2,0,0,0,0,3,//4
                            3,3,2,0,0,0,0,3,//5
                            1,1,1,2,2,2,2,1,//6
                            1,1,1,3,2,2,2,1 //7
	                      };
    int PrjY_SignLUT[3]={-1,1,0}; //符号表
    int Prj_YMend[3]={0,1,1}; //修正表
    int in_code,out_code,pointkind,i,s,y,N01[2];
	OFFSETX;OFFSETY;

	N01[0]=N01[1]=y=s=0;
	for(i=0;i<N;i++)
	{  	
		in_code=code[(i-1+N)%N];
		out_code=code[i];
		pointkind=PointKindLUT[in_code][out_code];
		if(pointkind==3) s+=1;
		else s+=PrjY_SignLUT[pointkind]*(y+Prj_YMend[pointkind]);
		y+=offsety[out_code];
		N01[Label[out_code]]++;
	}
    *Perimeter=(int)(N01[0]*1.0+N01[1]*sqrt(2.0)+0.5);
	*Area=abs(s);
	return;
}

void RmwContourRect(int x0,int y0,BYTE *pCode,int N,int *x1,int *x2,int *y1,int *y2)
{  
	int i;
    OFFSETX; OFFSETY;

	*y1=*y2=y0;
	*x1=*x2=x0; 
	for(i=0;i<N-1;i++)
	{ 
		x0=x0+offsetx[pCode[i]];
		y0=y0+offsety[pCode[i]];
		
		if (pCode[i]==pCode[i+1]) continue;

		if (x0>*x2) *x2=x0;	 //Rx
		else if (x0<*x1) *x1=x0; //Lx
		
		if (y0>*y2) *y2=y0;      //Dy
		else if (y0<*y1) *y1=y0;     //Uy    
    }
	return;
}
// Trace
int RmwTraceContour(BYTE *Img,int width,int x,int y,BYTE *codebuf,int bufsize,bool isOut)
{   //轮廓跟踪
	OFFSETX;OFFSETY;
    int firsttestcode[8]={7, 7, 1, 1, 3, 3, 5, 5};
    int offsetp[8];
    BYTE *pc0,*pci,*pc;
    int i,k,testcodei,curc,fc0,fck,codenum;

    for(i=0;i<8;i++) offsetp[i]=offsety[i]*width+offsetx[i];
	pc=pc0=Img+y*width+x; codenum=0;
	if (isOut) {*(pc-1)=1;curc=7;fc0=5;}
	else {curc=3;fc0=1;*(pc+1)=1;}
	do
	{   *pc=254;
		//for(i=0,testcodei=firsttestcode[curc];i<7;i=i+1,testcodei=(testcodei+1)%8)
		for(i=0,testcodei=firsttestcode[curc];i<7;i=i+1,testcodei=(testcodei+1)&0x07)
	    {  pci=pc+offsetp[testcodei];
           if (*pci<2) *pci=1;
		   else 
		   {  curc=testcodei;
			  if (codenum<bufsize-1) codebuf[codenum++]=testcodei;
		      if (pci==pc0)
			  {  
				 //for(k=0,fck=fc0; (fck!=(testcodei+4)%8)&&(k<7); k=k+1,fck=(fck+1)%8);
			     for(k=0,fck=fc0; (fck!=((testcodei+4)&0x07))&&(k<7); k=k+1,fck=((fck+1)&0x07));
                 //for(i=k+1,fck=(fck+1)%8; i<7; i=i+1,fck=(fck+1)%8)
                 for(i=k+1,fck=(fck+1)&0x07; i<7; i=i+1,fck=(fck+1)&0x07)
				 {  pci=pc0+offsetp[fck];
					if (*pci<2) *pci=1;
				    else
					{ curc=fck; 
					  if (codenum<bufsize-1)codebuf[codenum++]=fck; 
				      break;
					}
				 }
			  }
		      break;
		   }
		}
        pc=pci;
	}while(i<7);
    return(codenum);
} 

void RmwGetMaxRegion( BYTE *pBinImg,
			          BYTE *pImgBuf,
					  int width,
					  int height,
					  int *x1,int *x2,
					  int *y1,int *y2
				    )
{  
	int imgSize,i,y,x,length,Area,Perimeter; 
	BYTE *pBin,Cur,Pre;
	int maxArea;
	
    // step.1--------Init----------------------------------------//
	maxArea=0;
    imgSize = width*height;
	//step.2--------目标跟踪-------------------------------------//
	RmwDrawGryRect(pBinImg,width,height,0,width-1,0,height-1,0);
	for(y=1,pBin=pBinImg+y*width;y<height;y++)
	{
        for(x=0;x<width;x++,pBin++)
		{  
			Cur=*pBin;
			Pre=*(pBin-1);
			if (Cur==Pre) continue;
			// 链码跟踪 
			length=0;
			if ((Cur==255)&&(Pre<10))
			{
				length=RmwTraceContour(pBinImg,width,x,y,pImgBuf,imgSize,true);
				RmwRealAreaAndPerimeter(pImgBuf,length,&Area,&Perimeter);
				if (Area>maxArea)
				{
					RmwContourRect(x,y,pImgBuf,length,x1,x2,y1,y2);
					maxArea=Area;
				}
			}
			else if ((Cur==0)&&(Pre>250)) length=RmwTraceContour(pBinImg,width,x-1,y,pImgBuf,imgSize,false); 
		}
	}
	// step.3---------return-------------------------------------//
	return;
}
 
void RmwGetMaxBrightRegion( BYTE *pGryImg,
                        	BYTE *pBinImg,
							BYTE *pCodeImg,
                            int width,
					        int height,
					        int *x1,
							int *x2,
					        int *y1,
							int *y2
				         )
{

	int histogram[256],threshold;

	RmwGetHistogram(pGryImg,width,height,histogram);
    threshold=RmwGetThresholdByRatio(histogram,0.01);
    RmwThreshold(pGryImg,width,height,threshold,pBinImg);
	RmwGetMaxRegion(pBinImg,pCodeImg,width,height,x1,x2,y1,y2);
	return;
}



