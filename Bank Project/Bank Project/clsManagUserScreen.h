#pragma once
#include<iostream>
#include"clsBankClient.h"
#include"clsScreen.h"
#include"clsMainScreen.h"
#include<iomanip>
#include"clsListUsersScreen.h"
#include"clsAddNewUsersScreen.h"
#include"clsDeleteUserScreen.h"
#include"clsUpdateUserScreen.h"
#include"clsFindUserScreen.h"
class clsManagUserScreen : protected clsScreen
{
private:
	enum eManagUsersMenueOptions {
	eListUsers=1,eAddNewUser=2,eDeleteUser=3,eUpdateUser=4,eFindUsre=5 , eMainMenue=6};

	static short ReadManagUsersMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6] ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between [1 - 6] ");
		return Choice;
	}
	static void _GoBackToManageUsersMenue()
	{
		cout << "\n\nPress any key to go back to Manage Users Menue...";
		system("pause>0");
		ShowManageUsersMenue();
	}
	static void _ShowListUsersScreen()
	{
		clsListUsersScreen::ShowUsersList();
	}
	static void _ShowAddUsersScreen()
	{
		clsAddNewUsersScreen::ShowAddNewUserScreen();
	}
	static void _ShowDeleteUsersScreen()
	{
		
		clsDeleteUserScreen::ShowDeleteUserScreen();

	}
	static void _ShowUpdateUsersScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}
	static void _ShowFindUsersScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}



	static void _PerformManageUsersMenueOption(eManagUsersMenueOptions ManageUsersMenueOption)
	{
		switch (ManageUsersMenueOption)
		{
		case eManagUsersMenueOptions::eListUsers:
		{
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case eManagUsersMenueOptions::eAddNewUser:
		{
			system("cls");
			_ShowAddUsersScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case eManagUsersMenueOptions::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUsersScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case eManagUsersMenueOptions::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUsersScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case eManagUsersMenueOptions::eFindUsre:
		{
			system("cls");
			_ShowFindUsersScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case eManagUsersMenueOptions::eMainMenue:
		{
			
		}

		}

	}

	
public:

	static void ShowManageUsersMenue()
	{
		/*if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;
		}*/
		
		system("cls");

		_DrawScreenHeader("\t Manag Users Screen");
	
		cout << setw(37) << left << "" << "===================================\n";
		cout << setw(37) << left << "" << "\t\t  Manga Users Screen \n";
		cout << setw(37) << left << "" << "===================================\n";
		cout << setw(37) << left << "" << "[1] List Users.\n";
		cout << setw(37) << left << "" << "[2] Add New Users.\n";
		cout << setw(37) << left << "" << "[3] Delete Users.\n";
		cout << setw(37) << left << "" << "[4] Update Users.\n";
		cout << setw(37) << left << "" << "[5] Find Users.\n";
		cout << setw(37) << left << "" << "[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===================================\n";

		_PerformManageUsersMenueOption(eManagUsersMenueOptions(ReadManagUsersMenueOption()));
	}


};

