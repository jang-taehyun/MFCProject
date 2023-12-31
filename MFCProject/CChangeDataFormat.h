#pragma once

namespace CChangeDataFormat
{
	bool ChangeDateToCString(CString& _output, const CDateTimeCtrl& _input);		// 날짜를 CString 타입으로 변환
	bool ChangeDateToCString(CString& _output, const COleDateTime& _input);			// 날짜를 CString 타입으로 변환
	bool ChangeTimeToCString(CString& _output, const CDateTimeCtrl& _input);		// 시간을 CString 타입으로 변환
	bool GetYoilToCString(CString& _output, const CDateTimeCtrl& _input);			// 요일을 CString 타입으로 변환

	bool GetTimeToInt(int& _output, const CString& _input, int _flag);

	bool ChangeDateToCOleDateTime(COleDateTime& _output, const CDateTimeCtrl& _input);
}
