#pragma once
#include<iostream>
#include<string>
#include"clsPerson.h"
#include<vector>
#include<fstream>
#include"clsString.h"
#include"clsInputValidate.h"
#include<iomanip>
#include"clsUtil.h"
#include"clsUser.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode{EmptyMode = 0,UpdateMode =1,AddNewMode=2};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string>vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4],
			vClientData[5], stod(vClientData[6]));
	}
	
	


	
	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;

	}
	static vector<clsBankClient>_LoadClientDateFromFile()
	{
		vector<clsBankClient>vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;

	}
	static void _SaveClientsDataToFile(vector<clsBankClient>vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
			string DataLine;
			if (MyFile.is_open())
			{
				for (clsBankClient C : vClients)
				{
					if (C.MarkedForDeleted() == false)
					{
						DataLine = _ConvertClientObjectToLine(C);
						MyFile << DataLine << endl;

					}
					
				}
				MyFile.close();
			}
	}
	
	 void _Update()
	{
		vector<clsBankClient>_vClients;
		_vClients = _LoadClientDateFromFile();
		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}
	
	 void _AddNew()
	 {

		 _AddDataLineToFile(_ConvertClientObjectToLine(*this));
	 }

	 void _AddDataLineToFile(string  stDataLine)
	 {
		 fstream MyFile;
		 MyFile.open("Clients.txt", ios::out | ios::app);

		 if (MyFile.is_open())
		 {

			 MyFile << stDataLine << endl;

			 MyFile.close();
		 }

	 }

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, string UserName, string Seperator = "#//#")
	{
		string TransFerLogRecord = "";
		TransFerLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransFerLogRecord += AccountNumber() + Seperator;
		TransFerLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransFerLogRecord += to_string(Amount) + Seperator;
		TransFerLogRecord += to_string(AccountBalance) + Seperator;
		TransFerLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransFerLogRecord += UserName;

		return TransFerLogRecord;
	}



	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient,string UserName )
	{
		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}

	}

	string _PrepareWithdrawForLogRecourd(float Amount,string UserName,string Seperator = "#//#")
	{
		string DrawRecord = "";

		DrawRecord += clsDate::GetSystemDateTimeString() + Seperator;
		DrawRecord += AccountNumber() + Seperator;
		DrawRecord += to_string(Amount) + Seperator;
		DrawRecord += CurrentUser.FullName() + Seperator;

		return DrawRecord;
	}
	void _RegisterWithdrawRecord(float Amount,string UserName)
	{
		//Record withdrawals in a file
		string stDataLine = _PrepareWithdrawForLogRecourd(Amount, UserName);

		fstream MyFile;
		MyFile.open("WithdrawRecord.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}
	string _PrepareDepositRecord(float Amount, string UserName, string Seperator = "#//#")
	{
		string DepositRecord = "";
		DepositRecord += clsDate::GetSystemDateTimeString() + Seperator;
		DepositRecord += AccountNumber() + Seperator;
		DepositRecord += to_string(Amount) + Seperator;
		DepositRecord += CurrentUser.FullName() + Seperator;

		return DepositRecord;
	}
	void _RegisterDepositRecord(float Amount, string UsarName)
	{
		string stDatLine = _PrepareDepositRecord(Amount, UsarName);

		fstream MyFile;

		MyFile.open("DepositRecord.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDatLine << endl;
			MyFile.close();
		}

	}
	struct stTransferLogRecord;

	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTransferLogRecord TrnsferLogRecord;

		vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.SrcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.DesBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;

	}
public:

	struct stTransferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float SrcBalanceAfter;
		float DesBalanceAfter;
		string UserName;
	};
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string AccountNumber, string PinCod, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCod;
		_AccountBalance = AccountBalance;
	}
	string FullName()
	{
		return FirstName + " " + LastName;
	}
	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}
	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCod(string PinCode)
	{
		_PinCode = PinCode;
	}
	
	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCod))string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;

/*	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n______________________________";
		cout << "\nFirst Name     :" << GetFirstName();
		cout << "\nLast Name      :" << LastName;
		cout << "\nFull Name      :" << FullName();
		cout << "\nEmail          :" << Email;
		cout << "\nPhone          :" << Phone;
		cout << "\nAcc. Number    :" << _AccountNumber;
		cout << "\nPin Code       :" << PinCode;
		cout << "\nBalance        :" << _AccountBalance;
		cout << "\n______________________________\n";

	}*/

	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);///read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Clients = _ConvertLinetoClientObject(Line);
				if (Clients.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Clients;
				}
				vClients.push_back(Clients);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber,string PinCode)
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);///read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Clients = _ConvertLinetoClientObject(Line);
				if (Clients.AccountNumber() == AccountNumber && Clients.GetPinCode() == PinCode)
				{
					MyFile.close();
					return Clients;
				}
				vClients.push_back(Clients);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	
	enum enSaveResults{svFaildEmptyObject=0,svSucceeded =1,
		svFaildAccountNumberExists = 2};

	enSaveResults Save()
	{
		switch (_Mode)
		{
			case enMode::EmptyMode:
			{
				if (IsEmpty())
				{
					return enSaveResults::svFaildEmptyObject;
				}
			}

			case enMode::UpdateMode:
			{
				_Update();
				return enSaveResults::svSucceeded;

			break;
			}
			case enMode::AddNewMode:
			{
				if (clsBankClient::IsClientExist(_AccountNumber))
				{
					return enSaveResults::svFaildAccountNumberExists;

				}
				else
				{
					 _AddNew();
					 _Mode = enMode::UpdateMode;
					 return enSaveResults::svSucceeded;
				}
				break;
			}
		}
	}
	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		return (!Client1.IsEmpty());
	}

	void UpdateClient()
	{
		string AccountNumber = "";

		cout << "\nPlease Enter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Numbrt is not found,choose anther one: ";
			AccountNumber = clsInputValidate::ReadIntNumber();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
	//	Client1.Print();

		cout << "\n\nUpdate Client Info: ";
		cout << "\n_________________________\n";

		ReadClientInfo(Client1);
		clsBankClient::enSaveResults SaveResult;
		SaveResult = Client1.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "Account Updated Successflly \n";
			//Client1.Print();
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty\n";
		}
		}
	}
	
	void ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter First Name: ";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last Name: ";
		Client.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone Number: ";
		Client.Phone = clsInputValidate::ReadString();
		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();
		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();

	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	void AddNewClient()
	{
		string AccountNumber = "";
		cout << "\nPlease Enter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found,choose anther one: ";
			AccountNumber = clsInputValidate::ReadString();

		}
		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case  clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "\n________________________________________________________\n";
			cout << "\nAccount Addeded Successfully :-)\n";
			//NewClient.Print();
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;

		}
		case clsBankClient::enSaveResults::svFaildAccountNumberExists:
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;

		}

		}

	}
	bool Delete()
	{
		vector<clsBankClient>_vClient;
		_vClient = _LoadClientDateFromFile();
		for (clsBankClient &C : _vClient)
		{
			if (C.AccountNumber() == _AccountNumber )
			{
				C._MarkedForDelete = true;
				break;
			}
		}
		_SaveClientsDataToFile(_vClient);
		*this = _GetEmptyClientObject();
		
		return true;
	}
	void DeleteClient()
	{
		string AccountNumber = "";
		cout << "Please Enter Account Number to Delete\n";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found, choose anther one : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		//Client1.Print();
		cout << "\nAre you sure you want to delete this client? y/n\n";

		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client1.Delete())
			{
				cout << "\nClient Delete successflly\n";
				//Client1.Print();
			}
			else
			{
				cout << "Error Client was not Delete\n";
			}
		}
	}
	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientDateFromFile();
	}

	void ShowClientsList()
	{
		vector<clsBankClient> vClient = clsBankClient::GetClientsList();

		cout << "\n\t\t\tClients List ( " << vClient.size() << " ) Client";
		cout << "\n__________________________________________________________________________________\n\n";
		cout << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone ";
		cout << "| " << left << setw(10) << "Pin Code ";
		cout << "| " << left << setw(10) << "Account Balance ";
		cout << "\n__________________________________________________________________________________\n";

		if (vClient.size() == 0)
		{
			cout << "\t\t\tNo Client Available in this System!\n";
		}
		else
		{
			for (clsBankClient Client : vClient)
			{
				PrintClientRecordLien(Client);
				cout << endl;
			}
		}
		cout << "\n__________________________________________________________________________________\n";
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		if (Save())
		{
			_RegisterDepositRecord(Amount, AccountNumber());
			
		}
	}
	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			
			if (Save())
			{
				_RegisterWithdrawRecord(Amount,AccountNumber());
				return true;
			}
			else
			{
				return false;
			}
		}
		
	}
	bool Transfer(float Amount, clsBankClient& DestinationClient,string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}
		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);
		
		return true;
	}
	static double GetTotalBalance()
	{
		vector<clsBankClient>vClient = clsBankClient::GetClientsList();

		double TotalBalance = 0;
		for (clsBankClient Client : vClient)
		{
			TotalBalance += Client.AccountBalance;
		}
		return TotalBalance;
	}


	void PrintClientRecordLien(clsBankClient Client)
	{
		cout << "| " << setw(15) << Client.AccountNumber();
		cout << "| " << setw(20) << Client.FullName();
		cout << "| " << setw(12) << Client.Phone;
		cout << "| " << setw(10) << Client.PinCode;
		cout << "| " << setw(10) << Client.AccountBalance;

	}
	void ShowTotalBalances()
	{
		vector<clsBankClient> vClient = clsBankClient::GetClientsList();

		cout << "\n\t\t\tClients List ( " << vClient.size() << " ) Client";
		cout << "\n__________________________________________________________________________________\n\n";
		cout << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone ";
		cout << "| " << left << setw(10) << "Pin Code ";
		cout << "| " << left << setw(10) << "Account Balance ";
		cout << "\n__________________________________________________________________________________\n";

		double TotalBalances = clsBankClient::GetTotalBalance();
		if (vClient.size() == 0)
		{
			cout << "\t\t\tNo Client Available in this System!\n";
		}
		else
		{
			for (clsBankClient Client : vClient)
			{
				PrintClientRecordLien(Client);
				cout << endl;
			}
		}
		cout << "\n__________________________________________________________________________________\n";
		cout << "\n\t\t\t Total Balance :" << TotalBalances << endl;
		cout << "\n\t\t" << clsUtil::NumberToText(TotalBalances) << endl;
	}

	static vector<stTransferLogRecord>GetTransFerLogList()
	{
		vector< stTransferLogRecord>vTransferLogRecord;

		fstream MyFile;

		MyFile.open("TransFerLog.txt", ios::in);
		
			if (MyFile.is_open())
			{
				string Line;

				stTransferLogRecord TransferRecord;

				while (getline(MyFile, Line))
				{
					TransferRecord = _ConvertTransferLogLineToRecord(Line);

					vTransferLogRecord.push_back(TransferRecord);
				}
				MyFile.close();
			}
			return vTransferLogRecord;
	}

};

