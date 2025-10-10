#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;

	bool _MarkedForDelete = false;

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsBankClient _ConvertLinetoObject(string Line, string delim = "#//#")
	{
		vector <string> SplitString = clsString::VSplitString (Line, delim);


		clsBankClient ClientData(enMode::UpdateMode, SplitString[0], SplitString[1], SplitString[2], SplitString[3],
			SplitString[4], SplitString[5], stof(SplitString[6])
		);

		return ClientData;
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;

		fstream myFile;
		myFile.open("Clients.txt", ios::in);

		if (myFile.is_open())
		{
			string Line;

			while (getline(myFile, Line))
			{
				clsBankClient Client = _ConvertLinetoObject(Line);
				vClients.push_back(Client);
			}

			myFile.close();
		}
		return vClients;
	}

	static string _ConvertClientObjectToLine(clsBankClient ClientData, string delim = "#//#")
	{
		string  ClientLine = "";

		ClientLine += ClientData.FirstName + delim;
		ClientLine += ClientData.LastName + delim;
		ClientLine += ClientData.Email + delim;
		ClientLine += ClientData.Phone + delim;
		ClientLine += ClientData.getAccountNumber() + delim;
		ClientLine += ClientData.PinCode + delim;
		ClientLine += to_string(ClientData.AccountBalance);

		return ClientLine;
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::out);

		string DataLine;

		if (myFile.is_open())
		{

			for (clsBankClient C : vClients)
			{
				if (C._MarkedForDelete == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					myFile << DataLine << endl;
				}
			}

			myFile.close();
		}
	}

	void _Update()
	{
		vector < clsBankClient > _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.getAccountNumber() == getAccountNumber())
			{
				C = *this;
				break;
			}

		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}



	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
										string UserName, string Seperator = "#//#")
	{
		string TransferLogRecord = "";

		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord +=  getAccountNumber()  + Seperator;
		TransferLogRecord += DestinationClient.getAccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(getAccountBalance()) + Seperator;
		TransferLogRecord += to_string(DestinationClient.getAccountBalance()) + Seperator;
		TransferLogRecord += UserName;

		return TransferLogRecord;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
	{

		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static vector <string> _LoadTransferLogDataFromFile()
	{
		vector <string> vTransferLogs;

		fstream myFile;
		myFile.open("TransferLog.txt", ios::in);

		if (myFile.is_open())
		{
			string Line;

			while (getline(myFile, Line))
			{
				vTransferLogs.push_back(Line);
			}

			myFile.close();
		}
		return vTransferLogs;
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}


	string getAccountNumber()
	{
		return _AccountNumber;
	}

	void setPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string getPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	void setAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float getAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;


	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}*/

	static clsBankClient FindClient(string AccountNumber)
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.getAccountNumber() == AccountNumber)
			{
				return C;
			}
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient FindClient(string AccountNumber, string PinCode)
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		
		for (clsBankClient& C : vClients)
		{
			if (C.getAccountNumber() == AccountNumber && C.PinCode == PinCode)
			{
				return C;
			}
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = FindClient(AccountNumber);
		return !Client1.IsEmpty();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{

		case enMode::EmptyMode:
		{
			return enSaveResults::svFaildEmptyObject;
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to file or database
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				//We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}

		}



	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.getAccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}

		}

		_SaveClientsDataToFile(_vClients);


		*this = _GetEmptyClientObject();

		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();
		double TotalBalances = 0;

		for (clsBankClient& C : vClients)
		{
			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(float Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}


	bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);

		return true;
	}

	static vector <string> GetTransferLogsList()
	{
		return _LoadTransferLogDataFromFile();
	}

};

