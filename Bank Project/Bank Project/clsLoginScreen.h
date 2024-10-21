#pragma once
#include<iomanip>
#include"Global.h"
#include"clsMainScreen.h"



class clsLoginScreen:protected clsScreen
{
private:
	static bool _Login()
	{
		bool LoginFaild = false;
		short FaildLoginCount = 0;

		string UserName, Password;
				
		do
		{			
			if (LoginFaild)
			{
				FaildLoginCount++;

				cout << "\n Invalid UserName/Password\n";
				cout << "\n\nyou have " << (3 - FaildLoginCount)
					<< " Trials to login\n\n\n";
			}
			if(FaildLoginCount==3)
			{
				cout << "\n\nyour aer looked after 3  failed trials!!\n";
				return false;
			}
			
			cout << "Enter User Name : ";
			cin >> UserName;
			cout << "Enter Password  : ";
			cin >> Password;

				CurrentUser = clsUser::Find(UserName, Password);

				LoginFaild = CurrentUser.IsEmpty();

			
				
		
		} while (LoginFaild);
		
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		return true;
	}


public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Login Screen");
		return _Login();
		
	}
};

