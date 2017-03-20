// client.h
// ATM_solution의 Data Object 클래스로
// View(clientATM, adminATM)에 대한 수행(Model = fileControl)을 위한
// 중간 단계 역할을 수행한다.
// 일종의 Web에서 MVC패턴 형식으로 구현하였으며(MVC는 객체지향을 기반으로 하는 점을 참조)
// private 접근 지정자로 데이터의 캡슐화를 통한 정보 은닉을 담당한다.

#pragma once
#include "fileControl.h"

class client {
private:
	char accountNum[_ACCOUNT_NUMBER_LENGTH];
	wchar_t userName[_MAX_USERNAME_LENGTH];
	char password[_MAX_PASSWORD_LENGTH];
	int balance;
	char tradeDate[_TRADE_DATE_LENGTH];
	int tradeMoney;
	char type[_TYPE_LENGTH];
public:
	client(void) {}
	client(char* _gtAc, int _gtBal, char* gtTyp) {
		strcpy(accountNum, _gtAc);
		balance = _gtBal;
		strcpy(type, gtTyp);
	}
	client(char* _ac, wchar_t* _un, char* _pwd,
		int _bal, char* _td, int _tm, char* _typ)
	{
		strcpy(accountNum, _ac);
		wcscpy(userName, _un);
		strcpy(password, _pwd);
		balance = _bal;
		strcpy(tradeDate, _td);
		tradeMoney = _tm;
		strcpy(type, _typ);
	}
	client(wchar_t* _an, char* _pwd) {
		wcscpy(userName, _an);
		strcpy(password, _pwd);
	}
	char* getAccountNum();
	void setAccountNum(char*);

	wchar_t* getUserName();
	void setUserName(wchar_t*);
	
	char* getPassword();
	void setPassword(char*);

	int getBalance();
	void setBalance(int);

	char* getTradeDate();
	void setTradeDate(char*);

	int getTradeMoney();
	void setTradeMoney(int);

	char* getType();
	void setType(char*);
};
