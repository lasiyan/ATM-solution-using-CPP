// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <conio.h>

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <time.h>

#include "ExcelFormat.h"

#define _CHARACTER_BLANK ""
#define _WIDE_CHARACTER_BLANK L""
#define _KOREAN_CHARACTER_SET "kor"
#define _DATABASE_FILE_NAME "dataBase.xls"
#define _WORKSHEET_ONE 0
#define _WORKSHEET_TWO 1
#define _MAX_FAIL_COUNT 4
#define _IS_SAME 0

#define _NO_CARDINALITIES 0
#define _NO_USER_IN_DB 0
#define _FINE_CORRECT_USER 1
#define _DATA_ACCESS_ERROR -1
#define _NOT_CORRECT_PWD -1

#define _MIN_PASSWORD_LENGTH 6
#define _MAX_PASSWORD_LENGTH 16
#define _MIN_USERNAME_LENGTH 2
#define _MAX_USERNAME_LENGTH 16
#define _ACCOUNT_NUMBER_LENGTH 13
#define _TRADE_DATE_LENGTH 20
#define _TYPE_LENGTH 2
#define _FIRST_HYPHEN 3
#define _LAST_HYPHEN 8
#define _NUM_TO_CHAR_CONVERT 48

using namespace std;
using namespace ExcelFormat;	// Basic Excel ��� ���ӽ����̽�


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
