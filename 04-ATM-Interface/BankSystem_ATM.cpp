#include <iostream>  
#include <cstdlib>    
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


enum enChoiseTransactions { QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5 };

struct stClientData {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
};

const string ClientsFileName = "Clients.txt";

stClientData CurrentClient;
void Login();
void ATMMainMain();


void PressAnyKeyToATMMainMenu()
{
	cout << "\n\n\nPress any key to go back to ATM Main Menu...";
	system("pause>nul");
	ATMMainMain();
}

vector <string> VSplitString(string Write, string delim = " ")
{
	vector <string> SplitString;

	short pos = 0;
	string sword;

	while ((pos = Write.find(delim)) != std::string::npos)
	{
		sword = Write.substr(0, pos);
		if (sword != "")
		{
			SplitString.push_back(sword);
		}
		Write.erase(0, pos + delim.length());
	}

	if (Write != "")
	{
		SplitString.push_back(Write);
	}
	return SplitString;
}

stClientData ConvertLinetoRecord(string Line, string delim = "#//#")
{
	stClientData ClientData;
	vector <string> SplitString;

	SplitString = VSplitString(Line, delim);

	ClientData.AccountNumber = SplitString[0];
	ClientData.PinCode = SplitString[1];
	ClientData.Name = SplitString[2];
	ClientData.Phone = SplitString[3];
	ClientData.AccountBalance = stod(SplitString[4]);

	return ClientData;
}

vector <stClientData> LoadClientDataFromFile(string ClientsFileName)
{
	vector <stClientData> vClients;
	fstream myFile;
	myFile.open(ClientsFileName, ios::in);

	if (myFile.is_open())
	{
		string Line;
		stClientData Client;

		while (getline(myFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}

		myFile.close();
	}
	return vClients;
}

bool FindClientByAccountNumber(string AccountNumber, string PinCode, stClientData& Client, vector <stClientData>& vClients)
{
	vClients = LoadClientDataFromFile(ClientsFileName);

	for (stClientData& C : vClients)
	{
		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

string ConvertRecordToLine(stClientData Client, string delim = "#//#") {
	string  Write = "";

	Write += Client.AccountNumber + delim;
	Write += Client.PinCode + delim;
	Write += Client.Name + delim;
	Write += Client.Phone + delim;
	Write += to_string(Client.AccountBalance);

	return Write;
}

vector <stClientData> SaveClientsDataToFile(string ClientsFileName, vector <stClientData> vClients)
{
	fstream myFile;
	myFile.open(ClientsFileName, ios::out);

	string DataLine;

	if (myFile.is_open())
	{

		for (stClientData C : vClients)
		{
			{
				DataLine = ConvertRecordToLine(C);
				myFile << DataLine << endl;
			}
		}

		myFile.close();
	}
	return vClients;
}








void DoneWithDrawTransaction(vector <stClientData>& vClients, double NewAmount = 0.0, bool IsDeposit = false)
{

	for (stClientData& C : vClients)
	{
		if (C.AccountNumber == CurrentClient.AccountNumber)
		{
			if (IsDeposit)
				C.AccountBalance += NewAmount;
			else
				C.AccountBalance -= NewAmount;


			CurrentClient.AccountBalance = C.AccountBalance;

			break;
		}
	}

	SaveClientsDataToFile(ClientsFileName, vClients);
	cout << "\n\nDone Successfully new balance is " << CurrentClient.AccountBalance << endl << endl;

	PressAnyKeyToATMMainMenu();
}

int QuickChoiseToNewAmount(short Choose)
{

	int NewAmount = 0;
	switch (Choose)
	{
	case 1:
		NewAmount = 20;
		break;

	case 2:
		NewAmount = 50;
		break;

	case 3:
		NewAmount = 100;
		break;

	case 4:
		NewAmount = 200;
		break;

	case 5:
		NewAmount = 400;
		break;

	case 6:
		NewAmount = 600;
		break;

	case 7:
		NewAmount = 800;
		break;

	case 8:
		NewAmount = 1000;
		break;
	}

	return NewAmount;
}

bool ConfirmWithdraw()
{
	char answer = 'n';
	cout << "\n\nAre you sure you want to perform this transaction? y/n ? ";
	cin >> answer;
	return tolower(answer) == 'y';
}

void YourChooseQuickwithdraw(vector <stClientData>& vClients, short Choose)
{
	int NewAmount = 0;

	do {
		if (Choose == 9)
		{
			ATMMainMain();
			return;
		}

		NewAmount = QuickChoiseToNewAmount(Choose);

		if (!ConfirmWithdraw())
		{
			PressAnyKeyToATMMainMenu();
			return;
		}



		if (NewAmount > CurrentClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentClient.AccountBalance;
			cout << "\nPlease enter another amount? ";
			cin >> Choose;
			continue;
		}

		break;

	} while (true);


	DoneWithDrawTransaction(vClients, NewAmount);

}

void PrintQuickWithdrawHeader()
{
	cout << string(43, '=') << "\n";
	cout << "\t\t Quick Withdraw\n";
	cout << string(43, '=') << "\n";
}

void QuickWithdrawScreen(vector <stClientData>& vClients)
{
	PrintQuickWithdrawHeader();
	cout << left << "\t" << setw(15) << "[1] 20" << setw(15) << "[2] 50" << endl;
	cout << "\t" << setw(15) << "[3] 100" << setw(15) << "[4] 200" << endl;
	cout << "\t" << setw(15) << "[5] 400" << setw(15) << "[6] 600" << endl;
	cout << "\t" << setw(15) << "[7] 800" << setw(15) << "[8] 1000" << endl;
	cout << "\t" << setw(15) << "[9] Exit" << endl;
	cout << string(43, '=') << "\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance;
	cout << "\nChoose what to withdraw from [1] to [9] ? ";

	short Choose = 1;

	do {
		cin >> Choose;
	} while (Choose > 9 || Choose <= 0);

	YourChooseQuickwithdraw(vClients, Choose);

}






void PrintNormalWithdrawHeader()
{
	cout << string(43, '=') << "\n";
	cout << "\t\t Normal Withdraw Screen\n";
	cout << string(43, '=') << "\n";
}

void NormalWithdrawScreen(vector <stClientData>& vClients)
{
	int NewAmount = 0;

	PrintNormalWithdrawHeader();
	cout << "Your Balance is " << CurrentClient.AccountBalance;

	do {
		cout << "\nEnter an amount multiple of 5's ? ";
		cin >> NewAmount;
	} while (NewAmount % 5 != 0);


	if (!ConfirmWithdraw())
	{
		PressAnyKeyToATMMainMenu();
		return;
	}


	while (NewAmount > CurrentClient.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentClient.AccountBalance;
		cout << "\nPlease enter another amount? ";
		cin >> NewAmount;
	}

	DoneWithDrawTransaction(vClients, NewAmount);

	PressAnyKeyToATMMainMenu();
}




void PrintDepositHeader()
{
	cout << string(43, '=') << "\n";
	cout << "\t\t Deposit Screen\n";
	cout << string(43, '=') << "\n";
}

void DepositScreen(vector <stClientData>& vClients)
{
	int NewAmount = 0;

	PrintDepositHeader();
	cout << "Your Balance is " << CurrentClient.AccountBalance;

	do {
		cout << "\nEnter an amount multiple of 5's ? ";
		cin >> NewAmount;
	} while (NewAmount % 5 != 0);


	if (!ConfirmWithdraw())
	{
		PressAnyKeyToATMMainMenu();
		return;
	}


	while (NewAmount <= 0)
	{
		cout << "\nDeposit failed: The amount must be a positive number.";
		cout << "\nPlease enter another amount? ";
		cin >> NewAmount;
	}

	DoneWithDrawTransaction(vClients, NewAmount, true);

	PressAnyKeyToATMMainMenu();
}






void PrintCheckBalanceHeader()
{
	cout << string(35, '=');
	cout << "\n\t Check Balance Screen";
	cout << endl << string(35, '=') << endl;
}

void CheckBalanceScreen()
{
	PrintCheckBalanceHeader();

	cout << "Your Balance is " << CurrentClient.AccountBalance;

	PressAnyKeyToATMMainMenu();
}





stClientData ReadClientLogin()
{
	stClientData Client;

	cout << "Enter Account Number? ";
	cin >> Client.AccountNumber;

	cout << "Enter PinCode? ";
	cin >> Client.PinCode;

	return Client;
}

void PrintLoginHeader()
{
	cout << string(43, '=') << "\n";
	cout << "\t\t Login Screen\n";
	cout << string(43, '=') << "\n";
}



enChoiseTransactions MainMenuScreen()
{
	cout << string(43, '=') << "\n";
	cout << "\t\tATM Main Menu Screen\n";
	cout << string(43, '=') << "\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << string(43, '=') << "\n";

	short Choose = 1;
	do {
		cout << "Choose what do you want to do? [1 to 5]? ";
		cin >> Choose;
	} while (Choose > 5 || Choose <= 0);
	return (enChoiseTransactions)Choose;
}


void SetChoiseScreen(enChoiseTransactions UserCoise, vector <stClientData>& vClients)
{

	switch (UserCoise)
	{
	case enChoiseTransactions::QuickWithdraw:
		system("cls");
		QuickWithdrawScreen(vClients);

	case enChoiseTransactions::NormalWithdraw:
		system("cls");
		NormalWithdrawScreen(vClients);

	case enChoiseTransactions::Deposit:
		system("cls");
		DepositScreen(vClients);

	case enChoiseTransactions::CheckBalance:
		system("cls");
		CheckBalanceScreen();

	case enChoiseTransactions::Logout:
		system("cls");
		Login();
		break;
	}

}

void ATMMainMain()
{
	vector <stClientData> vClients;
	enChoiseTransactions ClientChoise;

	do {
		system("cls");
		vClients = LoadClientDataFromFile(ClientsFileName);
		ClientChoise = MainMenuScreen();

		SetChoiseScreen(ClientChoise, vClients);

	} while (ClientChoise != enChoiseTransactions::Logout);


}

void Login()
{
	stClientData Client;
	vector <stClientData > vClients;
	bool LoginSuccess = false;
	bool FirstTry = true;

	do
	{
		system("cls");
		PrintLoginHeader();

		if (!FirstTry)
		{
			cout << "\nInvalid Account Number/PinCode! Please try again.\n\n";
		}

		Client = ReadClientLogin();

		LoginSuccess = FindClientByAccountNumber(Client.AccountNumber, Client.PinCode, Client, vClients);
		FirstTry = false;

	} while (!LoginSuccess);

	CurrentClient = Client;

	ATMMainMain();

}

int main()
{
	Login();
	return 0;
}