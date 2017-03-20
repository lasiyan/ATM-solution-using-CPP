#include "stdafx.h"
#include "mainATM.h"
#include "clientATM.h"
#include "adminATM.h"

clientATM clntATM;
adminATM admATM;
client initClnt(
		_CHARACTER_BLANK,
		_WIDE_CHARACTER_BLANK,
		_CHARACTER_BLANK,
		0,
		_CHARACTER_BLANK,
		0,
		_CHARACTER_BLANK
		);
extern client clnt;

bool _session_clear = true;

namespace MAIN_MENU {
	enum {
		START_CLIENT = '1',
		START_ADMIN,
		END_ATM = '0'
	};
}

mainATM::mainATM() {}
void mainATM::startATM() {
	while (1) {
		// ���� �� mainATM �Ӽ� �� �ʱ�ȭ
		init();

		// ����� ��� �Ǵ� ������ ��� ���� ��
		// �ʱ� ���� ���ƿ� ���
		// ��� ���� �� �ʱ�ȭ
		if (_session_clear == false) {
			clnt = init(initClnt);
			admATM.init();
		}
		selection = printMenu();

		switch (selection) {
		case MAIN_MENU::START_CLIENT: {
			// ����� �޴� ���
			clntATM.startATM();
		}
				  break;
		case MAIN_MENU::START_ADMIN: {
			// ������ �޴� ���
			admATM.startATM();
		}
				  break;
		case MAIN_MENU::END_ATM:
			endATM();
		}
	}
}

char mainATM::printMenu() {
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "			1. ����� ���             \n" << endl;
	cout << "			2. ������ ���             \n" << endl;
	cout << "			0. ����                  \n" << endl;
	cout << "	====================================================\n" << endl;

	char sel;
	while (1) {
		cout << "	�޴��� �����ϼ���";
		sel = getch();

		if (sel < MAIN_MENU::END_ATM || sel > MAIN_MENU::START_ADMIN) {
			cout << "	�߸� �Է��ϼ̽��ϴ�. �ٽ� Ȯ���ϼ���" << endl;
			continue;
		}
		else
			return sel;
	}
}

void mainATM::endATM() {
	cout << "\n\n	ATM ����. �̿����ּż� �����մϴ�\n" << endl;
	system("pause>>null");
	exit(0);
}

void mainATM::init() {
	strcpy(account, _CHARACTER_BLANK);
	strcpy(password, _CHARACTER_BLANK);
	balance = 0;
	selection = NULL;
	ret = false;
}

client mainATM::init(client c) {
	client tmp;
	return tmp = c;
}

void mainATM::exitState(char c) {
	char input = NULL;

	cout << "	[Enter] ó������	[q] ���α׷� ����" << endl;
	input = getch();

	switch (input) {
	case 'q':
	case 'Q':
		endATM();
		break;
	default:
		if (c == 'c') clntATM.startATM();
		else if (c == 'a') admATM.startATM();
		else startATM();
	}
}

mainATM::~mainATM() {
	return;
}

