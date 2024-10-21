#pragma once
#include<iostream>
#include"clsPerson.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsScreen.h"


class clsFindClientScreen :protected clsScreen
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
	
	static void ShowFindClientScreen()
	{
		/*if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;
		}
		*/
		_DrawScreenHeader("\t Find Client Screen");
		
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
			cout << "Account Number is not fount ,choose another one\n";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		if (!Client.IsEmpty())
		{
			cout << "\nClient fund \n";
		}
		else
		{
			cout << "\nClient was not found :\n";
		
		}
		_PrintClient(Client);
	}


};

