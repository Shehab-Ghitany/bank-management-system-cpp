#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
using namespace std;

class clsLoginScreen :protected clsScreen
{
private:

    static  bool _Login()
    {
        bool LoginFaild = false;
        short FailedLoginCounter = 3;

        string Username, Password;

        do
        {
            if (LoginFaild)
            {
                --FailedLoginCounter;
                cout << "\nInvlaid Username/Password!\n";
                cout << "You have " << FailedLoginCounter << " Trials to login.\n\n";
            }

            if (FailedLoginCounter == 0)
            {
                cout << "You are Locked after 3 faild trials\n\n";
                return false;
            }


            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsBankUser::FindUser(Username, clsUtil::EncryptText(Password));

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenu();
        return true;
    }


public:

    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();
    }


};
