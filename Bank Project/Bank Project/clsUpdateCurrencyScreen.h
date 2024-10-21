#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsCurrency.h"
#include"clsInputValidate.h"
class clsUpdateCurrencyScreen :protected clsScreen
{

	static float _ReadRate()
	{
		cout << "\nEnter New Rate:\n";
		float NewRate = 0;
		NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;
	}
	static void _PrintCurrencyUpdate(clsCurrency Currency)
	{
		cout << "\n____________________________________";
		cout << "\n\tCurrency Card";
		cout << "\n____________________________________\n";
		cout << "\nCountry      :" << Currency.Country();
		cout << "\nCode         :" << Currency.CurrencyCode();
		cout << "\nName         :" << Currency.CurrencyName();
		cout << "\nRate(1$)     :" << Currency.Rate();
		cout << "\n____________________________________\n";

	}
public:

	static void ShowCurrencyScreen()
	{
		
		_DrawScreenHeader("\tUpdate Currency Screen");
		string CurrencyCode="";

		cout << "\nPlease Enter currency code: ";
		
		CurrencyCode = clsInputValidate::ReadString();
	
		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\n Code Currency is not found,choice anther one:";
			CurrencyCode = clsInputValidate::ReadString();

		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrencyUpdate(Currency);

		cout << "Aer you sure you want to update the rate of " << Currency.CurrencyName() << " ?y/n ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\nUpdate Currency Rate:";
			cout << "\n______________________________\n";

			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate update successfully\n";
			_PrintCurrencyUpdate(Currency);
		}

	}

};

