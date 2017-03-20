// ClientATM.h
// ���� ���� ATM�� ó���� ����ϴ� Ŭ����
// ���� ����, �Ա�, ���� ��ȸ, ���� ��ü ����� �����ϸ�
// ������ ����� client ��ü�� ���� ����Ǹ�
// ���������� fileControl ���� client ��ü�� ���� ����ȴ�.

#pragma once
#include "mainATM.h"
#include "client.h"

class clientATM : public mainATM {
private:
	void withdrawl();
	void balanceInquiry();
	void deposit();
	void accountTransfer();
	virtual void endATM();
public:
	void startATM();
	char printMenu();
	bool clientChk();
};
