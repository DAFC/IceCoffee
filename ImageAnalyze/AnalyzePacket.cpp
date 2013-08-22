#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "OpenCVHeader.h"
#include "stdlib.h"
#include "AnalyzePacket.h"

using namespace System::IO;
using namespace System;

int packetData[4][24];
//char* filename;

//画像処理によるパケットの解析　引数　750x500の画像
void AnalyzePacketMain(IplImage* src_img){
	int wakuMargin,DiceSizeX,DiceSizeY,DiceMargin,BlockWidth,BlockHeight;
	//設定を取得
	readSettingFile(wakuMargin,DiceSizeX,DiceSizeY,DiceMargin,BlockWidth,BlockHeight);
	printf("wakuMargin = %d\n",wakuMargin);
	printf("DiceSizeX = %d\n", DiceSizeX);
	printf("DiceSizeY = %d\n", DiceSizeY);
	printf("DiceMargin = %d\n", DiceMargin);
	printf("BlockWidth = %d\n", BlockWidth);
	printf("BlockHeight = %d\n", BlockHeight);

	//四隅の画像用のメモリ確保
	IplImage* rightUp = cvCreateImage(cvSize(BlockWidth,BlockHeight),IPL_DEPTH_8U,1);			//右上
	IplImage* rightDown = cvCreateImage(cvSize(BlockWidth,BlockHeight),IPL_DEPTH_8U,1);		//右下
	IplImage* leftUp = cvCreateImage(cvSize(BlockWidth,BlockHeight),IPL_DEPTH_8U,1);			//左上
	IplImage* leftDown = cvCreateImage(cvSize(BlockWidth,BlockHeight),IPL_DEPTH_8U,1);		//左下
	IplImage* grayImage = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U,1);

	cvCvtColor(src_img,grayImage,CV_BGR2GRAY);

	//画像に作業領域をコピー
	//左上
	cvSetImageROI(grayImage,cvRect(wakuMargin,wakuMargin,BlockWidth,BlockHeight));
	cvCopy(grayImage,leftUp);
	cvResetImageROI(grayImage);
	//左下
	cvSetImageROI(grayImage,cvRect(wakuMargin,grayImage->height-(BlockHeight+wakuMargin),BlockWidth,BlockHeight));
	cvCopy(grayImage,leftDown);
	cvResetImageROI(grayImage);
	//右上
	cvSetImageROI(grayImage,cvRect(grayImage->width-(BlockWidth+wakuMargin),wakuMargin,BlockWidth,BlockHeight));
	cvCopy(grayImage,rightUp);
	cvResetImageROI(grayImage);
	//右下
	cvSetImageROI(grayImage,cvRect(grayImage->width-(BlockWidth+wakuMargin),grayImage->height-(BlockHeight+wakuMargin),BlockWidth,BlockHeight));
	cvCopy(grayImage,rightDown);
	cvResetImageROI(grayImage);
	    
	AnalyzePacketBlock(leftUp,1,DiceSizeX,DiceSizeY,DiceMargin);
	AnalyzePacketBlock(rightUp,2,DiceSizeX,DiceSizeY,DiceMargin);
	AnalyzePacketBlock(leftDown,3,DiceSizeX,DiceSizeY,DiceMargin);
	AnalyzePacketBlock(rightDown,4,DiceSizeX,DiceSizeY,DiceMargin);

	/*cvNamedWindow("rightUp",0);
	cvShowImage("rightUp",rightUp);
	cvNamedWindow("rightDown",0);
	cvShowImage("rightDown",rightDown);
	cvNamedWindow("leftUp",0);
	cvShowImage("leftUp",leftUp);
	cvNamedWindow("leftDown",0);
	cvShowImage("leftDown",leftDown);
	cvWaitKey(0);
	cvDestroyAllWindows();*/

	/*cvSaveImage("rightUp.jpg",rightUp);
	cvSaveImage("rightDown.jpg",rightUp);
	cvSaveImage("leftUp.jpg",leftUp);
	cvSaveImage("leftDown.jpg",leftDown);*/

	//処理用の画像解放
	cvReleaseImage(&rightUp);
	cvReleaseImage(&rightDown);
	cvReleaseImage(&leftUp);
	cvReleaseImage(&leftDown);

	Console::WriteLine("-------------------------------------------------");
	for(int block = 0; block < 4; block++){
		Console::WriteLine("blockNo : "+block);
		for(int index = 0; index < 12; index++){
			Console::Write(packetData[block][index]);
		}
		Console::WriteLine("");
		Console::WriteLine("-------------------------------------------------");
	}
}


//ブロックごとのパケットの解析　引数はブロックのグレーイメージ　ブロックナンバー　ダイス情報
void AnalyzePacketBlock(IplImage *src_img, int blockNo, int diceX, int diceY,int diceMargin){

	IplImage *DiceSector = cvCreateImage(cvSize(diceMargin,diceMargin),IPL_DEPTH_8U,1);
	int packetType = 0;
	char diceRoll[2];
	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 4; x++){
			cvSetImageROI(src_img,cvRect(x * diceX, y * diceY, diceMargin, diceMargin));
			cvCopy(src_img,DiceSector);
			cvResetImageROI(src_img);
			
			packetData[blockNo - 1][y*4+x] = AnalyzePacketSector(DiceSector,blockNo,x,y);
		}
	}
}

//ダイスの解析
int AnalyzePacketSector(IplImage* src_img, int blockNo, int idx, int idy){
	double min = 99999;
	int DiceResult = 0;
	double result = 0;
	int DiceRollNum = 0;
	CvMemStorage *storage;
	CvSeq *circles = 0;
	CvSeq *contours = 0;
	CvPoint2D32f* centerPoint = new CvPoint2D32f[6];

	IplImage *Dice[9];
	IplImage *binsrc = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U,1);
	IplImage *binsrcOpen = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U,1);
	IplImage *tmp_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U,1);
	IplConvKernel *element;

	Dice[0] = cvLoadImage("DiceInv\\1b.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Dice[1] = cvLoadImage("DiceInv\\2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Dice[2] = cvLoadImage("DiceInv\\3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Dice[3] = cvLoadImage("DiceInv\\4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Dice[4] = cvLoadImage("DiceInv\\5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Dice[5] = cvLoadImage("DiceInv\\6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Dice[6] = cvLoadImage("DiceInv\\2a.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Dice[7] = cvLoadImage("DiceInv\\3a.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Dice[8] = cvLoadImage("DiceInv\\6a.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	//StreamWriter^ sw = gcnew StreamWriter("DiceAnalyze.csv",true);
	Console::Write(" blockNo = "+blockNo);
	Console::Write(" x = "+ idx);
	Console::Write(" y = "+ idy);
	Console::WriteLine(" ");

	
	//平滑化
	//cvSmooth (src_img, src_img, CV_GAUSSIAN, 11, 11, 0, 0);
	cvThreshold(src_img, binsrc, 0, 255, CV_THRESH_BINARY_INV |CV_THRESH_OTSU);

	char filename[255] = {'\0'};
	_snprintf(filename,255,"FindDice\\%d%d%d.jpg",blockNo,idx,idy);
	cvSaveImage(filename,binsrc);
	
	//opening
	/*element = cvCreateStructuringElementEx (9, 9, 4, 4, CV_SHAPE_ELLIPSE, NULL);
	cvErode(binsrc,tmp_img,element,1);
	cvDilate(tmp_img,binsrcOpen,element,1);*/

	/*
	element = cvCreateStructuringElementEx (9, 9, 4, 4, CV_SHAPE_RECT, NULL);
	tmp_img = cvCloneImage(binsrc);
	cvMorphologyEx (binsrc, binsrcClosed, tmp_img, element, CV_MOP_OPEN, 1);
	binsrc = cvCloneImage(binsrcClosed);
	cvMorphologyEx (binsrc, binsrcClosed, tmp_img, element, CV_MOP_CLOSE, 1);*/

	storage = cvCreateMemStorage(0);
	
	//cvCanny(binsrc, tmp_img, 100.0, 200.0, 3);
	cvFindContours (binsrc, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	cvRectangle(tmp_img,cvPoint(0,0),cvPoint(src_img->width,src_img->height),CV_RGB(0,0,0),-1);
	CvSeq* workContours = 0;
	
	if(contours->total > 0){
		workContours = contours;
		int ContoursArea = 0;
		CvBox2D ellipse;
		while(1){
			ContoursArea = cvContourArea(workContours);
			Console::WriteLine("輪郭面積 : "+ContoursArea);
			if(workContours->total > 5 && ContoursArea > 30){
				ellipse = cvFitEllipse2 (workContours);
				ellipse.angle = 90.0 - ellipse.angle;
				if(MAX(ellipse.size.height,ellipse.size.width) / MIN(ellipse.size.height,ellipse.size.width) < 1.3){
					if(ContoursArea / (ellipse.size.height * ellipse.size.width) > 0.5){
						Console::Write("Elllipse Height : "+ellipse.size.height);
						Console::WriteLine(" Elllipse Width : "+ellipse.size.width);
						//cvDrawContours(tmp_img, workContours, CV_RGB (255, 255, 255), CV_RGB (255, 255, 255),0,-1);
						centerPoint[DiceRollNum] = ellipse.center;
						DiceRollNum++;
						cvEllipseBox (tmp_img, ellipse, CV_RGB (255, 255, 255), -1);
					}
				}
			}
			if(workContours->h_next != NULL){
				workContours = workContours->h_next;
			}else{
				break;
			}
		}
	}

	/*cvNamedWindow("tmp_img",0);
	cvShowImage("tmp_img",tmp_img);	
	cvNamedWindow("src_img",0);
	cvShowImage("src_img",src_img);	
	cvWaitKey();
	cvDestroyAllWindows();*/

	//ハフ変換により
	/*
	circles = cvHoughCircles(binsrc,storage,CV_HOUGH_GRADIENT,1, 1, 200, 10, 0, MAX(src_img->width,src_img->height));
	tmp_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U,1);
	float *p;
	Console::WriteLine("findCircleNumber : "+circles->total);
	cvRectangle(tmp_img,cvPoint(0,0),cvPoint(src_img->width,src_img->height),CV_RGB(0,0,0),-1);
	for(int index = 0; index < circles->total; ++index){
		p = (float*)cvGetSeqElem(circles,index);
		cvCircle (tmp_img, cvPoint (cvRound (p[0]), cvRound (p[1])), cvRound (p[2]), CV_RGB(255,255,255), -1);
		Console::WriteLine("p[0] : "+p[0] + " p[1] : " + p[1] + " p[2] : " + p[2]);
	}
    cvNamedWindow("tmp_img",0);
	cvShowImage("tmp_img",tmp_img);	
	cvWaitKey();
	cvDestroyAllWindows();*/

	//評価画像と形状マッチングし、一番近いものを選択する
	for(int diceType = 0; diceType < 6; diceType++){
		result = cvMatchShapes(tmp_img, Dice[diceType], CV_CONTOURS_MATCH_I1, 0);
		result += (double)(abs(diceType+1-DiceRollNum)*0.1);
		//sw->WriteLine(blockNo + "," + idx + "," + idy + "," + diceType + "," + result + ",");
		Console::WriteLine(blockNo + "," + idx + "," + idy + "," + diceType + "," + result + ",");
		if(result < min){
			min = result;
			DiceResult = diceType;
		}
	}
	DiceResult = AnalyzePacketSector_getDiceType(DiceResult,centerPoint);
	Console::WriteLine("白い部分の数 "+DiceRollNum);
	Console::WriteLine("DiceResult = "+DiceResult);
	/*cvNamedWindow("src_img",0);
	cvShowImage("src_img",tmp_img);
    cvNamedWindow("DiceResult_img",0);
	cvShowImage("DiceResult_img",Dice[DiceResult]);
	cvWaitKey();
	cvDestroyAllWindows();*/

	cvReleaseImage(&Dice[0]);
	cvReleaseImage(&Dice[1]);
	cvReleaseImage(&Dice[2]);
	cvReleaseImage(&Dice[3]);
	cvReleaseImage(&Dice[4]);
	cvReleaseImage(&Dice[5]);
	cvReleaseImage(&Dice[6]);
	cvReleaseImage(&Dice[7]);
	cvReleaseImage(&binsrc);
	cvReleaseImage(&binsrcOpen);
	cvReleaseImage(&tmp_img);
	return DiceResult;
	//sw->WriteLine(blockNo + "," + idx + "," + idy + ", Result ," + DiceResult);
	//sw->Close();
	
}

int AnalyzePacketSector_getDiceType(int DiceType, CvPoint2D32f* centerPoint){
	float x_sum = 0;
	float dx = 0;
	float dy = 0;
	switch (DiceType)
	{
		//目が2の時
		case 1 :
			x_sum = centerPoint[0].x - centerPoint[1].x;
			if(centerPoint[0].y - centerPoint[1].y > 0){
				if(x_sum < 0){
					return 6;
				}
			}else{
				if(x_sum > 0){
					return 6;
				}
			}
			break;
		//目が3の時
		case 2 :
			x_sum = centerPoint[0].x - centerPoint[1].x;
			if(centerPoint[0].y - centerPoint[1].y > 0){
				if(x_sum < 0){
					return 7;
				}
			}else{
				if(x_sum > 0){
					return 7;
				}
			}
			break;
		//目が6の時
		case 5 :
			dx = MAX(MAX(MAX(MAX(MAX(centerPoint[0].x,centerPoint[1].x),centerPoint[2].x),centerPoint[3].x),centerPoint[4].x),centerPoint[5].x) - MIN(MIN(MIN(MIN(MIN(centerPoint[0].x,centerPoint[1].x),centerPoint[2].x),centerPoint[3].x),centerPoint[4].x),centerPoint[5].x);
			dy = MAX(MAX(MAX(MAX(MAX(centerPoint[0].y,centerPoint[1].y),centerPoint[2].y),centerPoint[3].y),centerPoint[4].y),centerPoint[5].y) - MIN(MIN(MIN(MIN(MIN(centerPoint[0].y,centerPoint[1].y),centerPoint[2].y),centerPoint[3].y),centerPoint[4].y),centerPoint[5].y);
			//dxのほうが長ければ横向き、dyのほうが長ければ縦向き
			if(dx > dy){
				return 8;
			}
			break;
	}
	return DiceType;
}

//Setting.txtから必要情報を読み込み、整数値として取得
void readSettingFile(int& wakuMargin,int& DiceX, int& DiceY, int& DiceMargin, int& BlockWidth, int& BlockHeight){
   int settingValue[6];
   try
   {
      StreamReader^ sr = gcnew StreamReader( "Setting.txt" );
      try
      {
		 String^ line;
		 int idx = 0;
         while ( line = sr->ReadLine() )
         {
			 if(idx < 6){
				 settingValue[idx] = Convert::ToInt32(line->Split(' ')[0]);
				 idx++;
			 }
         }
      }
      finally
      {
		  wakuMargin = settingValue[0];
		  DiceX = settingValue[1];
		  DiceY = settingValue[2];
		  DiceMargin = settingValue[3];
		  BlockWidth = settingValue[4];
		  BlockHeight = settingValue[5];

          if ( sr )
            delete (IDisposable^)sr;
      }
   }
   catch ( Exception^ e ) 
   {
	  Console::WriteLine( "The file could not be read:" );
      Console::WriteLine( e->Message );
   }
}