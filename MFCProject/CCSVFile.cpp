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
	// CSV ���� ����
	FILE* fp = nullptr;
	fopen_s(&fp, "./DataFile.csv", "w");

	// �迭�� ����� ���� ���Ͽ� write
	for (int i = 0; i < DataCount; i++)
	{
		// ---------- 13���� �߰� �ڵ� ---------- //
		fprintf(fp, "%s,%s,%s,%s,%s,%s\n", data[i].m_strDate, data[i].m_strYoil, data[i].m_strData, data[i].m_strCategory, data[i].m_strStartTime, data[i].m_strEndTime);
		// ---------- 13���� �߰� �ڵ� ---------- //
	}

	// CSV ���� �ݱ�
	fclose(fp);
	fp = nullptr;

	return true;
}

bool CCSVFile::BringInData()
{
	// CSV ���� ����
	FILE* fp = nullptr;
	fopen_s(&fp, "./DataFile.csv", "r");

	if (fp)
	{
		char szContent[2048];
		memset(szContent, NULL, sizeof(szContent));

		// �� line�� data �б�
		while (fgets(szContent, sizeof(szContent), fp))
		{
			CString strContent;
			strContent.Format("%s", szContent);

			// buffer �ʱ�ȭ
			memset(szContent, NULL, sizeof(szContent));

			// ������ �� #�� ������ �ǳʶٱ�
			if (strContent.Find('#') >= 0)
				continue;

			// ���� ���� ���� -> \r, \n
			strContent.Remove('\r');
			strContent.Remove('\n');

			// �����ڵ�� �����ؼ� ����
			strContent = _T(strContent);

			CString InputString;
			int CategoryNum = 0;

			// data �о����
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
					AfxMessageBox(_T("������ ����"));
					break;
				}
			}

			DataCount++;
		}

		// ���� �ݱ�
		fclose(fp);
		fp = nullptr;
	}

	return true;
}

bool CCSVFile::DeleteData(int _index)
{
	// ������ ����� ������ ���� ������ �������� ����
	if (_index < 0 || _index >= DataCount)
		return false;

	// ������ �����͸� ���� �����ͷ� ������
	for (int i = _index; i < DataCount - 1; i++)
	{
		data[i].m_strDate = data[i+1].m_strDate;
		data[i].m_strYoil = data[i+1].m_strYoil;
		data[i].m_strData = data[i+1].m_strData;
		data[i].m_strCategory = data[i+1].m_strCategory;
		data[i].m_strStartTime = data[i+1].m_strStartTime;
		data[i].m_strEndTime = data[i+1].m_strEndTime;
	}

	// �� �������� ����� ������ �����
	data[DataCount].m_strDate = _T("");
	data[DataCount].m_strYoil = _T("");
	data[DataCount].m_strData = _T("");
	data[DataCount].m_strCategory = _T("");
	data[DataCount].m_strStartTime = _T("");
	data[DataCount].m_strEndTime = _T("");

	// ��ü data�� ������ �� �� �����ϰ�, CSV ���Ͽ� ����
	DataCount--;
	StoreData();

	return true;
}

bool CCSVFile::AddData(const FILEDATA& _data)
{
	// ������ ����� ������ �߰� ������ �������� ����
	if(DataCount >= MAX_DATA_NUM)
		return false;

	// ������ ���Ŀ� ���� ������ ����
	data[DataCount].m_strDate = _data.m_strDate;
	data[DataCount].m_strYoil = _data.m_strYoil;
	data[DataCount].m_strData = _data.m_strData;
	data[DataCount].m_strCategory = _data.m_strCategory;
	data[DataCount].m_strStartTime = _data.m_strStartTime;
	data[DataCount].m_strEndTime = _data.m_strEndTime;

	// ��ü data ���� �� �� ������Ű��, CSV ���Ͽ� ����
	DataCount++;
	StoreData();

	return true;
}

bool CCSVFile::ModifyData(int _index, const FILEDATA& _data)
{
	// ������ ����� ������ ���� ������ �������� ����
	if (_index < 0 || _index >= DataCount)
		return false;

	// ������ ���Ŀ� ���� ������ ����
	data[_index].m_strDate = _data.m_strDate;
	data[_index].m_strYoil = _data.m_strYoil;
	data[_index].m_strData = _data.m_strData;
	data[_index].m_strCategory = _data.m_strCategory;
	data[_index].m_strStartTime = _data.m_strStartTime;
	data[_index].m_strEndTime = _data.m_strEndTime;

	// CSV ���Ͽ� ����
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

	// �� control�鿡 ����� ������ CString Ÿ������ ��ȯ
	CChangeDataFormat::ChangeDateToCString(strSelectDate, _SelDate);
	CChangeDataFormat::ChangeTimeToCString(strSelectStartTime, _StartTime);
	CChangeDataFormat::ChangeTimeToCString(strSelectEndTime, _EndTime);
	CChangeDataFormat::GetYoilToCString(strSelectYoil, _SelDate);

	// CString Ÿ�Կ� ��ȯ�� ������, CSV ���� ��Ŀ� ���� output ���ۿ� ����
	_output.m_strDate = strSelectDate;
	_output.m_strYoil = strSelectYoil;
	_output.m_strData = strInputData;
	_output.m_strCategory = strInputCategory;
	_output.m_strStartTime = strSelectStartTime;
	_output.m_strEndTime = strSelectEndTime;

	return true;
}

// ---------- 13���� �߰� �ڵ� ---------- //
bool CCSVFile::GetCategoryInWeek(CString& _output, const COleDateTime& _standard, int flag)
{
	// flag�� ��ȿ���� �ʴٸ� �Լ� ����
	if (flag > 6 || flag < 0)
		return false;

	COleDateTime tmp = _standard;

	// �������� �Ǵ� ���ϰ� ���� ����(�Ͽ���)�� ���̸� ���ϰ� �����Ѵ�.
	COleDateTimeSpan diff1(tmp.GetDayOfWeek() - 1, 0, 0, 0);

	// �������� �Ǵ� ��¥�� '�������� �Ǵ� ���ϰ� ���� ����(�Ͽ���)�� ����'�� ����.
	tmp -= diff1;

	// ���� ������� flag ���� ���Ѵ�.
	COleDateTimeSpan diff2(flag, 0, 0, 0);
	tmp += diff2;

	// ���� ����� ���� ��¥ data�� CString �������� ��ȯ�Ѵ�.
	CString strtmp = _T("");
	CChangeDataFormat::ChangeDateToCString(strtmp, tmp);

	// ����� data�� ������ ��¥�� ���õ� CSV data �� category �����͸� �̾� ���δ�.
	FILEDATA data;
	for (int i = 0; i < DataCount; i++)
	{
		GetData(i, data);
		if (data.m_strDate == strtmp)
			_output += (data.m_strCategory + "\r\n");
	}

	return true;
}
// ---------- 13���� �߰� �ڵ� ---------- //