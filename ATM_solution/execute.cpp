// execute.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "mainATM.h"
#include "fileControl.h"

fileControl fc;

int main()
{
	srand((unsigned long long)time(NULL));	// ���� ��ȣ ���� ����
	
	// wchar_t* �ѱ� ��� ����
	std::wcout.imbue(std::locale(_KOREAN_CHARACTER_SET));
	std::wcin.imbue(std::locale(_KOREAN_CHARACTER_SET));

	mainATM atm;
	if (fc.loadFile(_DATABASE_FILE_NAME))
		atm.startATM();

	return 0;
}
