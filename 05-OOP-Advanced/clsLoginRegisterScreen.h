#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsBankUser.h"
#include "clsString.h"
using namespace std;


class clsLoginRegisterScreen :protected clsScreen
{
private:

    static void PrintLoginRegisterRecordLine(vector <string> Line)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << Line[0];
        cout << "| " << setw(20) << left << Line[1];
        cout << "| " << setw(12) << left << Line[2];
        cout << "| " << setw(20) << left << Line[3];
    }

public:

    static void ShowLoginRegisterScreen()
    {

        if (!CheckAccessRights(clsBankUser::enPermissions::pLoginRegister))
        {
            return;// this will exit the function and it will not continue
        }


        vector <string> vLoginRegisterLines = clsBankUser::GetLoginRegistersList();

        string Title = "\t  Login Register List Screen";
        string SubTitle = "\t    (" + to_string(vLoginRegisterLines.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
        cout << "| " << left << setw(20) << "User Client";
        cout << "| " << left << setw(12) << "Password";
        cout << "| " << left << setw(20) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


            for (clsString Client : vLoginRegisterLines)
            {
                vector <string> Line = Client.VSplitString();
                PrintLoginRegisterRecordLine(Line);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }


};

