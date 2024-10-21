#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsPerson.h"
#include"clsUser.h"
#include"clsInputValidate.h"
class clsFindUserScreen:protected clsScreen
{
private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

public:

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t Find User Screen");
		
		string UserName = "";
		cout << "\nPlease Enter User";
		UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser is not found,chose another one\n";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User1 = clsUser::Find(UserName);
		if (!User1.IsEmpty())
		{
			cout << "\nUser found.\n";
		}
		else
		{
			cout << "\n\aUser was not found!!\n";
		}
		_PrintUser(User1);

	}

};

