#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
using namespace std;

class clsBankUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

	static clsBankUser _GetEmptyUserObject()
	{
		return clsBankUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsBankUser _ConvertLinetoObject(string Line, string delim = "#//#")
	{
		vector <string> SplitString = clsString::VSplitString(Line, delim);


		clsBankUser UserData(enMode::UpdateMode, SplitString[0], SplitString[1], SplitString[2], SplitString[3],
			SplitString[4], SplitString[5], stof(SplitString[6])
		);

		return UserData;
	}

	static vector <clsBankUser> _LoadUsersDataFromFile()
	{
		vector <clsBankUser> vUsers;

		fstream myFile;
		myFile.open("Users.txt", ios::in);

		if (myFile.is_open())
		{
			string Line;

			while (getline(myFile, Line))
			{
				clsBankUser User = _ConvertLinetoObject(Line);
				vUsers.push_back(User);
			}

			myFile.close();
		}
		return vUsers;
	}

	static string _ConvertUserObjectToLine(clsBankUser UserData, string delim = "#//#")
	{
		string  UserLine = "";

		UserLine += UserData.FirstName + delim;
		UserLine += UserData.LastName + delim;
		UserLine += UserData.Email + delim;
		UserLine += UserData.Phone + delim;
		UserLine += UserData.UserName + delim;
		UserLine += UserData.Password + delim;
		UserLine += to_string(UserData.Permissions);

		return UserLine;
	}

	static void _SaveUsersDataToFile(vector <clsBankUser> vUsers)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::out);

		string DataLine;

		if (myFile.is_open())
		{

			for (clsBankUser C : vUsers)
			{
				if (C._MarkedForDelete == false)
				{
					DataLine = _ConvertUserObjectToLine(C);
					myFile << DataLine << endl;
				}
			}

			myFile.close();
		}
	}

	void _Update()
	{
		vector < clsBankUser > _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsBankUser& C : _vUsers)
		{
			if (C.UserName == UserName)
			{
				C = *this;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += Password + Seperator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}

	static vector <string> _LoadLoginRegisterDataFromFile()
	{
		vector <string> vLoginRegisters;

		fstream myFile;
		myFile.open("LoginRegister.txt", ios::in);

		if (myFile.is_open())
		{
			string Line;

			while (getline(myFile, Line))
			{
				vLoginRegisters.push_back(Line);
			}

			myFile.close();
		}
		return vLoginRegisters;
	}

public:

    clsBankUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions)
        :clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    void setUserName(string UserName)
    {
        _UserName = UserName;
    }
    string getUserName()
    {
        return _UserName;
    }
    __declspec(property(get = getUserName, put = setUserName)) string UserName;

    void setPassword(string Password)
    {
        _Password = Password;
    }
    string getPassword()
    {
        return _Password;
    }
    __declspec(property(get = getPassword, put = setPassword)) string Password;

    void setPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int getPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = getPermissions, put = setPermissions)) int Permissions;


	static clsBankUser FindUser(string UserName)
	{
		vector <clsBankUser> vUsers = _LoadUsersDataFromFile();

		for (clsBankUser& C : vUsers)
		{
			if (C.UserName == UserName)
			{
				return C;
			}
		}
		return _GetEmptyUserObject();
	}

	static clsBankUser FindUser(string UserName, string Password)
	{
		vector <clsBankUser> vUsers = _LoadUsersDataFromFile();

		for (clsBankUser& C : vUsers)
		{
			if (C.UserName == UserName && C.Password == Password)
			{
				return C;
			}
		}
		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName)
	{
		clsBankUser User1 = FindUser(UserName);
		return !User1.IsEmpty();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

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
			if (clsBankUser::IsUserExist(_UserName))
			{
				return enSaveResults::svFaildUserExists;
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

	static clsBankUser GetAddNewUserObject(string UserName)
	{
		return clsBankUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete()
	{
		vector <clsBankUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsBankUser& C : _vUsers)
		{
			if (C.UserName == _UserName)
			{
				C._MarkedForDelete = true;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);


		*this = _GetEmptyUserObject();

		return true;
	}

	static vector <clsBankUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64,
		pLoginRegister = 128, pCurrencyExchange = 256
	};

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;

		if ((this->Permissions & Permission) == Permission)
			return true;
		else
			return false;
	}

	void RegisterLogIn()
	{

		string stDataLine = _PrepareLogInRecord();

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static vector <string> GetLoginRegistersList()
	{
		return _LoadLoginRegisterDataFromFile();
	}


};