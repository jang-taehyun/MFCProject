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
	static CCSVFile* GetCSVFileInterface()
	{
		static CCSVFile inst;
		return &inst;
	}
	int GetDataCount() { return DataCount; }
	void GetData(int _index, FILEDATA& _buffer)
	{
		_buffer.m_strDate = data[_index].m_strDate;
		_buffer.m_strYoil = data[_index].m_strYoil;
		_buffer.m_strData = data[_index].m_strData;
		_buffer.m_strCategory = data[_index].m_strCategory;
		_buffer.m_strStartTime = data[_index].m_strStartTime;
		_buffer.m_strEndTime = data[_index].m_strEndTime;
	}

	// interface : store data //
	bool StoreData();
	bool BringInData();
};

