#pragma once
#include"clsPerson.h"
#include"clsScreen.h"
#include <iostream>
#include<iomanip>
#include<string>

class clsLoginRegster : protected clsScreen
{

private:



	static clsLoginRegster _ConvertLinetoRegster(string Line, string Seperator = "#//#")
	{
		
		vector<string>vLoginRegster;
		vLoginRegster = clsString::Split(Line, Seperator);
		
		if (vLoginRegster.size() >= 4) {
			return clsLoginRegster {vLoginRegster[0], vLoginRegster[1], vLoginRegster[2], vLoginRegster[3] };
		}
		else {
			throw runtime_error("Invalid line format or insufficient data.");
		}
		
	}

	static vector<clsLoginRegster>_LoadRegsterDateFromFile()
	{
		vector<clsLoginRegster>vClients;
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsLoginRegster Client = _ConvertLinetoRegster(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;

	}

	static vector <clsLoginRegster> GetRegsterList()
	{
		return _LoadRegsterDateFromFile();
	}



};

