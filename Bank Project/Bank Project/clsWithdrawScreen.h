#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"


class clsWithdrawScreen :protected clsScreen
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
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		cout << "\n Please enter Account Number? : ";
		cin >> AccountNumber;
		return AccountNumber;
	}

public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t  Withdraw Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Client whit [" << AccountNumber << "] does not exist\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		_PrintClient(Client1);

		cout << "Please enter Withdraw amount? \n";
		double Amount = 0;
		Amount = clsInputValidate::ReadDblNumber();
		
		cout << "\n Are you sure you want perform this transaction? ";

		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client1.Withdraw(Amount))
			{
				cout << "\nAmount withdrew successflly.\n";
				cout << "\nNew Balance is : " << Client1.AccountBalance;
			}
			else
			{
				cout << "Cannot withdraw, Insufficient Balance!\n";
				cout << "\a\nAmount to withdraw is:" << Amount;
				cout << "\nYour Balance is: " << Client1.AccountBalance<<" !!\n\n";
			}
		}
		else
		{
			cout << "\nOperation was canceled\n";
		}
	}


};

