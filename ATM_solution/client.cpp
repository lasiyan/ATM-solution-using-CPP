// atmŬ�������� ���Ǵ� ������(value)�� ����
// ��ü�� �����Ͽ� �ڵ带 ĸ��ȭ�ϰ� ������ �����Ѵ�.

#include "stdafx.h"
#include "client.h"

char* client::getAccountNum() {
	return accountNum;
}

void client::setAccountNum(char* acNo) {
	strcpy(accountNum, acNo);
}

wchar_t* client::getUserName() {
	return userName;
}

void client::setUserName(wchar_t* uName) {
	wcscpy(userName, uName);
}

char* client::getPassword() {
	return password;
}
void client::setPassword(char* pwd) {
	strcpy((char*)password, (char*)pwd);
}

int client::getBalance() {
	return balance;
}

void client::setBalance(int bal) {
	balance = bal;
}

char* client::getTradeDate() {
	return tradeDate;
}

void client::setTradeDate(char* td) {
	strcpy((char*)tradeDate, (char*)td);
}

int client::getTradeMoney() {
	return tradeMoney;
}

void client::setTradeMoney(int tm) {
	tradeMoney = tm;
}

char* client::getType() {
	return type;
}

void client::setType(char* tp) {
	strcpy((char*)type, (char*)tp);
}
