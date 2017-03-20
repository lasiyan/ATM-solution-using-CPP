#include "stdafx.h"
#include "fileControl.h"

BasicExcel xls;
client clnt;
client adm;

const string currentDateTime() {
	time_t     now = time(0); //현재 시간을 time_t 타입으로 저장
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct); // YYYY-MM-DD.HH:mm:ss 형태의 스트링

	return buf;
}

// 엑셀 파일 로드 함수(vector를 생성하고 해당 벡터에 데이터를 담아옴)
bool fileControl::loadFile(char* fileName) {
	if ((xls.Load(fileName)) == 0) {
		cout << "\n	데이터베이스 불러오기 실패\n" << endl;
		return 0;
	}
	else return true;
}

void fileControl::backupFile() {
	try {
		xls.SaveAs("dataBase_backup.xls");
	}
	catch (DWORD dwError) { exit(0); }
}

// 특정 계좌 번호가 들어있는 행을 찾는 메서드
int fileControl::searchAcNum(char* acNo) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	size_t maxRows = sheet->GetTotalRows();
	BasicExcelCell* cell;

	int i;
	const char* temp;

	try {
		for (i = _FIRST_COLUM; i < maxRows; i++) {
			cell = sheet->Cell(i, _ACCOUNT_NUMBER);
			temp = cell->GetString();
			if (temp == NULL) continue;
			if (strcmp(acNo, temp) == _IS_SAME) break;
		}
		if (i == maxRows) throw i;
	}
	catch (int exception) {
		cout << "	목록에 해당하는 회원이 없습니다\n" << endl;
		return 0;
	}
	return i;
}

// 모든 클라이언트를 출력하는 메서드
bool fileControl::selectAllClient() {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	size_t maxRows = sheet->GetTotalRows();
	BasicExcelCell* cell;


	int i;
	try {
		for (i = _FIRST_COLUM; i < maxRows; i++) {
			cell = sheet->Cell(i, _ACCOUNT_NUMBER);
			if (cell->GetString() == NULL) continue;
			
			clnt.setAccountNum((char*)cell->GetString());
			cell = sheet->Cell(i, _USERNAME);
			clnt.setUserName((wchar_t*)cell->GetWString());
			cell = sheet->Cell(i, _BALANCE);
			clnt.setBalance(cell->GetInteger());

			cout << "		" << clnt.getAccountNum();
			wcout << L"	" << clnt.getUserName();
			cout << "	" << clnt.getBalance() << " 원" << endl;
			puts("");
		}
		if (i != maxRows) throw i;
		return true;
	}
	catch (int i) {
		return false;
	}
}

// 고객을 검색하는 클래스
bool fileControl::selectClient(char* acNo) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	size_t maxRows = sheet->GetTotalRows();
	BasicExcelCell* cell;

	try {
		int i = searchAcNum(acNo);

		if (i == _NO_CARDINALITIES) throw i;
		cell = sheet->Cell(i, _ACCOUNT_NUMBER);
		clnt.setAccountNum((char*)cell->GetString());
		cell = sheet->Cell(i, _USERNAME);
		clnt.setUserName((wchar_t*)cell->GetWString());
		cell = sheet->Cell(i, _PASSWORD);
		clnt.setPassword((char*)cell->GetString());
		cell = sheet->Cell(i, _BALANCE);
		clnt.setBalance(cell->GetInteger());

		return true;
	}
	catch (int i) {
		return false;
	}
}

// 회원가입 또는 데이터 처리 시 이미 있는 계좌인지 체크
bool fileControl::alreadyChk(char* acNo) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	size_t maxRows = sheet->GetTotalRows();
	BasicExcelCell* cell;

	int i;
	const char* tmp;
	
	for (i = _FIRST_COLUM; i < maxRows; i++) {
		cell = sheet->Cell(i, _ACCOUNT_NUMBER);
		tmp = cell->GetString();
		if (tmp == NULL) continue;
		if (strcmp(acNo, tmp) == _IS_SAME) return true;
	}
	return false;
}

// 고객 등록
bool fileControl::insertClient(char* acNo, wchar_t* uName, char* pwd) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	size_t maxRows = sheet->GetTotalRows();
	BasicExcelCell* cell;

	int i;
	const char* temp;

	if (alreadyChk(acNo)) {
		cout << "\n	이미 있는 계좌번호입니다." << endl;
		return false;
	}
	for (i = _FIRST_COLUM; i < maxRows; i++) {
		cell = sheet->Cell(i, _ACCOUNT_NUMBER);
		temp = cell->GetString();
		if (temp == NULL) break;
	}
	if (i == maxRows) {
		cell = sheet->Cell(maxRows, _ACCOUNT_NUMBER);
		cell->Set(acNo);
		cell = sheet->Cell(maxRows, _USERNAME);
		cell->SetWString(uName);
		cell = sheet->Cell(maxRows, _PASSWORD);
		cell->Set(pwd);
		cell = sheet->Cell(maxRows, _BALANCE);
		cell->Set(0);
		xls.Save();
		return true;
	}
	else {
		cell = sheet->Cell(i, _ACCOUNT_NUMBER);
		cell->Set(acNo);
		cell = sheet->Cell(i, _USERNAME);
		cell->SetWString(uName);
		cell = sheet->Cell(i, _PASSWORD);
		cell->Set(pwd);
		cell = sheet->Cell(i, _BALANCE);
		cell->Set(0);
		xls.Save();
		return true;
	}
}

// 고객 삭제
bool fileControl::deleteClient(char* acNo) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	size_t maxRows = sheet->GetTotalRows();
	size_t maxCols = sheet->GetTotalCols();
	BasicExcelCell* cell;
	int i = searchAcNum(acNo);
	if (i == _NO_CARDINALITIES) return false;
	for (int j = _FIRST_ATTRIBUTE; j < maxCols; j++) {
		cell = sheet->Cell(i, j);
		sheet->EraseCell(i, j);
	}
	xls.Save();
	return true;
}

// 고객 정보 갱신( pwd위주로 구현)
bool fileControl::updateClient(char* acNo, char* pwd) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	BasicExcelCell* cell;
	int i = searchAcNum(acNo);
	try {
		if (i == _NO_CARDINALITIES) throw i;
		cell = sheet->Cell(i, _PASSWORD);
		cell->Set(pwd);
		xls.Save();
		return true;
	}
	catch (int i) {
		return false;
	}
}

// 고객 정보 갱신 (balance 내용 업데이트 - 오버로딩)
void fileControl::updateClient(char* acNo, int bal) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	size_t maxRows = sheet->GetTotalRows();
	size_t maxCols = sheet->GetTotalCols();
	BasicExcelCell* cell;
	int i = searchAcNum(acNo);
	cell = sheet->Cell(i, _BALANCE);
	cell->Set(bal);
	xls.Save();
}

// clientATM 로그인 기능
int fileControl::loginCheck(char* acNo, char* pwd) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	size_t maxRows = sheet->GetTotalRows();
	BasicExcelCell* cell;

	int i = searchAcNum(acNo);
	if (i == _NO_CARDINALITIES) return _NO_USER_IN_DB;
	cell = sheet->Cell(i, _PASSWORD);
	const char* temp = cell->GetString();	

	if (strcmp(pwd, temp) == _IS_SAME) return _FINE_CORRECT_USER;
	else return _DATA_ACCESS_ERROR;
}

// TradeList (거래 내역) 삽입 - balance update시 처리
void fileControl::insertTradeList(char* acNo, wchar_t* uName, int bal, int balance, char* type) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_TWO);
	size_t maxRows = sheet->GetTotalRows();
	size_t maxCols = sheet->GetTotalCols();
	BasicExcelCell* cell;

	string date = currentDateTime();
	const char* _cdate = date.c_str();
	wchar_t* ownName;
	date.c_str();
	
	cell = sheet->Cell(maxRows, _ACCOUNT_NUMBER);
	cell->Set(acNo);

	ownName = searchUserName(acNo);
	cell = sheet->Cell(maxRows, _OWNER_NAME);
	cell->SetWString(ownName);

	cell = sheet->Cell(maxRows, _USERNAME_);
	cell->SetWString(uName);

	cell = sheet->Cell(maxRows, _TYPE);
	cell->Set(type);

	cell = sheet->Cell(maxRows, _TRADE_MONEY);
	cell->Set(bal);
	cell = sheet->Cell(maxRows, _BALANCE_);
	cell->Set(balance);
	
	cell = sheet->Cell(maxRows, _TRADE_DATE);
	cell->SetString(_cdate);
}

// 트랜잭션시 sheet 1의 Balance 정보 갱신
bool fileControl::updateBalance(char* acNo, wchar_t* uName, int bal, char* type) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	BasicExcelCell* cell;

	int i = searchAcNum(acNo);
	cell = sheet->Cell(i, _BALANCE);
	int balance = cell->GetInteger();

	// 연산자 오버로딩을 위한 객체 생성
	BALANCE bOrigin(balance);
	BALANCE bInput(bal);

	if (strcmp(type, "-") == _IS_SAME) {
		BALANCE bSub = bOrigin - bInput;	// 연산자 오버로딩
		if ( bSub.getBalance() < 0) {
			cout << "\n	잔액이 부족합니다.\n" << endl;
			return false;
		}
		else {
			balance = bSub.getBalance();
			cell->Set(balance);
			clnt.setBalance(cell->GetInteger());
			insertTradeList(acNo, uName, bal, balance, type);
			xls.Save();
			return true;
		}
	}
	else if (strcmp(type, "+") == _IS_SAME) {
		BALANCE bSUM = bOrigin + bInput;
		balance = bSUM.getBalance();
		cell->Set(balance);
		clnt.setBalance(cell->GetInteger());
		insertTradeList(acNo, uName, bal, balance, type);
		xls.Save();
		return true;
	}
	else return false;
}

// 특정 거래 내역 조회
bool fileControl::selectTradeList(char* acNo) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_TWO);
	size_t maxRows = sheet->GetTotalRows();
	BasicExcelCell* cell;
	wchar_t* temp;
	
	fret_b = false;
	for (int i = 1; i < maxRows; i++) {
		cell = sheet->Cell(i, _ACCOUNT_NUMBER);
		if (strcmp(acNo, cell->GetString()) == _IS_SAME) {
			fret_b = true;
			cell = sheet->Cell(i, _ACCOUNT_NUMBER);
			clnt.setAccountNum((char*)cell->GetString());
			cell = sheet->Cell(i, _TRADE_DATE);
			clnt.setTradeDate((char*)cell->GetString());
			cell = sheet->Cell(i, _USERNAME_);
			clnt.setUserName((wchar_t*)cell->GetWString());
			temp = clnt.getUserName();
			cell = sheet->Cell(i, _TRADE_MONEY);
			clnt.setTradeMoney(cell->GetInteger());
			cell = sheet->Cell(i, _BALANCE_);
			clnt.setBalance(cell->GetInteger());
			cell = sheet->Cell(i, _TYPE);
			clnt.setType((char*)cell->GetString());

			// 디자인을 위해 글자수가 줄어들면 공백 추가
			cout << "	" << clnt.getAccountNum();
			cout << "	" << clnt.getTradeDate();
			if (wcslen(temp) <= 3) {
				wcscat(temp, L"	");
				wcout << L"	" << temp;
			}
			else {
				wcout << L"	" << temp;
			}
			cout << "	" << clnt.getType() << clnt.getTradeMoney();
			cout << "	" << clnt.getBalance() << endl;
		}
		else continue;
	}
	return fret_b;
}

// AccountNumber에서 해당 계좌에 맞는 고객 이름 반환
wchar_t* fileControl::searchUserName(char* acNo) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	BasicExcelCell* cell;

	int i = searchAcNum(acNo);

	if (i == _NO_USER_IN_DB) return L"이름 없음";
	cell = sheet->Cell(i, 2);
	return (wchar_t*)cell->GetWString();
}
