#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsPerson.h"
#include"clsUser.h"
#include"clsInputValidate.h"

class clsUpdateUserScreen :protected clsScreen
{
private:

	static void _ReadUserInfo(clsUser& User)
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
	static short _ReadPermissionsToSet()
	{
		short Permissions = 0;
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
		cout << "\nShow Login Register? y/n? ";
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

	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\t Update User Screen");

		cout << "\nPlease enter User Name: ";
		string UserName = "";

		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Not found,choose anther one!\n";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User1 = clsUser::Find(UserName);
		_PrintUser(User1);
		cout << "Are you suer do you wat to Update User? y/n ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\n\nUpdate User Info:";
			cout << "\n____________________________\n";

			_ReadUserInfo(User1);
			clsUser::enSaveResults SaveResult;
			
			SaveResult = User1.Save();
			switch (SaveResult)
			{
			case clsUser::enSaveResults::svSucceeded:
			{
				cout << "\nUpdate Successfully.";
				_PrintUser(User1);
				break;
			}
			case clsUser::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nError User was not Update!!\a\n";
				break;
			}
			case clsUser::enSaveResults::svFaildUserExists:
			{
				cout << "\nError User was not Saved because it's already User Exists!!\a\n";
				break;
			}
			
			}
		}
	}
};

