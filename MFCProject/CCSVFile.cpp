#include "pch.h"
#include "targetver.h"
#include "CCSVFile.h"
#include "CChangeDataFormat.h"

CCSVFile::CCSVFile() : DataCount(0)
{
	BringInData();
}

CCSVFile::~CCSVFile()
{
}

bool CCSVFile::StoreData()
{
	// CSV 파일 열기
	FILE* fp = nullptr;
	fopen_s(&fp, "./DataFile.csv", "w");

	// 배열에 저장된 값을 파일에 write
	for (int i = 0; i < DataCount; i++)
	{
		// ---------- 13주차 추가 코드 ---------- //
		fprintf(fp, "%s,%s,%s,%s,%s,%s\n", data[i].m_strDate, data[i].m_strYoil, data[i].m_strData, data[i].m_strCategory, data[i].m_strStartTime, data[i].m_strEndTime);
		// ---------- 13주차 추가 코드 ---------- //
	}

	// CSV 파일 닫기
	fclose(fp);
	fp = nullptr;

	return true;
}

bool CCSVFile::BringInData()
{
	// CSV 파일 열기
	FILE* fp = nullptr;
	fopen_s(&fp, "./DataFile.csv", "r");

	if (fp)
	{
		char szContent[2048];
		memset(szContent, NULL, sizeof(szContent));

		// 한 line씩 data 읽기
		while (fgets(szContent, sizeof(szContent), fp))
		{
			CString strContent;
			strContent.Format("%s", szContent);

			// buffer 초기화
			memset(szContent, NULL, sizeof(szContent));

			// 데이터 중 #이 있으면 건너뛰기
			if (strContent.Find('#') >= 0)
				continue;

			// 개행 문자 제거 -> \r, \n
			strContent.Remove('\r');
			strContent.Remove('\n');

			// 유니코드로 변경해서 저장
			strContent = _T(strContent);

			CString InputString;
			int CategoryNum = 0;

			// data 읽어오기
			while (AfxExtractSubString(InputString, strContent, CategoryNum++, ','))
			{
				switch (CategoryNum)
				{
				case 1:
				{
					data[DataCount].m_strDate = _T(InputString);
				}
				break;
				case 2:
				{
					data[DataCount].m_strYoil = _T(InputString);
				}
				break;
				case 3:
				{
					data[DataCount].m_strData = _T(InputString);
				}
				break;
				case 4:
				{
					data[DataCount].m_strCategory = _T(InputString);
				}
				break;
				case 5:
				{
					data[DataCount].m_strStartTime = _T(InputString);
				}
				break;
				case 6:
				{
					data[DataCount].m_strEndTime = _T(InputString);
				}
				break;
				default:
					AfxMessageBox(_T("데이터 없음"));
					break;
				}
			}

			DataCount++;
		}

		// 파일 닫기
		fclose(fp);
		fp = nullptr;
	}

	return true;
}

bool CCSVFile::DeleteData(int _index)
{
	// 범위에 벗어나면 데이터 삭제 연산을 수행하지 않음
	if (_index < 0 || _index >= DataCount)
		return false;

	// 삭제할 데이터를 다음 데이터로 덮어씌우기
	for (int i = _index; i < DataCount - 1; i++)
	{
		data[i].m_strDate = data[i+1].m_strDate;
		data[i].m_strYoil = data[i+1].m_strYoil;
		data[i].m_strData = data[i+1].m_strData;
		data[i].m_strCategory = data[i+1].m_strCategory;
		data[i].m_strStartTime = data[i+1].m_strStartTime;
		data[i].m_strEndTime = data[i+1].m_strEndTime;
	}

	// 맨 마지막에 저장된 데이터 지우기
	data[DataCount].m_strDate = _T("");
	data[DataCount].m_strYoil = _T("");
	data[DataCount].m_strData = _T("");
	data[DataCount].m_strCategory = _T("");
	data[DataCount].m_strStartTime = _T("");
	data[DataCount].m_strEndTime = _T("");

	// 전체 data의 개수를 한 개 감소하고, CSV 파일에 저장
	DataCount--;
	StoreData();

	return true;
}

bool CCSVFile::AddData(const FILEDATA& _data)
{
	// 범위에 벗어나면 데이터 추가 연산을 수행하지 않음
	if(DataCount >= MAX_DATA_NUM)
		return false;

	// 데이터 형식에 맞춰 값들을 저장
	data[DataCount].m_strDate = _data.m_strDate;
	data[DataCount].m_strYoil = _data.m_strYoil;
	data[DataCount].m_strData = _data.m_strData;
	data[DataCount].m_strCategory = _data.m_strCategory;
	data[DataCount].m_strStartTime = _data.m_strStartTime;
	data[DataCount].m_strEndTime = _data.m_strEndTime;

	// 전체 data 수를 한 개 증가시키고, CSV 파일에 저장
	DataCount++;
	StoreData();

	return true;
}

bool CCSVFile::ModifyData(int _index, const FILEDATA& _data)
{
	// 범위에 벗어나면 데이터 수정 연산을 수행하지 않음
	if (_index < 0 || _index >= DataCount)
		return false;

	// 데이터 형식에 맞춰 값들을 수정
	data[_index].m_strDate = _data.m_strDate;
	data[_index].m_strYoil = _data.m_strYoil;
	data[_index].m_strData = _data.m_strData;
	data[_index].m_strCategory = _data.m_strCategory;
	data[_index].m_strStartTime = _data.m_strStartTime;
	data[_index].m_strEndTime = _data.m_strEndTime;

	// CSV 파일에 저장
	StoreData();

	return true;
}

bool CCSVFile::MakeDataFormat(FILEDATA& _output, const CDateTimeCtrl& _SelDate, const CDateTimeCtrl& _StartTime, const CDateTimeCtrl& _EndTime)
{
	CString strSelectDate = _T("");
	CString strSelectStartTime = _T("");
	CString strSelectEndTime = _T("");
	CString strSelectYoil = _T("");
	CString strInputCategory = _T("");
	CString strInputData = _T("");

	// 각 control들에 저장된 값들을 CString 타입으로 변환
	CChangeDataFormat::ChangeDateToCString(strSelectDate, _SelDate);
	CChangeDataFormat::ChangeTimeToCString(strSelectStartTime, _StartTime);
	CChangeDataFormat::ChangeTimeToCString(strSelectEndTime, _EndTime);
	CChangeDataFormat::GetYoilToCString(strSelectYoil, _SelDate);

	// CString 타입에 변환된 값들을, CSV 파일 양식에 맞춰 output 버퍼에 저장
	_output.m_strDate = strSelectDate;
	_output.m_strYoil = strSelectYoil;
	_output.m_strData = strInputData;
	_output.m_strCategory = strInputCategory;
	_output.m_strStartTime = strSelectStartTime;
	_output.m_strEndTime = strSelectEndTime;

	return true;
}

// ---------- 13주차 추가 코드 ---------- //
bool CCSVFile::GetCategoryInWeek(CString& _output, const COleDateTime& _standard, int flag)
{
	// flag가 유효하지 않다면 함수 종료
	if (flag > 6 || flag < 0)
		return false;

	COleDateTime tmp = _standard;

	// 기준점이 되는 요일과 시작 요일(일요일)의 차이를 구하고 저장한다.
	COleDateTimeSpan diff1(tmp.GetDayOfWeek() - 1, 0, 0, 0);

	// 기준점이 되는 날짜와 '기준점이 되는 요일과 시작 요일(일요일)의 차이'를 뺀다.
	tmp -= diff1;

	// 연산 결과에서 flag 값을 더한다.
	COleDateTimeSpan diff2(flag, 0, 0, 0);
	tmp += diff2;

	// 연산 결과로 나온 날짜 data를 CString 형식으로 변환한다.
	CString strtmp = _T("");
	CChangeDataFormat::ChangeDateToCString(strtmp, tmp);

	// 저장된 data중 설정된 날짜에 관련된 CSV data 중 category 데이터를 이어 붙인다.
	FILEDATA data;
	for (int i = 0; i < DataCount; i++)
	{
		GetData(i, data);
		if (data.m_strDate == strtmp)
			_output += (data.m_strCategory + "\r\n");
	}

	return true;
}
// ---------- 13주차 추가 코드 ---------- //