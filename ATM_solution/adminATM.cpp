#include "stdafx.h"
#include "adminATM.h"

// 외부 변수 선언 - clnt의 경우 DO 클래스로 사용
extern client clnt;
extern fileControl fc;
extern bool _session_clear;

// 관리자 메뉴 정의
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

// 메뉴 출력 및 선택된 문자 값 리턴
char adminATM::printMenu() {
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "			1. 사용자 조회	\n" << endl;
	cout << "			2. 고객 검색	\n" << endl;
	cout << "			3. 고객 등록	\n" << endl;
	cout << "			4. 고객 정보 수정	\n" << endl;
	cout << "			5. 고객 정보 삭제	\n" << endl;
	cout << "			6. DB 백업	\n" << endl;
	cout << "			9. 이전 메뉴	\n" << endl;
	cout << "			0. 종료	\n" << endl;
	cout << "	====================================================\n" << endl;

	char sel;
	while (1) {
		std::cout << "	메뉴를 선택하세요";
		sel = getch();

		if ((sel < '0' || sel > '6') && sel != '9') {
			cout << "	잘못 입력하셨습니다. 다시 확인하세요" << endl;
			continue;
		}
		else
			return sel;
	}
}

// adminATM 시작 메서드
void adminATM::startATM() {
	bool adChk = adminChk();	// 관리자 계정 체크
	if (adChk == false) {
		exitState(NULL);
		return;	// 관리자 접속 계정이 틀리면 종료
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
			// 전체 사용자 조회
			admShowAll();
			break;
		case ADMIN_MENU::SELECT_CLIENT:
			// 고객 검색
			admSelectClient();
			break;
		case ADMIN_MENU::INSERT_CLIENT:
			// 고객 등록
			admInsertClient();
			break;
		case ADMIN_MENU::UPDATE_CLIENT:
			// 고객 정보 수정 
			admUpdateClient();
			break;
		case ADMIN_MENU::DELETE_CLIENT:
			// 고객 정보 삭제
			admDeleteClient();
			break;
		case ADMIN_MENU::DB_BACK_UP:
			// DB 백업
			admBackup();
			break;
		}
		exitState('a');	// 특정 메서드 수행이 끝나면
						// 다시 adminATM으로 회귀
	}
}

bool adminATM::adminChk() {
	// 계정 확인
	if (wcscmp(admName, _ADMIN_ID) == 0 && strcmp(admPwd, _ADMIN_PWD) == 0)
		return true;

	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		관리자 ID :	";
	wcin >> admName;
	cout << "\n		비밀 번호 :	";
	cin >> admPwd;
	cout << "\n	====================================================\n" << endl;

	if (wcscmp(admName, _ADMIN_ID) == 0 && strcmp(admPwd, _ADMIN_PWD) == 0) {
		_session_clear = false;
		return true;
	}
	else {
		cout << "	아이디 또는 비밀번호가 일치하지 않습니다\n" << endl;
		return false;
	}
}

void adminATM::admShowAll() {
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		  계좌번호	고객명	  잔액" << endl;
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
	cout << "		검색할 계좌 :	";
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
	cout << "		계좌 번호	 " << clnt.getAccountNum() << endl;
	puts("");
	wcout << L"		고객 명		 " << clnt.getUserName() << endl;
	puts("");
	cout << "		예금 잔액	 " << clnt.getBalance() << " 원" << endl;
	cout << "\n	====================================================\n" << endl;
}

void adminATM::admInsertClient() {
	// 계좌 생성
	wchar_t userName[_MAX_USERNAME_LENGTH];
	strcpy(account, createAccount());
	clnt.setAccountNum(account);
	system("cls");
	cout << "\n	====================================================\n" << endl;
	int count1 = 0, count2 = 0;
	while (1) {
		count1++;
		wcout << L"		고객 명		 ";
		wcin >> userName;
		if (count1 > _MAX_FAIL_COUNT) {
			cout << "\n		   연속된 실패. 잠시 후 다시 시도해주세요\n\n" << endl;
			return;
		}
		if (wcslen(userName) >= _MIN_USERNAME_LENGTH) break;
		else cout << "\n		   이름은 최소 2글자 이상입니다.\n" << endl;
	}
	clnt.setUserName(userName);
	puts("");
	while (1) {
		count2++;
		cout << "		비밀 번호	 ";
		cin >> password;
		if (count2 > _MAX_FAIL_COUNT) {
			cout << "\n		   연속된 실패. 잠시 후 다시 시도해주세요\n" << endl;
			return;
		}
		if (strlen(password) >= _MIN_PASSWORD_LENGTH) break;
		else cout << "\n		   비밀번호는 최소 6자 이상입니다.\n" << endl;
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
		cout << "	" << clnt.getAccountNum() << " 계좌가 생성되었습니다.\n" << endl;
	}
	catch (bool ret) {
		return;
	}
}

char* createAccount() {
	char acNoTmp[_ACCOUNT_NUMBER_LENGTH] = { 0 };
	acNoTmp[0] = (char)(((rand() % 8) + 1) + _NUM_TO_CHAR_CONVERT);
		// 1~9 중 숫자 하나 생성
	for (int i = 1; i < _ACCOUNT_NUMBER_LENGTH - 1; i++) {
		acNoTmp[i] = (char)((rand() % 10) + _NUM_TO_CHAR_CONVERT);
			// 0~9 중 숫자 하나 생성
		if (i == _FIRST_HYPHEN || i == _LAST_HYPHEN) acNoTmp[i] = '-';
	}
	return acNoTmp;
}

void adminATM::admDeleteClient() {
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		계좌 번호	 ";
	cin >> account;
	clnt.setAccountNum(account);
	cout << "\n	====================================================" << endl;
	try {
		ret = fc.deleteClient(clnt.getAccountNum());
		if (ret == false) throw ret;
		cout << "	삭제가 완료되었습니다\n" << endl;
	}
	catch (bool ret) {
		return;
	}
}

void adminATM::admUpdateClient() {
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		계좌 번호	 ";
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
		cout << "		변경할 비밀 번호	 ";
		cin >> password;
		if (count > _MAX_FAIL_COUNT) {
			cout << "\n		   연속된 실패. 잠시 후 다시 시도해주세요.\n" << endl;
			return;
		}
		if (strlen(password) >= _MIN_PASSWORD_LENGTH) break;
		else cout << "\n		   비밀번호는 최소 6자 이상입니다.\n" << endl;
	}
	clnt.setPassword(password);
	cout << "\n	====================================================" << endl;

	try {
		ret = fc.updateClient(clnt.getAccountNum(), clnt.getPassword());
		if (ret == false) throw ret;
		cout << "	비밀번호가 갱신되었습니다.\n" << endl;
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
	cout << "\n\n	백업되었습니다.\n" << endl;
}

void adminATM::endATM() {
	cout << "\n\n	admin ATM 종료. 이용해주셔서 감사합니다\n" << endl;
	system("pause>>null");
	exit(0);
}