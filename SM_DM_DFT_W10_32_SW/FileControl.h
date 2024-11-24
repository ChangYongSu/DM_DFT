#pragma once
//#include "stdafx.h"

// CDlgModelSetup ��ȭ �����Դϴ�.

class CFileControl 
{
	

public:
	CFileControl();   // ǥ�� �������Դϴ�.
	virtual ~CFileControl();

// ��ȭ ���� �������Դϴ�.




public:	

	int  OpenModel(CString lFilename);
	
	int SaveModel(CString lFilename);
	int RemoveModel(CString lFilename);
	int SaveINIModel();
	int Read_IniModel();

	//int Read_ConfigData();
	//int SaveConfigData();

	int Read_ConfigSeqData();
	int SaveConfigSeqData();
	int Save_ConfigPassword();
	int Read_ConfigPassword();

	int SaveLog();
	int SaveGmesLOG(CString LogStr, int lRev = 0);
	int SaveProcessLOG(CString LogStr,  int lNew = 0);//int CFileControl::SaveProcessLOG(CString LogStr, int lRev)
	
	
	int SaveCountData();
	int ReadCountData();

	int SaveCableCountData();
	int ReadCableCountData();

	int OpenModelSeq(CString lFilename);
	CString FindStepName(CString StringLine);
	CString FindStepWork(CString StringLine);

	unsigned char  ReadHex(CString lstrASCII);

		
	int SaveImageRangeData(CString lFileName, CRect rect);
	int ReadImageRangeData(CString lFileName, CRect *rectP);
	RgbColor  COLORREF_to_BMP3Byte(COLORREF lCoolorRef);


public:
	
	
	
};
