#include "Translator1.h"
#include <stdio.h>
#include <sstream>

using namespace System;
using namespace System::IO;
using namespace std;

Translator1::Translator1(void)
{
	this->encodeRules->Clear();
	this->decodeRules->Clear();
	this->readEncodeTranslateRule();
}
void Translator1::readEncodeTranslateRule(){
	String^ fileName = "trEn.rule";
	 try 
   {
      StreamReader^ sr = File::OpenText(fileName);

      String^ str;
      while ((str = sr->ReadLine()) != nullptr) 
      {
		  this->encodeRules->Add(str);
      }
   }
   catch (Exception^ e)
   {
      if (dynamic_cast<FileNotFoundException^>(e))
         Console::WriteLine("file '{0}' not found", fileName);
      else
         Console::WriteLine("problem reading file '{0}'", fileName);
   }
}
String^ Translator1::Encoder(String^ text){
	String^ resultText = text;
	String^ No = "";
	int idx = 0;
	for(idx = this->encodeRules->Count - 1; idx >= 0; idx--)
	{
		resultText->Replace(this->encodeRules[idx], Convert::ToString(idx));
	}
	return resultText;
}
String^ Translator1::Decoder(String^ text){
	String^ resultText = "";
	int maxCount = text->Length - 3;
	int idx = 0;
	//3文字取り出してデコード
	for(idx = 0; idx < maxCount; idx += 3){
		resultText += this->decodeRules[Convert::ToInt32(text->Substring(idx,3))];
	}
	return resultText;
}
void Translator1::readDecodeTranslateRule(){
	String^ fileName = "trDe.rule";
	 try 
   {
      StreamReader^ sr = File::OpenText(fileName);

      String^ str;
      while ((str = sr->ReadLine()) != nullptr) 
      {
		  this->decodeRules->Add(str);
      }
   }
   catch (Exception^ e)
   {
      if (dynamic_cast<FileNotFoundException^>(e))
         Console::WriteLine("file '{0}' not found", fileName);
      else
         Console::WriteLine("problem reading file '{0}'", fileName);
   }
}




