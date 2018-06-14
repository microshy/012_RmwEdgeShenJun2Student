///////////////////////////////////////////////////////////////////////////////////
// �������� �� 
//  1. ������������������˿�����������Ȩ������������ҵĿ�ļ�Ӧ�������     
//  2. ���ڱ������Ǹ��˿����ģ����ɱ���ش��ڸ��ָ�����ȱ�ݻ�������Ա��������
//     ����Ӧ���ڿ����о��ͽ�ѧ�С�
//  3. ����������Ӧ����ʵ������ʱ�����䵼�µĸ��ֲ�����������˸Ų�����
//     ��������ִ��󣬿�����ϵrenmingwu@mail.njust.edu.cn, renmingwu@sina.com
//  4. �����ַ����ļ����뱣����Щ����
//
///////////////////////////////////////////////////////////////////////////////////
// Caution:
// 1) If you do not get authorization from Mingwu Ren, 
//    this lib CAN NOT be used for commerce.
// 2) It is only developed by individual, so the errors can not be avioded. 
//    I strongly suggest that it should only be used for research and education.
// 3) If you find errors, you can tell me. E-Mail: renmingwu@mail.njust.edu.cn
//    renmingwu@sina.com,
//    you can call me: 13952033136 
// 4) If you redistribute this lib, please keep these words.
///////////////////////////////////////////////////////////////////////////////////
#ifndef RMW_CHAIN_FILTER_H
#define RMW_CHAIN_FILTER_H

void XsySetImageBoundary(BYTE *pBinImg,int width,int height,int color);
void RmwSetRGBImageBoundary(BYTE *pBinImg,int width,int height,int color);
int RmwTraceContour(BYTE *pImg,int width,int x,int y,BYTE *codebuf,int bufsize,bool isOut);
int RmwFillingContour( BYTE *pGryImg,int width,
					   int x0,int y0,BYTE *pCode,int N,
					   bool fillEdge,int nonc,int fillc
					 );
void RmwAreaFilter(BYTE *pBinImg,BYTE *pBufImg,int width,int height,BYTE *pResImg);
void RmwAreaAndPerimeter(BYTE *Code,int N,int *Area,int *Perimeter);

#endif
