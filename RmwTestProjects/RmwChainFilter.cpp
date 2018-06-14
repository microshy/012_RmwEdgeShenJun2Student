////////////////////////////////////////////////////////////////////////////////////////
//File Name : RmwChain.cpp  
//Version   : 1.0 
//Author    : Ren Ming Wu
//Date      : June-October,1999, 2005.05.18 
//Function  : Fast algorithms of contour tracing and filling for 8 bit gray image
//Reference : Proposed by Ren Ming Wu
/////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
 
///////////////////////////////////////////////////////////////////////////////////
//
//
//  表定义
//
//
///////////////////////////////////////////////////////////////////////////////////
#define OFFSETX static int offsetx[8]={1, 1, 0,-1,-1,-1, 0, 1}
#define OFFSETY static int offsety[8]={0,-1,-1,-1, 0, 1, 1, 1}

///////////////////////////////////////////////////////////////////////////////////
//
//
//  链码跟踪
//
//
///////////////////////////////////////////////////////////////////////////////////
void XsySetImageBoundary(BYTE *pBinImg,int width,int height,int color)
{	
	BYTE *pCur1,*pCur2;
	int y;

	memset(pBinImg,0,width);
	memset(pBinImg+(height-1L)*width,0,width);

	for( y=0,pCur1=pBinImg,pCur2=pBinImg+width-1;
		 y<height;
		 y++,pCur1+=width,pCur2+=width
	   )
	{
		*pCur1=*pCur2=color;
	}
	return;
}

void RmwRealAreaAndPerimeter(BYTE *pCode,int N,int *Area,int *Perimeter)
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
		in_code=pCode[(i-1+N)%N];
		out_code=pCode[i];
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

void RmwAreaAndPerimeter(BYTE *Code,int N,int *Area,int *Perimeter)
{  
	OFFSETX;OFFSETY;
   static int Label[8]={0,1,0,1,0,1,0,1};
   int i,c,y,N01[2];
   double area;
   
   area=N01[0]=N01[1]=y=0;
   for(i=0;i<N;i++){ c=Code[i];area+=offsetx[c]*(y+0.5*offsety[c]); y+=offsety[c];N01[Label[c]]++;}
   *Perimeter=(int)(N01[0]*1.0+N01[1]*sqrt(2.0)+0.5);
   *Area=(int)(fabs(area)+0.5+(*Perimeter)/2);
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
///////////////////////////////////////////////////////////////////////////////////
//
//
//  链码填充
//
//
///////////////////////////////////////////////////////////////////////////////////
int RmwFillingContour( BYTE *pGryImg,int width,
					   int x0,int y0,BYTE *pCode,int N,
					   bool fillEdge,int nonc,int fillc
					 )
{   int angle[8][8]={  0, 1, 2, 3, 4,-1,-1,-1,
                      -1, 0, 1, 2, 3, 4,-1,-2, 
                      -1,-1, 0, 1, 2, 3, 4,-1,
                      -1,-2,-1, 0, 1, 2, 3, 4,
                       4,-1,-1,-1, 0, 1, 2, 3,
                       3, 4,-1,-2,-1, 0, 1, 2,
                       2, 3, 4,-1,-1,-1, 0, 1,
                       1, 2, 3, 4,-1,-2,-1, 0
	               };            
	OFFSETX;OFFSETY;
	BYTE *pbegin,*pcur,*ptst,buff[4096],*data_buff=NULL;
    int i,offsetp[8],shiftc,direction,g;
	int used_color[256],k,startc,preCode;

	// step.0-----init,skipc and shiftc--------------------//
	pbegin=pGryImg+y0*width+x0;
	for(i=0;i<8;i++) offsetp[i]=offsety[i]*width+offsetx[i];
    // shiftc
    for(i=0;i<256;i++) used_color[i]=0;
	used_color[nonc]=used_color[fillc]=1;
	for(i=0,k=0;i<256;i++)
	{ 
		if (used_color[i]==0) k++;
		else k=0;
		if (k==5) { shiftc=i-2; break; }
	}
	for(i=-2;i<=2;i++) used_color[shiftc+i]=1;
	for(i=0;i<256;i++)
	{
		if (used_color[i]==0) { startc=i; break; }
	}
    // step.1-----backup ----------------------------------//
	if (!fillEdge)
	{   
		if (N<=4096) data_buff=buff;
	    else data_buff = new BYTE [N];
		if (data_buff)
		{
			for(i=0,pcur=pbegin;i<N;pcur+=offsetp[pCode[i]],i++) data_buff[i]=*pcur;
		}
	}
    // step.2-----sum offsety of reach and leave pCode------//
    for(i=0,pcur=pbegin;i<N;pcur+=offsetp[pCode[i]],i++) *pcur=shiftc;
 	for(i=0,direction=0,pcur=pbegin,preCode=pCode[N-1];i<N;pcur+=offsetp[pCode[i]],i++) 
	{	
		(*pcur)=(*pcur)+offsety[preCode]+offsety[pCode[i]];
		direction+=angle[preCode][pCode[i]];
		preCode=pCode[i];
	}
	direction/=8;
	// step.3-----classify contour points-----------------//
    for(i=0,pcur=pbegin;i<N;pcur+=offsetp[pCode[i]],i++) 
	{   
		g=*pcur;
		if ( (g==shiftc+1)||(g==shiftc+2) ) *pcur=startc;
		else if ( (g==shiftc-1)||(g==shiftc-2) ) *pcur=nonc;
	}
    // step.4-----filling interior------------------------//
    for(i=0,pcur=pbegin;i<N;pcur+=offsetp[pCode[i]],i++) 
	{   
		if (*pcur!=startc) continue;
	    ptst=pcur;
		while (*ptst!=nonc) 
		{ *ptst=fillc;
		  ptst+=direction; 
		} 
		*pcur=nonc; // avoid repeatly filling
	}
    // step.5-----filling boundary------------------------//
	if (!fillEdge)
	{   
		if (data_buff)
		{
			for(i=0,pcur=pbegin;i<N;pcur+=offsetp[pCode[i]],i++) *pcur=data_buff[i];
			if (N>4096) delete data_buff;
		}
	}
    else for(i=0,pcur=pbegin;i<N;pcur+=offsetp[pCode[i]],i++) *pcur=fillc;
    // step.6-----return----------//
	return direction;
}
///////////////////////////////////////////////////////////////////////////////////
//
//
//  滤波
//
//
///////////////////////////////////////////////////////////////////////////////////
void RmwAreaFilter(BYTE *pBinImg,BYTE *pBufImg,int width,int height,BYTE *pResImg)
{
	BYTE *pBin,cur,pre;
	int y,x,length,S,P; 

	memcpy(pResImg,pBinImg,width*height);
	XsySetImageBoundary(pBinImg,width,height,0);
	for(y=1,pBin=pBinImg+y*width;y<height;y++)
	{
        for(x=0;x<width;x++,pBin++)
		{  
			cur=*pBin;
			pre=*(pBin-1);
			if (cur==pre) continue;
			// 链码跟踪 
			length=0;
			if ((cur==255)&&(pre<10))
			{
				length=RmwTraceContour(pBinImg,width,x,y,pBufImg,width*height,true);
				//孤立点
				if (length<=3)
				{
					*(pResImg+y*width+x)=0;
				}
				//小
				RmwRealAreaAndPerimeter(pBufImg,length,&S,&P);
				if (S<=3) 
				{
					RmwFillingContour(pResImg,width,x,y,pBufImg,length,true,128,0);
				}
 			}
			else if ((cur==0)&&(pre>250))
			{
				length=RmwTraceContour(pBinImg,width,x-1,y,pBufImg,width*height,false); 
			}
		}
	}
	return;
}
