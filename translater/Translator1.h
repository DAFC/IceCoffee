#pragma once

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;

ref class Translator1
{
public:
	Translator1(void);
	String^ Encoder(String^ text);
	String^ Decoder(String^ text);
private:
	//125pattarn
	List<String^>^ encodeRules;
	List<String^>^ decodeRules;
	void readEncodeTranslateRule(void);
	void readDecodeTranslateRule(void);
	//String int2String(int number);
};

