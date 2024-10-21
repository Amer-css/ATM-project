#pragma once
#include"clsScreen.h"
#include<iostream>
#include"clsUser.h"
#include"clsInputValidate.h"
#include<iomanip>

class clsAddNewUsersScreen :public clsScreen
{
	static void _ReadUserInfo(clsUser & User)
	{
		cout << "\Enter First Name: ";
		User.FirstName = clsInputValidate::ReadString();
		cout << "\Enter Last Name: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\Enter Email: ";
		User.Email = clsInputValidate::ReadString();
		cout << "\Enter Phone: ";
		User.Phone = clsInputValidate::ReadString();
		cout << "\Enter Passwerd: ";
		User.Password = clsInputValidate::ReadString();
		cout << "\Enter Permission: ";
		User.Permissions = _ReadPermissionsToSet();
	}

	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;
		char Answer = 'n';
		
		cout << "Do You want to give full access? y/n ? : ";
		cin >> Answer;
		
		if (Answer == 'y' || Answer == 'Y')
		{
		   return -1;
		}

		cout << "Do you want to give access to : \n";

		cout << "\nShow Client List? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pListClients;
		}

		cout << "\nAdd Client List? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pAddNewCleint;
		}

		cout << "\nDelete Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pDeleteCleint;
		}

		cout << "\nUpdate Client  y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pUpdateClient;
		}

		cout << "\nFind Client  y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransaction? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pTranactions;
		}
		cout << "\nManage Users? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}
		cout << "\nShiow Login Reigister? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pShowLoginRegister;
		}

		return Permissions;
	}
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

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t Add New User Screen");

		string UserName = "";
		cout << "\nPlease enter User Name: ";

		UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(UserName))
		{
			cout << "\n User Name is Already used, choose another one:  ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser NawUser = clsUser::GetAddNewUserObject(UserName);
		_ReadUserInfo(NawUser);

		clsUser::enSaveResults SaveResult;

		SaveResult = NawUser.Save();

		switch (SaveResult)
		{
		case clsUser::enSaveResults::svSucceeded:
		{
			cout << "\n User Addended Successfully \n";
			_PrintUser(NawUser);
			break;
		}
		case clsUser::enSaveResults::svFaildEmptyObject:
		{
			cout << "Error User was not saved because it's Empty";
			break;
		}
		case clsUser::enSaveResults::svFaildUserExists:
		{
			cout << "Error User was not saved because Users is used!! ";
			break;
		}
	
		}
	}
};

