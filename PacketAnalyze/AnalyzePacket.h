#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "OpenCVHeader.h"

void AnalyzePacketBlock(IplImage *src_img, int blockNo, int diceX, int diceY,int diceMargin);
int AnalyzePacketSector(IplImage* src_img, int blockNo, int idx, int idy);
void readSettingFile(int& wakuMargin,int& DiceSizeX, int& DiceSizeY, int& DiceMargin, int& BlockWidth, int& BlockHeight);
int AnalyzePacketSector_getDiceType(int DiceType, CvPoint2D32f* centerPoint);