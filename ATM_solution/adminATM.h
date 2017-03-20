// adminATM.h
// ���� ���� ������ ������ ��� ����
// ��ü ����� ���, Ư�� ����� �˻�, ����� �߰�
// ����, ����� �н����� ���� ����
// �׸��� �����ͺ��̽�(.xls) ���Ͽ� ���� ��� ��� ����
// ���������� �����ͺ��̽��� input �� output�� ����
// Client ��ü�� ���

#pragma once
#include "mainATM.h"
#include "client.h"

#define _ADMIN_ID L"admin"
#define _ADMIN_PWD "admin"
#define _ADMIN_ID_INIT L""
#define _ADMIN_PWD_INIT ""

char* createAccount();

class adminATM : public mainATM {
public:
	char printMenu();
	void startATM();
	bool adminChk();
	void init();
private:
	wchar_t admName[_MAX_USERNAME_LENGTH] = { NULL };
	char admPwd[_MAX_USERNAME_LENGTH] = { NULL };
	virtual void endATM();

	void admShowAll();
	void admSelectClient();
	void admInsertClient();
	void admDeleteClient();
	void admUpdateClient();
	void admBackup();
};
