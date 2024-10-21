#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsUser.h"
class clsTransferScreen :clsScreen
{

	private:

		static void _PrintClient(clsBankClient Client)
		{
			cout << "\nClient Card:";
			cout << "\n___________________";
			cout << "\nFull Name   : " << Client.FullName();
			cout << "\nAcc. Number : " << Client.AccountNumber();
			cout << "\nBalance     : " << Client.AccountBalance;
			cout << "\n___________________\n";
		}

		static string _ReadAccountNumber(string S1)
		{
			string AccountNumber = "";
			cout << "\n Please enter Account Number? : ";
			cin >> AccountNumber;
			return AccountNumber;
		}
		
		static float ReadAmount(clsBankClient SourceClient)
		{
			float Amount;

			cout << "\nEnter Transfer Amount? ";

			Amount = clsInputValidate::ReadFloatNumber();

			while (Amount > SourceClient.AccountBalance)
			{
				cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
				Amount = clsInputValidate::ReadDblNumber();
			}
			return Amount;
		}
	

		


	public:

		static void ShowTransferScreen()
		{
			_DrawScreenHeader("\t  Transfer Screen");
			
			clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("From"));
			_PrintClient(SourceClient);

			clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("To"));
			while (DestinationClient.AccountNumber() == SourceClient.AccountNumber())
			{
				cout << "\nYou cannot transfer to the same account.";
				 DestinationClient = clsBankClient::Find(_ReadAccountNumber("To"));
				
			}
			
			
			_PrintClient(DestinationClient);

			float Amount = ReadAmount(SourceClient);

			cout << "\nAre you sure you want to perform this operation?\n";
			char Answer = 'n';
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
			{
				if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.UserName))
				{
					
					cout << "\nTransfer done successfully\n";
				}
				else
				{
					cout << "\n Transfer failed!!\a\n";
				}
			}
			_PrintClient(SourceClient);
			_PrintClient(DestinationClient);

		}


};

