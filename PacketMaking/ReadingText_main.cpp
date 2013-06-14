#include "DialogUI.h"

using namespace ReadingText;

[STAThreadAttribute]
int main(){
	DialogUI ^ui=gcnew DialogUI();
	ui->ShowDialog();
	return 0;
}