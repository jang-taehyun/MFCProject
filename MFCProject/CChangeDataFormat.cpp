#include "pch.h"
#include "CChangeDataFormat.h"

//CChangeDataFormat::CChangeDataFormat()
//{
//}
//
//CChangeDataFormat::~CChangeDataFormat()
//{
//}

bool CChangeDataFormat::GetYoilToCString(CString& _output, const CDateTimeCtrl& _input)
{
	COleDateTime sel_date;
	CString _date = _T("");

	// input�� ����� ���� COleDateTime Ÿ������ ����
	_input.GetTime(sel_date);

	// ������ int ���� �޾ƿ�, ID�� ���� CString Ÿ������ ����
	int ntmp = sel_date.GetDayOfWeek();
	switch (ntmp)
	{
	case 1:
		_date = _T("�Ͽ���");
		break;
	case 2:
		_date = _T("������");
		break;
	case 3:
		_date = _T("ȭ����");
		break;
	case 4:
		_date = _T("������");
		break;
	case 5:
		_date = _T("�����");
		break;
	case 6:
		_date = _T("�ݿ���");
		break;
	case 7:
		_date = _T("�����");
		break;
	default:
		break;
	}

	// output ���ۿ� ����� CString �� ����
	_output = _date;

	return true;
}

bool CChangeDataFormat::GetTimeToInt(int& _output, const CString& _input, int _flag)
{
	// 0 : hour, year
	// 1 : minute, month
	// 2 : second, day
	if (0 > _flag || _flag > 2)
		return false;

	CString strtmp = _T("");
	int index = 0;
	int flag = 0;

	while (true)
	{
		if (flag != _flag)
		{
			if (_input[index] == _T('-') || _input[index] == _T(':'))
				flag++;
		}
		else
			break;

		index++;
	}

	while (true)
	{
		if (_input[index] == NULL || _input[index] == _T('-') || _input[index] == _T(':'))
			break;

		strtmp += _input[index];
		index++;
	}

	_output = _ttoi(strtmp);

	return true;
}

bool CChangeDataFormat::ChangeDateToCOleDateTime(COleDateTime& _output, const CDateTimeCtrl& _input)
{
	CTime sel_date;

	// input�� ����� ���� CTime Ÿ������ ����
	_input.GetTime(sel_date);

	int year, month, day;

	// ��, ��, �� ������� CTime Ÿ������ ����� ���� �ҷ��ͼ�,
	// CString Ÿ������ ��ȯ�� �Ŀ� ��� �̾� ���̱�
	year = sel_date.GetYear();
	month = sel_date.GetMonth();
	day = sel_date.GetDay();
	_output.SetDate(year, month, day);

	return true;
}



bool CChangeDataFormat::ChangeDateToCString(CString& _output, const CDateTimeCtrl& _input)
{
	CTime sel_date;
	CString _date = _T("");

	// input�� ����� ���� CTime Ÿ������ ����
	_input.GetTime(sel_date);

	CString strtmp;
	int ntmp;

	// ��, ��, �� ������� CTime Ÿ������ ����� ���� �ҷ��ͼ�,
	// CString Ÿ������ ��ȯ�� �Ŀ� ��� �̾� ���̱�
	ntmp = sel_date.GetYear();
	strtmp.Format(_T("%d"), ntmp);
	_date += (strtmp + _T('-'));

	ntmp = sel_date.GetMonth();
	strtmp.Format(_T("%d"), ntmp);
	_date += (strtmp + _T('-'));

	ntmp = sel_date.GetDay();
	strtmp.Format(_T("%d"), ntmp);
	_date += strtmp;

	// ������� CString �����͸� output ���ۿ� ����
	_output = _date;

	return true;
}

bool CChangeDataFormat::ChangeDateToCString(CString& _output, const COleDateTime& _input)
{
	CString _date = _T("");

	CString strtmp;
	int ntmp;

	// ��, ��, �� ������� CTime Ÿ������ ����� ���� �ҷ��ͼ�,
	// CString Ÿ������ ��ȯ�� �Ŀ� ��� �̾� ���̱�
	ntmp = _input.GetYear();
	strtmp.Format(_T("%d"), ntmp);
	_date += (strtmp + _T('-'));

	ntmp = _input.GetMonth();
	strtmp.Format(_T("%d"), ntmp);
	_date += (strtmp + _T('-'));

	ntmp = _input.GetDay();
	strtmp.Format(_T("%d"), ntmp);
	_date += strtmp;

	// ������� CString �����͸� output ���ۿ� ����
	_output = _date;

	return true;
}

bool CChangeDataFormat::ChangeTimeToCString(CString& _output, const CDateTimeCtrl& _input)
{
	COleDateTime sel_time;
	CString _time = _T("");

	// input�� ����� ���� COleDateTime Ÿ������ ����
	_input.GetTime(sel_time);

	CString strtmp;
	int ntmp;

	// ��, ��, �� ������� COleDateTime Ÿ������ ����� ���� �ҷ��ͼ�,
	// CString Ÿ������ ��ȯ�� �Ŀ� ��� �̾� ���̱�
	ntmp = sel_time.GetHour();
	strtmp.Format(_T("%d"), ntmp);
	_time += (strtmp + _T(':'));

	ntmp = sel_time.GetMinute();
	strtmp.Format(_T("%d"), ntmp);
	_time += (strtmp + _T(':'));

	ntmp = sel_time.GetSecond();
	strtmp.Format(_T("%d"), ntmp);
	_time += strtmp;

	// ������� CString �����͸� output ���ۿ� ����
	_output = _time;

	return true;
}
