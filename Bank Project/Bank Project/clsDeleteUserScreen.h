#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsPerson.h"
#include"clsUser.h"
#include"clsInputValidate.h"

class clsDeleteUserScreen :protected clsScreen
{

private:

	static void _PrintUser(clsUser User)
	{
		cout << "\n User Card: ";
		cout << "\n_____________________";
		cout << "\nFirst Name     :" << User.FirstName;
		cout << "\nLast Name      :" << User.LastName;
		cout << "\nFull Name      :" << User.FullName();
		cout << "\nEmail          :" << User.Email;
		cout << "\nPhone          :" << User.Phone;
		cout << "\nPassword       :" << User.Password;
		cout << "\nPermissions    :" << User.Permissions;
		cout << "\n_____________________\n";
	}

public:
	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\t Delete User Screen");
		
		string UserName = "";
		
		cout << "\nPlease Enter User Name: ";

		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\n User is not found ,choose anthor one: ";
			UserName = clsInputValidate::ReadString();

		}

		clsUser User1 = clsUser::Find(UserName);
		_PrintUser(User1);

		cout << "\n Are you suer you want to Delete this User!!? y/n\n";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (User1.Delete())
			{
				cout << "\n================================================\n";
				cout << "\n\tUser Delete successfully. \n";
				cout << "\n================================================\n";
				_PrintUser(User1);
			}
			else
			{
				cout << "\nError User was not Delete !!\n\a";
			}

		}

	}

};

