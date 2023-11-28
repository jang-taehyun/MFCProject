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
	static CCSVFile* GetCSVFileInterface()									// CSVFile 객체 반환
	{
		static CCSVFile inst;
		return &inst;
	}
	int GetDataCount() { return DataCount; }								// 전체 data의 개수 반환
	bool GetData(int _index, FILEDATA& _buffer)								// 특정 data를 output buffer에 저장하는 방식으로 data를 가져오는 함수
	{
		// 범위에 벗어나면 데이터 가져오기 연산을 수행하지 않음
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
	bool StoreData();														// FILEDATA data[]에 저장된 값들을 CSV 파일에 저장하는 함수
	bool BringInData();														// CSV 파일에 저장된 값들을 FILEDATA data[]에 불러오는 함수

	bool DeleteData(int _index);											// 특정 data를 삭제
	bool AddData(const FILEDATA& _data);									// data 추가
	bool ModifyData(int _index, const FILEDATA& _data);						// 특정 data 수정

	// CSV 파일 양식으로 만들어주는 함수
	bool MakeDataFormat(FILEDATA& _output, const CDateTimeCtrl& _SelDate, const CDateTimeCtrl& _StartTime, const CDateTimeCtrl& _EndTime);

	// ---------- 13주차 추가 코드 ---------- //
	// week에서 1개 day의 Category data를 얻오는 함수
	bool GetCategoryInWeek(CString& _output, const COleDateTime& _standard, int flag);
	// ---------- 13주차 추가 코드 ---------- //
};

