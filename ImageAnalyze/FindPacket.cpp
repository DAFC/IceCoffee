#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "OpenCVHeader.h"
#include "FindPacket.h"

IplImage* FindPacketMain(IplImage* src_img){
	IplImage* bin_img;
	IplImage* affined_img;
	bin_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);

	//�ό`��̉摜�T�C�Y�́@750 x 500 pixel �Ƃ���B
	affined_img = cvCreateImage(cvSize(750,500), IPL_DEPTH_8U, 3);
	
	//�g�̒��o
	bin_img = FindPacketMain_useGetExtentionImage_Version(src_img);

/*	cvNamedWindow("bin_img",0);
	cvShowImage("bin_img",bin_img);
	cvWaitKey(0);
	cvDestroyAllWindows();*/

	//�֊s�̒��o�A�����ߎ�
	CvPoint p[4];
	CvPoint p2[4];
	findRectangle(bin_img,p);
	sortPoint(p,p2);
	for(int x = 0; x < 4; x++){
		printf("���_ X = %d, Y = %d\n", p2[x].x, p2[x].y);
	}

	affined_img = getAffinedImage(src_img,p2);

	//���o���������`��`��
	cvDrawLine(src_img,p2[0],p2[1],CV_RGB(255,0,0),5);
	cvDrawLine(src_img,p2[1],p2[2],CV_RGB(255,0,0),5);
	cvDrawLine(src_img,p2[2],p2[3],CV_RGB(255,0,0),5);
	cvDrawLine(src_img,p2[3],p2[0],CV_RGB(255,0,0),5);

	printf("��]�p�x1-2�@%f Rad\n",GetAngle(p2[1],p2[2]));
	printf("��]�p�x2-3�@%f Rad\n",GetAngle(p2[2],p2[3]));
	printf("��]�p�x3-4�@%f Rad\n",GetAngle(p2[3],p2[4]));
	printf("��]�p�x4-1�@%f Rad\n",GetAngle(p2[4],p2[1]));
	
	/*cvNamedWindow("affined_img",0);
	cvShowImage("affined_img",affined_img);

	cvNamedWindow("src_img",0);
	cvShowImage("src_img",src_img);

	cvWaitKey(0);
	cvDestroyAllWindows();*/
	//cvSaveImage("DetectPacketWaku.jpg",src_img);
	cvSaveImage("ExtractPacketImage.jpg",affined_img);

	//�摜�������̉��
	cvReleaseImage(&bin_img);

	//�c�݂�␳�����摜�����^�[������
	return affined_img;
}

//H S V �̓��A��摜���g���g�̒��o�@�{�c
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

	//HSV�@�e2�l���摜��ۑ�
	cvSaveImage("H_img.jpg",H_img);
	cvSaveImage("S_img.jpg",S_img);
	cvSaveImage("V_img.jpg",V_img);

	cvThreshold(V_img,bin_img,0,255,CV_THRESH_BINARY | CV_THRESH_OTSU);

	cvSaveImage("bin_img.jpg",bin_img);
	cvWaitKey (0);

	//�摜�������̉��
	cvReleaseImage(&bin_img);
	cvReleaseImage(&H_img);
	cvReleaseImage(&S_img);
	cvReleaseImage(&V_img);
	cvReleaseImage(&H_bin);
	cvReleaseImage(&S_bin);
	cvReleaseImage(&V_bin);
	cvReleaseImage(&tmp_img);

	//���^�[��
	return bin_img;
}

//HSV�ɕ������A�w��̐F�����R�[�h�@�̗p
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

	//HSV�@�e2�l���摜��ۑ�
	cvSaveImage("H_img.jpg",H_img);
	cvSaveImage("S_img.jpg",S_img);
	cvSaveImage("V_img.jpg",V_img);

	//�w���H�͈̗̔͂̈�𒊏o  360�x��100���ɕϊ�����
	H_bin = getExtractionImage(H_img,5,10);
	cvSaveImage("H_bin.jpg",H_bin);
	//�w���S�͈̗̔͂̈�𒊏o
	S_bin = getExtractionImage(S_img,10,35);
	cvSaveImage("S_bin.jpg",S_bin);
	//�w���V�͈̗̔͂̈�𒊏o
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

//�F�̒��o�@0�`100
//Min Max�Ԃ̒l��������255,����ȊO�Ȃ�0��2�l�摜���o�͂���
IplImage* getExtractionImage(IplImage* src_img, int min, int max){
	IplImage *smooth_img;
	IplImage *dst_img;
	IplImage *bin_img;
	IplImage *bininv_img;

	//min max�̓p�[�Z���g�̂��߁A�ő�255�@�ŏ�0�̒l�ɂȂ�悤�Ɍv�Z
	int ThreadshouldMin = min * 2.55;
	int ThreadshouldMax = max * 2.55;

	//iplImage�̏�����
	dst_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U, 1);
	bin_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U, 1);
	bininv_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U, 1);
	smooth_img = cvCreateImage(cvGetSize(src_img),IPL_DEPTH_8U, 1);
	printf("ThreadshouldMin = %d, ThreadshouldMax = %d\n",ThreadshouldMin,ThreadshouldMax);
	//���ƂȂ�O���[�C���[�W�̍쐬
	//cvCvtColor(src_img, gray_img, CV_BGR2GRAY);
	
	//�K�E�V�A���łڂ����čׂ����m�C�Y����
	cvSmooth(src_img, smooth_img, CV_GAUSSIAN,5,0,0,0);

	//CV_THRESH_BINARY �́A臒l�𒴂�����̂�255�ɂ���ȊO��0
	//CV_THRESH_BINARYINV �́A臒l�𒴂�����̂�0�ɂ���ȊO��255
	cvThreshold(smooth_img, bin_img, ThreadshouldMin, 255, CV_THRESH_BINARY);
    cvThreshold(smooth_img, bininv_img, ThreadshouldMax, 255, CV_THRESH_BINARY_INV);
	
	//cvNamedWindow("bin_img",0);
	//cvShowImage("bin_img",bin_img);
	//cvNamedWindow("bininv_img",0);
	//cvShowImage("bininv_img",bininv_img);
	//cvWaitKey(0);
	//cvDestroyAllWindows();

	//bin_img ��bininv_img��And����dst_img��
	cvAnd(bin_img,bininv_img,dst_img);


	//�g��Ȃ�iplImage�̌㏈��
	cvReleaseImage(&smooth_img);
	cvReleaseImage(&bin_img);
	cvReleaseImage(&bininv_img);

	//�߂�l
	return dst_img;
}

//�����`���o
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
	//�֊s���o
	cvFindContours (bin_img, storage, &contours, sizeof (CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	//workContours = contours;
	while(contours->ptr != NULL){
		result = cvApproxPoly(contours,contours->header_size, storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours) * 0.02, 0);
		//�S�ӂł���
		printf("result->total = %d\n", result->total);
		if(result->total == 4){
			AreaSize = abs(cvContourArea(contours, CV_WHOLE_SEQ));
			//�����`�̗̈�`�F�b�N
			printf("AreaSize = %f\n",AreaSize);
			if(AreaSize > MinSize){
				//���^�A�܂��́A�ӂ��������Ă��邩
				printf("cvCheckContourConvexity(result) = %d\n",cvCheckContourConvexity(result));
				if(cvCheckContourConvexity(result) == 1){
					//�ʌ^�ŕӂ͌������Ă��Ȃ�
					CvPoint *tmpPoint;
					//���_�̎擾
					for(int x = 0; x < 4; x++){
						tmpPoint = reinterpret_cast<CvPoint*>(cvGetSeqElem(result,x));
						vtx[x] = tmpPoint[0];
						printf("vtx[%d] = (%d, %d)\n",x,vtx[x].x,vtx[x].y);
					}

					//��`���L���ł��邩
					if(IsUseableRectangle(vtx, size, 60)){
						//�L���ȋ�`�ł���
						
						//���܂ł̋�`�̒��ōő傩
						if(MaxAreaSize < AreaSize){
							//��`�̃T�C�Y��ۑ�
							MaxAreaSize = AreaSize;
							
							//���_�̕ۑ�
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

//��`���L���ł��邩�`�F�b�N
bool IsUseableRectangle(CvPoint Vertex[4], CvSize Size, double MaxAngle){
	//���_���ǂ��ɂ��邩
	int cnt = 0;
	//���㔻�f
	int x1 = Size.width / 10;
	int y1 = Size.height / 10;
	//�E�����f
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

	//�l����2�_�ȏ゠�邩
	if(cnt > 1){
		//�L���ȋ�`�łȂ����߁Afalse��Ԃ�
		return false;
	}

	//4�̊p�����ꂼ��90�}MaxAngle�x�ȓ��ł��邩�H
	double r = 0;
	for(int x = 0; x < 4; x++){
		r = abs(GetAngle(Vertex[x], Vertex[(x + 1) % 4], Vertex[(x + 2) % 4]) * 180.0 / 3.1415 - 90.0);
		if(r > MaxAngle){
			return false;
		}
	}
	return true;
}

//3�̈ʒu�����]�p�x�����߂�
double GetAngle(CvPoint p1, CvPoint p2, CvPoint p3){
	double dx1 = p1.x - p2.x;
	double dy1 = p1.y - p2.y;
	double dx2 = p3.x - p2.x;
	double dy2 = p3.y - p2.y;
	double w1 = sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2));
	
	//w1��0�Ȃ�v�Z�ł��Ȃ��̂�0��Ԃ�
	if(w1 == 0){
		return 0;
	}
	double w2 = dx1 * dx2 + dy1 * dy2;
	double r = acos(w2 / w1);
	return r;
}
//2�̈ʒu�����]�p�x�����߂� ������
double GetAngle(CvPoint p1, CvPoint p2){
    double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	return atan(dy/dx);
}


//�A�t�B���ϊ��@��]�̏C���y�јc�ݕ␳
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
	//dst_pnt[]�̐ݒ�
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

//�ʒu�̕��ёւ��@���@���@���@��
void sortPoint(CvPoint *p,CvPoint *dst_point){
	dst_point[0] = p[1];
	dst_point[1] = p[0];
	dst_point[2] = p[3];
	dst_point[3] = p[2];
}