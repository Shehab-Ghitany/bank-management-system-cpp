#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsBankClient.h"
#include "clsString.h"
using namespace std;

class clsTransferLogScreen :protected clsScreen
{
private:

    static void PrintTransferLogRecordLine(vector <string> Line)
    {
        cout << setw(8) << left << "" << "| " << setw(22) << left << Line[0];
        cout << "| " << setw(8) << left << Line[1];
        cout << "| " << setw(8) << left << Line[2];
        cout << "| " << setw(13) << left << Line[3];
        cout << "| " << setw(13) << left << Line[4];
        cout << "| " << setw(13) << left << Line[5];
        cout << "| " << setw(12) << left << Line[6];
    }



public:
    
    static void ShowTransferLogScreen()
	{
        vector <string> vTransferLogLines = clsBankClient::GetTransferLogsList();

        string Title = "\t  Transfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogLines.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(22) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(13) << "Amount";
        cout << "| " << left << setw(13) << "s.Balance";
        cout << "| " << left << setw(13) << "d.Balance";
        cout << "| " << left << setw(12) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;



        for (clsString Client : vTransferLogLines)
        {
            vector <string> Line = Client.VSplitString();
            PrintTransferLogRecordLine(Line);
            cout << endl;
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

	}




};

