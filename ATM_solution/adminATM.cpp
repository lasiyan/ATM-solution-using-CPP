#include "stdafx.h"
#include "adminATM.h"

// �ܺ� ���� ���� - clnt�� ��� DO Ŭ������ ���
extern client clnt;
extern fileControl fc;
extern bool _session_clear;

// ������ �޴� ����
namespace ADMIN_MENU {
	enum {
		SHOW_ALL = '1',
		SELECT_CLIENT,
		INSERT_CLIENT,
		UPDATE_CLIENT,
		DELETE_CLIENT,
		DB_BACK_UP,
		BACK = '9',
		END_ATM = '0'
	};
}

// �޴� ��� �� ���õ� ���� �� ����
char adminATM::printMenu() {
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "			1. ����� ��ȸ	\n" << endl;
	cout << "			2. �� �˻�	\n" << endl;
	cout << "			3. �� ���	\n" << endl;
	cout << "			4. �� ���� ����	\n" << endl;
	cout << "			5. �� ���� ����	\n" << endl;
	cout << "			6. DB ���	\n" << endl;
	cout << "			9. ���� �޴�	\n" << endl;
	cout << "			0. ����	\n" << endl;
	cout << "	====================================================\n" << endl;

	char sel;
	while (1) {
		std::cout << "	�޴��� �����ϼ���";
		sel = getch();

		if ((sel < '0' || sel > '6') && sel != '9') {
			cout << "	�߸� �Է��ϼ̽��ϴ�. �ٽ� Ȯ���ϼ���" << endl;
			continue;
		}
		else
			return sel;
	}
}

// adminATM ���� �޼���
void adminATM::startATM() {
	bool adChk = adminChk();	// ������ ���� üũ
	if (adChk == false) {
		exitState(NULL);
		return;	// ������ ���� ������ Ʋ���� ����
	}

	selection = printMenu();

	if (selection == ADMIN_MENU::END_ATM)
		endATM();
	if (selection == ADMIN_MENU::BACK) {
		mainATM::startATM();
	}
	else {
		switch (selection) {
		case ADMIN_MENU::SHOW_ALL:
			// ��ü ����� ��ȸ
			admShowAll();
			break;
		case ADMIN_MENU::SELECT_CLIENT:
			// �� �˻�
			admSelectClient();
			break;
		case ADMIN_MENU::INSERT_CLIENT:
			// �� ���
			admInsertClient();
			break;
		case ADMIN_MENU::UPDATE_CLIENT:
			// �� ���� ���� 
			admUpdateClient();
			break;
		case ADMIN_MENU::DELETE_CLIENT:
			// �� ���� ����
			admDeleteClient();
			break;
		case ADMIN_MENU::DB_BACK_UP:
			// DB ���
			admBackup();
			break;
		}
		exitState('a');	// Ư�� �޼��� ������ ������
						// �ٽ� adminATM���� ȸ��
	}
}

bool adminATM::adminChk() {
	// ���� Ȯ��
	if (wcscmp(admName, _ADMIN_ID) == 0 && strcmp(admPwd, _ADMIN_PWD) == 0)
		return true;

	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		������ ID :	";
	wcin >> admName;
	cout << "\n		��� ��ȣ :	";
	cin >> admPwd;
	cout << "\n	====================================================\n" << endl;

	if (wcscmp(admName, _ADMIN_ID) == 0 && strcmp(admPwd, _ADMIN_PWD) == 0) {
		_session_clear = false;
		return true;
	}
	else {
		cout << "	���̵� �Ǵ� ��й�ȣ�� ��ġ���� �ʽ��ϴ�\n" << endl;
		return false;
	}
}

void adminATM::admShowAll() {
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		  ���¹�ȣ	����	  �ܾ�" << endl;
	cout << "	----------------------------------------------------\n" << endl;
	
	try {
		ret = fc.selectAllClient();
		if (ret == false) throw ret;
	}
	catch (bool ret) {
		cout << "		admShowAll() Error !" << endl;
	}
	cout << "	====================================================\n" << endl;
}

void adminATM::admSelectClient() {
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		�˻��� ���� :	";
	cin >> account;
	clnt.setAccountNum(account);
	cout << "\n	====================================================\n" << endl;

	try {
		ret = fc.selectClient(clnt.getAccountNum());
		if (ret == false) throw ret;
	}
	catch (bool ret) {
		return;
	}
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		���� ��ȣ	 " << clnt.getAccountNum() << endl;
	puts("");
	wcout << L"		�� ��		 " << clnt.getUserName() << endl;
	puts("");
	cout << "		���� �ܾ�	 " << clnt.getBalance() << " ��" << endl;
	cout << "\n	====================================================\n" << endl;
}

void adminATM::admInsertClient() {
	// ���� ����
	wchar_t userName[_MAX_USERNAME_LENGTH];
	strcpy(account, createAccount());
	clnt.setAccountNum(account);
	system("cls");
	cout << "\n	====================================================\n" << endl;
	int count1 = 0, count2 = 0;
	while (1) {
		count1++;
		wcout << L"		�� ��		 ";
		wcin >> userName;
		if (count1 > _MAX_FAIL_COUNT) {
			cout << "\n		   ���ӵ� ����. ��� �� �ٽ� �õ����ּ���\n\n" << endl;
			return;
		}
		if (wcslen(userName) >= _MIN_USERNAME_LENGTH) break;
		else cout << "\n		   �̸��� �ּ� 2���� �̻��Դϴ�.\n" << endl;
	}
	clnt.setUserName(userName);
	puts("");
	while (1) {
		count2++;
		cout << "		��� ��ȣ	 ";
		cin >> password;
		if (count2 > _MAX_FAIL_COUNT) {
			cout << "\n		   ���ӵ� ����. ��� �� �ٽ� �õ����ּ���\n" << endl;
			return;
		}
		if (strlen(password) >= _MIN_PASSWORD_LENGTH) break;
		else cout << "\n		   ��й�ȣ�� �ּ� 6�� �̻��Դϴ�.\n" << endl;
	}
	clnt.setPassword(password);
	puts("");
	cout << "	====================================================" << endl;

	try {
		ret = fc.insertClient(
			clnt.getAccountNum(),
			clnt.getUserName(),
			clnt.getPassword()
		);
		if (ret == false) throw ret;
		cout << "	" << clnt.getAccountNum() << " ���°� �����Ǿ����ϴ�.\n" << endl;
	}
	catch (bool ret) {
		return;
	}
}

char* createAccount() {
	char acNoTmp[_ACCOUNT_NUMBER_LENGTH] = { 0 };
	acNoTmp[0] = (char)(((rand() % 8) + 1) + _NUM_TO_CHAR_CONVERT);
		// 1~9 �� ���� �ϳ� ����
	for (int i = 1; i < _ACCOUNT_NUMBER_LENGTH - 1; i++) {
		acNoTmp[i] = (char)((rand() % 10) + _NUM_TO_CHAR_CONVERT);
			// 0~9 �� ���� �ϳ� ����
		if (i == _FIRST_HYPHEN || i == _LAST_HYPHEN) acNoTmp[i] = '-';
	}
	return acNoTmp;
}

void adminATM::admDeleteClient() {
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		���� ��ȣ	 ";
	cin >> account;
	clnt.setAccountNum(account);
	cout << "\n	====================================================" << endl;
	try {
		ret = fc.deleteClient(clnt.getAccountNum());
		if (ret == false) throw ret;
		cout << "	������ �Ϸ�Ǿ����ϴ�\n" << endl;
	}
	catch (bool ret) {
		return;
	}
}

void adminATM::admUpdateClient() {
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		���� ��ȣ	 ";
	cin >> account;
	clnt.setAccountNum(account);
	puts("");
	try {
		ret = fc.selectClient(clnt.getAccountNum());
		if (ret == false) throw ret;
	}
	catch (bool ret) {
		return;
	}
	int count = 0;
	while (1) {
		count++;
		cout << "		������ ��� ��ȣ	 ";
		cin >> password;
		if (count > _MAX_FAIL_COUNT) {
			cout << "\n		   ���ӵ� ����. ��� �� �ٽ� �õ����ּ���.\n" << endl;
			return;
		}
		if (strlen(password) >= _MIN_PASSWORD_LENGTH) break;
		else cout << "\n		   ��й�ȣ�� �ּ� 6�� �̻��Դϴ�.\n" << endl;
	}
	clnt.setPassword(password);
	cout << "\n	====================================================" << endl;

	try {
		ret = fc.updateClient(clnt.getAccountNum(), clnt.getPassword());
		if (ret == false) throw ret;
		cout << "	��й�ȣ�� ���ŵǾ����ϴ�.\n" << endl;
	}
	catch (bool ret) {
		return;
	}
}

void adminATM::init() {
	wcscpy(admName, _ADMIN_ID_INIT);
	strcpy(admPwd, _ADMIN_PWD_INIT);
}

void adminATM::admBackup() {
	fc.backupFile();
	cout << "\n\n	����Ǿ����ϴ�.\n" << endl;
}

void adminATM::endATM() {
	cout << "\n\n	admin ATM ����. �̿����ּż� �����մϴ�\n" << endl;
	system("pause>>null");
	exit(0);
}