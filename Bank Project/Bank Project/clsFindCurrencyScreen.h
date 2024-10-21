#pragma once
#include"clsScreen.h"
#include"clsCurrency.h"
#include<iostream>
#include"clsInputValidate.h"
class clsFindCurrencyScreen :protected clsScreen
{
private:

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "\n____________________________\n";
		cout << "\nCountry      :" << Currency.Country();
		cout << "\nCode         :" << Currency.CurrencyCode();
		cout << "\nName         :" << Currency.CurrencyName();
		cout << "\nRate(1$)     :" << Currency.Rate();
		cout << "\n____________________________\n";
	}
	static void _ShowResults(clsCurrency Currncy)
	{
		if (!Currncy.IsEmpty())
		{
			cout << "\nCurrency found \n";
			_PrintCurrency(Currncy);
		}
		else
		{
			cout << "Currency not found \n";
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t Find Currency Screen");


		cout << "\nFind By:[1] Code or [2] Country ?";
		short Answer = 1;

		cin >> Answer;

		if (Answer == 1)
		{
			string CurrenceyCode;
			cout << "Please enter Currency Code\n";
			
			 CurrenceyCode = clsInputValidate::ReadString();
			 clsCurrency Currency = clsCurrency::FindByCode(CurrenceyCode);
			 _ShowResults(Currency);
		}
		else
		{
			string Country;
			cout << "Please Enter Currency Name\n";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
		}
		


	}


};

