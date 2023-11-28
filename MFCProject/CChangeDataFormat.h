#pragma once

// ---------- 13���� �߰� �ڵ� ---------- //
namespace CChangeDataFormat
{
	bool ChangeDateToCString(CString& _output, const CDateTimeCtrl& _input);		// ��¥�� CString Ÿ������ ��ȯ
	bool ChangeDateToCString(CString& _output, const COleDateTime& _input);			// ��¥�� CString Ÿ������ ��ȯ
	bool ChangeTimeToCString(CString& _output, const CDateTimeCtrl& _input);		// �ð��� CString Ÿ������ ��ȯ
	bool GetYoilToCString(CString& _output, const CDateTimeCtrl& _input);			// ������ CString Ÿ������ ��ȯ

	bool GetTimeToInt(int& _output, const CString& _input, int _flag);

	// ---------- 13���� �߰� �ڵ� ---------- //
	bool ChangeDateToCOleDateTime(COleDateTime& _output, const CDateTimeCtrl& _input);
	// ---------- 13���� �߰� �ڵ� ---------- //
}
// ---------- 13���� �߰� �ڵ� ---------- //