// ClientATM.h
// 고객에 대한 ATM의 처리를 담당하는 클래스
// 고객의 인출, 입금, 예금 조회, 계좌 이체 기능을 수행하며
// 각각의 기능은 client 객체를 통해 수행되며
// 마찬가지로 fileControl 역시 client 객체를 통해 실행된다.

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
