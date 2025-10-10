#pragma once
#include "clsDate.h"
#include "clsUtil.h"
using namespace std;


class clsInputValidate
{

public:

	static bool IsNumberBetween(int YourNumber, int RangeStart, int RangeEnd)
	{
		if (YourNumber >= RangeStart && YourNumber <= RangeEnd)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	static bool IsNumberBetween(double YourNumber, double RangeStart, double RangeEnd)
	{
		if (YourNumber <= RangeEnd && (YourNumber >= RangeStart))
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	static bool IsNumberBetween(short YourNumber, short RangeStart, short RangeEnd)
	{
		if (YourNumber <= RangeEnd && (YourNumber >= RangeStart))
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	static bool IsNumberBetween(float YourNumber, float RangeStart, float RangeEnd)
	{
		if (YourNumber <= RangeEnd && (YourNumber >= RangeStart))
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	static bool isDateBetween(clsDate YourDate, clsDate StartDate, clsDate EndDate)
	{

		if (clsDate::IsDate1LessThanDate2(EndDate, StartDate))
		{
			clsUtil::Swap(EndDate, StartDate);
		}

		if (clsDate::IsDate1LessThanDate2(YourDate, EndDate) &&
			!clsDate::IsDate1LessThanDate2(YourDate, StartDate))
		{
			return true;
		}


		return false;
	}

	static int ReadIntNumber(string Message = "Invalid Number, Enter again\n")
	{
		int Number;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << Message;

			cin >> Number;
		}

		return Number;
	}

	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		short Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	
	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		short Number = ReadShortNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadShortNumber();
		}
		return Number;
	}

	static double ReadDblNumber(string Message = "Invalid Number, Enter again\n")
	{
		double Number;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << Message;

			cin >> Number;
		}

		return Number;
	}

	static int ReadIntNumberBetween(int RangeStart, int RangeEnd, string Message = "Number is not within range, Enter again:\n")
	{
		int Number;
		cin >> Number;

		while (cin.fail() || !IsNumberBetween(Number, RangeStart, RangeEnd))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << Message;

			cin >> Number;
		}

		return Number;
	}

	static double ReadDblNumberBetween(double RangeStart, double RangeEnd, string Message = "Number is not within range, Enter again:\n")
	{
		double Number;
		cin >> Number;

		while (cin.fail() || !IsNumberBetween(Number, RangeStart, RangeEnd))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << Message;

			cin >> Number;
		}

		return Number;
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValidateDate(Date);
	}

	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		float Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		float Number = ReadFloatNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadFloatNumber();
		}
		return Number;
	}

	static string ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, S1);
		return S1;
	}


};

