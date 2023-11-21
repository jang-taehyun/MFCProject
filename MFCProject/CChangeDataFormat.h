#pragma once
class CChangeDataFormat
{
private:
	CChangeDataFormat();
	~CChangeDataFormat();

public:
	static CChangeDataFormat* GetInst()
	{
		static CChangeDataFormat inst;

		return &inst;
	}

public:
	bool ChangeDateToCString(CString& _output, const CDateTimeCtrl& _input);		// 날짜를 CString 타입으로 변환
	bool ChangeTimeToCString(CString& _output, const CDateTimeCtrl& _input);		// 시간을 CString 타입으로 변환
	bool GetYoilToCString(CString& _output, const CDateTimeCtrl& _input);			// 요일을 CString 타입으로 변환
};

