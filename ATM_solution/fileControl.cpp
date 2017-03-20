#include "stdafx.h"
#include "fileControl.h"

BasicExcel xls;
client clnt;
client adm;

const string currentDateTime() {
	time_t     now = time(0); //���� �ð��� time_t Ÿ������ ����
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct); // YYYY-MM-DD.HH:mm:ss ������ ��Ʈ��

	return buf;
}

// ���� ���� �ε� �Լ�(vector�� �����ϰ� �ش� ���Ϳ� �����͸� ��ƿ�)
bool fileControl::loadFile(char* fileName) {
	if ((xls.Load(fileName)) == 0) {
		cout << "\n	�����ͺ��̽� �ҷ����� ����\n" << endl;
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

// Ư�� ���� ��ȣ�� ����ִ� ���� ã�� �޼���
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
		cout << "	��Ͽ� �ش��ϴ� ȸ���� �����ϴ�\n" << endl;
		return 0;
	}
	return i;
}

// ��� Ŭ���̾�Ʈ�� ����ϴ� �޼���
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
			cout << "	" << clnt.getBalance() << " ��" << endl;
			puts("");
		}
		if (i != maxRows) throw i;
		return true;
	}
	catch (int i) {
		return false;
	}
}

// ���� �˻��ϴ� Ŭ����
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

// ȸ������ �Ǵ� ������ ó�� �� �̹� �ִ� �������� üũ
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

// �� ���
bool fileControl::insertClient(char* acNo, wchar_t* uName, char* pwd) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	size_t maxRows = sheet->GetTotalRows();
	BasicExcelCell* cell;

	int i;
	const char* temp;

	if (alreadyChk(acNo)) {
		cout << "\n	�̹� �ִ� ���¹�ȣ�Դϴ�." << endl;
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

// �� ����
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

// �� ���� ����( pwd���ַ� ����)
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

// �� ���� ���� (balance ���� ������Ʈ - �����ε�)
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

// clientATM �α��� ���
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

// TradeList (�ŷ� ����) ���� - balance update�� ó��
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

// Ʈ����ǽ� sheet 1�� Balance ���� ����
bool fileControl::updateBalance(char* acNo, wchar_t* uName, int bal, char* type) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	BasicExcelCell* cell;

	int i = searchAcNum(acNo);
	cell = sheet->Cell(i, _BALANCE);
	int balance = cell->GetInteger();

	// ������ �����ε��� ���� ��ü ����
	BALANCE bOrigin(balance);
	BALANCE bInput(bal);

	if (strcmp(type, "-") == _IS_SAME) {
		BALANCE bSub = bOrigin - bInput;	// ������ �����ε�
		if ( bSub.getBalance() < 0) {
			cout << "\n	�ܾ��� �����մϴ�.\n" << endl;
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

// Ư�� �ŷ� ���� ��ȸ
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

			// �������� ���� ���ڼ��� �پ��� ���� �߰�
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

// AccountNumber���� �ش� ���¿� �´� �� �̸� ��ȯ
wchar_t* fileControl::searchUserName(char* acNo) {
	BasicExcelWorksheet* sheet = xls.GetWorksheet(_WORKSHEET_ONE);
	BasicExcelCell* cell;

	int i = searchAcNum(acNo);

	if (i == _NO_USER_IN_DB) return L"�̸� ����";
	cell = sheet->Cell(i, 2);
	return (wchar_t*)cell->GetWString();
}
