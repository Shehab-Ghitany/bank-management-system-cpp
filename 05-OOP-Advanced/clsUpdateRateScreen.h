#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
using namespace std;


class clsUpdateRateScreen : protected clsScreen
{

private:


    static void _ReadCurrencyRate(clsCurrency& Currency)
    {
        cout << "\nEnter New Rate: ";
        Currency.Rate = clsInputValidate::ReadFloatNumber();
    }


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


    static void ShowUpdateRateScreen()
    {
        _DrawScreenHeader("\tUpdate Currency Screen");

        string CurrencyCode = "";

        cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency Code is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency1 = clsCurrency::FindCurrency(CurrencyCode);

        _PrintCurrency(Currency1);

        cout << "\nAre you sure you want to update this Currency Rate y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\n\nUpdate Currency Info:";
            cout << "\n____________________\n";

            _ReadCurrencyRate(Currency1);

            clsCurrency::enSaveResults SaveResult;

            SaveResult = Currency1.Save();

            switch (SaveResult)
            {

            case  clsCurrency::enSaveResults::svSucceeded:
            {
                cout << "\nCurrency Updated Successfully :-)\n";
                _PrintCurrency(Currency1);
                break;
            }
            case clsCurrency::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError Currency was not saved because it's Empty";
                break;
            }

            }
        }
    }










};

