#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "MyStringLib.h"
#include "MyInputLib.h"
#include <limits>


using namespace std;
using namespace MyStringLib;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

namespace MyBankDataLib
{
	string GetClientsFileName()
	{
		return ClientsFileName;
	}
	string GetUsersFileName()
	{
		return UsersFileName;
	}
	struct stClientData
	{
		string AccountNumber = "";
		string Name = "";
		string Phone = "";
		string PinCode = "";
		double AccountBalance = 0;
		bool MarkForDelete = false;
	};
	struct stUser
	{
		string UserName = "";
		string Password = "";
		short Permissions = 0;
		bool MarkForDelete = false;
	};
	
	enum enMainMenuOptions {
		eShowClientsList = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eMangeUsers = 7, eLogout = 8
	};
	enum enTransactions {
		eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenu = 4
	};
	enum enManageUsersOptions{
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenuBack = 6
	};
	enum enPermissions {
		epShowClientsList = 1, epAddNewClient = 2, epDeleteClient = 4, epUpdateClient = 8, epFindClient = 16, epTransactions = 32, epMangeUsers = 64, epAll = -1
	};

	bool IsClientExistsByAccountNumber(const string& FileName, const string& AccountNumber);
	
	vector<stUser> LoadUsersDataFromFile(string FileName);
	//stClientData ConvertLineToRecord();
	stUser CurrentUser;
	void AccessDenied(bool GoBackToMainMenu = true);
	bool CheckAccessPermission(enPermissions Permission)
	{
		if (CurrentUser.Permissions == enPermissions::epAll) return true;

		return((CurrentUser.Permissions & Permission) == Permission);
	};
	stClientData ReadNewClient()
	{
		stClientData Client;
		cout << "Enter Client.AccountNumber: ";
		getline(cin >> ws, Client.AccountNumber);
		Client.AccountNumber = Trim(Client.AccountNumber);
		
		while (IsClientExistsByAccountNumber(ClientsFileName, Client.AccountNumber))
		{
			cout << "Client with [" << Client.AccountNumber << "] already exists\nEnter another account number : ";
			getline(cin >> ws, Client.AccountNumber);
			Client.AccountNumber = Trim(Client.AccountNumber);
		}
		cout << "Enter Client.Name : ";
		getline(cin, Client.Name);
		Client.Name = Trim(Client.Name);
		cout << "Enter Client.Phone : ";
		getline(cin, Client.Phone);
		Client.Phone = Trim(Client.Phone);
		cout << "Enter Client.PinCode : ";
		getline(cin, Client.PinCode);
		Client.PinCode = Trim(Client.PinCode);
		cout << "Enter Client.AccountBalance: ";
		cin >> Client.AccountBalance;

cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return Client;
	}

	string ConvertRecordToLine(const stClientData& Client, string Separator = "#//#")
	{
		string Record = "";
		Record += Client.AccountNumber + Separator;
		Record += Client.Name + Separator;
		Record += Client.Phone + Separator;
		Record += Client.PinCode + Separator;
		Record += to_string(Client.AccountBalance);

		return Record;
	}
	

	stClientData ConvertLineToRecord(string Line, string Separator = "#//#")
	{
		vector<string> vString = SplitString(Line, Separator);
		stClientData Client;
		if (vString.size() < 5)
		{
			return Client; // هيرجع Struct قيمها الافتراضية فاضية ورصيدها 0
		}
		Client.AccountNumber = vString[0];
		Client.Name = vString[1];
		Client.Phone = vString[2];
		Client.PinCode = vString[3];
		Client.AccountBalance = stod(vString[4]);

		return Client;
	}

	void PrintClientCard(const stClientData& Client)
	{
		cout << "AccountNumber : " << Client.AccountNumber << endl;
		cout << "Name : " << Client.Name << endl;
		cout << "Phone : " << Client.Phone << endl;
		cout << "PinCode : " << Client.PinCode << endl;
		cout << "AccountBalance: " << Client.AccountBalance << endl;
	}
	void AddDataLineToFile(string FileName, const string DataLine)
	{
		fstream myFile;
		myFile.open(FileName, ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << DataLine << endl;
			myFile.close();
		}
	}
	vector<stClientData> LoadClientsDataFromFile(string FileName)
	{
		vector<stClientData> vClients;
		fstream myFile;
		myFile.open(FileName, ios::in);//Read (input) mode.

		if (myFile.is_open())
		{
			string line;
			stClientData Client;
			while (getline(myFile, line))
			{
				// لو السطر فاضي تماماً في الملف تخطاه فوراً ولا تقم بتحويله
				if (line == "")
					continue;
				Client = ConvertLineToRecord(line);
				vClients.push_back(Client);
			}
			myFile.close();
		}
		return vClients;
	}
	void AddNewClient(vector<stClientData>& vClients)
	{
		stClientData Client;
		Client = ReadNewClient();
		AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
		vClients = LoadClientsDataFromFile(ClientsFileName);
	}
	void AddClients(vector<stClientData>& vClients)
	{
		char AddMore = 'Y';
		do
		{
			//system("cls");
		//	cout << "Adding New Client:\n\n";
			AddNewClient(vClients);
			cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
				cin >> AddMore;
		} while (toupper(AddMore) == 'Y');
	}
	void PrintHeader(const vector<stClientData>& vClients)
	{
		cout << "\n\t\t\t\t\t Clients List (" << vClients.size() << ") Client(s)\n";
		cout << "________________________________________________________________________________________________\n";
		cout << "| " << left << setw(10) << "Acc.No";
		cout << "| " << left << setw(25) << "Name";
		cout << "| " << left << setw(16) << "Phone";
		cout << "| " << left << setw(10) << "PinCode";
		cout << "| " << left << setw(20) << "AccountBalance" << endl;
		cout << "________________________________________________________________________________________________\n";
	}
	void PrintClientRecord(const stClientData Client)
	{
		cout << "| " << left << setw(10) << Client.AccountNumber;
		cout << "| " << left << setw(25) << Client.Name;
		cout << "| " << left << setw(16) << Client.Phone;
		cout << "| " << left << setw(10) << Client.PinCode;
		cout << "| " << left << setw(20) << Client.AccountBalance << endl;
	}
	void PrintClientsTable(const vector<stClientData>& vClients)
	{
		PrintHeader(vClients);
		for (const stClientData& client : vClients) {
			PrintClientRecord(client);
		}
		cout << "________________________________________________________________________________________________\n";


	};


	bool FindClientByAccountNumber(const string& AccountNumber, stClientData& Client,const vector<stClientData>& vClients)
	{
		for (const stClientData& c : vClients)
		{
			if (AccountNumber == c.AccountNumber)
			{
				Client = c;
				return true;
			}
		}
		return false;
	}
	bool FindClientByAccountNumberAndPinCode(const string& AccountNumber, const string& PinCode, stClientData& Client,const vector<stClientData>& vClients)
	{
		for (const stClientData& c : vClients)
		{
			if (AccountNumber == c.AccountNumber && PinCode == c.PinCode)
			{
				Client = c;
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

	void SaveClientsDataToFile(string FileName, const vector<stClientData>& vClients)
	{
		fstream myFile;
		myFile.open(FileName, ios::out);

		if (myFile.is_open())
		{
			string line;
			//stClientData Client;
			for (const stClientData& c : vClients)
			{
				if (c.MarkForDelete == false)
				{
					line = ConvertRecordToLine(c);
					myFile << line << endl;
				}
			}
			myFile.close();
		}
	}

	bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClientData>& vClients)
	{
		for (stClientData& c : vClients)
		{
			if (AccountNumber == c.AccountNumber)
			{
				c.MarkForDelete = true;
				return true;
			}
		}
		return false;
	}
	void DeleteClientByAccountNumber(string AccountNumber, vector <stClientData>& vClients)
	{
		stClientData Client;
		char Answer = 'n';

		if (FindClientByAccountNumber(AccountNumber, Client, vClients))
		{

			cout << "\nThe following are the client details:\n\n";
			PrintClientCard(Client);


			cout << "\nAre you sure you want to delete this Client ? [Y/N] >> ";
			cin >> Answer;

			if (toupper(Answer) == 'Y')
			{
				MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
				SaveClientsDataToFile(ClientsFileName, vClients);
				vClients = LoadClientsDataFromFile(ClientsFileName);

				cout << "\nClient deleted successfully.\n";
			}
			else cout << "\nClient Not Deleted.\n";

		}
		else cout << "\nClient with Account Number [" << AccountNumber << "] Not Found!\n";

	}


	stClientData changeClientRecord(string AccountNumber)
	{
		stClientData Client;
		Client.AccountNumber = AccountNumber;
		cout << "Update Name : ";
		getline(cin >> ws, Client.Name);
		Client.Name = Trim(Client.Name);

		cout << "Update Phone : ";
		getline(cin, Client.Phone);
		Client.Phone = Trim(Client.Phone);

		cout << "Update Pin Code : ";
		getline(cin, Client.PinCode);
		Client.PinCode = Trim(Client.PinCode);

		cout << "Update Account Balance : ";
		cin >> Client.AccountBalance;

cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return Client;
	}
	bool UpdateRecord(string AccountNumber, vector <stClientData>& vClients)
	{
		for (stClientData& c : vClients)
		{
			if (AccountNumber == c.AccountNumber)
			{
				c = changeClientRecord(AccountNumber);
				return true;
			}
		}
		return false;
	}
	bool UpdateClientPinCode(string AccountNumber, vector <stClientData>& vClients,string NewPinCode)
	{
		for (stClientData& c : vClients)
		{
			if (AccountNumber == c.AccountNumber)
			{
				c.PinCode = NewPinCode;
				SaveClientsDataToFile(ClientsFileName, vClients);
				return true;
			}
		}
		return false;
	}
	void UpdateClientByAccountNumber(string AccountNumber, vector <stClientData>& vClients)
	{
		stClientData Client;
		char Answer = 'n';

		if (FindClientByAccountNumber(AccountNumber, Client, vClients))
		{
			cout << "\nThe following are the client details:\n\n";
			PrintClientCard(Client);

			cout << "\nAre you sure you want to Update this Client ? [Y/N] >> ";
			cin >> Answer;

			if (toupper(Answer) == 'Y')
			{

				UpdateRecord(AccountNumber, vClients);
				SaveClientsDataToFile(ClientsFileName, vClients);

				cout << "\nClient Updated Successfully.\n";
				FindClientByAccountNumber(AccountNumber, Client, vClients); // عشان نطبع البيانات الجديدة صح، بنجيبها من الفيكتور بعد ما اتحدث
				cout << "\nThe following are the updated client details:\n\n";
				PrintClientCard(Client);
			}
			else cout << "\nUpdated Cancelled.\n";

		}
		else cout << "\nClient with Account Number [" << AccountNumber << "] Not Found!\n";
	}
	bool IsClientExistsByAccountNumber(const string& FileName,
		const string& AccountNumber)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				if (Line == "") continue; 
				stClientData Client = ConvertLineToRecord(Line);
				if (Client.AccountNumber == AccountNumber)
				{
					MyFile.close();
					return true;
				}
			}
			MyFile.close();
		}
		return false; 
	}
	


	void ShowTransactionsMenuScreen(vector<stClientData>& vClients);


	void BackToMainMenu()
	{
		cout << "\n\nPress any key to go back to Main Menu...";
		system("pause>0");
	}
	void BackToTransactionsScreen()
	{
		cout << "\n\nPress any key to go back to Transactions Menu...";
		system("pause>0");
	}
	void BackToManageUsersScreen()
	{
		cout << "\n\nPress any key to go back to Manage Users Menu...";
		system("pause>0");
	}
	void showExitScreen()
	{
		system("cls");
		cout << "=========================================\n";
		cout << "\tThe End of Program ^_^\n";
		cout << "=========================================\n";
		//	system("pause>0");
	}
	void ShowClientsListScreen(const vector<stClientData>& vClients)
	{
		system("cls");
		//cout << "=========================================\n";
		//cout << "\tShow Clients Screen\n";
		//cout << "=========================================\n";
		if (!CheckAccessPermission(enPermissions::epShowClientsList))
		{
			 AccessDenied(); return;
		}
		PrintClientsTable(vClients);
		BackToMainMenu();
	}
	void AddNewClientsScreen(vector<stClientData>& vClients)
	{
		system("cls");
		if (!CheckAccessPermission(enPermissions::epAddNewClient))
		{
			 AccessDenied(); return;
		}
		cout << "=========================================\n";
		cout << "\tAdd New Client Screen\n";
		cout << "=========================================\n";
		AddClients(vClients);
		BackToMainMenu();
	}
	void DeleteClientScreen(vector<stClientData>& vClients)
	{
		system("cls");
		if (!CheckAccessPermission(enPermissions::epDeleteClient))
		{
			 AccessDenied(); return;
		}
		cout << "=========================================\n";
		cout << "\tDelete Client Screen\n";
		cout << "=========================================\n";
		DeleteClientByAccountNumber(ReadClientAccountNumber(), vClients);
		BackToMainMenu();
	}

	void UpdateClientScreen(vector<stClientData>& vClients)
	{
		system("cls");
		if (!CheckAccessPermission(enPermissions::epUpdateClient))
		{
			 AccessDenied(); return;
		}
		cout << "=========================================\n";
		cout << "\tUpdate Client Screen\n";
		cout << "=========================================\n";
		UpdateClientByAccountNumber(ReadClientAccountNumber(), vClients);
		BackToMainMenu();
	}

	void FindClientScreen(const vector<stClientData>& vClients)
	{
		system("cls");
		if (!CheckAccessPermission(enPermissions::epFindClient))
		{
			 AccessDenied(); return;
		}
		cout << "=========================================\n";
		cout << "\tFind Client Screen\n";
		cout << "=========================================\n";
		stClientData Client;
		string AccountNumber = ReadClientAccountNumber();
		if (FindClientByAccountNumber(AccountNumber, Client, vClients))
			PrintClientCard(Client);
		else cout << "\nClient with Account Number [" << AccountNumber << "] Not Found! :(\n";
		BackToMainMenu();
	}

	void PrintShortClientHeader(const vector<stClientData>& vClients)
	{
		cout << "\n\t\t\t\t\t Clients List (" << vClients.size() << ") Client(s)\n";
		cout << "________________________________________________________________________________________________\n";
		cout << "| " << left << setw(10) << "Acc.No";
		cout << "| " << left << setw(40) << "Name";
		cout << "| " << left << setw(20) << "AccountBalance" << endl;
		cout << "________________________________________________________________________________________________\n";
	}
	void PrintShortClientRecord(const stClientData Client)
	{
		cout << "| " << left << setw(10) << Client.AccountNumber;
		cout << "| " << left << setw(40) << Client.Name;
		cout << "| " << left << setw(20) << Client.AccountBalance << endl;
	}
	void PrintClientsShortTableWithTotalBalancesScreen(const vector<stClientData>& vClients)
	{
		double total = 0;
		PrintShortClientHeader(vClients);
		for (const stClientData& client : vClients) {
			PrintShortClientRecord(client);
			total += client.AccountBalance;
		}

		cout << "________________________________________________________________________________________________\n";
		cout << "\n\t\t\t\t\t Total Balances = " << total << endl;

	};
	//double CalculateTotalBalances(const vector<stClientData>& vClients)
	//{
	//	double total = 0;
	//	for (const stClientData& client : vClients) {
	//		total += client.AccountBalance;
	//	}
	//	return total;
	//}
	//void PrintClientsShortTable(const vector<stClientData>& vClients)
	//{
	//	PrintShortClientHeader(vClients);
	//	for (const stClientData& client : vClients) {
	//		PrintShortClientRecord(client);
	//	}
	//	cout << "________________________________________________________________________________________________\n";
	//};

	bool UpdateBalance(string AccountNumber, vector <stClientData>& vClients, double NewBalance)
	{
		for (stClientData& c : vClients)
		{
			if (AccountNumber == c.AccountNumber)
			{
				c.AccountBalance = NewBalance;
				SaveClientsDataToFile(GetClientsFileName(), vClients);
				return true;
			}
		}
		return false;
	}
	void WithdrawFromClientBalanceByAccountNumber(string AccountNumber, vector <stClientData>& vClients/*, double Amount ,double NewBalance*/)
	{
		stClientData Client;
		char Answer = 'n';

		if (FindClientByAccountNumber(AccountNumber, Client, vClients))
		{
			cout << "\nThe following are the client details:\n\n";

			PrintClientCard(Client);

			//Amount
			double WithdrawAmount = MyInputLib::ReadPositiveNumber("\n\nPlease Enter Withdraw Amount : ");

			while (Client.AccountBalance < WithdrawAmount)
			{
				cout << "\nAmount Exceeds the Balance!\n";
				cout << "You can withdraw up to : " << Client.AccountBalance << endl;
				WithdrawAmount = MyInputLib::ReadPositiveNumber("Please Enter another Amount : ");
			}
			double NewBalance = Client.AccountBalance - WithdrawAmount;


			cout << "\nAre you sure you want to perform this transaction ? [Y/N] >> ";
			cin >> Answer;

			if (toupper(Answer) == 'Y')
			{

				UpdateBalance(AccountNumber, vClients, NewBalance);

				cout << "New balance is [" << NewBalance << "]." << endl;
			}
			else cout << "\nNo Changes..\n";

		}
		else cout << "\nClient with Account Number [" << AccountNumber << "] Not Found!\n";
	}
	void DepositClientBalanceByAccountNumber(string AccountNumber, vector <stClientData>& vClients/*, double Amount ,double NewBalance*/)
	{
		stClientData Client;
		char Answer = 'n';

		if (FindClientByAccountNumber(AccountNumber, Client, vClients))
		{
			cout << "\nThe following are the client details:\n\n";

			PrintClientCard(Client);

			//Amount
			double DepositAmount = MyInputLib::ReadPositiveNumber("\n\nPlease Enter Deposit Amount : ");

			double NewBalance = DepositAmount + Client.AccountBalance;


			cout << "\nAre you sure you want to perform this transaction ? [Y/N] >> ";
			cin >> Answer;

			if (toupper(Answer) == 'Y')
			{

				UpdateBalance(AccountNumber, vClients, NewBalance);

				cout << "Done Successfully, New balance is [" << NewBalance << "]." << endl;
			}
			else cout << "\nNo Changes..\n";

		}
		else cout << "\nClient with Account Number [" << AccountNumber << "] Not Found!\n";
	}
	void DepositClientBalanceByAccountNumberForATM(string AccountNumber, double DepositAmount)
	{
		vector <stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
		stClientData Client;
		char Answer = 'n';

		if (FindClientByAccountNumber(AccountNumber, Client, vClients))
		{
			double NewBalance = DepositAmount + Client.AccountBalance;


			cout << "\nAre you sure you want to perform this transaction ? [Y/N] >> ";
			cin >> Answer;

			if (toupper(Answer) == 'Y')
			{

				UpdateBalance(AccountNumber, vClients, NewBalance);

				cout << "Done Successfully, New balance is [" << NewBalance << "]." << endl;
			}
			else cout << "\nNo Changes..\n";

		}
		else cout << "\nClient with Account Number [" << AccountNumber << "] Not Found!\n";
		SaveClientsDataToFile(ClientsFileName, vClients);
	}

	void ShowDepositScreen(vector<stClientData>& vClients)
	{
		stClientData Client;

		system("cls");
		cout << "=========================================\n";
		cout << "\tDeposit Screen \n";
		cout << "=========================================\n";
		string AccountNumber = "";

		AccountNumber = ReadClientAccountNumber();
		/*	double DepositAmount = MyInputLib::ReadPositiveNumber("Please Enter Deposit Amount : ");*/
			//double NewBalance = DepositAmount + Client.AccountBalance;
		DepositClientBalanceByAccountNumber(AccountNumber, vClients);

	}
	void ShowWithdrawScreen(vector<stClientData>& vClients)
	{
		stClientData Client;

		system("cls");
		cout << "=========================================\n";
		cout << "\tWithdraw Screen \n";
		cout << "=========================================\n";
		string AccountNumber = "";

		AccountNumber = ReadClientAccountNumber();
		/*	double DepositAmount = MyInputLib::ReadPositiveNumber("Please Enter Deposit Amount : ");*/
			//double NewBalance = DepositAmount + Client.AccountBalance;
		WithdrawFromClientBalanceByAccountNumber(AccountNumber, vClients);

	}

	void PerformTransactionsScreen(enTransactions TransactionsOptions, vector<stClientData>& vClients)
	{

		//	string AccountNumber = ""; 
		stClientData Client;

		switch (TransactionsOptions)
		{
		case eDeposit: ShowDepositScreen(vClients);
			BackToTransactionsScreen();
			break;
		case eWithdraw: ShowWithdrawScreen(vClients);
			BackToTransactionsScreen();
			break;
		case eTotalBalances: system("cls");
			PrintClientsShortTableWithTotalBalancesScreen(vClients);
			BackToTransactionsScreen();
			break;
		case eMainMenu:
			break;
		}
	}
	//---Users----	

	stUser ConvertLineToUserRecord(string Line, string Separator = "#//#")
	{
		vector<string> vString = SplitString(Line, Separator);
		stUser User;
		if (vString.size() < 3)
		{
			return User; 
		}
		User.UserName = vString[0];
		User.Password = vString[1];
		User.Permissions = stoi(vString[2]);

		return User;
	}
	vector<stUser> LoadUsersDataFromFile(string FileName)
	{
		vector<stUser> vUsers;
		fstream myFile;
		myFile.open(FileName, ios::in);//Read (input) mode.

		if (myFile.is_open())
		{
			string line;
			stUser User;
			while (getline(myFile, line))
			{
				// لو السطر فاضي تماماً في الملف تخطاه فوراً ولا تقم بتحويله
				if (line == "")
					continue;
				User = ConvertLineToUserRecord(line);
				vUsers.push_back(User);
			}
			myFile.close();
		}
		return vUsers;
	}

	string ConvertUserRecordToLine(const stUser& User, string Separator = "#//#")
	{
		string Record = "";
		Record += User.UserName + Separator;
		Record += User.Password + Separator;
		Record += to_string(User.Permissions);

		return Record;
	}
	void PrintUserCard(const stUser& User)
	{
		cout << "UserName : " << User.UserName << endl;
		cout << "Password : " << User.Password << endl;
		cout << "Permissions: " << User.Permissions << endl;
	}

	bool FindUserByUserNameAndPassword(const string& UserName, string& Password, stUser& User, const vector<stUser>& vUsers)
	{
		for (const stUser& u : vUsers)
		{
			if (UserName == u.UserName && Password == u.Password)
			{
				User = u;
				return true;
			}
		}
		return false;
	}
	bool FindUserByUserName(const string& UserName, stUser& User, const vector<stUser>& vUsers)
	{
		for (const stUser& c : vUsers)
		{
			if (UserName == c.UserName)
			{
				User = c;
				return true;
			}
		}
		return false;
	}
	string ReadUserName()
	{
		string UserName = "";
		cout << "\nPlease enter UserName: ";
		getline(cin >> ws, UserName);
		return UserName;
	}
	void SaveUsersDataToFile(string FileName, const vector<stUser>& vUsers)
	{
		fstream myFile;
		myFile.open(FileName, ios::out);

		if (myFile.is_open())
		{
			string line;
			//stUser User;
			for (const stUser& u : vUsers)
			{
				if (u.MarkForDelete == false)
				{
					line = ConvertUserRecordToLine(u);
					myFile << line << endl;
				}
			}
			myFile.close();
		}
	}
	bool MarkUserForDeleteByUserName(string UserName, vector <stUser>& vUsers)
	{
		for (stUser& c : vUsers)
		{
			if (UserName == c.UserName)
			{
				c.MarkForDelete = true;
				return true;
			}
		}
		return false;
	}
	bool SecureAdmin(string UserName)
	{
		string CurrentLoggedUser = MyStringLib::lowerAllString(CurrentUser.UserName);
		UserName = MyStringLib::lowerAllString(UserName);

		if (CurrentLoggedUser == "admin" || CurrentLoggedUser == "yahia")
		{
			return false;
		}
		
		if (UserName == "admin" || UserName == "yahia")
		{
			AccessDenied(0); 
			system("pause");
			return true;
		}
		return false;
	}
	void DeleteUserByUserName(string UserName, vector <stUser>& vUsers)
	{
			
		if (SecureAdmin(UserName)) 
		{
			 return;
		}

		stUser User;
		char Answer = 'n';

		if (FindUserByUserName(UserName, User, vUsers))
		{

			cout << "\nThe following are the User details:\n\n";
			PrintUserCard(User);


			cout << "\nAre you sure you want to delete this User ? [Y/N] >> ";
			cin >> Answer;

			if (toupper(Answer) == 'Y')
			{
				MarkUserForDeleteByUserName(UserName, vUsers);
				SaveUsersDataToFile(UsersFileName, vUsers);
				vUsers = LoadUsersDataFromFile(UsersFileName);

				cout << "\nUser Deleted Successfully.\n";
			}
			else cout << "\nUser Not Deleted.\n";

		}
		else cout << "\nUser with Account Number [" << UserName << "] Not Found!\n";

	}
	void AccessDenied(bool GoBackToMainMenu)
	{

		system("cls");
		system("color 04");

		cout << "\n=========================================\n";
		cout <<   "=============[Access Denied]=============\n";
		cout << "You don't have permissions to do this,\n";
		cout << "Please contact your admin.";
		cout << "\n=========================================\n";
		if(GoBackToMainMenu) BackToMainMenu();
		/*
		if(!CheckAccessPermission(epShowClientsList))
		{
			 AccessDenied(); return;
		}
		*/
	}
	short ReadPermissions()
	{
		short Permissions = 0;
		char choice = 'y';
		cout << "\nDo you want to give full access ? [Y/N] >> ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y') return Permissions = -1;

		cout << "\nDo you want to give access to :\n";

		cout << "\nShow Clients List ? [Y/N] >> ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')  Permissions += enPermissions::epShowClientsList;

		cout << "\nAdd New Client ? [Y/N] >> ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')  Permissions += enPermissions::epAddNewClient;

		cout << "\nDelete Client ? [Y/N] >> ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')  Permissions += enPermissions::epDeleteClient;

		cout << "\nUpdate Client ? [Y/N] >> ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')  Permissions += enPermissions::epUpdateClient;

		cout << "\nFind Client ? [Y/N] >> ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')  Permissions += enPermissions::epFindClient;

		cout << "\nTransactions ? [Y/N] >> ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')  Permissions += enPermissions::epTransactions;

		cout << "\nMange Users ? [Y/N] >> ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')  Permissions += enPermissions::epMangeUsers;

		return Permissions;
	}
	stUser changeUserRecord(string UserName)
	{
		stUser User;
		User.UserName = UserName;

		cout << "Update Password : ";
		getline(cin >> ws, User.Password);
		User.Password = Trim(User.Password);
		//Update Permissions 
		cout << "Update Permissions : ";
		User.Permissions = ReadPermissions();

cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return User;
	}
	bool UpdateUserRecord(string UserName, vector <stUser>& vUsers)
	{
		for (stUser& c : vUsers)
		{
			if (UserName == c.UserName)
			{
				c = changeUserRecord(UserName);
				return true;
			}
		}
		return false;
	}
	void UpdateUserByUserName(string UserName, vector <stUser>& vUsers)
	{
		if (SecureAdmin(UserName)) return;


		stUser User;
		char Answer = 'n';

		if (FindUserByUserName(UserName, User, vUsers))
		{
			cout << "\nThe following are the User details:\n\n";
			PrintUserCard(User);

			cout << "\nAre you sure you want to Update this User ? [Y/N] >> ";
			cin >> Answer;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (toupper(Answer) == 'Y')
			{

				UpdateUserRecord(UserName, vUsers);
				SaveUsersDataToFile(UsersFileName, vUsers);

				cout << "\nUser Updated Successfully.\n";
				FindUserByUserName(UserName, User, vUsers); // عشان نطبع البيانات الجديدة صح، بنجيبها من الفيكتور بعد ما اتحدث
				cout << "\nThe following are the updated User details:\n\n";
				PrintUserCard(User);
			}
			else cout << "\nUpdated Cancelled.\n";

		}
		else cout << "\nUser [" << UserName << "] Not Found!\n";
	}
	bool IsUserExistsByUserName(const string& FileName,
		const string& UserName)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				if (Line == "") continue;
				stUser User = ConvertLineToUserRecord(Line);
				if (MyStringLib::lowerAllString(User.UserName) == MyStringLib::lowerAllString(UserName))
				{
					MyFile.close();
					return true;
				}
			}
			MyFile.close();
		}
		return false;
	}

	
	stUser ReadNewUser()
	{
		stUser User;
		cout << "Enter User Name  : ";
		getline(cin >> ws, User.UserName);
		User.UserName = Trim(User.UserName);

		while (IsUserExistsByUserName(UsersFileName, User.UserName))
		{
			cout << "User Name [" << User.UserName << "] already exists\nEnter another account number : ";
			getline(cin >> ws, User.UserName);
			User.UserName = Trim(User.UserName);
		}
		cout << "Enter Password   : ";
		getline(cin, User.Password);
		User.Password = Trim(User.Password);
		cout << "Enter Permissions: ";
		User.Permissions = ReadPermissions();

cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return User;
	}

	void AddNewUser(vector<stUser>& vUsers)
	{
		stUser User;
		User = ReadNewUser();
		AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));
		vUsers = LoadUsersDataFromFile(UsersFileName);
	}
	void AddUsers(vector<stUser>& vUsers)
	{
		char AddMore = 'y';
		do
		{
			AddNewUser(vUsers);
			cout << "\nUser Added Successfully\nDo you want to add more Users ? [Y/N] >> ";
			cin >> AddMore;
		} while (tolower(AddMore) == 'y');
	}
	void PrintHeader(const vector<stUser>& vUsers)
	{
		cout << "\n\t\t\t\t\t Users List (" << vUsers.size() << ") User(s)\n";
		cout << "________________________________________________________________________________________________\n";
		cout << "| " << left << setw(15) << "UserName";
		cout << "| " << left << setw(15) << "Password";
		cout << "| " << left << setw(15) << "Permissions" << endl;
		cout << "________________________________________________________________________________________________\n";
	}
	void PrintUserRecord(const stUser User)
	{
		cout << "| " << left << setw(15) << User.UserName;
		cout << "| " << left << setw(15) << User.Password;
		cout << "| " << left << setw(15) << User.Permissions << endl;
	}
	void PrintUsersTable(const vector<stUser>& vUsers)
	{
		PrintHeader(vUsers);
		for (const stUser& User : vUsers) {
			PrintUserRecord(User);
		}
		cout << "________________________________________________________________________________________________\n";


	};
	void ShowUsersListScreen(const vector<stUser>& vUsers)
	{
		system("cls");
		//cout << "=========================================\n";
		//cout << "\tShow Users Screen\n";
		//cout << "=========================================\n";
		PrintUsersTable(vUsers);
	}
	void ShowAddNewUsersScreen(vector<stUser>& vUsers)
	{
		system("cls");
		cout << "=========================================\n";
		cout << "\tAdd New User Screen\n";
		cout << "=========================================\n";
		AddUsers(vUsers);
	}
	void ShowDeleteUserScreen(vector<stUser>& vUsers)
	{
		system("cls");
		cout << "=========================================\n";
		cout << "\tDelete User Screen\n";
		cout << "=========================================\n";
		DeleteUserByUserName(ReadUserName(), vUsers);
	}
	void ShowUpdateUserScreen(vector<stUser>& vUsers)
	{
		system("cls");
		cout << "=========================================\n";
		cout << "\tUpdate User Screen\n";
		cout << "=========================================\n";
		UpdateUserByUserName(ReadUserName(), vUsers);
	}
	void ShowFindUserScreen(const vector<stUser>& vUsers)
	{
		stUser User;
		system("cls");
		cout << "=========================================\n";
		cout << "\tFind User Screen\n";
		cout << "=========================================\n";
		string UserName = ReadUserName();
		if (FindUserByUserName(UserName, User, vUsers))
			PrintUserCard(User);
		else cout << "\nUser with Account Number [" << UserName << "] Not Found! :(\n";
	}
	void PerformManageUsersMenuScreen(enManageUsersOptions ManageUsersOptions, vector<stUser>& vUsers)
	{

		//	string UserName = ""; 
		stUser User;

		switch (ManageUsersOptions)
		{
		case eListUsers:
			ShowUsersListScreen(vUsers);
			BackToManageUsersScreen();
			break;

		case eAddNewUser:
			ShowAddNewUsersScreen(vUsers);
			BackToManageUsersScreen();
			break;

		case eDeleteUser:
			ShowDeleteUserScreen(vUsers);
			BackToManageUsersScreen();
			break;

		case eUpdateUser:
			ShowUpdateUserScreen(vUsers);
			BackToManageUsersScreen();
			break;

		case eFindUser:
			ShowFindUserScreen(vUsers);
			BackToManageUsersScreen();
			break;

		case eMainMenuBack:
			break;

		}

	}
	void ShowManageUsersScreen(vector<stUser>& vUsers)
	{
		if (!CheckAccessPermission(enPermissions::epMangeUsers))
		{
			AccessDenied();
			return; 
		}
		enManageUsersOptions Choice;

		do {
			system("cls");
			system("color 0A");

			stUser User;
			system("cls");
			cout << "\n==========================================\n";
			cout << "=========[Mange Users Menu Screen]========";
			cout << "\n==========================================\n";
			cout << "\t[1] List Users.\n";
			cout << "\t[2] Add New User.\n";
			cout << "\t[3] Delete User.\n";
			cout << "\t[4] Update User.\n";
			cout << "\t[5] Find User.\n";
			cout << "\t[6] Main Menu.\n";
			cout << "==========================================\n";
			Choice = (enManageUsersOptions)MyInputLib::ReadNumberInRange(1, 6, "Choose what do you want to do");
			PerformManageUsersMenuScreen(Choice, vUsers);
		} while (Choice != enManageUsersOptions::eMainMenuBack);
	}
	//---UsersEnd---

	void ShowTransactionsMenuScreen(vector<stClientData>& vClients)
	{
		if (!CheckAccessPermission(enPermissions::epTransactions))
		{
			 AccessDenied(); return;
		}
		enTransactions Choice;

		do {
			system("cls");
			system("color 0A");

			stClientData Client;
			system("cls");
			cout << "\n==========================================\n";
			cout << "========[Transactions Menu Screen]========";
			cout << "\n==========================================\n";
			cout << "\t[1] Deposit.\n";
			cout << "\t[2] Withdraw.\n";
			cout << "\t[3] Total Balances.\n";
			cout << "\t[4] Main Menu.\n";
			cout << "==========================================\n";
			Choice = (enTransactions)MyInputLib::ReadNumberInRange(1, 4, "Choose what do you want to do");
			PerformTransactionsScreen(Choice, vClients);
		} while (Choice != enTransactions::eMainMenu);
	}
	void Login();
	void PerformMainMenuOption(enMainMenuOptions MainMenuOptions, vector<stClientData>& vClients, vector<stUser>& vUsers)
	{

		//	string AccountNumber = ""; 
		//stClientData Client;

		switch (MainMenuOptions)
		{
		case eShowClientsList:
			ShowClientsListScreen(vClients);
			break;

		case eAddNewClient:
			AddNewClientsScreen(vClients);
			break;

		case eDeleteClient:
			DeleteClientScreen(vClients);
			break;

		case eUpdateClient:
			UpdateClientScreen(vClients);
			break;

		case eFindClient:
			FindClientScreen(vClients);
			break;

		case eTransactions:
			ShowTransactionsMenuScreen(vClients);
			break;
		case eMangeUsers:
			ShowManageUsersScreen(vUsers);
			break;
		case eLogout:
			break;
		}
	}

	void ShowMainMenuScreen(vector<stClientData>& vClients, vector<stUser>& vUsers)
	{
		enMainMenuOptions Choice;

		do {
			system("cls");
			system("color 0A");
			cout << "\n=========================================\n";
			cout << "============[Main Menu Screen]===========";
			cout << "\n=========================================\n";
			cout << "\t[1] Show Clients List.\n";
			cout << "\t[2] Add New Client.\n";
			cout << "\t[3] Delete Client.\n";
			cout << "\t[4] Update Client Info.\n";
			cout << "\t[5] Find Client.\n";
			cout << "\t[6] Transactions.\n";
			cout << "\t[7] Mange Users.\n";
			cout << "\t[8] Logout.\n";
			cout << "=========================================\n";
			Choice = (enMainMenuOptions)MyInputLib::ReadNumberInRange(1, 8, "Choose what do you want to do");
			PerformMainMenuOption(Choice, vClients, vUsers);
		} while (Choice != enMainMenuOptions::eLogout);

	}
	void LoginHeader()
	{
		system("cls");
		system("color 07");
		cout << "\n=========================================\n";
		cout << "==============[Login Screen]=============";
		cout << "\n=========================================\n";
	}
	string ReadPassword()
	{
		string Password = "";
		cout << "\nPlease enter Password: ";
		getline(cin >> ws, Password);
		return Password;
	}
	void Login()
	{

		vector<stClientData> vClients = LoadClientsDataFromFile(GetClientsFileName());

		vector<stUser> vUsers = LoadUsersDataFromFile(GetUsersFileName());

		stUser User;
		string UserName = "", Password = "";

		while (true)
		{
			LoginHeader();

			UserName = ReadUserName();
			Password = ReadPassword();

			while (!FindUserByUserNameAndPassword(UserName, Password, User, vUsers))
			{
				LoginHeader();
				cout << "\nInvalid UserName/Password!\n";
				UserName = ReadUserName();
				Password = ReadPassword();
			}

			CurrentUser = User;
			ShowMainMenuScreen(vClients, vUsers);
		}
	}

}

