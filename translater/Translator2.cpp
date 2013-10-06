#include "Translator2.h"

#include <sstream>

using namespace System::Collections::Generic;
using namespace std;

Translator2::Translator2(void)
{
}
String^ Translator2::Encoder(String^ row){
	String^ result = "";
	String^ tmp = "";
	 
	tmp = this->upByteEncoder(row);
	result = this->downByteEncoder(tmp);

	return result;
}
String^ Translator2::upByteEncoder(String^ text){
	String^ result = "";
	String^ tmpStr = "";
	int j = 0;

	for(int i = 0; i < text->Length - 1; i++){
		j = i + 1;
		tmpStr += text[i];
		if((Byte)(text[j])-(Byte)(text[i]) != 1){
			if(tmpStr->Length > 4){
				result += this->getUpByteEncodedString(tmpStr);
			}else{
				result += tmpStr;
			}
			tmpStr = "";
		}
	}
	return result;
}
String^ Translator2::getUpByteEncodedString(String^ text){
	String^ resultStr;

	resultStr = "[";
	resultStr += text[0];
	resultStr += Convert::ToString(text->Length -1);
	resultStr = "]";
	return resultStr;
}
String^ Translator2::downByteEncoder(String^ text){
	String^ result = "";
	String^ tmpStr = "";
	int j = 0;

	for(int i = 0; i < text->Length - 1; i++){
		j = i + 1;
		tmpStr += text[i];
		if((Byte)(text[j])-(Byte)(text[i]) != -1){
			if(tmpStr->Length > 4){
				result += this->getDownByteEncodedString(tmpStr);
			}else{
				result += tmpStr;
			}
			tmpStr = "";
		}
	}
	return result;
}
String^ Translator2::getDownByteEncodedString(String^ text){
	String^ resultStr;

	resultStr = "{";
	resultStr += text[0];
	resultStr += Convert::ToString(text->Length -1);
	resultStr = "}";
	return resultStr;
}

String^ Translator2::Decoder(String^  row){
	String^ result = "";
	String^ tmp = "";

	tmp = this->upByteDecoder(row);
	result = this->downByteDecoder(tmp);

	return result;
}

String^ Translator2::upByteDecoder(String^ text){
	String^ result = "";
	String^ tmp = "";

	int flag = 0;
	for(int i = 0; i < text->Length; i++){
		if(text[i] == '{' || flag == 1){
			flag = 1;
			if(text[i] == '}' && tmp != ""){
				result += this->getUpByteDecodedString(tmp);
				tmp = "";
				flag = 0;
			}else{
				tmp += text[i];
			}
		}else{
			result += text[i];
		}
		
	}
	return result;
}

String^ Translator2::downByteDecoder(String^ text){
	String^ result = "";
	String^ tmp = "";

	int flag = 0;
	for(int i = 0; i < text->Length; i++){
		if(text[i] == '[' || flag == 1){
			flag = 1;
			if(text[i] == ']' && tmp != ""){
				result += this->getDownByteDecodedString(tmp);
				tmp = "";
				flag = 0;
			}else{
				tmp += text[i];
			}
		}else{
			result += text[i];
		}
		
	}
	return result;
}

String^ Translator2::getUpByteDecodedString(String^ text){
	String ^result = "";
	char original = text[1];
	int countMax = Convert::ToInt32(text->Substring(2));
	for(int idx = 0; idx < countMax; idx++){
		result += original;
		original++;
	}
	return result;
}
String^ Translator2::getDownByteDecodedString(String^ text){
	String ^result = "";
	char original = text[1];
	int countMax = Convert::ToInt32(text->Substring(2));
	for(int idx = 0; idx < countMax; idx++){
		result += original;
		original--;
	}
	return result;
}
