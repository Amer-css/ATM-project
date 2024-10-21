#pragma once
#include<iostream>
#include"clsScreen.h"
#include<iomanip>
#include<fstream>
#include"clsBankClient.h"
#include"clsUser.h"
#include<vector>
class clsTransferLogScreen : protected clsScreen 
{

	static void PeintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLog)
	{
        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLog.DateTime;
        cout << "| " << setw(8) << left << TransferLog.SourceAccountNumber;
        cout << "| " << setw(8) << left << TransferLog.DestinationAccountNumber;
        cout << "| " << setw(8) << left << TransferLog.Amount;
        cout << "| " << setw(10) << left << TransferLog.SrcBalanceAfter;
        cout << "| " << setw(10) << left << TransferLog.DesBalanceAfter;
        cout << "| " << setw(8) << left << TransferLog.UserName;

	}
    
public:

    static void ShowTransferLogScreen()
    {
        vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransFerLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTransferLogRecord Record : vTransferLogRecord)
            {

               PeintTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
    
};


