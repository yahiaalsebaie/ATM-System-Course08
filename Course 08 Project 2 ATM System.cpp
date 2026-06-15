
#include <iostream>
#include "MyBankDataLib.h"
#include "MyDateLib.h"
#include "MyHijriDateLib.h"
#include <limits>
#include <string>

using namespace std;
namespace bank = MyBankDataLib;

enum enATM { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eChangePassword = 5, eLogout = 6 };

void ShowDate(bool FullDate = true)
 {
	if(FullDate)
	{
		MyDateLib::stDate MDate = MyDateLib::GetSystemDate();
		cout << MyDateLib::PrintDate(MDate, 1);
		MyHijriDateLib::stHijriDate HDate = MyHijriDateLib::ConvertMiladiToHijriTrastedUsingMiladiDay(MDate.Day, MDate.Month, MDate.Year);
		cout << "\t | " << MyHijriDateLib::PrintHijriDate(HDate);
	}
	else
	{
		cout << MyDateLib::PrintDate(MyDateLib::GetSystemDate() , 1);
	}

 }
 void Header(string Title)
{
	ShowDate();
	cout << "\n=========================================\n";
	cout << "\t     " << Title;
	cout << "\n=========================================\n";
}
 
 short GetQuickWithdrawChoiceAmount(short Choice)
 {
	 short arr[] = { 20, 50, 100, 200, 400, 600, 800, 1000 };	 
	 return arr[Choice - 1];
 }
 void ShowQuickWithdrawScreen(bank::stClientData& Client)
{
	 system("cls");
	 short Choice;
	 ShowDate();
	 Header("Quick Withdraw");
	 cout << "\t[1] 20.\t";
	 cout << "\t[2] 50.\n";
	 cout << "\t[3] 100.";
	 cout << "\t[4] 200.\n";
	 cout << "\t[5] 400.";
	 cout << "\t[6] 600.\n";
	 cout << "\t[7] 800.";
	 cout << "\t[8] 1000.\n";
	 cout << "\t\t[9] Exit.";
	 cout << "\n=========================================\n";
	 cout << "Your Balance is " << to_string(Client.AccountBalance) << endl;
	 Choice = MyInputLib::ReadNumberInRange(1, 9, "Choose what do you want to do");
	 if (Choice == 9) return;

	 short Amount = GetQuickWithdrawChoiceAmount(Choice);

	 while (Amount > Client.AccountBalance)
	 {
		 cout << "\n [Transaction Denied]: Insufficient Balance!\n";
		 Choice = MyInputLib::ReadNumberInRange(1, 9, "Choose what do you want to do");

		 if (Choice == 9) return;

		 Amount = GetQuickWithdrawChoiceAmount(Choice);
	 }

	 bank::DepositClientBalanceByAccountNumberForATM(Client.AccountNumber, (Amount * -1));
	 Client.AccountBalance -= Amount;
}
 void ShowNormalWithdrawScreen(bank::stClientData& Client)
{
	 system("cls");
	 ShowDate();
	 Header("Normal Withdraw");
	
	 cout << "Your Balance is " << to_string(Client.AccountBalance);
	 
	 cout << "\n=========================================\n";
	 
	 short Amount = MyInputLib::ReadPositiveNumber("Enter an Amount multiply of 5`s : ");

	 while (Amount > Client.AccountBalance || Amount%5 != 0)
	 {
		 cout << "\n [Transaction Denied]: Insufficient Balance!\n";
		 Amount = MyInputLib::ReadPositiveNumber("Enter an Amount multiply of 5`s : ");
	 }

	 bank::DepositClientBalanceByAccountNumberForATM(Client.AccountNumber, (Amount * -1));
	 Client.AccountBalance -= Amount;

}
 void ShowDepositScreen(bank::stClientData& Client)
{
	 system("cls");
	 ShowDate();
	 Header("Normal Withdraw");
	
	 cout << "Your Balance is " << to_string(Client.AccountBalance);
	 
	 cout << "\n=========================================\n";
	 
	 short Amount = MyInputLib::ReadPositiveNumber("Enter an Amount multiply of 5`s : ");

	 while (Amount % 5 != 0)
	 {
		 cout << "\n [Transaction Denied]!\n";
		 Amount = MyInputLib::ReadPositiveNumber("Enter an Amount multiply of 5`s : ");
	 }

	 bank::DepositClientBalanceByAccountNumberForATM(Client.AccountNumber, (Amount));
	 Client.AccountBalance += Amount;

}
 void GoBackToMainMenu()
 {
	 cout << "\n\nPress any key to go back to Main Menu...";
	 system("pause>0");
 }
 void CheckBalanceScreen(const bank::stClientData& Client)
 {
	 system("cls");
	 ShowDate();
	 Header("Check Balance");
	 cout << "Your Balance is " << to_string(Client.AccountBalance) << endl;
 }
 void ShowChangePasswordScreen(vector<bank::stClientData>& vClients, bank::stClientData& Client)
 {
	 string PinCode = "";
	 string RePinCode = "";
	 char Answer = 'n';

	 system("cls");
	 ShowDate();
	 Header("Change Password/PinCode");

	 cout << "\nAre you sure you want to change PinCode? [Y/N] : ";
	 cin >> Answer;
	 cin.ignore(numeric_limits<streamsize>::max(), '\n');

	 if (Answer == 'y' || Answer == 'Y')
	 {
		 do
		 {
			 system("cls");
			 ShowDate();
			 Header("Change Password/PinCode");
			 PinCode = MyStringLib::ReadString("Enter New PinCode: ");
			 RePinCode = MyStringLib::ReadString("Re Enter New PinCode: ");
			 if (PinCode != RePinCode) cout << "\nInvalid New Password!\n";
		 } while (PinCode != RePinCode);

		 if (PinCode == RePinCode)
		 {
			
			 if (bank::UpdateClientPinCode(Client.AccountNumber, vClients, RePinCode))
			 {
				 cout << "\n[PinCode Changed Successfully].\n";
				 Client.PinCode = RePinCode;
			 }
			 else
				 cout << "\nSomething Wrong Happened!\n[Operation Failed].\n";
		 }
		 else
			 cout << "\n[Operation Failed].\n";
	 }
	 else return;
 }
 /*
 bool UpdateClientPinCode(string AccountNumber, vector <stClientData>& vClients,string NewPinCode)
	{
		for (stClientData& c : vClients)
		{
			if (AccountNumber == c.AccountNumber)
			{
				c.PinCode == NewPinCode;
				return true;
			}
		}
		return false;
	}
 */
 void PerformATM_Screen(enATM ATMOptions, vector<bank::stClientData>& vClients, bank::stClientData& Client)
{

	switch (ATMOptions)
	{
	case eQuickWithdraw: ShowQuickWithdrawScreen(Client);
		GoBackToMainMenu();
		break;
	case eNormalWithdraw:ShowNormalWithdrawScreen(Client);
		GoBackToMainMenu();
		break;
	case eDeposit:ShowDepositScreen(Client);
		break;
	case eCheckBalance: CheckBalanceScreen(Client);
		GoBackToMainMenu();
		break;
	case eChangePassword: ShowChangePasswordScreen(vClients, Client);
		GoBackToMainMenu();
		break;
	case eLogout:
		break;
	}
}


void ShowATM_MainMenuScreen(vector<bank::stClientData>& vClients, bank::stClientData& Client)
{
	enATM Choice;

	do {
		system("cls");
		system("color 0A");
		ShowDate();
		cout << "\n==========================================\n";
		cout <<   "==========[ATM Main Menu Screen]==========";
		cout << "\n==========================================\n";
		cout << "\t[1] Quick Withdraw.\n";
		cout << "\t[2] Normal Withdraw.\n";
		cout << "\t[3] Deposit.\n";
		cout << "\t[4] Check Balances.\n";
		cout << "\t[5] ChangePassword.\n";
		cout << "\t[6] Logout.\n";
		cout << "==========================================\n";
		Choice = (enATM)MyInputLib::ReadNumberInRange(1, 6, "Choose what do you want to do");
cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		PerformATM_Screen(Choice, vClients,Client);
	} while (Choice != enATM::eLogout);


}
void Login()
{
	vector<bank::stClientData> vClients = bank::LoadClientsDataFromFile(bank::GetClientsFileName());

	bank::stClientData Client;

	string AccountNumber = "", PinCode = "";
	do
	{
		system("cls");
		Header("Login Screen");


		AccountNumber = MyStringLib::ReadString("Enter Account Number: ");
		PinCode = MyStringLib::ReadString("Enter PinCode: ");

		while (!bank::FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, Client, vClients))
		{
			system("cls");
			Header("Login Screen");
			cout << "\nInvalid AccountNumber/PinCode!\n";
			AccountNumber = MyStringLib::ReadString("Enter Account Number: ");
			string PinCode = MyStringLib::ReadString("Enter PinCode: ");
		}

		ShowATM_MainMenuScreen(vClients, Client);
	} while (true);

}
int main()
{
	Login();
}

