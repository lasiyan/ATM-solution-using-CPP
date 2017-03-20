// clientATM�� mainATM�� parent Class��
// ATM Solution ���ݿ� ��ģ ����� �Լ����� Classȭ ��Ű��
// �ش� �Լ��� �� Child Class���� ��� �Ǵ�
// Method Overwriting �Ͽ� ��� �� ��ü������ �������� ���,
// �� �� adminATM�� clientATM���� ����� ���� ���뼺�� ������Ų��.

#pragma once
#include "client.h"

class mainATM {
public:
	char account[_ACCOUNT_NUMBER_LENGTH];
	char password[_MAX_PASSWORD_LENGTH];
	int balance;

	char selection;
	bool ret;
	
	// mainATM ������ �� �Ҹ���
	mainATM();
	~mainATM();

	// ATM ���� ��� ����
	void init();
	client init(client c);	// ���� �ʱ�ȭ �Լ�

	void startATM();	// ATM ���� �Լ�
	char printMenu();	// �ʱ� �޴� ȭ�� ���

	virtual void endATM();		// ATM ���� �Լ�(���μ��� ����)
	void exitState(char c);
};
