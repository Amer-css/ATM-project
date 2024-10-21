#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include<iomanip>


class clsAddNewClientScreen :protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
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

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n______________________________";
		cout << "\nFirst Name     :" << Client.GetFirstName();
		cout << "\nLast Name      :" << Client.LastName;
		cout << "\nFull Name      :" << Client.FullName();
		cout << "\nEmail          :" << Client.Email;
		cout << "\nPhone          :" << Client.Phone;
		cout << "\nAcc. Number    :" << Client.AccountNumber();
		cout << "\nPin Code       :" << Client.PinCode;
		cout << "\nBalance        :" << Client.AccountBalance ;
		cout << "\n______________________________\n";

	}

public:

	static void ShowAddNewClientScreen()
	{
		/*if (!CheckAccessRights(clsUser::enPermissions::pAddNewCleint))
		{
			return;
		}*/
		_DrawScreenHeader("\t Add Nwe Client Screen");
		
		string AccountNumber = "";
		cout << "\nPlease Enter Client Account Number (or 0 to go back): ";

		AccountNumber = clsInputValidate::ReadString();

		if (AccountNumber == "0")
		{
			cout << "\nReturning to the previous screen...\n";
			return;
		}
		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found,choose anther one: ";
			AccountNumber = clsInputValidate::ReadString();

		}
		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case  clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(NewClient);
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;

		}
		case clsBankClient::enSaveResults::svFaildAccountNumberExists:
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;

		}

		}


	}

};

