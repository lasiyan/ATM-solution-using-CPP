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
		// 시작 시 mainATM 속성 값 초기화
		init();

		// 사용자 모드 또는 관리자 모드 접속 후
		// 초기 모드로 돌아올 경우
		// 모든 세션 값 초기화
		if (_session_clear == false) {
			clnt = init(initClnt);
			admATM.init();
		}
		selection = printMenu();

		switch (selection) {
		case MAIN_MENU::START_CLIENT: {
			// 사용자 메뉴 출력
			clntATM.startATM();
		}
				  break;
		case MAIN_MENU::START_ADMIN: {
			// 관리자 메뉴 출력
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
	cout << "			1. 사용자 모드             \n" << endl;
	cout << "			2. 관리자 모드             \n" << endl;
	cout << "			0. 종료                  \n" << endl;
	cout << "	====================================================\n" << endl;

	char sel;
	while (1) {
		cout << "	메뉴를 선택하세요";
		sel = getch();

		if (sel < MAIN_MENU::END_ATM || sel > MAIN_MENU::START_ADMIN) {
			cout << "	잘못 입력하셨습니다. 다시 확인하세요" << endl;
			continue;
		}
		else
			return sel;
	}
}

void mainATM::endATM() {
	cout << "\n\n	ATM 종료. 이용해주셔서 감사합니다\n" << endl;
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

	cout << "	[Enter] 처음으로	[q] 프로그램 종료" << endl;
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

