// DataBase(.xls) ���Ͽ� ���� ���� Ŭ����
// ������ ����� �� ������ ����(HDD)�� �����Ű�� ������ ���
// C, C++�� File ����°� ����
// Excel ���Ͽ� ���� �� ��� ���� STL�� vector �������� ������ ��
// ������ Cell�� ���� ���� �� ó���� ����

#pragma once
#include <fstream>
#include "client.h"

#define _FIRST_COLUM 1
#define _FIRST_ATTRIBUTE 1
#define _ACCOUNT_NUMBER 1
#define _USERNAME 2
#define _PASSWORD 3
#define _BALANCE 4

#define _OWNER_NAME 2
#define _USERNAME_ 3
#define _TYPE 4
#define _TRADE_MONEY 5
#define _BALANCE_ 6
#define _TRADE_DATE 7

class fileControl {
private:
	int searchAcNum(char * acNo);
	bool alreadyChk(char* acNo);
	int fret_i = 0;		// _file return value integer;
	int fret_b = false;		// _file return value boolean
public:
	bool loadFile(char* fileName);
	void backupFile();

	bool selectAllClient();
	bool selectClient(char * acNo);
	bool insertClient(char* acNo, wchar_t* uName, char* pwd);
	bool deleteClient(char* acNo);
	bool updateClient(char* acNo, char* passwd);
	void updateClient(char * acNo, int bal);

	int loginCheck(char * acNo, char * pwd);

	bool updateBalance(char* acNo, wchar_t* uName, int bal, char* type);
	void insertTradeList(char*, wchar_t*, int bal, int balance, char* type);
	bool selectTradeList(char* acNo);
	wchar_t* searchUserName(char* acNo);
};

class BALANCE {
private:
	int result;
public:
	BALANCE::BALANCE(int input) : result(input) { }
	BALANCE operator+(BALANCE &ref) {
		return BALANCE(result + ref.result);
	}
	BALANCE operator-(BALANCE &ref) {
		return BALANCE(result - ref.result);
	}
	int getBalance() {
		return result;
	}
};