#pragma once

#include<string>
#include"clsString.h"
#include<vector>
#include<fstream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsMainScreen.h"
class clsCurrency:protected clsScreen
{

private:

	enum enMode{EmptyMode = 0 , UpdateMode=1};
	enMode _Mode;	
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#")
	{
		vector<string>vCurrencyDate;

		vCurrencyDate = clsString::Split(Line,Seperator);

		return clsCurrency(enMode::UpdateMode, vCurrencyDate[0], vCurrencyDate[1], vCurrencyDate[2],stof(vCurrencyDate[3]));

	}
	static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
	{
		string stCurrencyRecord = "";

		stCurrencyRecord += Currency._Country + Seperator;
		stCurrencyRecord += Currency._CurrencyCode + Seperator;
		stCurrencyRecord += Currency._CurrencyName + Seperator;
		stCurrencyRecord += to_string(Currency._Rate) + Seperator;

		return stCurrencyRecord;
	}
	static  vector <clsCurrency> _LoadCurrencysDataFromFile()
	{
		vector<clsCurrency> vCurrency;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode
		
		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile,Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);

				vCurrency.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrency;
	}
	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys)
	{

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsCurrency C : vCurrencys)
			{
				DataLine = _ConverCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsCurrency> vCurrency;

		vCurrency = _LoadCurrencysDataFromFile();
		
		for (clsCurrency& C : vCurrency)
		{
			C = *this;
			break;
		}
		_SaveCurrencyDataToFile(vCurrency);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:
	
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	static vector <clsCurrency> GetAllUSDRates()
	{

		return _LoadCurrencysDataFromFile();

	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}
	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}
	static   clsCurrency FindByCode(string CurrencyCode)
	{

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();

		}

		return _GetEmptyCurrencyObject();

	}
	static   clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}

			}

			MyFile.close();

		}

		return _GetEmptyCurrencyObject();

	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
		return (!C1.IsEmpty());

	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencysDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);
		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}
		return (float)(AmountInUSD * Currency2.Rate());
	}
};

