#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
using namespace std;


class clsCurrency
{

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1};
	enMode _Mode;
	string _Country;
	string _Code;
	string _Name;
	float _Rate;


	static clsCurrency _ConvertLinetoObject(string Line, string delim = "#//#")
	{
		vector <string> SplitString = clsString::VSplitString(Line, delim);


		clsCurrency CurrencyData(enMode::UpdateMode, SplitString[0], SplitString[1],
			SplitString[2], stof(SplitString[3]));

		return CurrencyData;
	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector <clsCurrency> vCurrencies;

		fstream myFile;
		myFile.open("Currencies.txt", ios::in);

		if (myFile.is_open())
		{
			string Line;

			while (getline(myFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoObject(Line);
				vCurrencies.push_back(Currency);
			}

			myFile.close();
		}
		return vCurrencies;
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency CurrencyData, string delim = "#//#")
	{
		string  CurrencyLine = "";

		CurrencyLine += CurrencyData.Country+ delim;
		CurrencyLine += CurrencyData.Code + delim;
		CurrencyLine += CurrencyData.Name + delim;
		CurrencyLine += to_string(CurrencyData.Rate);

		return CurrencyLine;
	}

	static void _SaveCurrenciesDataToFile(vector <clsCurrency> vCurrencies)
	{
		fstream myFile;
		myFile.open("Currencies.txt", ios::out);

		string DataLine;

		if (myFile.is_open())
		{

			for (clsCurrency C : vCurrencies)
			{
					DataLine = _ConvertCurrencyObjectToLine(C);
					myFile << DataLine << endl;
			}

			myFile.close();
		}

	}

	void _Update()
	{
		vector < clsCurrency > _vCurrencies;
		_vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : _vCurrencies)
		{
			if (C.Code == Code)
			{
				C = *this;
				break;
			}

		}

		_SaveCurrenciesDataToFile(_vCurrencies);
	}


public:

	clsCurrency(enMode Mode,string Country, string Code, string Name, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_Code = Code;
		_Name = Name;
		_Rate = Rate;
	}

	string getCountry()
	{
		return _Country;
	}
	__declspec(property(get = getCountry)) string Country;

	string getCode()
	{
		return _Code;
	}
	__declspec(property(get = getCode)) string Code;
	
	string getName()
	{
		return _Name;
	}
	__declspec(property(get = getName)) string Name;

	void setRate(float Rate)
	{
		_Rate = Rate;
	}
	float getRate()
	{
		return _Rate;
	}
	__declspec(property(get = getRate, put = setRate)) float Rate;


	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	static clsCurrency FindCurrency(string EnterCurrency,short FindBy=1)
	{
		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		if(FindBy == 1)
		{
			for (clsCurrency& C : vCurrencies)
			{
				if (clsString::LowerAllLettersInString(C.Code) == clsString::LowerAllLettersInString(EnterCurrency))
				{
					return C;
				}
			}
		}
		else
		{
			for (clsCurrency& C : vCurrencies)
			{
				if (clsString::LowerAllLettersInString(C.Country) == clsString::LowerAllLettersInString(EnterCurrency))
				{
					return C;
				}
			}
		}


		return _GetEmptyCurrencyObject();
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static bool IsCurrencyExist(string EnterCurrency,short FindBy=1)
	{
		clsCurrency Currency1 = FindCurrency(EnterCurrency, FindBy);
		return !Currency1.IsEmpty();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 };

	enSaveResults Save()
	{
		switch (_Mode)
		{

		case enMode::EmptyMode:
		{
			return enSaveResults::svFaildEmptyObject;
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
		}

		}

	}


};

