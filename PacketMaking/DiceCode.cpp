using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;

namespace DiceCode
{
	List<int>^ Encode(String^ text)
	{
		List<int>^ result = gcnew List<int>();
		array<wchar_t>^ chars = text->ToCharArray();
		for each (wchar_t var in chars)
		{

			result->Add(var/25);
			result->Add((var/5)%5);
			result->Add(var%5);

		}
		return result;
	}

	String^ Decode(List<int>^ numbers)
	{
		StringBuilder^ sb = gcnew StringBuilder();
		for (int i = 0; i < numbers->Count; i+=3)
		{

			sb->Append((wchar_t)(numbers[i]*25+numbers[i+1]*5+numbers[i+2]));

		}
		return sb->ToString();
	}
}

//#define Test
#ifdef Test

using namespace DiceCode;
int main()
{
	Console::WriteLine("#teststart#");
	String^ testMessage ="'a-!_iidesune\"";
	Console::WriteLine("SendMessage:"+testMessage);
	List<int>^ aaa=Encode(testMessage);
	for each (int var in aaa)
	{
		Console::WriteLine(var);
	}
	Console::WriteLine("ReceiveMessage:"+Decode(aaa));
	Console::WriteLine("#testend#");
	return 0;
}

#endif