#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "OpenCVHeader.h"
#include "FindPacket.h"

IplImage* FindPacketMain(IplImage* src_img){
	IplImage* bin_img;
	IplImage* affined_img;
	bin_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);

	//変形後の画像サイズは　750 x 500 pixel とする。
	affined_img = cvCreateImage(cvSize(750,500), IPL_DEPTH_8U, 3);
	
	//枠の抽出
	bin_img = FindPacketMain_useGetExtentionImage_Version(src_img);

/*	cvNamedWindow("bin_img",0);
	cvShowImage("bin_img",bin_img);
	cvWaitKey(0);
	cvDestroyAllWindows();*/

	//輪郭の抽出、直線近似
	CvPoint p[4];
	CvPoint p2[4];
	findRectangle(bin_img,p);
	sortPoint(p,p2);
	for(int x = 0; x < 4; x++){
		printf("頂点 X = %d, Y = %d\n", p2[x].x, p2[x].y);
	}

	affined_img = getAffinedImage(src_img,p2);

	//検出した長方形を描画
	cvDrawLine(src_img,p2[0],p2[1],CV_RGB(255,0,0),5);
	cvDrawLine(src_img,p2[1],p2[2],CV_RGB(255,0,0),5);
	cvDrawLine(src_img,p2[2],p2[3],CV_RGB(255,0,0),5);
	cvDrawLine(src_img,p2[3],p2[0],CV_RGB(255,0,0),5);

	printf("回転角度1-2　%f Rad\n",GetAngle(p2[1],p2[2]));
	printf("回転角度2-3　%f Rad\n",GetAngle(p2[2],p2[3]));
	printf("回転角度3-4　%f Rad\n",GetAngle(p2[3],p2[4]));
	printf("回転角度4-1　%f Rad\n",GetAngle(p2[4],p2[1]));
	
	/*cvNamedWindow("affined_img",0);
	cvShowImage("affined_img",affined_img);

	cvNamedWindow("src_img",0);
	cvShowImage("src_img",src_img);

	cvWaitKey(0);
	cvDestroyAllWindows();*/
	//cvSaveImage("DetectPacketWaku.jpg",src_img);
	cvSaveImage("ExtractPacketImage.jpg",affined_img);

	//画像メモリの解放
	cvReleaseImage(&bin_img);

	//歪みを補正した画像をリターンする
	return affined_img;
}

//H S V の内、一つ画像を使い枠の抽出　ボツ
IplImage* FindPacketMain_useOneBinImage_version(IplImage *src_img){
	IplImage *HSV_Img;
//	IplImage *gray_img;
	IplImage *bin_img;
	IplImage *H_img;
	IplImage *S_img;
	IplImage *V_img;
	IplImage *H_bin;
	IplImage *S_bin;
	IplImage *V_bin;
	IplImage *tmp_img;
//	IplImage *dst_img;

	HSV_Img = cvCreateImage(cvGetSize(src_img), src_img->depth, src_img->nChannels);
//	gray_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	bin_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	tmp_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	H_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	S_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	V_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	H_bin = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	S_bin = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	V_bin = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);	

	cvCvtColor(src_img,HSV_Img,CV_BGR2HSV);
	cvSplit(HSV_Img,H_img,S_img,V_img,NULL);

	//HSV　各2値化画像を保存
	cvSaveImage("H_img.jpg",H_img);
	cvSaveImage("S_img.jpg",S_img);
	cvSaveImage("V_img.jpg",V_img);

	cvThreshold(V_img,bin_img,0,255,CV_THRESH_BINARY | CV_THRESH_OTSU);

	cvSaveImage("bin_img.jpg",bin_img);
	cvWaitKey (0);

	//画像メモリの解放
	cvReleaseImage(&bin_img);
	cvReleaseImage(&H_img);
	cvReleaseImage(&S_img);
	cvReleaseImage(&V_img);
	cvReleaseImage(&H_bin);
	cvReleaseImage(&S_bin);
	cvReleaseImage(&V_bin);
	cvReleaseImage(&tmp_img);

	//リターン
	return bin_img;
}

//HSVに分離し、指定の色を取るコード　採用
IplImage* FindPacketMain_useGetExtentionImage_Version(IplImage *src_img){
	IplImage *HSV_Img;
//	IplImage *gray_img;
	IplImage *bin_img;
	IplImage *H_img;
	IplImage *S_img;
	IplImage *V_img;
	IplImage *H_bin;
	IplImage *S_bin;
	IplImage *V_bin;
	IplImage *tmp_img;
	IplImage *dst_img;
	IplConvKernel *element;

	HSV_Img = cvCreateImage(cvGetSize(src_img), src_img->depth, src_img->nChannels);
	dst_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	bin_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	tmp_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	H_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	S_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	V_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	H_bin = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	S_bin = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
	V_bin = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);	

	cvCvtColor(src_img,HSV_Img,CV_BGR2HSV);
	cvSplit(HSV_Img,H_img,S_img,V_img,NULL);

	//HSV　各2値化画像を保存
	cvSaveImage("H_img.jpg",H_img);
	cvSaveImage("S_img.jpg",S_img);
	cvSaveImage("V_img.jpg",V_img);

	//指定のHの範囲の領域を抽出  360度を100％に変換後代入
	H_bin = getExtractionImage(H_img,5,10);
	cvSaveImage("H_bin.jpg",H_bin);
	//指定のSの範囲の領域を抽出
	S_bin = getExtractionImage(S_img,10,35);
	cvSaveImage("S_bin.jpg",S_bin);
	//指定のVの範囲の領域を抽出
	V_bin = getExtractionImage(V_img,50,85);
	cvSaveImage("V_bin.jpg",V_bin);

	cvAnd(H_bin, S_bin, tmp_img);
	cvAnd(tmp_img, V_bin, bin_img);

	//closing
	element = cvCreateStructuringElementEx (9, 9, 4, 4, CV_SHAPE_RECT, NULL);
	tmp_img = cvCloneImage(bin_img);
	cvMorphologyEx (bin_img, dst_img, tmp_img, element, CV_MOP_OPEN, 1);
	bin_img = cvCloneImage(dst_img);
	cvMorphologyEx (bin_img, dst_img, tmp_img, element, CV_MOP_CLOSE, 1);

	//cvSaveImage("bin_img.jpg",bin_img);
	//cvSaveImage("dst_img.jpg",dst_img);
	//cvWaitKey (0);

	cvReleaseImage(&bin_img);
	cvReleaseImage(&H_img);
	cvReleaseImage(&S_img);
	cvReleaseImage(&V_img);
	cvReleaseImage(&H_bin);
	cvReleaseImage(&S_bin);
	cvReleaseImage(&V_bin);
	cvReleaseImage(&tmp_img);
	return dst_img;
}

//色の抽出　0～100
//Min Max間の値だったら255,それ以外なら0の2値画像を出力する
IplImage* getExtractionImage(IplImage* src_img, int min, int max){
	IplImage *smooth_img;
	IplImage *dst_img;
	IplImage *bin_img;
	IplImage *bininv_img;

	//min maxはパーセントのため、最大255　最小0の値になるように計算
	int ThreadshouldMin = min * 2.55;
	int ThreadshouldMax = max * 2.55;

	//iplImageの初期化
	dst_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U, 1);
	bin_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U, 1);
	bininv_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U, 1);
	smooth_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U, 1);
	printf("ThreadshouldMin = %d, ThreadshouldMax = %d\n",ThreadshouldMin,ThreadshouldMax);
	//元となるグレーイメージの作成
	//cvCvtColor(src_img, gray_img, CV_BGR2GRAY);
	
	//ガウシアンでぼかして細かいノイズ除去
	cvSmooth(src_img, smooth_img, CV_GAUSSIAN,5,0,0,0);

	//CV_THRESH_BINARY は、閾値を超えるものを255にそれ以外を0
	//CV_THRESH_BINARYINV は、閾値を超えるものを0にそれ以外を255
	cvThreshold(smooth_img, bin_img, ThreadshouldMin, 255, CV_THRESH_BINARY);
    cvThreshold(smooth_img, bininv_img, ThreadshouldMax, 255, CV_THRESH_BINARY_INV);
	
	//cvNamedWindow("bin_img",0);
	//cvShowImage("bin_img",bin_img);
	//cvNamedWindow("bininv_img",0);
	//cvShowImage("bininv_img",bininv_img);
	//cvWaitKey(0);
	//cvDestroyAllWindows();

	//bin_img とbininv_imgをAndしてdst_imgに
	cvAnd(bin_img,bininv_img,dst_img);


	//使わないiplImageの後処理
	cvReleaseImage(&smooth_img);
	cvReleaseImage(&bin_img);
	cvReleaseImage(&bininv_img);

	//戻り値
	return dst_img;
}

//長方形検出
void findRectangle(IplImage *bin_img,CvPoint *p){
	CvMemStorage *storage = cvCreateMemStorage (0);
	CvSeq *contours = 0;
	CvSeq *workContours = 0;
	CvSeq *result;
	double AreaSize = 0;
	double macareasize = 0;
	int headsize = sizeof(CvSeq);
	int MinSize = 20;
	double MaxAreaSize = 0;
	CvPoint vtx[4];
//	CvPoint Points[4];
	CvSize size = cvGetSize(bin_img);
	//輪郭抽出
	cvFindContours (bin_img, storage, &contours, sizeof (CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	//workContours = contours;
	while(contours->ptr != NULL){
		result = cvApproxPoly(contours,contours->header_size, storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours) * 0.02, 0);
		//４辺である
		printf("result->total = %d\n", result->total);
		if(result->total == 4){
			AreaSize = abs(cvContourArea(contours, CV_WHOLE_SEQ));
			//長方形の領域チェック
			printf("AreaSize = %f\n",AreaSize);
			if(AreaSize > MinSize){
				//凹型、または、辺が交差しているか
				printf("cvCheckContourConvexity(result) = %d\n",cvCheckContourConvexity(result));
				if(cvCheckContourConvexity(result) == 1){
					//凸型で辺は交差していない
					CvPoint *tmpPoint;
					//頂点の取得
					for(int x = 0; x < 4; x++){
						tmpPoint = reinterpret_cast<CvPoint*>(cvGetSeqElem(result,x));
						vtx[x] = tmpPoint[0];
						printf("vtx[%d] = (%d, %d)\n",x,vtx[x].x,vtx[x].y);
					}

					//矩形が有効であるか
					if(IsUseableRectangle(vtx, size, 60)){
						//有効な矩形である
						
						//今までの矩形の中で最大か
						if(MaxAreaSize < AreaSize){
							//矩形のサイズを保存
							MaxAreaSize = AreaSize;
							
							//頂点の保存
							for(int idx = 0; idx < 4; idx++){
								p[idx] = vtx[idx];
							}
						}
					}
				}
			}
		}
		if(contours->h_next != NULL){
			contours = contours->h_next;
		}else{
			break;
		}
	}
	for(int idx = 0; idx < 4; idx++){
		printf("Points[idx] = (%d, %d)\n",p[idx].x,p[idx].y);
	}
	cvReleaseMemStorage(&storage);
}

//矩形が有効であるかチェック
bool IsUseableRectangle(CvPoint Vertex[4], CvSize Size, double MaxAngle){
	//頂点がどこにあるか
	int cnt = 0;
	//左上判断
	int x1 = Size.width / 10;
	int y1 = Size.height / 10;
	//右下判断
	int x2 = 9 * Size.width / 10;
	int y2 = 9 * Size.height / 10;

	for(int x = 0; x < 4; x++){
		if(Vertex[x].x < x1 && Vertex[x].y < y1){
			cnt += 1;
		}
		if(x2 < Vertex[x].x && Vertex[x].y < y1){
			cnt += 1;
		}
		if(x2 < Vertex[x].x && y2 < Vertex[x].y){
			cnt += 1;
		}
		if(Vertex[x].x < x1 && y2 < Vertex[x].y){
			cnt += 1;
		}
	}

	//四隅の2点以上あるか
	if(cnt > 1){
		//有効な矩形でないため、falseを返す
		return false;
	}

	//4つの角がそれぞれ90±MaxAngle度以内であるか？
	double r = 0;
	for(int x = 0; x < 4; x++){
		r = abs(GetAngle(Vertex[x], Vertex[(x + 1) % 4], Vertex[(x + 2) % 4]) * 180.0 / 3.1415 - 90.0);
		if(r > MaxAngle){
			return false;
		}
	}
	return true;
}

//3つの位置から回転角度を求める
double GetAngle(CvPoint p1, CvPoint p2, CvPoint p3){
	double dx1 = p1.x - p2.x;
	double dy1 = p1.y - p2.y;
	double dx2 = p3.x - p2.x;
	double dy2 = p3.y - p2.y;
	double w1 = sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2));
	
	//w1が0なら計算できないので0を返す
	if(w1 == 0){
		return 0;
	}
	double w2 = dx1 * dx2 + dy1 * dy2;
	double r = acos(w2 / w1);
	return r;
}
//2つの位置から回転角度を求める 未実装
double GetAngle(CvPoint p1, CvPoint p2){
    double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	return atan(dy/dx);
}


//アフィン変換　回転の修正及び歪み補正
IplImage* getAffinedImage(IplImage *src_img, CvPoint src_p[4]){
	IplImage* dst_img;
	CvMat *map;
	dst_img = cvCreateImage(cvSize(750,500), IPL_DEPTH_8U, 3);
	CvPoint2D32f src_pnt[4];
	CvPoint2D32f dst_pnt[4];

	for(int idx = 0; idx < 4; idx++){
		src_pnt[idx].x = (float)src_p[idx].x;
		src_pnt[idx].y = (float)src_p[idx].y;
	}
	//dst_pnt[]の設定
	dst_pnt[0].x = 0;
	dst_pnt[0].y = 0;
	dst_pnt[1].x = dst_img->width;
	dst_pnt[1].y = 0;
	dst_pnt[2].x = dst_img->width;
	dst_pnt[2].y = dst_img->height;
	dst_pnt[3].x = 0;
	dst_pnt[3].y = dst_img->height;

	map = cvCreateMat(3,3,CV_32FC1);
	cvGetPerspectiveTransform(src_pnt, dst_pnt, map);
	cvWarpPerspective (src_img, dst_img, map, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll (0));
	return dst_img;
}

//位置の並び替え　→　↓　←　↑
void sortPoint(CvPoint *p,CvPoint *dst_point){
	dst_point[0] = p[1];
	dst_point[1] = p[0];
	dst_point[2] = p[3];
	dst_point[3] = p[2];
}