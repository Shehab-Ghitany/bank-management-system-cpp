#include <iostream>  
#include <cstdlib>    
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

enum enChoise { ShowClintList = 1, AddClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, Transactions = 6, Exit = 7 };
enum enChoiseTransactions { Deposite = 1, Withdraw = 2, TotalBalances = 3, TransMainMenu = 4 };

struct stClientData {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

const string ClientsFileName = "Clients.txt";




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

void PrintClientData(stClientData ClientData)
{
	cout << left << "| " << setw(16) << ClientData.AccountNumber;
	cout << "| " << setw(10) << ClientData.PinCode;
	cout << "| " << setw(40) << ClientData.Name;
	cout << "| " << setw(12) << ClientData.Phone;
	cout << "| " << setw(12) << ClientData.AccountBalance;
}

void PrintClientList(vector <stClientData>& vClients, bool AddExtra = false)
{
	cout << endl << string(5, '\t') << "Client List (" << vClients.size() << ") Client(s)." << endl;
	cout << string(100, '_') << endl << endl;
	cout << left << "| " << setw(16) << "Account Number";
	cout << "| " << setw(10) << "Pin Code";
	cout << "| " << setw(40) << "Client Name";
	cout << "| " << setw(12) << "Phone";
	cout << "| " << setw(12) << "Balance" << endl;
	cout << string(100, '_') << endl << endl;

	double TransTotalBalances = 0.0;
	for (stClientData& Client : vClients)
	{
		PrintClientData(Client);
		cout << endl;
		TransTotalBalances += Client.AccountBalance;
	}

	cout << endl << string(100, '_') << endl << endl;

	if (AddExtra == true)
	{
		cout << "\t\t\t\tTotal Balances = " << TransTotalBalances;
	}

	cout << "\n\n\nPress any key to go back to Main Menu...";
	system("pause>nul");
	system("cls");
}




bool FindClientByAccountNumber(string AccountNumber, stClientData& Client, vector <stClientData>& vClients)
{
	vClients = LoadClientDataFromFile(ClientsFileName);

	for (stClientData& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

stClientData ReadNewClient(string AccountNumber)
{
	stClientData Client;

	Client.AccountNumber = AccountNumber;
	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
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

void SaveRecordIntoFile(string FileName, string ConvertRecordToLine)
{
	fstream myFile;

	myFile.open(FileName, ios::out | ios::app);

	if (myFile.is_open())
	{
		myFile << ConvertRecordToLine << endl;

		myFile.close();
	}

}

void AddNewClient(string AccountNumber)
{
	stClientData Client = ReadNewClient(AccountNumber);
	SaveRecordIntoFile(ClientsFileName, ConvertRecordToLine(Client));
}

void PrintAddClientsHeader()
{
	cout << endl << string(35, '-');
	cout << "\n\tAdd New Clients Screen";
	cout << endl << string(35, '-');
}

void AddClients()
{
	char Addmore = 'Y';

	do
	{
		system("cls");
		PrintAddClientsHeader();

		cout << "\nAdding New Client: " << endl << endl;
		string AccountNumber = ReadClientAccountNumber();

		stClientData Client;
		bool Founded;
		do {
			vector <stClientData> vClients;
			if (Founded = FindClientByAccountNumber(AccountNumber, Client, vClients))
			{
				cout << "Client with " << AccountNumber << " already exists, Enter another Account Number ? ";
				cin >> AccountNumber;
			}
		} while (Founded == true);

		AddNewClient(AccountNumber);
		cout << "\n\nClient Added Successfully, do you want to add more clients? Y/N ?  ";
		cin >> Addmore;
	} while (toupper(Addmore) == 'Y');
}




void PrintClientCard(stClientData Client)
{
	cout << "\nThe following are the client details:\n";
	cout << string(35, '-');
	cout << "\nAccount Number: " << Client.AccountNumber;
	cout << "\nPin Code      : " << Client.PinCode;
	cout << "\nName          : " << Client.Name;
	cout << "\nPhone         : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << endl << string(35, '-');
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClientData>& vClients)
{
	for (stClientData& C : vClients)
	{

		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
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
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				myFile << DataLine << endl;
			}
		}

		myFile.close();
	}
	return vClients;
}

void PrintDeleteHeader()
{

	cout << endl << string(35, '-');
	cout << "\n\tDelete Client Screen";
	cout << endl << string(35, '-');
}

bool DeleteClientByAccountNumber(vector <stClientData>& vClients)
{
	stClientData Client;
	char Answer = 'n';

	PrintDeleteHeader();

	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);

		cout << "\n\n\nAre you sure you want delete this client? y/n ?  ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);

			vClients = LoadClientDataFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully." << endl << endl;
			cout << "Press any key to go back to Main Menu...";
			system("pause>nul");

			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found" << endl << endl;
		cout << "Press any key to go back to Main Menu...";
		system("pause>nul");

		return false;
	}

}




void PrintUpdateHeader()
{
	cout << endl << string(35, '-');
	cout << "\n\tUpdate Client Info Screen";
	cout << endl << string(35, '-') << endl;
}

void UpdateClientByAccountNumber(vector <stClientData>& vClients)
{
	stClientData Client;
	char Answer = 'n';


	PrintUpdateHeader();

	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);

		cout << "\n\n\nAre you sure you want update this client? y/n ?  ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClientData& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ReadNewClient(AccountNumber);
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Update Successfully." << endl;
			cout << "Press any key to go back to Main Menu...";
			system("pause>nul");

		}
		else
		{

			cout << "\nPress any key to go back to Main Menu...";
			system("pause>nul");

		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found";

		cout << "Press any key to go back to Main Menu...";
		system("pause>nul");

	}

}




void PrintFindHeader()
{
	cout << endl << string(35, '-');
	cout << "\n\tFind Client Screen";
	cout << endl << string(35, '-') << endl;
}

void FindClientChoise(vector <stClientData>& vClients)
{

	stClientData Client;

	PrintUpdateHeader();

	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);

		cout << endl << endl << "Press any key to go back to Main Menu...";
		system("pause>nul");
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Fount!" << endl;

		cout << "Press any key to go back to Main Menu...";
		system("pause>nul");
	}
}




void PrintClientListTransactions(vector <stClientData>& vClients)
{
	system("cls");

	PrintClientList(vClients, true);


}




void PrintWithdrawHeader()
{
	cout << endl << string(35, '-');
	cout << "\n\tWithdraw Screen";
	cout << endl << string(35, '-') << endl;
}

void PrintDepositHeader()
{
	cout << endl << string(35, '-');
	cout << "\n\tDepposti Screen";
	cout << endl << string(35, '-') << endl;
}

void Deposite_and_Withdrow_ClientByAccountNumber(vector <stClientData>& vClients, bool WithdrawExtra = false)
{
	stClientData Client;
	char Answer = 'n';
	double NewAmount = 0.0;
	double AllAmount = 0.0;
	bool repeatANagain = false;

	if (!WithdrawExtra) {
		PrintDepositHeader();
	}
	else
	{
		PrintWithdrawHeader();
	}

	do {
		string AccountNumber = ReadClientAccountNumber();

		if (FindClientByAccountNumber(AccountNumber, Client, vClients))
		{
			PrintClientCard(Client);

			if (!WithdrawExtra)
			{
				cout << "\n\nPlease enter deposite amount? ";
			}
			else
			{
				cout << "\n\nPlease enter withdraw amount? ";
			}
			cin >> NewAmount;

			cout << "\n\n\nAre you sure you want perform this transaction? y/n ?  ";
			cin >> Answer;

			if (Answer == 'y' || Answer == 'Y')
			{
				for (stClientData& C : vClients)
				{
					if (C.AccountNumber == AccountNumber)
					{
						if (!WithdrawExtra)
							C.AccountBalance += NewAmount;
						else
						{
							while (NewAmount > C.AccountBalance)
							{
								cout << "\nAmount Exceeds the balance, you can withdraw up to : " << C.AccountBalance;
								cout << "\nPlease enter another amount? ";
								cin >> NewAmount;
							}

							C.AccountBalance -= NewAmount;
						}
						AllAmount = C.AccountBalance;
						break;
					}
				}

				SaveClientsDataToFile(ClientsFileName, vClients);

				cout << "\n\nDone Successfully new balance is " << AllAmount << endl << endl;
				cout << "Press any key to go back to Transactions Menu...";
				system("pause>nul");

			}
			else
			{

				repeatANagain = false;
				cout << "\nPress any key to go back to Transations Menu...";
				system("pause>nul");

			}
		}
		else
		{
			cout << "\nClient with Account Number (" << AccountNumber << ") does Not exist" << endl;

			repeatANagain = true;
		}
	} while (repeatANagain == true);

}

enChoiseTransactions TransactionsMenuScreen()
{
	cout << string(43, '=') << "\n";
	cout << "\t\tTransactions Menu Screen\n";
	cout << string(43, '=') << "\n";
	cout << "\t[1] Deposite.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menu.\n";
	cout << string(43, '=') << "\n";

	short Choose = 1;
	do {
		cout << "Choose what do you want to do? [1 to 4]? ";
		cin >> Choose;
	} while (Choose > 4 || Choose <= 0);
	return (enChoiseTransactions)Choose;
}

void SetChoiseScreenTransactions(enChoiseTransactions UserCoiseTransactionsMenu, vector <stClientData>& vClients)
{


	switch (UserCoiseTransactionsMenu)
	{
	case enChoiseTransactions::Deposite:
		system("cls");
		Deposite_and_Withdrow_ClientByAccountNumber(vClients);
		break;

	case enChoiseTransactions::Withdraw:
		system("cls");
		Deposite_and_Withdrow_ClientByAccountNumber(vClients, true);
		break;

	case enChoiseTransactions::TotalBalances:
		PrintClientListTransactions(vClients);

	case enChoiseTransactions::TransMainMenu:
		system("cls");
	}

}

void TransactionsEnvironment(vector <stClientData>& vClients)
{
	enChoiseTransactions UserChoise;

	do {
		system("cls");
		UserChoise = TransactionsMenuScreen();

		SetChoiseScreenTransactions(UserChoise, vClients);

	} while (UserChoise != enChoiseTransactions::TransMainMenu);
}




void PrintExitHeader()
{
	cout << endl << string(35, '-');
	cout << "\n\tProgram Ends:-)";
	cout << endl << string(35, '-');

	system("pause>nul");
}




enChoise MainMenuScreen()
{
	cout << string(43, '=') << "\n";
	cout << "\t\tMain Menu Screen\n";
	cout << string(43, '=') << "\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << string(43, '=') << "\n";

	short Choose = 1;
	do {
		cout << "Choose what do you want to do? [1 to 7]? ";
		cin >> Choose;
	} while (Choose > 7 || Choose <= 0);
	return (enChoise)Choose;
}

void SetChoiseScreen(enChoise UserCoise, vector <stClientData>& vClients)
{

	switch (UserCoise)
	{
	case enChoise::ShowClintList:
		system("cls");
		PrintClientList(vClients);
		break;

	case enChoise::AddClient:
		AddClients();
		system("cls");
		break;

	case enChoise::DeleteClient:
		system("cls");
		DeleteClientByAccountNumber(vClients);
		break;

	case enChoise::UpdateClientInfo:
		system("cls");
		UpdateClientByAccountNumber(vClients);
		break;

	case enChoise::FindClient:
		system("cls");
		FindClientChoise(vClients);
		break;

	case enChoise::Transactions:
		system("cls");
		TransactionsEnvironment(vClients);
		break;

	case enChoise::Exit:
		system("cls");
		PrintExitHeader();
		break;
	}

}

int main()
{
	vector <stClientData> vClients;
	enChoise UserChoise;

	do {
		system("cls");
		vClients = LoadClientDataFromFile(ClientsFileName);
		UserChoise = MainMenuScreen();

		SetChoiseScreen(UserChoise, vClients);

	} while (UserChoise != enChoise::Exit);


	return 0;
}
