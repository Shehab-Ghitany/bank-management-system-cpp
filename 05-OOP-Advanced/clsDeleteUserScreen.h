#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen :protected clsScreen
{
private:

    static void _PrintUser(clsBankUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";
    }

public:

    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\tDelete User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsBankUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsBankUser User1 = clsBankUser::FindUser(UserName);


        _PrintUser(User1);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            bool Deleted = User1.Delete();

            if (Deleted)
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
                system("pause>0");

                if (!clsBankUser::IsUserExist(CurrentUser.UserName))
                {
                    system("cls");
                    cout << "\nYou deleted the account you are currently logged in with!\n";
                    CurrentUser = clsBankUser::FindUser("", "");
                    system("pause>0");
                    return; 
                }

            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }

    }

};
