#pragma once
#include<iostream>
#include"clsPerson.h"
#include"clsScreen.h"
#include<iomanip>
#include"clsMainScreen.h"
#include"clsInputValidate.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTotalBalancesScreen.h"
#include"clsTransactionsScreen.h"
#include"clsTransferScreen.h"
using namespace std;
class clsTransactionsScreen : protected clsScreen
{

private:

	enum enTransactionsMenuOptions
	{		eDeposit = 1,eWithdraw = 2,
		eShowTotalBalance = 3 , eShowTransfer = 4 , eShowTransferLog = 5,eShowMainMenue = 6
	};

	static short ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to [1 - 6]: ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Choose what do you want to between 1 - 6 \n");

		return Choice;
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalanceScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}
	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLogScreen()
	{
		
	}
	static void _GoBackToTransactionMeuneOption()
	{
		cout << "\nPresse any kye to go back to transaction meune...\n";
		system("pause>0");
		
	}

	static void _PerformTranasactionMeuneOption(enTransactionsMenuOptions TransactionsMeuneOption)
	{


		switch (TransactionsMeuneOption)
		{
		case enTransactionsMenuOptions::eDeposit:
		  {
				system("cls");
				_ShowDepositScreen();
				_GoBackToTransactionMeuneOption();
				break;
		  }
		  case clsTransactionsScreen::eWithdraw:
		  {
			  system("cls");
			  _ShowWithdrawScreen();
			  _GoBackToTransactionMeuneOption();
				break;
		  }
		  case  clsTransactionsScreen::eShowTotalBalance:
		  {
			  system("cls");
			  _ShowTotalBalanceScreen();
			  _GoBackToTransactionMeuneOption();
				break;
		  }
		  case  clsTransactionsScreen::eShowTransfer:
		  {
			  system("cls");
			  _ShowTransferScreen();
			  _GoBackToTransactionMeuneOption();
			  break;
		  }
		  case  clsTransactionsScreen::eShowTransferLog:
		  {
			  system("cls");
			  _ShowTransferLogScreen();
			  _GoBackToTransactionMeuneOption();
			  break;
		  }
		  case clsTransactionsScreen::eShowMainMenue:
		  {
			 // system("cls");	 
		  }
		
		}

	}



public:

	static void ShowTransactionMenue()
	{
		/*if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
		{
			return;
		}*/
		
		system("cls");
		_DrawScreenHeader("\t Transaction Screen");
	
		cout << setw(37) << left << "" << "========================================\n";
		cout << setw(37) << left << "" << "\t\t Transaction Meune\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balance.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "========================================\n";

		_PerformTranasactionMeuneOption((enTransactionsMenuOptions)ReadTransactionsMenueOption());
	}



};

