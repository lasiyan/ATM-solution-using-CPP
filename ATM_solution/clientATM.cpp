#include "stdafx.h"
#include "clientATM.h"

extern client clnt;
extern fileControl fc;
extern bool _session_clear;

// 고객 메뉴 정의
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
	cout << "			1. 예금 인출\n" << endl;
	cout << "			2. 예금 조회\n" << endl;
	cout << "			3. 입금\n" << endl;
	cout << "			4. 계좌 이체\n" << endl;
	cout << "			9. 이전 메뉴\n" << endl;
	cout << "			0. 종료\n" << endl;
	cout << "	====================================================\n" << endl;

	char sel;
	while (1) {
		cout << "	메뉴를 선택하세요";
		sel = getch();
		if ((sel < CLIENT_MENU::END_ATM || sel > CLIENT_MENU::ACCOUNT_TRANSFER)
			&& sel != CLIENT_MENU::BACK) {
			cout << "	잘못 입력하셨습니다. 다시 확인하세요" << endl;
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
	cout << "		계좌 번호 :	";
	cin >> account;
	cout << "\n		비밀 번호 :	";
	cin >> password;
	cout << "\n	====================================================\n" << endl;

	// 1. 아이디 및 비밀번호 확인
	try {
		retval = fc.loginCheck(account, password);

		// 2. 아이디 또는 비밀번호가 일치하지 않으면
		// 해당 에러 코드 반환
		if (retval == _NO_USER_IN_DB) throw retval;
		if (retval == _NOT_CORRECT_PWD) throw retval;

		// throw되지 않으면 DO에 얻은 객체 저장(session)
		clnt.setAccountNum(account);
		clnt.setPassword(password);
		_session_clear = false;
		return true;
	}
	catch (int retval) {
		if (retval == _NOT_CORRECT_PWD) {
			cout << "	비밀번호가 일치하지 않습니다.\n	\n" << endl;
		}
		else {}
		return false;
	}
}

void clientATM::withdrawl() {

	// 1.1 금액 입력
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		인출할 금액		";
	cin >> balance;
	cout << "\n	====================================================\n" << endl;

	// 1.2 금액 저장
	clnt.setBalance(balance);
	clnt.setType("-");
	cout << "	정말로 " << clnt.getAccountNum() << " 계좌에서" << endl;
	cout << "	" << clnt.getBalance() << " 원을 인출하시겠습니까? [ y / n ]  ";
	cin >> selection;
	if (selection == 'y' || selection == 'Y') {
		
		// 1.3 DB 갱신
		try {
			ret = fc.updateBalance(
				clnt.getAccountNum(),
				L"예금 인출",
				clnt.getBalance(),
				"-"
			);

	// 1.4 결과 출력
			if (ret == false) throw ret;
			cout << "\n	인출되었습니다." << endl;
			cout << "	인출 후 잔액은 " << clnt.getBalance() << " 원 입니다\n" << endl;
		}
		catch (bool ret) {
			return;
		}
	}
		
	else if (selection == 'n' || selection == 'N') {
		cout << "\n	인출이 취소되었습니다.\n" << endl;
	}
	else {
		cout << "\n	잘못된 입력입니다. 처음으로 돌아갑니다.\n" << endl;
	}
}

void clientATM::balanceInquiry() {

	// 2.1 사용자 정보 Loading
	try {
		ret = fc.selectClient(clnt.getAccountNum());
		if (ret == false) throw ret;
	}
	catch (bool ret) {
		cout << "selectClient() Error" << endl;
		return;
	}

	// 2.2 단순 고객 정보 출력
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		계좌 번호	 " << clnt.getAccountNum() << endl;
	wcout << L"\n		고객 명		 " << clnt.getUserName() << endl;
	cout << "\n		예금 잔액	 " << clnt.getBalance() << " 원\n" << endl;
	cout << "	=======================================================================" << endl;

	// 2.3 상세 거래 내역 출력
	cout << "\n				    상세 거래 내역	 \n" << endl;
	cout << "	    계좌    	      거래일		 거래명		 금액	잔액" << endl;
	cout << "	-----------------------------------------------------------------------\n" << endl;

	// 2.4 DB에서 거래 내역 조회
	try {
		ret = fc.selectTradeList(clnt.getAccountNum());
		if (ret == false) throw ret;
		puts("");
	}
	catch (bool ret) {
		cout << "	거래 내역이 없습니다.\n" << endl;
	}
}

void clientATM::deposit() {

	// 3.1 금액 입력
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		입금할 금액		";
	cin >> balance;
	while (getchar() != '\n');
	cout << "\n	====================================================\n" << endl;

	// 3.2 금액 저장
	clnt.setBalance(balance);
	clnt.setType("+");

	// 3.3 입금 확인
	cout << "	입금할 계좌가 " << clnt.getAccountNum() << " 가 맞습니까? [ y / n ]  ";
	cin >> selection;
	while (getchar() != '\n');
	if (selection == 'y' || selection == 'Y') {
		try {

			// 3.4 DB 갱신
			ret = fc.updateBalance(
				clnt.getAccountNum(),
				L"입금",
				clnt.getBalance(),
				"+"
			);

	// 3.5 입금 결과 출력
			if (ret == false) throw ret;
			cout << "\n	입금되었습니다." << endl;
			cout << "	입금 후 금액은 " << clnt.getBalance() << " 원 입니다\n" << endl;
		}
		catch (bool ret)
		{
			cout << "\n	입금에 실패하였습니다. 잠시 후 다시 시도해주세요\n" << endl;
			return;
		}
	}

	else if (selection == 'n' || selection == 'N') {
		cout << "\n	입금이 취소되었습니다.\n" << endl;
		return;
	}
	else {
		cout << "\n	잘못된 입력입니다. 프로그램을 종료합니다.\n" << endl;
	}
}

void clientATM::accountTransfer() {
	// 4.1 받는 사람의 계좌 및 송금액 입력
	char rcvAcNo[50] = { 0 };
	int rcvBal = 0, resultBal;
	bool ret1, ret2;
	system("cls");
	cout << "\n	====================================================\n" << endl;
	cout << "		이체할 계좌		";
	cin >> rcvAcNo;
	while (getchar() != '\n');
	if (strcmp(clnt.getAccountNum(), rcvAcNo) == _IS_SAME) {
		cout << "\n	현재 계좌와 이체할 계좌가 동일합니다\n" << endl;
		return;
	}
	cout << "\n		이체 금액		";
	cin >> rcvBal;
	while (getchar() != '\n');
	cout << "\n	====================================================\n" << endl;

	// 4.2 받는 사람 객체 생성 후 데이터 저장
	client receiver(rcvAcNo, rcvBal, "+");
	if (wcscmp(fc.searchUserName(receiver.getAccountNum()), L"이름 없음") == _IS_SAME) {
		return;
	}
	receiver.setUserName(fc.searchUserName(receiver.getAccountNum()));
	clnt.setUserName(fc.searchUserName(clnt.getAccountNum()));

	// 4.3 받는 사람 정보 출력 및 재확인
	cout << "	입금 계좌		" << receiver.getAccountNum() << endl;
	wcout << L"	예금주			" << receiver.getUserName() << endl;
	cout << "\n	이체하시겠습니까? [ y / n ]  ";
	scanf("%c", &selection);
	if (selection == 'y' || selection == 'Y') {
		try {
			// 4.4.1 보내는 사람의 DB 갱신
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
			// 4.4.2 받는 사람의 DB 갱신
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
			
			// 4.4.3 둘의 return value를 AND 연산 후 참일 경우 commit
			if ((ret = (ret1 & ret2)) == true) {
				cout << "\n	이체가 완료되었습니다." << endl;
				cout << "	이체 후 잔액은 " << resultBal << " 원 입니다\n" << endl;
			}
			else throw ret;
		}
		catch (bool ret)
		{
			return;
		}
	}

	else if (selection == 'n' || selection == 'N') {
		cout << "\n	이체가 취소되었습니다.\n" << endl;
		return;
	}
	else {
		cout << "\n	잘못된 입력입니다. 처음으로 돌아갑니다.\n" << endl;
		return;
	}
}

void clientATM::endATM() {
	cout << "\n\n	client ATM 종료. 이용해주셔서 감사합니다\n" << endl;
	system("pause>>null");
	exit(0);
}