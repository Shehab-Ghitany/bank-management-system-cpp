
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen :protected clsScreen

{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.getAccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nPlease enter your FirstName : " << endl;
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nPlease enter your LastName : " << endl;
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nPlease enter your Email : " << endl;
		Client.Email = clsInputValidate::ReadString();

		cout << "\nPlease enter your Phone : " << endl;
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nPlease enter your Password : " << endl;
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nPlease enter your Balance : " << endl;
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}

public:

	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRights(clsBankUser::enPermissions::pUpdateClients))
		{
			return;
		}

		_DrawScreenHeader("\tUpdate Client Screen");

		string AccountNumber = "";

		cout << "Please enter your AccountNumber : " << endl;
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not Found, Please try again\n";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::FindClient(AccountNumber);
		_PrintClient(Client1);

		cout << "\nAre you sure you want to update this client y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\n\nUpdate Client Info";
			cout << "\n--------------------\n";

			_ReadClientInfo(Client1);

			clsBankClient::enSaveResults SaveResults;
			SaveResults = Client1.Save();

			switch (SaveResults)
			{
			case clsBankClient::enSaveResults::svSucceeded:
			{
				cout << "\nAccount Updated Successfully :-)\n";
				_PrintClient(Client1);
				break;
			}

			case clsBankClient::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nError account was not saved because it's Empty\n";
				break;
			}

			}
		}
	}

};
