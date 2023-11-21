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
	bool ChangeDateToCString(CString& _output, const CDateTimeCtrl& _input);		// ��¥�� CString Ÿ������ ��ȯ
	bool ChangeTimeToCString(CString& _output, const CDateTimeCtrl& _input);		// �ð��� CString Ÿ������ ��ȯ
	bool GetYoilToCString(CString& _output, const CDateTimeCtrl& _input);			// ������ CString Ÿ������ ��ȯ
};

