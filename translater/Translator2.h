#pragma once

using  namespace System;

ref class Translator2
{
public:
	Translator2(void);
	String^ Encoder(String^ row);
	String^ Decoder(String^ row);
private:
	String^ upByteEncoder(String^ text);
	String^ downByteEncoder(String^ text);
	String^ getUpByteEncodedString(String^ text);
	String^ getDownByteEncodedString(String^ text);

	String^ upByteDecoder(String^ text);
	String^ downByteDecoder(String^ text);
	String^ getUpByteDecodedString(String^ text);
	String^ getDownByteDecodedString(String^ text);
};

