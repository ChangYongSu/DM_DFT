#pragma once
//#include "stdafx.h"

// CDlgModelSetup 대화 상자입니다.

class CFileControl 
{
	

public:
	CFileControl();   // 표준 생성자입니다.
	virtual ~CFileControl();

// 대화 상자 데이터입니다.




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

	int CheckModelSeqFile(CString lFilename);

	int CFileControl::CheckStepLine(CString StringLine);
	int CFileControl::CheckFunctionLine(CString StringLine);


	unsigned char  ReadHex(CString lstrASCII);

public:
	
	
	
};
