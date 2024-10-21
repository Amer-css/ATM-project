#include <iostream>
#include "clsLoginScreen.h"
#include "clsCurrency.h"



int main()

{
   
    
    while (true)
	{
        system("cls");
        cout << "\n_______________________________________\n\n";
        cout << "Welcome to the login screen!\n";
        //cout << "Please select an option:\n";
        cout << "[1] Login\n";
        cout << "[2] Exit\n";
        cout << "\n_______________________________________\n";
        short choice = clsInputValidate::ReadIntNumberBetween(1,2);
      
        if (choice == 1)
        {
            if (!clsLoginScreen::ShowLoginScreen())
            {
                break;
            }
            
        }
        else if (choice == 2)
        {
            cout << "Exiting the program...\n";
            break;
        }
        else
        {
            cout << "Invalid choice! Please enter 1 or 2.\n";
        }
	}
   

    return 0;
}