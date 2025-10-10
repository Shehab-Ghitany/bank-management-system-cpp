#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;


class clsListCurrenciesScreen : protected clsScreen
{

private:

	static void PrintClientRecordLine(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(35) << left << Currency.Country;
		cout << "| " << setw(8) << left << Currency.Code;
		cout << "| " << setw(35) << left << Currency.Name;
        cout << "| " << setw(10) << left << Currency.Rate;
	}


public:

	static void	ShowListCurrenciesScreen()
	{
        vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

        string Title = "\t  Currencies List Screen";
        string SubTitle = "\t    (" + to_string(vCurrencies.size()) + ") Currencies.";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(35) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

            for (clsCurrency Currency : vCurrencies)
            {
                PrintClientRecordLine(Currency);
                cout << endl;
            }
     
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

	

};

