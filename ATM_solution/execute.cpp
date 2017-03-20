// execute.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "mainATM.h"
#include "fileControl.h"

fileControl fc;

int main()
{
	srand((unsigned long long)time(NULL));	// 계좌 번호 임의 생성
	
	// wchar_t* 한글 출력 설정
	std::wcout.imbue(std::locale(_KOREAN_CHARACTER_SET));
	std::wcin.imbue(std::locale(_KOREAN_CHARACTER_SET));

	mainATM atm;
	if (fc.loadFile(_DATABASE_FILE_NAME))
		atm.startATM();

	return 0;
}
