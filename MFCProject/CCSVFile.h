#pragma once

#define MAX_DATA_NUM 50
typedef struct struct_file_data
{
	CString m_strDate;
	CString m_strYoil;
	CString m_strData;
	CString m_strCategory;
	CString m_strStartTime;
	CString m_strEndTime;
} FILEDATA;

class CCSVFile
{

	// variable //
private:
	FILEDATA data[MAX_DATA_NUM];
	int DataCount;

	// constructor & destructor //
private:
	CCSVFile();
	~CCSVFile();

	// getter //
public:
	static CCSVFile* GetCSVFileInterface()									// CSVFile ��ü ��ȯ
	{
		static CCSVFile inst;
		return &inst;
	}
	int GetDataCount() { return DataCount; }								// ��ü data�� ���� ��ȯ
	bool GetData(int _index, FILEDATA& _buffer)								// Ư�� data�� output buffer�� �����ϴ� ������� data�� �������� �Լ�
	{
		// 23.11.19. �߰��� �ڵ� //
		// ������ ����� ������ �������� ������ �������� ����
		if (_index < 0 || _index >= DataCount)
			return false;
		// ................... //

		_buffer.m_strDate = data[_index].m_strDate;
		_buffer.m_strYoil = data[_index].m_strYoil;
		_buffer.m_strData = data[_index].m_strData;
		_buffer.m_strCategory = data[_index].m_strCategory;
		_buffer.m_strStartTime = data[_index].m_strStartTime;
		_buffer.m_strEndTime = data[_index].m_strEndTime;

		return true;
	}

	// interface //
	bool StoreData();														// FILEDATA data[]�� ����� ������ CSV ���Ͽ� �����ϴ� �Լ�
	bool BringInData();														// CSV ���Ͽ� ����� ������ FILEDATA data[]�� �ҷ����� �Լ�

	bool DeleteData(int _index);											// Ư�� data�� ����
	bool AddData(const FILEDATA& _data);									// data �߰�
	bool ModifyData(int _index, const FILEDATA& _data);						// Ư�� data ����

	// CSV ���� ������� ������ִ� �Լ�
	bool MakeDataFormat(FILEDATA& _output, const CDateTimeCtrl& _SelDate, const CDateTimeCtrl& _StartTime, const CDateTimeCtrl& _EndTime);
};

