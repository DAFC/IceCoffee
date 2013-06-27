#include "ReadingText.h"

using namespace ReadingText;

[STAThreadAttribute]
int main(){
	//UIを開く
	ReadingTextDialogUI ^ui=gcnew ReadingTextDialogUI();
	ui->ShowDialog();
	return 0;
}