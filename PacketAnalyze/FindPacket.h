#include <opencv\cv.h>
#include <opencv\highgui.h>

IplImage* getExtractionImage(IplImage* src_img, int min, int max);
IplImage* FindPacketMain_useOneBinImage_version(IplImage *src_img);
IplImage* FindPacketMain_useGetExtentionImage_Version(IplImage *src_img);
void findRectangle(IplImage *bin_img,CvPoint *p);
double GetAngle(CvPoint p1, CvPoint p2);
double GetAngle(CvPoint p1, CvPoint p2, CvPoint p3);
bool IsUseableRectangle(CvPoint Vertex[4], CvSize Size, double MaxAngle);
void sortPoint(CvPoint *p,CvPoint *dst_point);
IplImage* getAffinedImage(IplImage *src_img, CvPoint src_p[4]);