#include <opencv2/opencv.hpp>
#include "OpenCVheader.h"

IplImage dst_Img;

void getGammaImage(IplImage *src_img, IplImage *dst_img, int gamma);
extern IplImage* FindPacketMain(IplImage *src_img);
extern void AnalyzePacketMain(IplImage* src_img);


int main(int argc, char **argv)
{
	IplImage *src_Img;
	IplImage *gamma_correction_Img;
	IplImage *packet_Img;
	char packetData[4][24];

	//元画像の読み込み
	if(argc > 1){
		src_Img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
	}else{
		src_Img = cvLoadImage("test.jpg", CV_LOAD_IMAGE_COLOR);
	}
	//元ファイルがなかったら終了
	if(src_Img == 0){
		return -1;	
	}
	gamma_correction_Img = cvCloneImage(src_Img);
	getGammaImage(src_Img,gamma_correction_Img,2);
    //パケット対象部分の抽出
	packet_Img = FindPacketMain(gamma_correction_Img);
	AnalyzePacketMain(packet_Img);
	cvNamedWindow("packetImage",1);
	cvShowImage("packetImage",packet_Img);
	cvWaitKey();
	cvDestroyAllWindows();
	//メモリの解放
	cvReleaseImage(&packet_Img);
	cvReleaseImage(&gamma_correction_Img);
	cvReleaseImage(&src_Img);
}

//画像のガンマ補正　gammaの値を指定して調整する.
void getGammaImage(IplImage *src_img, IplImage *dst_img, int gamma){
	int i;  
    uchar LUT[256];  
              
    //ガンマ補正テーブルの作成  
    for (i = 0; i < 256; i++){  
        LUT[i] = (int)(pow((double)i / 255.0, 1.0 / gamma) * 255.0);  
    }  
  
    //CvMatへ変換  
    CvMat lut_mat = cvMat(1, 256, CV_8UC1, LUT);  
  
    //ルックアップテーブル変換  
    cvLUT(src_img, dst_img, &lut_mat);
}