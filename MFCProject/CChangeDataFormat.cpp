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

	// input에 저장된 값을 COleDateTime 타입으로 저장
	_input.GetTime(sel_date);

	// 요일의 int 값을 받아와, ID에 따라 CString 타입으로 저장
	int ntmp = sel_date.GetDayOfWeek();
	switch (ntmp)
	{
	case 1:
		_date = _T("일요일");
		break;
	case 2:
		_date = _T("월요일");
		break;
	case 3:
		_date = _T("화요일");
		break;
	case 4:
		_date = _T("수요일");
		break;
	case 5:
		_date = _T("목요일");
		break;
	case 6:
		_date = _T("금요일");
		break;
	case 7:
		_date = _T("토요일");
		break;
	default:
		break;
	}

	// output 버퍼에 저장된 CString 값 저장
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

	// input에 저장된 값을 CTime 타입으로 저장
	_input.GetTime(sel_date);

	int year, month, day;

	// 연, 월, 일 순서대로 CTime 타입으로 저장된 값을 불러와서,
	// CString 타입으로 변환한 후에 계속 이어 붙이기
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

	// input에 저장된 값을 CTime 타입으로 저장
	_input.GetTime(sel_date);

	CString strtmp;
	int ntmp;

	// 연, 월, 일 순서대로 CTime 타입으로 저장된 값을 불러와서,
	// CString 타입으로 변환한 후에 계속 이어 붙이기
	ntmp = sel_date.GetYear();
	strtmp.Format(_T("%d"), ntmp);
	_date += (strtmp + _T('-'));

	ntmp = sel_date.GetMonth();
	strtmp.Format(_T("%d"), ntmp);
	_date += (strtmp + _T('-'));

	ntmp = sel_date.GetDay();
	strtmp.Format(_T("%d"), ntmp);
	_date += strtmp;

	// 만들어진 CString 데이터를 output 버퍼에 저장
	_output = _date;

	return true;
}

bool CChangeDataFormat::ChangeDateToCString(CString& _output, const COleDateTime& _input)
{
	CString _date = _T("");

	CString strtmp;
	int ntmp;

	// 연, 월, 일 순서대로 CTime 타입으로 저장된 값을 불러와서,
	// CString 타입으로 변환한 후에 계속 이어 붙이기
	ntmp = _input.GetYear();
	strtmp.Format(_T("%d"), ntmp);
	_date += (strtmp + _T('-'));

	ntmp = _input.GetMonth();
	strtmp.Format(_T("%d"), ntmp);
	_date += (strtmp + _T('-'));

	ntmp = _input.GetDay();
	strtmp.Format(_T("%d"), ntmp);
	_date += strtmp;

	// 만들어진 CString 데이터를 output 버퍼에 저장
	_output = _date;

	return true;
}

bool CChangeDataFormat::ChangeTimeToCString(CString& _output, const CDateTimeCtrl& _input)
{
	COleDateTime sel_time;
	CString _time = _T("");

	// input에 저장된 값을 COleDateTime 타입으로 저장
	_input.GetTime(sel_time);

	CString strtmp;
	int ntmp;

	// 시, 분, 초 순서대로 COleDateTime 타입으로 저장된 값을 불러와서,
	// CString 타입으로 변환한 후에 계속 이어 붙이기
	ntmp = sel_time.GetHour();
	strtmp.Format(_T("%d"), ntmp);
	_time += (strtmp + _T(':'));

	ntmp = sel_time.GetMinute();
	strtmp.Format(_T("%d"), ntmp);
	_time += (strtmp + _T(':'));

	ntmp = sel_time.GetSecond();
	strtmp.Format(_T("%d"), ntmp);
	_time += strtmp;

	// 만들어진 CString 데이터를 output 버퍼에 저장
	_output = _time;

	return true;
}
