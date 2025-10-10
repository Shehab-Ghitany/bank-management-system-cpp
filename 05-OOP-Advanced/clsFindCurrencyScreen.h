#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;



class clsFindCurrencyScreen :protected clsScreen
{


    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n_______________________________\n";
        cout << "\nCountry    : " << Currency.Country;
        cout << "\nCode       : " << Currency.Code;
        cout << "\nName       : " << Currency.Name;
        cout << "\nRate(1$) = : " << Currency.Rate;
        cout << "\n_______________________________\n";
    }


public:

	static void ShowFindCurrencyScreen()
	{
        _DrawScreenHeader("\t  Find Currency Screen");

        short FindBy;
        cout << "\nFind By: [1] Code or [2] Country ? ";
        FindBy = clsInputValidate::ReadShortNumberBetween(1,2);

        string EnterCurrency;
        cout << "\nPlease Enter CurrencyCode: ";
        EnterCurrency = clsInputValidate::ReadString();


        clsCurrency Currency1 = clsCurrency::FindCurrency(EnterCurrency, FindBy);

        if (Currency1 .IsEmpty())
        {
            cout << "\nCurrency was not Found :-(\n";
            return;
        }
        else
        {
            cout << "\nCurrency Found\n";
        }

            _PrintCurrency(Currency1);
    }




};

