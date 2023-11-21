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
	_date += (strtmp + '-');

	ntmp = sel_date.GetMonth();
	strtmp.Format(_T("%d"), ntmp);
	_date += (strtmp + '-');

	ntmp = sel_date.GetDay();
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
	_time += (strtmp + ':');

	ntmp = sel_time.GetMinute();
	strtmp.Format(_T("%d"), ntmp);
	_time += (strtmp + ':');

	ntmp = sel_time.GetSecond();
	strtmp.Format(_T("%d"), ntmp);
	_time += strtmp;

	// 만들어진 CString 데이터를 output 버퍼에 저장
	_output = _time;

	return true;
}
