#include "pch.h"
#include "CChangeDataFormat.h"

CChangeDataFormat::CChangeDataFormat()
{
}

CChangeDataFormat::~CChangeDataFormat()
{
}

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
	_date += (strtmp + '-');

	ntmp = sel_date.GetMonth();
	strtmp.Format(_T("%d"), ntmp);
	_date += (strtmp + '-');

	ntmp = sel_date.GetDay();
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
	_time += (strtmp + ':');

	ntmp = sel_time.GetMinute();
	strtmp.Format(_T("%d"), ntmp);
	_time += (strtmp + ':');

	ntmp = sel_time.GetSecond();
	strtmp.Format(_T("%d"), ntmp);
	_time += strtmp;

	// ������� CString �����͸� output ���ۿ� ����
	_output = _time;

	return true;
}
