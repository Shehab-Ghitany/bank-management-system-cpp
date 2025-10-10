#include <iostream>  
#include <cstdlib>    
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

enum enChoise {
	ShowClintList = 1, AddClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5,
	Transactions = 6, ManageUsers = 7, Logout = 8
};
enum enChoiseTransactions { Deposite = 1, Withdraw = 2, TotalBalances = 3, TransMainMenu = 4 };

enum enChoiseManageUsers {
	eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4,
	eFindUser = 5, ManageUsersMainMenu = 6
};

enum enPermissions
{
	pShowClientList = 1,
	pAddNewClient = 2,
	pDeleteClient = 4,
	pUpdateClient = 8,
	pFindClient = 16,
	pTransactions = 32,
	pManageUsers = 64,
	pFullAccess = -1
};

struct stClientData {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

struct stUserNameandPassword {
	string UserName = "";
	string Password = "";
	int Permissions = 0;
	bool MarkForDelete = false;
};


const string ClientsFileName = "Clients.txt";
const string UserNamePasswordFileName = "Users.txt";

stUserNameandPassword CurrentUser;

void MainMain();
void ManageUsersEnvironment(vector <stUserNameandPassword>& vUsers);


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

	PrintFindHeader();

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
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << string(43, '=') << "\n";

	short Choose = 1;
	do {
		cout << "Choose what do you want to do? [1 to 8]? ";
		cin >> Choose;
	} while (Choose > 8 || Choose <= 0);
	return (enChoise)Choose;
}





void AccessDeniedMessage()
{
	system("cls");

	cout << endl;
	cout << string(37, '-') << endl;
	cout << "Access Denied," << endl;
	cout << "You don't Have Permission To Do this," << endl;
	cout << "Please Contact Your Admin." << endl;
	cout << string(37, '-') << endl;
	cout << endl << endl << endl;

	cout << "Press any key to go back to Transactions Menu...";
	system("pause>nul");
}

bool CheckAccessPermission(enPermissions Permission)
{
	if (CurrentUser.Permissions == -1)
	{
		return true;
	}

	return (CurrentUser.Permissions & Permission);
}

string ConvertRecordToLineManageUser(stUserNameandPassword User, string delim = "#//#") {
	string  Write = "";

	Write += User.UserName + delim;
	Write += User.Password + delim;
	Write += to_string(User.Permissions);

	return Write;
}

stUserNameandPassword ConvertLinetoRecordManageUser(string Line, string delim = "#//#")
{
	stUserNameandPassword User;
	vector <string> SplitString;

	SplitString = VSplitString(Line, delim);

	User.UserName = SplitString[0];
	User.Password = SplitString[1];
	User.Permissions = stoi(SplitString[2]);


	return User;
}

vector <stUserNameandPassword> LoadUserDataFromFile(string UserNamePasswordFileName)
{
	vector <stUserNameandPassword> vUsers;
	fstream myFile;
	myFile.open(UserNamePasswordFileName, ios::in);

	if (myFile.is_open())
	{
		string Line;
		stUserNameandPassword User;

		while (getline(myFile, Line))
		{
			User = ConvertLinetoRecordManageUser(Line);
			vUsers.push_back(User);
		}

		myFile.close();
	}
	return vUsers;
}


vector <stUserNameandPassword> LoadUserFile(string UserNamePasswordFileName)
{
	vector <stUserNameandPassword> vUsers;
	fstream myFile;
	myFile.open(UserNamePasswordFileName, ios::in);

	if (myFile.is_open())
	{
		string Line;
		stUserNameandPassword User;

		while (getline(myFile, Line))
		{
			User = ConvertLinetoRecordManageUser(Line);
			vUsers.push_back(User);
		}

		myFile.close();
	}
	return vUsers;
}

bool FindUserFromFile(string UserName, string Password, stUserNameandPassword& UserNameandPassword, vector <stUserNameandPassword>& vUsers)
{
	vUsers = LoadUserFile(UserNamePasswordFileName);

	for (stUserNameandPassword& C : vUsers)
	{
		if (C.UserName == UserName && C.Password == Password)
		{
			UserNameandPassword = C;
			return true;
		}
	}
	return false;
}

void PrintUserData(stUserNameandPassword UserData)
{
	cout << left << "| " << setw(16) << UserData.UserName;
	cout << "| " << setw(10) << UserData.Password;
	cout << "| " << setw(40) << UserData.Permissions;

}

void PrintUserList(vector <stUserNameandPassword>& vUsers)
{
	cout << endl << string(5, '\t') << "Users List (" << vUsers.size() << ") User(s)." << endl;
	cout << string(100, '_') << endl << endl;
	cout << left << "| " << setw(16) << "User Name";
	cout << "| " << setw(10) << "Password";
	cout << "| " << setw(40) << "Permissions" << endl;
	cout << string(100, '_') << endl << endl;


	for (stUserNameandPassword& User : vUsers)
	{
		PrintUserData(User);
		cout << endl;
	}

	cout << endl << string(100, '_') << endl << endl;


	cout << "\n\n\nPress any key to go back to Manage Users Menu...";
	system("pause>nul");
	ManageUsersEnvironment(vUsers);

}

stUserNameandPassword ReadNewUser(stUserNameandPassword User)
{
	char Addmore = 'n';

	cout << "Do you want to give full access? y/n? ";
	cin >> Addmore;
	if (tolower(Addmore) == 'y')
	{
		User.Permissions = pFullAccess;
		return User;
	}


	cout << endl << "Do you want to give full access to : \n";
	cout << "Show Client List? y/n? ";
	cin >> Addmore;
	if (tolower(Addmore) == 'y')
	{
		User.Permissions = pShowClientList;
	}

	cout << "Add New Client? y/n? ";
	cin >> Addmore;
	if (tolower(Addmore) == 'y')
	{
		User.Permissions += pAddNewClient;
	}

	cout << "Delete Client? y/n? ";
	cin >> Addmore;
	if (tolower(Addmore) == 'y')
	{
		User.Permissions += pDeleteClient;
	}

	cout << "Update Client? y/n? ";
	cin >> Addmore;
	if (tolower(Addmore) == 'y')
	{
		User.Permissions += pUpdateClient;
	}
	cout << "Find Client? y/n? ";
	cin >> Addmore;

	if (tolower(Addmore) == 'y')
	{
		User.Permissions += pFindClient;
	}
	cout << "Transactions? y/n? ";
	cin >> Addmore;

	if (tolower(Addmore) == 'y')
	{
		User.Permissions += pTransactions;
	}

	cout << "Manage Users? y/n? ";
	cin >> Addmore;

	if (tolower(Addmore) == 'y')
	{
		User.Permissions += pManageUsers;
	}




	if (User.Permissions == 127)
		User.Permissions = pFullAccess;

	return User;
}

void AddNewUser(stUserNameandPassword User)
{
	User = ReadNewUser(User);
	SaveRecordIntoFile(UserNamePasswordFileName, ConvertRecordToLineManageUser(User));
}

void PrintAddUsersHeader()
{
	cout << endl << string(35, '-');
	cout << "\n\tAdd New User Screen";
	cout << endl << string(35, '-');
}

void AddUsers()
{
	char Addmore = 'Y';

	do
	{
		system("cls");
		PrintAddUsersHeader();

		stUserNameandPassword User;

		cout << "\nAdding New User: " << endl << endl;

		cout << "Enter Username? ";
		cin >> User.UserName;
		cout << "Enter Password? ";
		cin >> User.Password;

		bool Founded;
		do {
			vector <stUserNameandPassword> vUsers;
			if (Founded = FindUserFromFile(User.UserName, User.Password, User, vUsers))
			{
				cout << "Client with " << User.UserName << " already exists, Enter another Username ? ";
				cin >> User.UserName;
				cout << "Enter Password? ";
				cin >> User.Password;
			}
		} while (Founded == true);

		AddNewUser(User);

		cout << "\n\nUser Added Successfully, do you want to add more Users? Y/N ?  ";
		cin >> Addmore;
	} while (toupper(Addmore) == 'Y');
}



void PrintUserCard(stUserNameandPassword User)
{
	cout << "\nThe following are the User details:\n";
	cout << string(35, '-');
	cout << "\nUsername      : " << User.UserName;
	cout << "\nPassword      : " << User.Password;
	cout << "\nPermissions   : " << User.Permissions;
	cout << endl << string(35, '-');
}

bool MarkUserForDeleteByUserName(string Username, vector <stUserNameandPassword>& vUsers)
{
	for (stUserNameandPassword& C : vUsers)
	{

		if (C.UserName == Username)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <stUserNameandPassword> SaveUsersDataToFile(string UserNamePasswordFileName, vector <stUserNameandPassword> vUsers)
{
	fstream myFile;
	myFile.open(UserNamePasswordFileName, ios::out);

	string DataLine;

	if (myFile.is_open())
	{

		for (stUserNameandPassword C : vUsers)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLineManageUser(C);
				myFile << DataLine << endl;
			}
		}

		myFile.close();
	}
	return vUsers;
}

void PrintDeleteUserHeader()
{
	cout << endl << string(35, '-');
	cout << "\n\tDelete Users Screen";
	cout << endl << string(35, '-') << endl;
}

bool DeleteUserByUserName(vector <stUserNameandPassword >& vUsers)
{
	stUserNameandPassword User;
	char Answer = 'n';

	bool BlockedAdmin = false;


	PrintDeleteUserHeader();

	cout << "\nDelete Users Screen: " << endl << endl;

	do {
		cout << "\nEnter Username? ";
		cin >> User.UserName;
		cout << "Enter Password? ";
		cin >> User.Password;

		if (BlockedAdmin = User.UserName == "Admin" && User.Password == "1234")
		{
			cout << endl << endl << "You cannot Delete This User.";
		}
	} while (BlockedAdmin == true);

	if (FindUserFromFile(User.UserName, User.Password, User, vUsers))
	{
		PrintUserCard(User);

		cout << "\n\n\nAre you sure you want delete this user? y/n ?  ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			MarkUserForDeleteByUserName(User.UserName, vUsers);
			SaveUsersDataToFile(UserNamePasswordFileName, vUsers);

			vUsers = LoadUserDataFromFile(UserNamePasswordFileName);

			cout << "\n\nUser Deleted Successfully." << endl << endl;
			cout << "Press any key to go back to Manage Users Menu...";
			system("pause>nul");

			return true;
		}
	}
	else
	{
		cout << "\nUser with Username (" << User.UserName << ") is Not Found" << endl << endl;
		cout << "Press any key to go back to Manage Users Menu...";
		system("pause>nul");

		return false;
	}

}




void PrintUpdateUserHeader()
{
	cout << endl << string(35, '-');
	cout << "\n\tUpdate Users Screen";
	cout << endl << string(35, '-') << endl;
}

void UpdateUserByUserName(vector <stUserNameandPassword >& vUsers)
{
	stUserNameandPassword User;
	char Answer = 'n';

	bool BlockedAdmin = false;


	PrintUpdateUserHeader();


	do {
		cout << "\nEnter Username? ";
		cin >> User.UserName;
		cout << "Enter Password? ";
		cin >> User.Password;

		if (BlockedAdmin = User.UserName == "Admin" && User.Password == "1234")
		{
			cout << endl << endl << "You cannot Delete This User.";
		}
	} while (BlockedAdmin == true);


	if (FindUserFromFile(User.UserName, User.Password, User, vUsers))
	{
		PrintUserCard(User);

		cout << "\n\n\nAre you sure you want update this user? y/n ?  ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (stUserNameandPassword& C : vUsers)
			{
				if (C.UserName == User.UserName)
				{
					cout << "Enter Password? ";
					cin >> User.Password;

					C.Password = User.Password;

					C = ReadNewUser(User);
					break;
				}
			}

			SaveUsersDataToFile(UserNamePasswordFileName, vUsers);

			cout << "\n\nUser Update Successfully." << endl;
			cout << "Press any key to go back to Manage Users Menu...";
			system("pause>nul");

		}
		else
		{

			cout << "\nPress any key to go back to Manage Users Menu...";
			system("pause>nul");

		}
	}
	else
	{
		cout << "\nClient with Account Number (" << User.UserName << ") is Not Found";

		cout << "Press any key to go back to Manage Users Menu...";
		system("pause>nul");

	}

}




void PrintFindUserHeader()
{
	cout << endl << string(35, '-');
	cout << "\n\tFind User Screen";
	cout << endl << string(35, '-') << endl;
}

void FindUserChoise(vector <stUserNameandPassword>& vUsers)
{

	stUserNameandPassword User;

	PrintFindUserHeader();


	cout << "Enter Username? ";
	cin >> User.UserName;
	cout << "Enter Password? ";
	cin >> User.Password;

	if (FindUserFromFile(User.UserName, User.Password, User, vUsers))
	{
		PrintUserCard(User);

		cout << endl << endl << "Press any key to go back to Manage Users Menu...";
		system("pause>nul");
	}
	else
	{
		cout << "\nUser with UserName(" << User.UserName << ") is Not Fount!" << endl;

		cout << "Press any key to go back to Manage Users Menu...";
		system("pause>nul");
	}
}




enChoiseManageUsers ManageUsersMenuScreen()
{
	cout << string(43, '=') << "\n";
	cout << "\t\tManage Users Menu Screen\n";
	cout << string(43, '=') << "\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << string(43, '=') << "\n";

	short Choose = 1;
	do {
		cout << "Choose what do you want to do? [1 to 6]? ";
		cin >> Choose;
	} while (Choose > 6 || Choose <= 0);
	return (enChoiseManageUsers)Choose;
}

void SetChoiseScreenManageUsers(enChoiseManageUsers UserCoiseManageUsersMenu, vector <stUserNameandPassword>& vUsers)
{

	switch (UserCoiseManageUsersMenu)
	{
	case enChoiseManageUsers::eListUsers:
		system("cls");
		PrintUserList(vUsers);
		break;

	case enChoiseManageUsers::eAddNewUser:
		system("cls");
		AddUsers();
		break;

	case enChoiseManageUsers::eDeleteUser:
		system("cls");
		DeleteUserByUserName(vUsers);
		break;

	case enChoiseManageUsers::eUpdateUser:
		system("cls");
		UpdateUserByUserName(vUsers);
		break;

	case enChoiseManageUsers::eFindUser:
		system("cls");
		FindUserChoise(vUsers);
		break;

	case enChoiseManageUsers::ManageUsersMainMenu:
		system("cls");
		MainMain();
	}

}

void ManageUsersEnvironment(vector <stUserNameandPassword>& vUsers)
{
	enChoiseManageUsers  UserChoise;

	do {
		system("cls");
		vUsers = LoadUserDataFromFile(UserNamePasswordFileName);
		UserChoise = ManageUsersMenuScreen();

		SetChoiseScreenManageUsers(UserChoise, vUsers);

	} while (UserChoise != enChoiseManageUsers::ManageUsersMainMenu);
}




void PrintLoginHeader()
{
	cout << endl << string(35, '-');
	cout << "\n\t Login Screen";
	cout << endl << string(35, '-') << endl;
}

stUserNameandPassword ReadUserLogin()
{
	stUserNameandPassword User;

	cout << "Enter Username? ";
	cin >> User.UserName;

	cout << "Enter Password? ";
	cin >> User.Password;

	return User;
}

void Login()
{
	stUserNameandPassword User;
	vector <stUserNameandPassword > vUsers;
	bool LoginSuccess = false;
	bool FirstTry = true;

	do
	{
		system("cls");
		PrintLoginHeader();

		if (!FirstTry)
		{
			cout << "\nInvalid UserName/Password! Please try again.\n\n";
		}

		User = ReadUserLogin();

		LoginSuccess = FindUserFromFile(User.UserName, User.Password, User, vUsers);
		FirstTry = false;

	} while (!LoginSuccess);

	CurrentUser = User;

	MainMain();

}







void SetChoiseScreen(enChoise UserCoise, vector <stClientData>& vClients, vector <stUserNameandPassword>& vUsers)
{

	switch (UserCoise)
	{
	case enChoise::ShowClintList:
		if (CheckAccessPermission(enPermissions::pShowClientList))
		{
			system("cls");
			PrintClientList(vClients);
		}
		else
		{
			AccessDeniedMessage();
		}

		break;

	case enChoise::AddClient:
		if (CheckAccessPermission(enPermissions::pAddNewClient))
		{
			AddClients();
			system("cls");
		}
		else
		{
			AccessDeniedMessage();
		}

		break;

	case enChoise::DeleteClient:
		if (CheckAccessPermission(enPermissions::pDeleteClient))
		{
			system("cls");
			DeleteClientByAccountNumber(vClients);
		}
		else
		{
			AccessDeniedMessage();
		}

		break;

	case enChoise::UpdateClientInfo:
		if (CheckAccessPermission(enPermissions::pUpdateClient))
		{
			system("cls");
			UpdateClientByAccountNumber(vClients);
		}
		else
		{
			AccessDeniedMessage();
		}

		break;

	case enChoise::FindClient:
		if (CheckAccessPermission(enPermissions::pFindClient))
		{
			system("cls");
			FindClientChoise(vClients);
		}
		else
		{
			AccessDeniedMessage();
		}

		break;

	case enChoise::Transactions:
		if (CheckAccessPermission(enPermissions::pTransactions))
		{
			system("cls");
			TransactionsEnvironment(vClients);
		}
		else
		{
			AccessDeniedMessage();
		}

		break;

	case enChoise::ManageUsers:
		if (CheckAccessPermission(enPermissions::pManageUsers))
		{
			system("cls");
			ManageUsersEnvironment(vUsers);
		}
		else
		{
			AccessDeniedMessage();
		}

		break;

	case enChoise::Logout:
		system("cls");
		Login();
		break;
	}

}

void MainMain()
{
	vector <stClientData> vClients;
	vector <stUserNameandPassword> vUsers;
	enChoise UserChoise;

	do {
		system("cls");
		vClients = LoadClientDataFromFile(ClientsFileName);
		UserChoise = MainMenuScreen();

		SetChoiseScreen(UserChoise, vClients, vUsers);

	} while (UserChoise != enChoise::Logout);


}

int main()
{
	Login();
	return 0;
}