#include <iostream>
#include <string>
#include <vector>
#pragma once
using namespace std;

class clsString
{

private:
	string _Value;

public:

	clsString()
	{
		_Value = "";
	}
	clsString(string Value)
	{
		_Value = Value;
	}

	void setValue(string Value)
	{
		_Value = Value;
	}
	string getValue()
	{
		return _Value;
	}

	__declspec(property(get = getValue, put = setValue)) string Value;


	static short CountWords(string Write)
	{
		string delim = " ";
		short Counter = 0;
		short pos = 0;
		string sword;

		while ((pos = Write.find(delim)) != std::string::npos)
		{
			sword = Write.substr(0, pos);
			if (sword != "")
			{
				Counter++;
			}
			Write.erase(0, pos + delim.length());
		}

		if (Write != "")
		{
			Counter++;
		}

		return Counter;
	}
	short CountWords()
	{
		return CountWords(_Value);
	}

	static void PrintFirstLetterOfEachWord(string Write)
	{
		cout << Write[0] << endl;

		for (int i = 0; i < Write.length(); i++)
		{
			if ((Write[i] == ' ') && (Write[i + 1] != ' '))
			{
				cout << Write[i + 1] << endl;
			}
		}

	}
	void PrintFirstLetterOfEachWord()
	{
		PrintFirstLetterOfEachWord(_Value);
	}

	static void UpperFirstLetterOfEachWord(string Write)
	{
		bool isFirstLetter = true;

		for (int i = 0; i < Write.length(); i++)
		{
			if ((Write[i] != ' ') && isFirstLetter)
			{
				cout << char(toupper(Write[i]));
			}
			else
			{
				cout << Write[i];
			}

			isFirstLetter = Write[i] == ' ' ? true : false;
		}

	}
	void UpperFirstLetterOfEachWord()
	{
		UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string Write)
	{
		bool isFirstLetter = true;

		for (int i = 0; i < Write.length(); i++)
		{
			if ((Write[i] != ' ') && isFirstLetter)
			{
				cout << char(tolower(Write[i]));
			}
			else
			{
				cout << Write[i];
			}

			isFirstLetter = Write[i] == ' ' ? true : false;
		}
		return Write;
	}
	string LowerFirstLetterOfEachWord()
	{
		return LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllLettersInString(string Write)
	{
		for (int i = 0; i < Write.length(); i++)
		{
			Write[i] = toupper(Write[i]);
		}
		return Write;
	}
	string UpperAllLettersInString()
	{
		return UpperAllLettersInString(_Value);
	}

	static string LowerAllLettersInString(string Write)
	{
		for (int i = 0; i < Write.length(); i++)
		{
			Write[i] = tolower(Write[i]);
		}
		return Write;
	}
	string LowerAllLettersInString()
	{
		return LowerAllLettersInString(_Value);
	}

	static char InvertChar(char Write)
	{

		if (islower(Write))
		{
			Write = toupper(Write);
		}
		else if (isupper(Write))
		{
			Write = tolower(Write);
		}

		return Write;
	}
	char InvertChar()
	{
		return InvertChar(_Value[0]);
	}

	static string InvertAllLettersInString(string Write)
	{
		for (int i = 0; i < Write.length(); i++)
		{
			Write[i] = isupper(Write[i]) ? tolower(Write[i]) : toupper(Write[i]);
		}
		return Write;
	}
	string InvertAllLettersInString()
	{
		return InvertAllLettersInString(_Value);
	}

	static void CountSmallAndCapitalAndLengthOfString(string Write)
	{
		short CountUpper = 0, CountLower = 0;

		cout << "\nString Length = " << Write.length() << endl;

		for (int i = 0; i < Write.length(); i++)
		{
			if (isupper(Write[i]))
			{
				CountUpper++;
			}
			else if (islower(Write[i]))
			{
				CountLower++;
			};
		}

		cout << "Capital Letters Count = " << CountUpper << endl;
		cout << "Small Letters Count   = " << CountLower << endl;
	}
	void CountSmallAndCapitalAndLengthOfString()
	{
		return CountSmallAndCapitalAndLengthOfString(_Value);
	}

	enum enWhatCount { Small = 0, Capital = 1, All = 2 };

	static short CountLetterByEnum(string Write, enWhatCount WhatCount = enWhatCount::All)
	{
		short Counter = 0;

		if (WhatCount == enWhatCount::All)
		{
			return Write.length();
		}

		for (int i = 0; i < Write.length(); i++)
		{
			if (WhatCount == enWhatCount::Capital && isupper(Write[i]))
			{
				Counter++;
			}
			else if (WhatCount == enWhatCount::Small && islower(Write[i]))
			{
				Counter++;
			}
		}

		return Counter;
	}
	short CountLetterByEnum(enWhatCount WhatCount = enWhatCount::All)
	{
		return CountLetterByEnum(_Value, WhatCount);
	}

	static string CountSpecificLetter(string Write, char Letter)
	{
		short CountLetter = 0;


		for (int i = 0; i < Write.length(); i++)
		{
			if (Write[i] == Letter)
			{
				CountLetter++;
			}
		}

		string PrintResult = "Letter '" + string(1, Letter) + "' Count = " + to_string(CountLetter);

		return PrintResult;
	}
	string CountSpecificLetter(char Letter)
	{
		return CountSpecificLetter(_Value, Letter);
	}

	static bool IsVowel(char Letter)
	{
		char arr[5] = { 'a','e','i','o','u' };

		for (int i = 0;i < 5;i++)
		{
			if (tolower(Letter) == arr[i])
				return true;
		}
		return false;
	}
	bool IsVowel()
	{
		return IsVowel(Value[0]);
	}

	static short CountVowels(string Write)
	{
		short VowelCounter = 0;

		char arr[5] = { 'a','e','i','o','u' };

		for (int i = 0;i < Write.length();i++)
		{
			for (int j = 0;j < 5;j++)
			{
				char Letter = Write.at(i);

				if (tolower(Letter) == arr[j])
					VowelCounter++;
			}
		}

		return VowelCounter;
	}
	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static void PrintAllVowels(string Write)
	{
		for (int i = 0;i < Write.length();i++)
		{
			if (IsVowel(Write[i]))
				cout << Write[i] << "    ";
		}
	}
	void PrintAllVowels()
	{
		PrintAllVowels(_Value);
	}

	static void PrintAllWordsInLine(string Write)
	{
		string word = "";

		for (int i = 0;i < Write.length();i++)
		{
			if ((Write[i] != ' '))
			{
				word.push_back(Write[i]);
			}
			else
			{
				cout << word << endl;
				word = "";
			}
		}
		cout << word << endl;
	}
	void PrintAllWordsInLine()
	{
		PrintAllWordsInLine(_Value);
	}

	static string TrimLeft(string Write)
	{

		for (short i = 0; i < Write.length();i++)
		{
			if (Write[i] != ' ')
			{
				return Write.substr(i, Write.length() - i);
			}
		}
		return "";
	}
	string TrimLeft()
	{
		return TrimLeft(_Value);
	}

	static string TrimRight(string Write)
	{

		for (int i = Write.length() - 1; i >= 0;i--)
		{
			if (Write[i] != ' ')
			{
				return Write.substr(0, i + 1);
			}
		}
		return "";
	}
	string TrimRight()
	{
		return TrimRight(_Value);
	}

	static string Trim(string Write)
	{
		return TrimLeft(TrimRight(Write));
	}
	string Trim()
	{
		return Trim(_Value);
	}

	static vector <string> VSplitString(string Write, string delim = "#//#")
	{
		vector <string> SplitString;

		short pos = 0;
		string sword;

		while ((pos = Write.find(delim)) != std::string::npos)
		{
			sword = Write.substr(0, pos);
			if (sword != "")
			{
				SplitString.push_back(sword);
			}
			Write.erase(0, pos + delim.length());
		}

		if (Write != "")
		{
			SplitString.push_back(Write);
		}
		return SplitString;
	}
	vector <string> VSplitString(string Delim = "#//#")
	{
		return VSplitString(_Value, Delim);
	}


	static string JoinStringByVector(vector<string>vString, string delim)
	{
		string Write;

		for (string& s : vString)
		{
			Write = Write + s + delim;
		}

		return Write.substr(0, Write.length() - delim.length());
	}

	static string JoinStringByArray(string arr[], int length, string delim)
	{
		string Write;

		for (int i = 0; i < length; i++)
		{
			Write = Write + arr[i] + delim;
		}

		return Write.substr(0, Write.length() - delim.length());
	}


	static string ReverseWordsInString(string Write)
	{
		vector<string> vString;
		string S = "";

		vString = VSplitString(Write, " ");

		vector<string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			--iter;

			S += *iter + " ";
		}

		S = S.substr(0, S.length() - 1);

		return S;
	}
	string ReverseWordsInString()
	{
		return ReverseWordsInString(_Value);
	}

	static string ReplaceWordInStringUsingSplit(string Write, string StringToReplace, string ReplaceTo, bool MatchCase = true)
	{
		vector<string> vWrite = VSplitString(Write, " ");

		for (string& s : vWrite)
		{
			if (MatchCase)
			{
				if (s == StringToReplace)
				{
					s = ReplaceTo;
				}
			}
			else
			{
				if (LowerAllLettersInString(s) == LowerAllLettersInString(StringToReplace))
				{
					s = ReplaceTo;
				}
			}
		}
		return JoinStringByVector(vWrite, " ");
	}
	string ReplaceWordInStringUsingSplit(string StringToReplace, string RepalceTo)
	{
		return ReplaceWordInStringUsingSplit(_Value, StringToReplace, RepalceTo);
	}

	static string RemovePunctuationFromString(string Write)
	{
		char s = ',';
		string text = "";

		for (int i = 0; i < Write.length();i++)
		{
			s = Write[i];
			if (!ispunct(s))
			{
				text += s;
			}
		}
		return text;
	}
	string RemovePunctuationFromString()
	{
		return RemovePunctuationFromString(_Value);
	}



};