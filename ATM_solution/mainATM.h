// clientATM과 mainATM의 parent Class로
// ATM Solution 전반에 걸친 공통된 함수들을 Class화 시키고
// 해당 함수를 각 Child Class에서 사용 또는
// Method Overwriting 하여 사용 및 객체지향의 다형성을 담당,
// 이 후 adminATM과 clientATM에서 사용을 통한 재사용성을 증가시킨다.

#pragma once
#include "client.h"

class mainATM {
public:
	char account[_ACCOUNT_NUMBER_LENGTH];
	char password[_MAX_PASSWORD_LENGTH];
	int balance;

	char selection;
	bool ret;
	
	// mainATM 생성자 및 소멸자
	mainATM();
	~mainATM();

	// ATM 공통 사용 인자
	void init();
	client init(client c);	// 세션 초기화 함수

	void startATM();	// ATM 실행 함수
	char printMenu();	// 초기 메뉴 화면 출력

	virtual void endATM();		// ATM 종료 함수(프로세스 종료)
	void exitState(char c);
};
