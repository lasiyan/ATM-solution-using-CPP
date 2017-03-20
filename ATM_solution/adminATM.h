// adminATM.h
// 고객에 대한 관리적 측면의 기능 수행
// 전체 사용자 출력, 특정 사용자 검색, 사용자 추가
// 삭제, 사용자 패스워드 정보 수정
// 그리고 데이터베이스(.xls) 파일에 대한 백업 기능 수행
// 마찬가지로 데이터베이스로 input 및 output을 위해
// Client 객체를 사용

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
