#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
using namespace std;


class clsCurrencyCalculatorScreen : public clsScreen
{

private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\n_______________________________\n";
        cout << "\nCountry    : " << Currency.Country;
        cout << "\nCode       : " << Currency.Code;
        cout << "\nName       : " << Currency.Name;
        cout << "\nRate(1$) = : " << Currency.Rate;
        cout << "\n_______________________________\n";
    }


public:

    static void ShowCurrencyCalculatorScreen()
    {
        _DrawScreenHeader("\tCurrency Calculator Screen");


        char Answer = 'n';
        
        do
        {
            string CurrencyCode1 = "";
            string CurrencyCode2 = "";

            cout << "\nPlease Enter Currency1 Code: ";
            CurrencyCode1 = clsInputValidate::ReadString();

            while (!clsCurrency::IsCurrencyExist(CurrencyCode1))
            {
                cout << "\nCurrency Code is not found, choose another one: ";
                CurrencyCode1 = clsInputValidate::ReadString();
            }
            

            cout << "\nPlease Enter Currency2 Code: ";
            CurrencyCode2 = clsInputValidate::ReadString();

            while (!clsCurrency::IsCurrencyExist(CurrencyCode2))
            {
                cout << "\nCurrency Code is not found, choose another one: ";
                CurrencyCode2 = clsInputValidate::ReadString();
            }


            clsCurrency Currency1 = clsCurrency::FindCurrency(CurrencyCode1);
            clsCurrency Currency2 = clsCurrency::FindCurrency(CurrencyCode2);

            cout << "\nEnter Amount to Exchange: ";
            float Amount = clsInputValidate::ReadFloatNumber();

            cout << "\nConvert From:";
            _PrintCurrency(Currency1);


            cout << endl << Amount << ' ' << Currency1.Code << " = " <<
                (Amount / Currency1.Rate) << " USD" << endl;

            if (Currency2.Code != "USD")
            {
                cout << "\n\nConverting From USD:" << endl << endl;
                cout << "TO:";

                _PrintCurrency(Currency2);

                cout << endl << Amount << ' ' << Currency1.Code << " = " <<
                    ((Amount / Currency1.Rate) * Currency2.Rate) << ' ' << Currency2.Code << endl;
            }

            cout << "\nDo you want to perform another calculation y/n? ";
            cin >> Answer;

        } while (Answer == 'y' || Answer == 'Y');



    }



};

