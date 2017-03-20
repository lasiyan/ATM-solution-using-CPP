#include "stdafx.h"
#include "clientATM.h"

extern client clnt;
extern fileControl fc;
extern bool _session_clear;

// �� �޴� ����
namespace CLIENT_MENU {
	enum {
		WITHDRAWL = '1',
		BALANCE_INQUIRY,
		DEPOSIT,
		ACCOUNT_TRANSFER,
		BACK = '9',
		END_ATM = '0'
	};
}

char clientATM::printMenu() {
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "			1. ���� ����\n" << endl;
	cout << "			2. ���� ��ȸ\n" << endl;
	cout << "			3. �Ա�\n" << endl;
	cout << "			4. ���� ��ü\n" << endl;
	cout << "			9. ���� �޴�\n" << endl;
	cout << "			0. ����\n" << endl;
	cout << "	====================================================\n" << endl;

	char sel;
	while (1) {
		cout << "	�޴��� �����ϼ���";
		sel = getch();
		if ((sel < CLIENT_MENU::END_ATM || sel > CLIENT_MENU::ACCOUNT_TRANSFER)
			&& sel != CLIENT_MENU::BACK) {
			cout << "	�߸� �Է��ϼ̽��ϴ�. �ٽ� Ȯ���ϼ���" << endl;
			continue;
		}
		else break;
	}
	return sel;
}

void clientATM::startATM() {
	selection = printMenu();
	
	if (selection == CLIENT_MENU::END_ATM)
		endATM();
	else if (selection == CLIENT_MENU::BACK) {
		mainATM::startATM();
	}
	else {
		if (clientChk() == true) {
			switch (selection) {
			case CLIENT_MENU::WITHDRAWL:
				withdrawl();
				break;
			case CLIENT_MENU::BALANCE_INQUIRY:
				balanceInquiry();
				break;
			case CLIENT_MENU::DEPOSIT:
				deposit();
				break;
			case CLIENT_MENU::ACCOUNT_TRANSFER:
				accountTransfer();
				break;
			}
		}
		exitState('c');
	}
}

bool clientATM::clientChk() {
	int retval;
	if (strcmp(clnt.getAccountNum(), "") != _IS_SAME)
		return true;
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		���� ��ȣ :	";
	cin >> account;
	cout << "\n		��� ��ȣ :	";
	cin >> password;
	cout << "\n	====================================================\n" << endl;

	// 1. ���̵� �� ��й�ȣ Ȯ��
	try {
		retval = fc.loginCheck(account, password);

		// 2. ���̵� �Ǵ� ��й�ȣ�� ��ġ���� ������
		// �ش� ���� �ڵ� ��ȯ
		if (retval == _NO_USER_IN_DB) throw retval;
		if (retval == _NOT_CORRECT_PWD) throw retval;

		// throw���� ������ DO�� ���� ��ü ����(session)
		clnt.setAccountNum(account);
		clnt.setPassword(password);
		_session_clear = false;
		return true;
	}
	catch (int retval) {
		if (retval == _NOT_CORRECT_PWD) {
			cout << "	��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n	\n" << endl;
		}
		else {}
		return false;
	}
}

void clientATM::withdrawl() {

	// 1.1 �ݾ� �Է�
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		������ �ݾ�		";
	cin >> balance;
	cout << "\n	====================================================\n" << endl;

	// 1.2 �ݾ� ����
	clnt.setBalance(balance);
	clnt.setType("-");
	cout << "	������ " << clnt.getAccountNum() << " ���¿���" << endl;
	cout << "	" << clnt.getBalance() << " ���� �����Ͻðڽ��ϱ�? [ y / n ]  ";
	cin >> selection;
	if (selection == 'y' || selection == 'Y') {
		
		// 1.3 DB ����
		try {
			ret = fc.updateBalance(
				clnt.getAccountNum(),
				L"���� ����",
				clnt.getBalance(),
				"-"
			);

	// 1.4 ��� ���
			if (ret == false) throw ret;
			cout << "\n	����Ǿ����ϴ�." << endl;
			cout << "	���� �� �ܾ��� " << clnt.getBalance() << " �� �Դϴ�\n" << endl;
		}
		catch (bool ret) {
			return;
		}
	}
		
	else if (selection == 'n' || selection == 'N') {
		cout << "\n	������ ��ҵǾ����ϴ�.\n" << endl;
	}
	else {
		cout << "\n	�߸��� �Է��Դϴ�. ó������ ���ư��ϴ�.\n" << endl;
	}
}

void clientATM::balanceInquiry() {

	// 2.1 ����� ���� Loading
	try {
		ret = fc.selectClient(clnt.getAccountNum());
		if (ret == false) throw ret;
	}
	catch (bool ret) {
		cout << "selectClient() Error" << endl;
		return;
	}

	// 2.2 �ܼ� �� ���� ���
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		���� ��ȣ	 " << clnt.getAccountNum() << endl;
	wcout << L"\n		�� ��		 " << clnt.getUserName() << endl;
	cout << "\n		���� �ܾ�	 " << clnt.getBalance() << " ��\n" << endl;
	cout << "	=======================================================================" << endl;

	// 2.3 �� �ŷ� ���� ���
	cout << "\n				    �� �ŷ� ����	 \n" << endl;
	cout << "	    ����    	      �ŷ���		 �ŷ���		 �ݾ�	�ܾ�" << endl;
	cout << "	-----------------------------------------------------------------------\n" << endl;

	// 2.4 DB���� �ŷ� ���� ��ȸ
	try {
		ret = fc.selectTradeList(clnt.getAccountNum());
		if (ret == false) throw ret;
		puts("");
	}
	catch (bool ret) {
		cout << "	�ŷ� ������ �����ϴ�.\n" << endl;
	}
}

void clientATM::deposit() {

	// 3.1 �ݾ� �Է�
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		�Ա��� �ݾ�		";
	cin >> balance;
	while (getchar() != '\n');
	cout << "\n	====================================================\n" << endl;

	// 3.2 �ݾ� ����
	clnt.setBalance(balance);
	clnt.setType("+");

	// 3.3 �Ա� Ȯ��
	cout << "	�Ա��� ���°� " << clnt.getAccountNum() << " �� �½��ϱ�? [ y / n ]  ";
	cin >> selection;
	while (getchar() != '\n');
	if (selection == 'y' || selection == 'Y') {
		try {

			// 3.4 DB ����
			ret = fc.updateBalance(
				clnt.getAccountNum(),
				L"�Ա�",
				clnt.getBalance(),
				"+"
			);

	// 3.5 �Ա� ��� ���
			if (ret == false) throw ret;
			cout << "\n	�ԱݵǾ����ϴ�." << endl;
			cout << "	�Ա� �� �ݾ��� " << clnt.getBalance() << " �� �Դϴ�\n" << endl;
		}
		catch (bool ret)
		{
			cout << "\n	�Աݿ� �����Ͽ����ϴ�. ��� �� �ٽ� �õ����ּ���\n" << endl;
			return;
		}
	}

	else if (selection == 'n' || selection == 'N') {
		cout << "\n	�Ա��� ��ҵǾ����ϴ�.\n" << endl;
		return;
	}
	else {
		cout << "\n	�߸��� �Է��Դϴ�. ���α׷��� �����մϴ�.\n" << endl;
	}
}

void clientATM::accountTransfer() {
	// 4.1 �޴� ����� ���� �� �۱ݾ� �Է�
	char rcvAcNo[50] = { 0 };
	int rcvBal = 0, resultBal;
	bool ret1, ret2;
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		��ü�� ����		";
	cin >> rcvAcNo;
	while (getchar() != '\n');
	if (strcmp(clnt.getAccountNum(), rcvAcNo) == _IS_SAME) {
		cout << "\n	���� ���¿� ��ü�� ���°� �����մϴ�\n" << endl;
		return;
	}
	cout << "\n		��ü �ݾ�		";
	cin >> rcvBal;
	while (getchar() != '\n');
	cout << "\n	====================================================\n" << endl;

	// 4.2 �޴� ��� ��ü ���� �� ������ ����
	client receiver(rcvAcNo, rcvBal, "+");
	if (wcscmp(fc.searchUserName(receiver.getAccountNum()), L"�̸� ����") == _IS_SAME) {
		return;
	}
	receiver.setUserName(fc.searchUserName(receiver.getAccountNum()));
	clnt.setUserName(fc.searchUserName(clnt.getAccountNum()));

	// 4.3 �޴� ��� ���� ��� �� ��Ȯ��
	cout << "	�Ա� ����		" << receiver.getAccountNum() << endl;
	wcout << L"	������			" << receiver.getUserName() << endl;
	cout << "\n	��ü�Ͻðڽ��ϱ�? [ y / n ]  ";
	scanf("%c", &selection);
	if (selection == 'y' || selection == 'Y') {
		try {
			// 4.4.1 ������ ����� DB ����
			try {
				ret1 = fc.updateBalance(
					clnt.getAccountNum(),
					receiver.getUserName(),
					receiver.getBalance(),
					"-"
				);
				resultBal = clnt.getBalance();
				if (ret1 == false) throw ret1;
			}
			catch (bool ret1) {	return;	}
			// 4.4.2 �޴� ����� DB ����
			try {
				ret2 = fc.updateBalance(
					receiver.getAccountNum(),
					clnt.getUserName(),
					receiver.getBalance(),
					"+"
				);
				if (ret2 == false) throw ret2;
			}
			catch (bool ret2) {	return;	}
			
			// 4.4.3 ���� return value�� AND ���� �� ���� ��� commit
			if ((ret = (ret1 & ret2)) == true) {
				cout << "\n	��ü�� �Ϸ�Ǿ����ϴ�." << endl;
				cout << "	��ü �� �ܾ��� " << resultBal << " �� �Դϴ�\n" << endl;
			}
			else throw ret;
		}
		catch (bool ret)
		{
			return;
		}
	}

	else if (selection == 'n' || selection == 'N') {
		cout << "\n	��ü�� ��ҵǾ����ϴ�.\n" << endl;
		return;
	}
	else {
		cout << "\n	�߸��� �Է��Դϴ�. ó������ ���ư��ϴ�.\n" << endl;
		return;
	}
}

void clientATM::endATM() {
	cout << "\n\n	client ATM ����. �̿����ּż� �����մϴ�\n" << endl;
	system("pause>>null");
	exit(0);
}