#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsPerson.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsMainScreen.h"


class clsDeleteClientScreen : protected clsScreen
{

private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n_______________________________";
		cout << "\nFirst Name        :" << Client.FirstName;
		cout << "\nLast Name         :" << Client.LastName;
		cout << "\nFull Name         :" << Client.FullName();
		cout << "\nEmail             :" << Client.Email;
		cout << "\nPhone             :" << Client.Phone;
		cout << "\nAcc.Number        :" << Client.AccountNumber();
		cout << "\nPassword          :" << Client.PinCode;
		cout << "\nBalance           :" << Client.AccountBalance;
		cout << "\n_______________________________";

	}

public:

	static void ShowDeleteClientScreen()
	{
		/*if (!CheckAccessRights(clsUser::enPermissions::pDeleteCleint))
		{
			return;
		}*/
		_DrawScreenHeader("\tDelete Client Screen");
		
		string AccountNumber = "";

		cout << "\nPlease Enter Client Account Number (or 0 to go back): ";
		AccountNumber = clsInputValidate::ReadString();
		if (AccountNumber == "0")
		{
			cout << "\nReturning to the previous screen...\n";
			return;
		}
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not Found,choose another Account\n";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		_PrintClient(Client1);

		cout << "\nAre you sure you want to delete this client? y/n\n";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{

			if (Client1.Delete())
			{
				cout << "\nClient delete successfully\n";
				
				_PrintClient(Client1);
			}
			else
			{
				cout << "\n Error Client was not Delete!\n";
			}
		}

	}

};

