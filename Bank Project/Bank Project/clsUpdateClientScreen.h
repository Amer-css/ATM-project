#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include<iomanip>
#include "clsScreen.h"

class clsUpdateClientScreen : protected clsScreen
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

	static void ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter First Name: ";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last Name: ";
		Client.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone Number: ";
		Client.Phone = clsInputValidate::ReadString();
		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();
		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();

	}
public:

static void ShowUpdateClientScreen()
	{
	    /*if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient))
	    {
	    	return;
	    }*/
	    _DrawScreenHeader("\t Update Client Screen");
		
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
			cout << "\nAccount Number is not found,choose anther one: ";
			AccountNumber = clsInputValidate::ReadIntNumber();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		cout << "\nAre you suer do you want to Update Client? y/n ?\n";
		char Answer;
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "Update Client Info: ";
			cout << "\n_________________________\n";

			ReadClientInfo(Client1);
			clsBankClient::enSaveResults SaveResult;
			SaveResult = Client1.Save();

			switch (SaveResult)
			{
			case clsBankClient::enSaveResults::svSucceeded:
			{
				cout << "Account Updated Successfully \n";
				_PrintClient(Client1);
				break;
			}
			case clsBankClient::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nError account was not saved because it's Empty\n";
			}
			}
		}

	}

};

