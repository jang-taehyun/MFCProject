#include "pch.h"
#include "targetver.h"
#include "CCSVFile.h"

CCSVFile::CCSVFile() : DataCount(0)
{
	
}

CCSVFile::~CCSVFile()
{
}

bool CCSVFile::StoreData()
{
	FILE* fp = nullptr;
	fopen_s(&fp, "./DataFile.csv", "w");

	CString tmp_date = _T("2019-10-11");
	CString tmp_Yoil = _T("Monday");
	CString tmp_data = _T("tmp2");
	CString tmp_Category = _T("tmp3");
	CString tmp_ST = _T("09:30");
	CString tmp_ET = _T("21:10");

	data[DataCount].m_strDate = tmp_date;
	data[DataCount].m_strYoil = tmp_Yoil;
	data[DataCount].m_strData = tmp_data;
	data[DataCount].m_strCategory = tmp_Category;
	data[DataCount].m_strStartTime = tmp_ST;
	data[DataCount].m_strEndTime = tmp_ET;

	DataCount++;

	for (int i = 0; i < DataCount; i++)
	{
		fprintf(fp, "%s, %s, %s, %s, %s, %s\n", data[i].m_strDate, data[i].m_strYoil, data[i].m_strData, data[i].m_strCategory, data[i].m_strStartTime, data[i].m_strEndTime);
	}

	// ���� �ݱ�
	fclose(fp);
	fp = nullptr;

	return true;
}

bool CCSVFile::BringInData()
{
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
