#pragma once
#include <iostream>
#include"clsUser.h"
#include"Global.h"
#include <ctime>
#include"clsDate.h"
class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        cout <<"\n\t\t\t\t\t\t  User: " << CurrentUser.FirstName;
        cout << "\n\t\t\t\t\t\t  Date: " << clsDate::DateToString(clsDate())<<endl;
    }


  /*  static bool CheckAccessRights(clsUser::enPermissions Permission)
    {

        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t_________________________________________________\n";
            cout << "\n\n\t\t Access Denied! Contact your Admin\n";
            cout << "\t\t\t_________________________________________________\n";
            return false;
        }
        else
        {
            return true;
        }

    }
  */


public:
   
};

