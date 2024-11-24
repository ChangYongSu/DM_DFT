// MesDb.cpp : implementation file
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"//#include "AVN_Test.h"
#include "MesDb.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if 0
CMesDb			g_MesDb;

/////////////////////////////////////////////////////////////////////////////
// CMesDb

CMesDb::CMesDb()
{
	if(FAILED(::CoInitialize(NULL))) 
	{
		m_bCoInit = false;
	}
	else
	{
		m_bCoInit = true;
	}

	//+add kwmoon 080501
	m_bDBconnection = false;

	//+add kwmoon 080501
	m_pConn = NULL;

	m_strWipId = _T("");			//Wip ID
	m_strBarPrecode = _T("");
	m_strBarPrePN = _T("");
	m_strBarPn = _T("");
	m_strBarSerial = _T("");

	m_sStepIn = _T("");
	m_sStepDesc = _T("");
	m_sTxNId = _T("");
	m_bStepCheck = FALSE;

	m_sPreCode = _T("");
	m_sMCode = _T("");
	m_sSerialNumber = _T("");
	m_sOobFlag = _T("");
	
	m_sOobFlag_Ref = _T("");

}

CMesDb::~CMesDb()
{
	////+add kwmoon 080501
	if(m_pConn != NULL)
	{
		//if(m_bDBconnection) 
		{
			TESTHR(m_pConn->Close());
			m_bDBconnection = false;

			m_pConn = NULL;
		}
	}
	
	//m_bDBconnection
	//if(m_bDBconnection) 
	//{
	//	m_pConn->Close();
	//	m_bDBconnection = FALSE;
	//	m_bCoInit = false;
	//	m_pConn = NULL;//CYS
	//}
	
	
	if(m_bCoInit == true)
	{
		::CoUninitialize();
	}
	
}


BEGIN_MESSAGE_MAP(CMesDb, CWnd)
	//{{AFX_MSG_MAP(CMesDb)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMesDb message handlers

//////////////////////////////////////////////////////////////////////////
void CMesDb::ParaInit()
{
	m_strWipId = _T("");			//Wip ID
	m_strBarPrecode = _T("");
	m_strBarPrePN = _T("");
	m_strBarPn = _T("");
	m_strBarSerial = _T("");

	m_sStepIn = _T("");
	m_sStepDesc = _T("");
	m_sTxNId = _T("");
	m_bStepCheck = FALSE;

	m_sPreCode = _T("");
	m_sMCode = _T("");
	m_sSerialNumber = _T("");
	m_sOobFlag = _T("");
	
	m_sOobFlag_Ref = _T("");

}

/*
===============================================================================
 �� �� �� : Mes_Open_Test()
 ��    �� : ���� �⺻���� MES ���� �� ���� �׽�Ʈ 
 �� �� �� : strDsn		=> MES DB DSN		default : DAVMDEV
			strUserID	=> MES DB UserID	�׽�Ʈ�뼭��ID : oraspc
			strPassWD	=> MES DB PassWD	�׽�Ʈ�뼭��Pass : spcora00
			strRtn		=> ������� false�� ��� ���� �޼����� ������
 �� �� �� : bool type
 �� �� �� : 2006.04.04
 �� �� �� : ������(usy79@lge.com)
===============================================================================
*/
BOOL CMesDb::Mes_Open_Test(CString strDsn, CString strUserID, CString strPassWD, CString &strRtn)
{
	CString strConn, strTmp;

//	ADODB::_ConnectionPtr m_pConn = NULL;
	HRESULT	hRst = S_OK;

	CString sString;
	//-
	//Coinitialize�� �ȵǾ� �ִٸ� �ٽ� �Ѵ�.
	try
	{
		if(m_bCoInit == false)
		{
			if(FAILED(::CoInitialize(NULL))) 
			{
				m_bCoInit = false;
				// sString.LoadString(IDS_MES_MSG);  //"DB ���� �ʱ�ȭ�� �����Ͽ����ϴ�!"
				 strRtn= "DB ���� �ʱ�ȭ�� �����Ͽ����ϴ�!";//.Format(sString);
				::CoUninitialize();
				m_bDBconnection = FALSE;
				return FALSE;
			}
			else{
				m_bCoInit = true;
			}
		}
	}
	catch (_com_error &e) 
	{       
		m_bCoInit = false;
		sString= "MES DB ���ῡ �����Ͽ����ϴ�!\n";//.LoadString(_T("IDS_MES_MSG2")); //"MES DB ���ῡ �����Ͽ����ϴ�!\n"
		strRtn.Format(sString);
		strTmp.Format("[%s]", Mes_ComErr_Make(e));
		strRtn += strTmp;
		::CoUninitialize();
		m_bDBconnection = FALSE;
		return FALSE;
	} 

	


	//DB Open
	try
	{
		TESTHR(hRst = m_pConn.CreateInstance(__uuidof(ADODB::Connection)));

		//Oracle DB ���� ���ڿ�
		strConn = "";
		strConn = strConn + "Provider=MSDAORA;";
		strConn = strConn + "Data Source=" + strDsn + ";";
		
		//m_pConn->CommandTimeout = 3;
		long lTimeout;
		//m_pConn->get_ConnectionTimeout(&lTimeout);
		//m_pConn->put_ConnectionTimeout(2);
		TESTHR(m_pConn->Open((_bstr_t)strConn,(_bstr_t)strUserID,(_bstr_t)strPassWD,NULL));
		//TESTHR(m_pConn->Open((_bstr_t)strConn,(_bstr_t)strUserID,(_bstr_t)strPassWD,100000));

		//cys sString.LoadString("IDS_MES_MSG1");  // "MES DB ���ῡ �����Ͽ����ϴ�!\n"
		//cys strRtn.Format(sString);
		m_bDBconnection = TRUE;
		return TRUE;
	}
	//����ó��
	catch (_com_error &e) 
	{
		//cys sString.LoadString("IDS_MES_MSG2"); //"MES DB ���ῡ �����Ͽ����ϴ�!\n"
		//cys strRtn.Format(sString);
		 strTmp.Format("[%s]", Mes_ComErr_Make(e));
		strRtn += strTmp;
		m_bDBconnection = FALSE;

		//m_pConn->
		m_pConn.Release();
		//m_pConn = NULL;
		return FALSE;
	}
	
}
BOOL CMesDb::IsOpen()
{
	if(m_bDBconnection ){
		return m_pConn->GetState() != 0; // adStateClosed;
	}
	return FALSE;
}


BOOL CMesDb::Close()
{
	BOOL bRet = TRUE;

	try 
	{
		if(m_bDBconnection) 
		{
			m_pConn->Close();
			m_bDBconnection = FALSE;
			m_bCoInit = false;
			
		}
	}
	catch(...)
	{
		m_bDBconnection = FALSE;
		m_bCoInit = false;
		bRet = FALSE;
	}
	return bRet;
}
/*
===============================================================================
 �� �� �� : Mes_GetFileID_Test()
 ��    �� : MES���� ������ ���ϸ��� ������
 �� �� �� : strDsn		=> MES DB DSN		default : DAVMDEV
			strUserID	=> MES DB UserID	�׽�Ʈ�뼭��ID : oraspc
			strPassWD	=> MES DB PassWD	�׽�Ʈ�뼭��Pass : spcora00
			strRtn		=> ������� true�� ��� ���ϸ��� ������
						   ������� false�� ��� ���� �޼����� ������
 �� �� �� : bool type
===============================================================================
*/
bool CMesDb::Mes_GetFileID_Test(CString strDsn, CString strUserID, CString strPassWD, CString &strRtn)
{
	CString			strConn, strTmp;
	ADODB::_ConnectionPtr	pConn = NULL;
	ADODB::_CommandPtr		pCmd  = NULL;
	ADODB::_ParameterPtr	pPara = NULL;
	ADODB::_RecordPtr		pRec  = NULL;
	HRESULT			hRst = S_OK;

	//+2006.08.28 Add BY USY
	CString sString;
	//-

	//Coinitialize�� �ȵǾ� �ִٸ� �ٽ� �Ѵ�.
	if(m_bCoInit == false)
	{
		if(FAILED(::CoInitialize(NULL))) 
		{
			m_bCoInit = false;
			//+2006.08.28 Add BY USY
			//sString.LoadString("IDS_MES_MSG");
			//strRtn.Format(sString);
			//strRtn.Format("DB ���� �ʱ�ȭ�� �����Ͽ����ϴ�!");
			//-
			return false;
		}
		else{
			m_bCoInit = true;
		}
	}

	
	//DB ����
	try
	{			
		TESTHR(hRst = pConn.CreateInstance(__uuidof(ADODB::Connection)));
		
		//Oracle DB ���� ���ڿ�
		strConn = "";
		strConn = strConn + "Provider=MSDAORA;";
		strConn = strConn + "Data Source=" + strDsn + ";";
		
		TESTHR(pConn->Open((_bstr_t)strConn,(_bstr_t)strUserID,(_bstr_t)strPassWD,NULL));
	}

	//����ó��
	catch (_com_error &e) 
	{
		//������ �����ߴٴ� �޼����� Mes_ComErr_Make�� ���� �����޼����� 
		//strRtn�� ������ �� false ����
		//+2006.08.28 Add BY USY
		//cys sString.LoadString("IDS_MES_MSG2");
		//cys strRtn.Format(sString);
		//strRtn.Format("MES DB ���ῡ �����Ͽ����ϴ�!\n");
		//-
		//+del kwmoon 080523
	//strTmp.Format("[%s]", Mes_ComErr_Make(e));
	//	strRtn += strTmp;
		return false;
	}
	//-
	
	//Get File ID
	try
	{
		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));

		//Oracle DB ���� ���ڿ�
		pCmd->ActiveConnection = pConn;
		//+2006.10.17 Mod BY USY
		pCmd->CommandText = "ORAKSAVMES.MES_SPC_PKG.GET_FILE_ID";
		//pCmd->CommandText = "ORADAVMES.MES_SPC_PKG.GET_FILE_ID";
		//-
		pCmd->CommandType = ADODB::adCmdStoredProc;		

		//�Ķ���� Output
		//V_RETVALUE => File ID
		pPara = pCmd->CreateParameter("V_RETVALUE", ADODB::adVarChar, ADODB::adParamOutput, 15);
		pCmd->Parameters->Append(pPara);

		//V_ERR_MSG => TRUE : File ID �������� ����
		//			   FALSE : File ID �������� ����
		pPara = pCmd->CreateParameter("V_ERRMSG", ADODB::adVarChar, ADODB::adParamOutput, 512);
		pCmd->Parameters->Append(pPara);

		//MES DB�κ��� V_ERR_MSG��  ��������
		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
		pPara = pCmd->Parameters->Item["V_ERRMSG"];
		strRtn.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));

		//V_ERR_MSG�� TRUE�� �ƴҰ�� File ID �������� ����
		if( strRtn.Compare("TRUE") != 0)
		{
			//+2006.08.28 Add BY USY
			//cys sString.LoadString("IDS_MES_MSG3");
			//cys strTmp.Format(sString, (const char*)strRtn);
			//strTmp.Format("MES DB���� �����̸��� �������µ� �����Ͽ����ϴ�!\n[%s]", strRtn);
			//-
			strRtn.Format("%s", (const char*)strTmp);
			return false;
		}
		//File ID �������� ����
		else 
		{	
			//V_RETVALUE�� ����� File ID�� strRtn�� �����ϰ� true ����
			pPara = pCmd->Parameters->Item["V_RETVALUE"];
			strRtn.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
			return true;
		}
	}

	//����ó��
	catch (_com_error &e) 
	{	
		//���� �̸��� ��������  �����ߴٴ� �޼����� Mes_ComErr_Make�� ���� �����޼����� 
		//strRtn�� ������ �� false ����
		//+2006.08.28 Add BY USY
		//cys sString.LoadString("IDS_MES_MSG7");
		//cys strRtn.Format(sString);
		//strRtn.Format("MES DB���� �����̸��� �������µ� �����Ͽ����ϴ�!\n");
		//-
		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
		strRtn += strTmp;
		return false;
	}
	//-
}

/*
===============================================================================
 �� �� �� : StepCheck()
 ��    �� : ���� �ڵ� ��������
 �� �� �� : strDsn		=> MES DB DSN		default : DAVMDEV
			strUserID	=> MES DB UserID	�׽�Ʈ�뼭��ID : oraspc
			strPassWD	=> MES DB PassWD	�׽�Ʈ�뼭��Pass : spcora00
			strSn		=> ���� S/N(25�ڸ�)

			strRtn1		=> ������� true�� ��� �����ڵ带 ������		ex)GMPBST
						   ������� false�� ��� ���� �޼����� ������	

			strRtn2		=> ������� true�� ��� �����ڵ忡 ���� ���� �޼����� ������ 
						   ex)	"���� ������ BST �˻� �Դϴ�."
			
 �� �� �� : BOOL type
===============================================================================
*/
//int CMesDb::StepCheck()
//{
//	CString			strConn, strTmp;
//	CString			sMsg;
////	ADODB::_ConnectionPtr	pConn = NULL;
//	ADODB::_CommandPtr		pCmd  = NULL;
//	ADODB::_ParameterPtr	pPara = NULL;
//	ADODB::_RecordPtr		pRec  = NULL;
//	HRESULT			hRst = S_OK;
//
//	CString sCmd;
//	CString sString;
//	int nRev = 0;
//	int bRev = FALSE;
//
//	m_bStepCheck = FALSE;
//
//	if(!m_bDBconnection){
//		bRev = Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
//		AddStringToStatus(sMsg);
//		if(!bRev){ return 3; }
//	}
//
//	try
//	{
//		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));
//
//		//Oracle DB ���� ���ڿ�
//		pCmd->ActiveConnection = m_pConn;
//		sCmd = GetCmd_StepCheck();
//		///*if(CurrentSet.nProvider == 0){
//		//	strTmp.Format("%s.%s", MES_AVN_PT_TABLE, sCmd);
//		//}
//		//else{
//		//	strTmp.Format("%s.%s", MES_AVN_KS_TABLE, sCmd);
//		//}*/
//		strTmp = CurrentSet.strMesAvn;
//		strTmp += _T(".");
//		strTmp += sCmd;
//
//		pCmd->CommandText = _bstr_t(strTmp);
//
//		pCmd->CommandType = ADODB::adCmdStoredProc;
//
//		//�Ķ���� Input
//		//V_SET_SN => ���� S/N(25�ڸ�)
//		pPara = pCmd->CreateParameter("V_SET_SN", ADODB::adVarChar, ADODB::adParamInput, 60);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)m_strWipId;
//
//		//�Ķ���� Output
//		//V_INSP_STEP => �����ڵ�
//		pPara = pCmd->CreateParameter("V_INSP_STEP", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_INSP_STEP_DESC => �����ڵ忡 ���� ����޼���
//		pPara = pCmd->CreateParameter("V_INSP_STEP_DESC", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_ERR_MSG => TRUE : �����ڵ� �������� ����
//		//			   FALSE : �����ڵ� �������� ����
//		pPara = pCmd->CreateParameter("V_ERRMSG", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//		
//		//�����ڵ� �������� ����
//		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
//		pPara = pCmd->Parameters->Item["V_ERRMSG"];
//		sString.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//
//		//V_ERR_MSG�� TRUE�� �ƴҰ�� �����ڵ� �������� ����
//		if((sString.Compare("TRUE") == 0) || (sString.Compare("OK") == 0)) 
//		{
//			//V_INSP_STEP�� ����� �����ڵ带 sStep ����
//			//V_INSP_STEP_DESC�� ����� �����ڵ弳���� sStepDesc �����ϰ� true ����
//			pPara = pCmd->Parameters->Item["V_INSP_STEP"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sStepIn = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_INSP_STEP_DESC"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sStepDesc = strTmp;
//
//			if(m_sStepIn.Compare(CurrentSet.strStepName) == 0){
//				m_bStepCheck = TRUE;
//			}
//
//			if(CurrentSet.bCommDisplay)
//			{
//				if(m_bStepCheck){
//					nRev = 1;
//					sMsg.Format("[MES]StepCheck->OK :: Cur Step - %s, Step In:%s", CurrentSet.strStepName, m_sStepIn);
//				}
//				else{
//					nRev = 0;
//					sMsg.Format("[MES]StepCheck->NG :: Cur Step - %s, Step In:%s", CurrentSet.strStepName, m_sStepIn);
//				}
//				AddStringToStatus(sMsg);
//			}
//
//			return m_bStepCheck;
//		}
//		//�����ڵ� �������� ����
//		else 
//		{
//			sMsg.Format("[MES]StepCheck(%s)->Error",m_strWipId);
//			AddStringToStatus(sMsg);
//			return 2;
//		}
//	}
//	//����ó��
//	catch (_com_error &e) 
//	{
//		//�����ڵ� ��������  �����ߴٴ� �޼����� Mes_ComErr_Make�� ���� �����޼����� 
//		//strRtn1�� ������ �� false ����
//	//	sString.Format(IDS_MES_MSG4);
//	//	sStep = sString;
//		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//	//	sString += strTmp;
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]StepCheck(%s):Fail ==>\n\r%s", m_strWipId, strTmp);
//			AddStringToStatus(sMsg);
//		}
//		return 3;
//	}
//
//
//}

/*
===============================================================================
 �� �� �� : StepComplete()
 ��    �� : ���� �Ϸ� ó��
 �� �� �� : strSn		=> ���� S/N(25�ڸ�)
			strStep		=> �˻�����ڵ�		default : GMPBST
			strLine		=> �������			default : PV03(���Ƕ���)
			strResult	=> �׽�Ʈ ���		OK / NG
			strRtn		=> ������� false�� ��� ���� �޼����� ������

 �� �� �� : BOOL type
===============================================================================
*/

//int CMesDb::StepComplete(BOOL bResult)
//{
//	CString			strConn, strTmp;
//	CString			sMsg;
////	ADODB::_ConnectionPtr	pConn = NULL;
//	ADODB::_CommandPtr		pCmd  = NULL;
//	ADODB::_ParameterPtr	pPara = NULL;
//	ADODB::_RecordPtr		pRec  = NULL;
//	HRESULT			hRst = S_OK;
//
//	CString sCmd;
//	CString sString;
//	BOOL bRev = TRUE;
//
//	if(!m_bDBconnection){
//		bRev = Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
//		AddStringToStatus(sMsg);
//		if(!bRev){ return 3; }
//	}
//
////	m_pConn->BeginTrans();
//	try
//	{
//		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));
//
//		pCmd->ActiveConnection = m_pConn;
//
//		sCmd = GetCmd_StepComplete();
//
////		/*if(CurrentSet.nProvider == 0){
////			strTmp.Format("%s%s", MES_AVN_PT_TABLE, sCmd);
////		}
////		else{
////			strTmp.Format("%s%s", MES_AVN_KS_TABLE, sCmd);
////		}
////*/
//
//		if(CurrentSet.strMesAvn.GetLength() > 1)
//		{
//
//			strTmp = CurrentSet.strMesAvn;
//			strTmp += _T(".");
//		}
//		strTmp += sCmd;
//
//		pCmd->CommandText = _bstr_t(strTmp);
//
//		pCmd->CommandType = ADODB::adCmdStoredProc;
//
//		//�Ķ���� Input
//		//V_SET_SN => ���� S/N(25�ڸ�)
//		pPara = pCmd->CreateParameter("V_SET_SN", ADODB::adVarChar, ADODB::adParamInput, 40);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)m_strWipId;
//
//		//V_INSP_STEP => �����ڵ�
//		pPara = pCmd->CreateParameter("V_INSP_STEP", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)CurrentSet.strStepName;
//
//		//V_LINE => �������
//		pPara = pCmd->CreateParameter("V_LINE", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)CurrentSet.strProductionLine;
//
//		//V_INSP_RESULT => �׽�Ʈ ���
//		pPara = pCmd->CreateParameter("V_INSP_RESULT", ADODB::adVarChar, ADODB::adParamInput, 10);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (bResult? "OK":"NG");
//
//		//�Ķ���� Output
//		//V_ERR_MSG => TRUE : �����ڵ� �������� ����
//		//			   FALSE : �����ڵ� �������� ����
//		pPara = pCmd->CreateParameter("V_ERRMSG", ADODB::adVarChar, ADODB::adParamOutput, 512);
//		pCmd->Parameters->Append(pPara);
//		
//		//�����Ϸ� ó�� ����
//		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
//		pPara = pCmd->Parameters->Item["V_ERRMSG"];
//		sString.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]StepComplete(%s):%s", m_strWipId, sString);
//			AddStringToStatus(sMsg);
//		}
//
//		//V_ERR_MSG�� TRUE�� �ƴҰ�� �����Ϸ� ó�� ����
//		if((sString.Compare("TRUE") == 0) || (sString.Compare("OK") == 0)) 
//		{
//			//strRtn�� �޼����� �������� �ʰ� true�� ����
//		//	m_pConn->CommitTrans();
//			if(CurrentSet.bCommDisplay)
//			{
//				sMsg.Format("[MES]StepComplete(%s)->OK", m_strWipId);
//				AddStringToStatus(sMsg);
//			}
//			return 1;
//		}
//		else 
//		{
//		//	m_pConn->RollbackTrans();
//			if(CurrentSet.bCommDisplay)
//			{
//				sMsg.Format("[MES]StepComplete(%s)->NG", m_strWipId);
//				AddStringToStatus(sMsg);
//			}
//			return 0;
//		}
//	}
//	//����ó��
//	catch (_com_error &e) 
//	{
//		//sString.LoadString(IDS_MES_MSG6);
//		//strRtn.Format(sString);
//		//strRtn.Format("�����Ϸ� ó���� �����Ͽ����ϴ�!\n");
//		//-
//		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]StepComplete(%s):Fail ==>\n\r%s", m_strWipId, strTmp);
//			AddStringToStatus(sMsg);
//		}
//		return 3;
//	}
//	//-
//}
//
//int CMesDb::MasterInsert(BOOL bResult, int nTestItems)
//{
//	CString			strConn, strTmp;
//	CString			sMsg;
////	ADODB::_ConnectionPtr	pConn = NULL;
//	ADODB::_CommandPtr		pCmd  = NULL;
//	ADODB::_ParameterPtr	pPara = NULL;
//	ADODB::_RecordPtr		pRec  = NULL;
//	HRESULT			hRst = S_OK;
//
//	CString sCmd;
//	CString sString;
//	BOOL bRev = TRUE;
//
//	if(!m_bDBconnection){
//		bRev = Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
//		AddStringToStatus(sMsg);
//		if(!bRev){ return 3; }
//	}
//
////	m_pConn->BeginTrans();
//	try
//	{
//		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));
//
//		pCmd->ActiveConnection = m_pConn;
//
//		sCmd = GetCmd_MasterInsert();
//		if(CurrentSet.nProvider == 0){
//			strTmp.Format("%s%s", MES_AVN_PT_TABLE, sCmd);
//		}
//		else{
//			strTmp.Format("%s%s", MES_AVN_KS_TABLE, sCmd);
//		}
//		pCmd->CommandText = _bstr_t(strTmp);
//
//		pCmd->CommandType = ADODB::adCmdStoredProc;
//
//		//�Ķ���� Input
//		//V_LINE => �������
//		pPara = pCmd->CreateParameter("V_LINE", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)CurrentSet.strProductionLine;
//
//		//V_STEP => �����ڵ�
//		pPara = pCmd->CreateParameter("V_INSP", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)CurrentSet.strStepName;
//
//		//V_SNNO => ���� S/N(25�ڸ�)
//		pPara = pCmd->CreateParameter("V_SNNO", ADODB::adVarChar, ADODB::adParamInput, 40);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)m_strWipId;
//
//		//V_RESULT => �׽�Ʈ ���
//		pPara = pCmd->CreateParameter("V_RESULT", ADODB::adVarChar, ADODB::adParamInput, 10);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (bResult? "OK":"NG");
//
//
//		//V_TIME => Current Time
//		CTime Time;
//		Time  = CTime::GetCurrentTime();
//		strTmp = Time.Format("%Y%m%d%H%M%S");
//		pPara = pCmd->CreateParameter("V_TIME", ADODB::adVarChar, ADODB::adParamInput, 40);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)strTmp;
//
//		//V_TESTCOUNT => �׽�Ʈ �׸��
//		strTmp.Format("%d", nTestItems);
//		pPara = pCmd->CreateParameter("V_TESTCOUNT", ADODB::adVarChar, ADODB::adParamInput, 10);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)strTmp;
//
//		//�Ķ���� Output
//		//V_TXNID => TRUE : �����ڵ� �������� ����
//		//			   FALSE : �����ڵ� �������� ����
//		pPara = pCmd->CreateParameter("V_TXNID", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//		
//		//�����Ϸ� ó�� ����
//		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
//		pPara = pCmd->Parameters->Item["V_TXNID"];
//		sString.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//		m_sTxNId = sString;
//		
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]MasterInsert(%s)->OK :%s", m_strWipId, sString);
//			AddStringToStatus(sMsg);
//		}
//
//	//	m_pConn->CommitTrans();
//		return 1;
//	}
//	//����ó��
//	catch (_com_error &e) 
//	{
//		//sString.LoadString(IDS_MES_MSG6);
//		//strRtn.Format(sString);
//		//strRtn.Format("�����Ϸ� ó���� �����Ͽ����ϴ�!\n");
//		//-
//		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]MasterInsert(%s):Fail ==>\n\r%s", m_strWipId, strTmp);
//			AddStringToStatus(sMsg);
//		}
//		return 3;
//	}
//	//-
//}
	
//int CMesDb::DetailInsert(CString sName, BOOL bResult, CString sValue)
//{
//	CString			strConn, strTmp;
//	CString			sMsg;
////	ADODB::_ConnectionPtr	pConn = NULL;
//	ADODB::_CommandPtr		pCmd  = NULL;
//	ADODB::_ParameterPtr	pPara = NULL;
//	ADODB::_RecordPtr		pRec  = NULL;
//	HRESULT			hRst = S_OK;
//
//	CString sCmd;
//	CString sString;
//	CString sResult			= _T("");
//	BOOL bRev = TRUE;
//
//	if(!m_bDBconnection){
//		bRev = Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
//		AddStringToStatus(sMsg);
//		if(!bRev){ return 3; }
//	}
//
////	m_pConn->BeginTrans();
//	try
//	{
//		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));
//
//		pCmd->ActiveConnection = m_pConn;
//
//		sCmd = GetCmd_DetailInsert();
//		if(CurrentSet.nProvider == 0){
//			strTmp.Format("%s%s", MES_AVN_PT_TABLE, sCmd);
//		}
//		else{
//			strTmp.Format("%s%s", MES_AVN_KS_TABLE, sCmd);
//		}
//		pCmd->CommandText = _bstr_t(strTmp);
//
//		pCmd->CommandType = ADODB::adCmdStoredProc;
//
//		//�Ķ���� Input
//		//V_TXNID => �ĺ� ID
//		pPara = pCmd->CreateParameter("V_TXNID", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)m_sTxNId;
//
//		//V_ITEMID => ITEM�ڵ�
//		pPara = pCmd->CreateParameter("V_ITEMID", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)sName;
//
//		//V_ITEMRESULT => Item �׽�Ʈ ���
//		pPara = pCmd->CreateParameter("V_ITEMRESULT", ADODB::adVarChar, ADODB::adParamInput, 40);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (bResult? "OK":"NG");
//
//		//V_ITEMVALUE => ��� ��
//		pPara = pCmd->CreateParameter("V_ITEMVALUE", ADODB::adVarChar, ADODB::adParamInput, 10);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)sValue;
//
//		//�����Ϸ� ó�� ����
//		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
//		
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]DetailInsert(%s):%s, %s", m_sTxNId, sName, sResult);
//			AddStringToStatus(sMsg);
//		}
//
//	//	m_pConn->CommitTrans();
//		return 1;
//	}
//	//����ó��
//	catch (_com_error &e) 
//	{
//		//sString.LoadString(IDS_MES_MSG6);
//		//strRtn.Format(sString);
//		//strRtn.Format("�����Ϸ� ó���� �����Ͽ����ϴ�!\n");
//		//-
//		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]DetailInsert(%s):Fail ==>\n\r%s", m_sTxNId, strTmp);
//			AddStringToStatus(sMsg);
//		}
//		return 3;
//	}
//	//-
//}
//int CMesDb::GetKeyInfoWip()
//{
//	CString			strConn, strTmp;
//	CString			sMsg;
////	ADODB::_ConnectionPtr	pConn = NULL;
//	ADODB::_CommandPtr		pCmd  = NULL;
//	ADODB::_ParameterPtr	pPara = NULL;
//	ADODB::_RecordPtr		pRec  = NULL;
//	HRESULT			hRst = S_OK;
//
//	CString sCmd;
//	CString sString;
//	CString sResult			= _T("");
//	BOOL bRev = TRUE;
//
//	if(!m_bDBconnection){
//		bRev = Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
//		AddStringToStatus(sMsg);
//		if(!bRev){ return 3; }
//	}
//
////	m_pConn->BeginTrans();
//	try
//	{
//		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));
//
//		pCmd->ActiveConnection = m_pConn;
//
//		sCmd = GetCmd_KeyInfoWip();
//		if(sCmd == ""){
//			sMsg.Format("[MES]GetKeyInfoWip->NG:MES Cmd");
//			AddStringToStatus(sMsg);
//			return 0;
//		}
//		if(CurrentSet.nProvider == 0){
//			strTmp.Format("%s%s", MES_AVN_PT_TABLE, sCmd);
//		}
//		else{
//			strTmp.Format("%s%s", MES_AVN_KS_TABLE, sCmd);
//		}
//		pCmd->CommandText = _bstr_t(strTmp);
//
//		pCmd->CommandType = ADODB::adCmdStoredProc;
//
//		//�Ķ���� Input
//		//X_WIP_ID => Wip ID
//		pPara = pCmd->CreateParameter("X_WIP_ID", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)m_strWipId;
//
//		//�Ķ���� Output
//		//V_WIP_ID => Wip ID
//		pPara = pCmd->CreateParameter("V_WIP_ID", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_PRE_CODE => �����ڵ忡 ���� ����޼���
//		pPara = pCmd->CreateParameter("V_PRE_CODE", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_M_CODE 
//		pPara = pCmd->CreateParameter("V_M_CODE", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_SERIALNUMBER 
//		pPara = pCmd->CreateParameter("V_SERIALNUMBER", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//ERRBUF => TRUE : �����ڵ� �������� ����
//		//			   FALSE : �����ڵ� �������� ����
//		pPara = pCmd->CreateParameter("ERRBUF", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//�����Ϸ� ó�� ����
//		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
//
//		pPara = pCmd->Parameters->Item["ERRBUF"];
//		sString.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//
//		//V_ERR_MSG�� TRUE�� �ƴҰ�� �����ڵ� �������� ����
//		if((sString.Compare("TRUE") == 0) || (sString.Compare("OK") == 0)) 
//		{
//			pPara = pCmd->Parameters->Item["V_PRE_CODE"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sPreCode = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_M_CODE"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sMCode = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_SERIALNUMBER"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sSerialNumber = strTmp;
//
//			if(CurrentSet.bCommDisplay)
//			{
//				sMsg.Format("[MES]GetKeyInfoWip->OK:PRE_CODE-%s,M_CODE-%s,SET_SN-%s", m_sPreCode, m_sMCode,m_sSerialNumber);
//				AddStringToStatus(sMsg);
//			}
//
//			return 1;
//		}
//		else 
//		{
//			sMsg.Format("[MES]GetKeyInfoWip->NG");
//			AddStringToStatus(sMsg);
//			return 2;
//		}
//
//	//	m_pConn->CommitTrans();
//		return TRUE;
//	}
//	//����ó��
//	catch (_com_error &e) 
//	{
//		//sString.LoadString(IDS_MES_MSG6);
//		//strRtn.Format(sString);
//		//strRtn.Format("�����Ϸ� ó���� �����Ͽ����ϴ�!\n");
//		//-
//		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]GetKeyInfoWip(%s):Fail ==>\n\r%s", m_strWipId, strTmp);
//			AddStringToStatus(sMsg);
//		}
//		return 3;
//	}
//	//-
//}
//int CMesDb::GetKeyInfoSerial()
//{
//	CString			strConn, strTmp;
//	CString			sMsg;
////	ADODB::_ConnectionPtr	pConn = NULL;
//	ADODB::_CommandPtr		pCmd  = NULL;
//	ADODB::_ParameterPtr	pPara = NULL;
//	ADODB::_RecordPtr		pRec  = NULL;
//	HRESULT			hRst = S_OK;
//
//	CString sCmd;
//	CString sString;
//	CString sResult			= _T("");
//	BOOL bRev = TRUE;
//
//	if(!m_bDBconnection){
//		bRev = Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
//		AddStringToStatus(sMsg);
//		if(!bRev){ return 3; }
//	}
//
//	if(CurrentSet.nOobType == 2){m_strBarSerial = m_sSerialNumber;}
////	m_pConn->BeginTrans();
//	try
//	{
//		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));
//
//		pCmd->ActiveConnection = m_pConn;
//
//		sCmd = GetCmd_KeyInfoSerial();
//		if(sCmd == ""){
//			sMsg.Format("[MES]GetKeyInfoSerial->NG:MES Cmd");
//			AddStringToStatus(sMsg);
//			return 0;
//		}
//		if(CurrentSet.nProvider == 0){
//			strTmp.Format("%s%s", MES_AVN_PT_TABLE, sCmd);
//		}
//		else{
//			strTmp.Format("%s%s", MES_AVN_KS_TABLE, sCmd);
//		}
//		pCmd->CommandText = _bstr_t(strTmp);
//
//		pCmd->CommandType = ADODB::adCmdStoredProc;
//
//		//�Ķ���� Input
//		//X_SERIAL => Serial
//		pPara = pCmd->CreateParameter("X_SERIAL", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)m_strBarSerial;
//
//		//�Ķ���� Output
//		//V_WIP_ID => Wip ID
//		pPara = pCmd->CreateParameter("V_WIP_ID", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_PRE_CODE => �����ڵ忡 ���� ����޼���
//		pPara = pCmd->CreateParameter("V_PRE_CODE", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_M_CODE 
//		pPara = pCmd->CreateParameter("V_M_CODE", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_SERIALNUMBER 
//		pPara = pCmd->CreateParameter("V_SERIALNUMBER", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//ERRBUF => TRUE : �����ڵ� �������� ����
//		//			   FALSE : �����ڵ� �������� ����
//		pPara = pCmd->CreateParameter("ERRBUF", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//�����Ϸ� ó�� ����
//		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
//
//		pPara = pCmd->Parameters->Item["ERRBUF"];
//		sString.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//
//		//V_ERR_MSG�� TRUE�� �ƴҰ�� �����ڵ� �������� ����
//		if((sString.Compare("TRUE") == 0) || (sString.Compare("OK") == 0)) 
//		{
//			pPara = pCmd->Parameters->Item["V_WIP_ID"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_strWipId = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_PRE_CODE"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sPreCode = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_M_CODE"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sMCode = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_SERIALNUMBER"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sSerialNumber = strTmp;
//
//			if(CurrentSet.bCommDisplay)
//			{
//				sMsg.Format("[MES]GetKeyInfoSerial->OK:WipID-%s, PRE_CODE-%s,M_CODE-%s,SET_SN-%s", m_strWipId, m_sPreCode, m_sMCode,m_sSerialNumber);
//				AddStringToStatus(sMsg);
//			}
//
//			return 1;
//		}
//		else 
//		{
//			sMsg.Format("[MES]GetKeyInfoSerial->NG");
//			AddStringToStatus(sMsg);
//			return 2;
//		}
//
//	//	m_pConn->CommitTrans();
//		return TRUE;
//	}
//	//����ó��
//	catch (_com_error &e) 
//	{
//		//sString.LoadString(IDS_MES_MSG6);
//		//strRtn.Format(sString);
//		//strRtn.Format("�����Ϸ� ó���� �����Ͽ����ϴ�!\n");
//		//-
//		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]GetKeyInfoSerial(%s):Fail ==>\n\r%s", m_strBarSerial, strTmp);
//			AddStringToStatus(sMsg);
//		}
//		return 3;
//	}
//	//-
//}
//
//int CMesDb::GetKeyInfoWip2()
//{
//	CString			strConn, strTmp;
//	CString			sMsg;
////	ADODB::_ConnectionPtr	pConn = NULL;
//	ADODB::_CommandPtr		pCmd  = NULL;
//	ADODB::_ParameterPtr	pPara = NULL;
//	ADODB::_RecordPtr		pRec  = NULL;
//	HRESULT			hRst = S_OK;
//
//	CString sCmd;
//	CString sString;
//	CString sResult			= _T("");
//	BOOL bRev = TRUE;
//
//	if(!m_bDBconnection){
//		bRev = Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
//		AddStringToStatus(sMsg);
//		if(!bRev){ return 3; }
//	}
//
////	m_pConn->BeginTrans();
//	try
//	{
//		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));
//
//		pCmd->ActiveConnection = m_pConn;
//
//		sCmd = GetCmd_KeyInfoWip2();
//		if(sCmd == ""){
//			sMsg.Format("[MES]GetKeyInfoWip2->NG:MES Cmd");
//			AddStringToStatus(sMsg);
//			return 0;
//		}
//		if(CurrentSet.nProvider == 0){
//			strTmp.Format("%s%s", MES_AVN_PT_TABLE, sCmd);
//		}
//		else{
//			strTmp.Format("%s%s", MES_AVN_KS_TABLE, sCmd);
//		}
//		pCmd->CommandText = _bstr_t(strTmp);
//
//		pCmd->CommandType = ADODB::adCmdStoredProc;
//
//		//�Ķ���� Input
//		//X_WIP_ID => Wip ID
//		pPara = pCmd->CreateParameter("X_WIP_ID", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)m_strWipId;
//
//		//�Ķ���� Output
//		//V_WIP_ID => Wip ID
//		pPara = pCmd->CreateParameter("V_WIP_ID", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_PRE_CODE => �����ڵ忡 ���� ����޼���
//		pPara = pCmd->CreateParameter("V_PRE_CODE", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_M_CODE 
//		pPara = pCmd->CreateParameter("V_M_CODE", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_SERIALNUMBER 
//		pPara = pCmd->CreateParameter("V_SERIALNUMBER", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_SKU 
//		pPara = pCmd->CreateParameter("V_SKU", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_PARTNUMBER 
//		pPara = pCmd->CreateParameter("V_PARTNUMBER", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//ERRBUF => TRUE : �����ڵ� �������� ����
//		//			   FALSE : �����ڵ� �������� ����
//		pPara = pCmd->CreateParameter("ERRBUF", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//�����Ϸ� ó�� ����
//		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
//
//		pPara = pCmd->Parameters->Item["ERRBUF"];
//		sString.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//
//		//V_ERR_MSG�� TRUE�� �ƴҰ�� �����ڵ� �������� ����
//		if((sString.Compare("TRUE") == 0) || (sString.Compare("OK") == 0)) 
//		{
//			pPara = pCmd->Parameters->Item["V_PRE_CODE"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sPreCode = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_M_CODE"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sMCode = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_SERIALNUMBER"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sSerialNumber = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_SKU"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sSku = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_PARTNUMBER"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sPrePN = strTmp;
//
//			m_sPartNumber = strTmp.Left(10);
//
//			if(CurrentSet.bCommDisplay)
//			{
//				sMsg.Format("[MES]GetKeyInfoWip2->OK:PRE_CODE-%s,M_CODE-%s,SET_SN-%s", m_sPreCode, m_sMCode,m_sSerialNumber);
//				AddStringToStatus(sMsg);
//			}
//
//			return 1;
//		}
//		else 
//		{
//			sMsg.Format("[MES]GetKeyInfoWip2->NG");
//			AddStringToStatus(sMsg);
//			return 2;
//		}
//
//	//	m_pConn->CommitTrans();
//		return TRUE;
//	}
//	//����ó��
//	catch (_com_error &e) 
//	{
//		//sString.LoadString(IDS_MES_MSG6);
//		//strRtn.Format(sString);
//		//strRtn.Format("�����Ϸ� ó���� �����Ͽ����ϴ�!\n");
//		//-
//		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]GetKeyInfoWip2(%s):Fail ==>\n\r%s", m_strWipId, strTmp);
//			AddStringToStatus(sMsg);
//		}
//		return 3;
//	}
//	//-
//}
//
//int CMesDb::GetKeyInfoSerial2()
//{
//	CString			strConn, strTmp;
//	CString			sMsg;
////	ADODB::_ConnectionPtr	pConn = NULL;
//	ADODB::_CommandPtr		pCmd  = NULL;
//	ADODB::_ParameterPtr	pPara = NULL;
//	ADODB::_RecordPtr		pRec  = NULL;
//	HRESULT			hRst = S_OK;
//
//	CString sCmd;
//	CString sString;
//	CString sResult			= _T("");
//	BOOL bRev = TRUE;
//
//	if(!m_bDBconnection){
//		bRev = Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
//		AddStringToStatus(sMsg);
//		if(!bRev){ return 3; }
//	}
//
////	m_pConn->BeginTrans();
//	try
//	{
//		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));
//
//		pCmd->ActiveConnection = m_pConn;
//
//		sCmd = GetCmd_KeyInfoSerial2();
//		if(sCmd == ""){
//			sMsg.Format("[MES]GetKeyInfoSerial2->NG:MES Cmd");
//			AddStringToStatus(sMsg);
//			return 0;
//		}
//		if(CurrentSet.nProvider == 0){
//			strTmp.Format("%s%s", MES_AVN_PT_TABLE, sCmd);
//		}
//		else{
//			strTmp.Format("%s%s", MES_AVN_KS_TABLE, sCmd);
//		}
//		pCmd->CommandText = _bstr_t(strTmp);
//
//		pCmd->CommandType = ADODB::adCmdStoredProc;
//
//		if(CurrentSet.nOobType == 2){m_strBarSerial = m_sSerialNumber;}
//	//�Ķ���� Input
//		//X_SERIAL => Serial
//		pPara = pCmd->CreateParameter("X_SERIAL", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)m_strBarSerial;
//
//		//�Ķ���� Output
//		//V_WIP_ID => Wip ID
//		pPara = pCmd->CreateParameter("V_WIP_ID", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_PRE_CODE => �����ڵ忡 ���� ����޼���
//		pPara = pCmd->CreateParameter("V_PRE_CODE", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_M_CODE 
//		pPara = pCmd->CreateParameter("V_M_CODE", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_SERIALNUMBER 
//		pPara = pCmd->CreateParameter("V_SERIALNUMBER", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_SKU 
//		pPara = pCmd->CreateParameter("V_SKU", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_PARTNUMBER 
//		pPara = pCmd->CreateParameter("V_PARTNUMBER", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//ERRBUF => TRUE : �����ڵ� �������� ����
//		//			   FALSE : �����ڵ� �������� ����
//		pPara = pCmd->CreateParameter("ERRBUF", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//�����Ϸ� ó�� ����
//		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
//
//		pPara = pCmd->Parameters->Item["ERRBUF"];
//		sString.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//
//		//V_ERR_MSG�� TRUE�� �ƴҰ�� �����ڵ� �������� ����
//		if((sString.Compare("TRUE") == 0) || (sString.Compare("OK") == 0)) 
//		{
//			pPara = pCmd->Parameters->Item["V_WIP_ID"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_strWipId = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_PRE_CODE"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sPreCode = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_M_CODE"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sMCode = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_SERIALNUMBER"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sSerialNumber = strTmp;
//
//
//			pPara = pCmd->Parameters->Item["V_SERIALNUMBER"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sSerialNumber = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_SKU"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sSku = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_PARTNUMBER"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sPrePN = strTmp;
//
//			if(CurrentSet.bCommDisplay)
//			{
//				sMsg.Format("[MES]GetKeyInfoSerial2->OK:WipID-%s, PRE_CODE-%s,M_CODE-%s,SET_SN-%s", m_strWipId, m_sPreCode, m_sMCode,m_sSerialNumber);
//				AddStringToStatus(sMsg);
//			}
//
//			return 1;
//		}
//		else 
//		{
//			sMsg.Format("[MES]GetKeyInfoSerial2->NG");
//			AddStringToStatus(sMsg);
//			return 2;
//		}
//
//	//	m_pConn->CommitTrans();
//		return TRUE;
//	}
//	//����ó��
//	catch (_com_error &e) 
//	{
//		//sString.LoadString(IDS_MES_MSG6);
//		//strRtn.Format(sString);
//		//strRtn.Format("�����Ϸ� ó���� �����Ͽ����ϴ�!\n");
//		//-
//		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]GetKeyInfoSerial2(%s):Fail ==>\n\r%s", m_strBarSerial, strTmp);
//			AddStringToStatus(sMsg);
//		}
//		return 3;
//	}
//	//-
//}
//
//int CMesDb::OobGetInfo()
//{
//	CString			strConn, strTmp;
//	CString			sMsg;
////	ADODB::_ConnectionPtr	pConn = NULL;
//	ADODB::_CommandPtr		pCmd  = NULL;
//	ADODB::_ParameterPtr	pPara = NULL;
//	ADODB::_RecordPtr		pRec  = NULL;
//	HRESULT			hRst = S_OK;
//
//	CString sCmd;
//	CString sString;
//	CString sResult			= _T("");
//	BOOL bRev = TRUE;
//
//	if(!m_bDBconnection){
//		bRev = Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
//		AddStringToStatus(sMsg);
//		if(!bRev){ return 3; }
//	}
//
////	m_pConn->BeginTrans();
//	try
//	{
//		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));
//
//		pCmd->ActiveConnection = m_pConn;
//
//		sCmd = GetCmd_OobGetInfo();
//		if(sCmd == ""){
//			sMsg.Format("[MES]OobGetInfo->NG:MES Cmd");
//			AddStringToStatus(sMsg);
//			return 0;
//		}
//		if(CurrentSet.nOobType == 2){m_strBarSerial = m_sSerialNumber;}
//
//
//		if(CurrentSet.nProvider == 0){
//			strTmp.Format("%s%s", MES_AVN_PT_TABLE, sCmd);
//		}
//		else{
//			strTmp.Format("%s%s", MES_AVN_KS_TABLE, sCmd);
//		}
//		pCmd->CommandText = _bstr_t(strTmp);
//
//		pCmd->CommandType = ADODB::adCmdStoredProc;
//
// /*   PROCEDURE ULC_OOB_GET_INFO( V_SETINFO      IN  VARCHAR2
//                              , V_WIPID         OUT VARCHAR2
//                              , V_PRECODE       OUT VARCHAR2
//                              , V_FCODE         OUT VARCHAR2
//                              , V_OOB_FLAG     OUT VARCHAR2
//                              , V_ERRMSG        OUT VARCHAR2
//                         ) ;
//*/
//		//�Ķ���� Input
//		//V_SETINFO => Serial
//		pPara = pCmd->CreateParameter("V_SETINFO", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)m_strBarSerial;
//
//		//�Ķ���� Output
//		//V_WIP_ID => Wip ID
//		pPara = pCmd->CreateParameter("V_WIPID", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_PRE_CODE => �����ڵ忡 ���� ����޼���
//		pPara = pCmd->CreateParameter("V_PRECODE", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_FCODE 
//		pPara = pCmd->CreateParameter("V_FCODE", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_OOB_FLAG 
//		pPara = pCmd->CreateParameter("V_OOB_FLAG", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//V_ERRMSG => TRUE : �����ڵ� �������� ����
//		//			   FALSE : �����ڵ� �������� ����
//		pPara = pCmd->CreateParameter("V_ERRMSG", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//�����Ϸ� ó�� ����
//		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
//
//		pPara = pCmd->Parameters->Item["V_ERRMSG"];
//		sString.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//		//V_ERR_MSG�� TRUE�� �ƴҰ�� �����ڵ� �������� ����
//		if((sString.Compare("TRUE") == 0) || (sString.Compare("OK") == 0)) 
//		{
//			pPara = pCmd->Parameters->Item["V_WIPID"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_strWipId = strTmp;
//
//		//	pPara = pCmd->Parameters->Item["V_PRECODE"];
//		//	strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//		//	m_sPreCode = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_FCODE"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sMCode = strTmp;
//
//			pPara = pCmd->Parameters->Item["V_OOB_FLAG"];
//			strTmp.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//			m_sOobFlag = strTmp;
//
//			if(CurrentSet.bCommDisplay)
//			{
//				sMsg.Format("[MES]OobGetInfo->OK:WIP_ID-%s,PRE_CODE-%s,FCODE-%s,OOB_FLAG-%s",m_strWipId, m_sPreCode, m_sMCode,m_sOobFlag);
//				AddStringToStatus(sMsg);
//			}
//
//			return 1;
//		}
//		else 
//		{
//			sMsg.Format("[MES]OobGetInfo->NG");
//			AddStringToStatus(sMsg);
//			return 2;
//		}
//
//	//	m_pConn->CommitTrans();
//		return TRUE;
//	}
//	//����ó��
//	catch (_com_error &e) 
//	{
//		//sString.LoadString(IDS_MES_MSG6);
//		//strRtn.Format(sString);
//		//strRtn.Format("�����Ϸ� ó���� �����Ͽ����ϴ�!\n");
//		//-
//		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]OobGetInfo(%s):Fail ==>\n\r%s", m_strBarSerial, strTmp);
//			AddStringToStatus(sMsg);
//		}
//		return 3;
//	}
//	//-
//}
//
//int CMesDb::OobSetInfo()
//{
//	CString			strConn, strTmp;
//	CString			sMsg;
////	ADODB::_ConnectionPtr	pConn = NULL;
//	ADODB::_CommandPtr		pCmd  = NULL;
//	ADODB::_ParameterPtr	pPara = NULL;
//	ADODB::_RecordPtr		pRec  = NULL;
//	HRESULT			hRst = S_OK;
//
//	CString sCmd;
//	CString sString;
//	CString sResult			= _T("");
//	BOOL bRev = TRUE;
//
//	if(!m_bDBconnection){
//		bRev = Mes_Open_Test(CurrentSet.strMesDsn, CurrentSet.strMesUserId, CurrentSet.strMesPassWord, sMsg);
//		AddStringToStatus(sMsg);
//		if(!bRev){ return 3; }
//	}
//
////	m_pConn->BeginTrans();
//	try
//	{
//		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));
//
//		pCmd->ActiveConnection = m_pConn;
//
//		sCmd = GetCmd_OobSetInfo();
//		if(sCmd == ""){
//			sMsg.Format("[MES]OobSetInfo->NG:MES Cmd");
//			AddStringToStatus(sMsg);
//			return 0;
//		}
//
//		if(CurrentSet.nProvider == 0){
//			strTmp.Format("%s%s", MES_AVN_PT_TABLE, sCmd);
//		}
//		else{
//			strTmp.Format("%s%s", MES_AVN_KS_TABLE, sCmd);
//		}
//		pCmd->CommandText = _bstr_t(strTmp);
//
//		pCmd->CommandType = ADODB::adCmdStoredProc;
//
//		/*
//    PROCEDURE ULC_OOB_SET_INFO( V_DIVISION        IN  VARCHAR2
//                          , V_SETINFO          IN  VARCHAR2
//                          , V_OOB_TEST_YN     IN  VARCHAR2
//                          , V_ERRMSG          OUT VARCHAR2
//                         );
//		*/
//		//�Ķ���� Input
//		//V_DIVISION
//		pPara = pCmd->CreateParameter("V_DIVISION", ADODB::adVarChar, ADODB::adParamInput, 30);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)"AV";
//
//		//V_SETINFO => Serial
//		pPara = pCmd->CreateParameter("V_SETINFO", ADODB::adVarChar, ADODB::adParamInput, 60);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)m_strBarSerial;
//
//		//V_OOB_TEST_YN
//		pPara = pCmd->CreateParameter("V_OOB_TEST_YN", ADODB::adVarChar, ADODB::adParamInput, 60);
//		pCmd->Parameters->Append(pPara);
//		pPara->Value = (_bstr_t)CurrentSet.strOobFlag;
//
//		//�Ķ���� Output
//		//V_ERRMSG => TRUE : �����ڵ� �������� ����
//		//			   FALSE : �����ڵ� �������� ����
//		pPara = pCmd->CreateParameter("V_ERRMSG", ADODB::adVarChar, ADODB::adParamOutput, 60);
//		pCmd->Parameters->Append(pPara);
//
//		//�����Ϸ� ó�� ����
//		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdStoredProc);
//
//		pPara = pCmd->Parameters->Item["V_ERRMSG"];
//		sString.Format("%s",(LPCSTR)(_bstr_t)(pPara->Value));
//		//V_ERR_MSG�� TRUE�� �ƴҰ�� �����ڵ� �������� ����
//		if((sString.Compare("TRUE") == 0) || (sString.Compare("OK") == 0)) 
//		{
//			if(CurrentSet.bCommDisplay)
//			{
//				sMsg.Format("[MES]OobSetInfo->OK:SN-%s,OOB_FLAG-%s",m_strBarSerial,CurrentSet.strOobFlag);
//				AddStringToStatus(sMsg);
//			}
//
//			return 1;
//		}
//		else 
//		{
//			sMsg.Format("[MES]OobSetInfo->NG");
//			AddStringToStatus(sMsg);
//			return 2;
//		}
//
//	//	m_pConn->CommitTrans();
//		return TRUE;
//	}
//	//����ó��
//	catch (_com_error &e) 
//	{
//		//sString.LoadString(IDS_MES_MSG6);
//		//strRtn.Format(sString);
//		//strRtn.Format("�����Ϸ� ó���� �����Ͽ����ϴ�!\n");
//		//-
//		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//		if(CurrentSet.bCommDisplay)
//		{
//			sMsg.Format("[MES]OobSetInfo(%s:%s):Fail ==>\n\r%s", m_strBarSerial,CurrentSet.strOobFlag, strTmp);
//			AddStringToStatus(sMsg);
//		}
//		return 3;
//	}
//	//-
//}


/*
===============================================================================
 �� �� �� : Mes_ComErr_Make()
 ��    �� : MES DB ���� �۾� ������ ������ �߻��ϸ� �׿� ���õ� �����޼����� ���� �Ѱ���.
 �� �� �� : e => ���� ��
			
 �� �� �� : CString type (�����޼����� ��������)
 �� �� �� : 2006.04.04
 �� �� �� : ������(usy79@lge.com)
===============================================================================
*/
CString	CMesDb::Mes_ComErr_Make(_com_error &e)
{
	CString sMsg, errMsg;
	
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());

	errMsg.Format("%08lx : %s\n", e.Error(), e.ErrorMessage());
	sMsg += errMsg;
	errMsg.Format("Source = %s\n", (LPCSTR) bstrSource);
	sMsg += errMsg;
	errMsg.Format("Description =%s", (LPCSTR) bstrDescription);
	sMsg += errMsg;

	return sMsg;
}


/*
===============================================================================
 �� �� �� : Mes_ExcuteSql_Test()
 ��    �� : Sql���� ������
 �� �� �� : strDsn		=> MES DB DSN		default : MESDEV
			strUserID	=> MES DB UserID	�׽�Ʈ�뼭��ID : dft
			strPassWD	=> MES DB PassWD	�׽�Ʈ�뼭��Pass : dft
			strSql		=> Sql Query 		
			strRtn		=> ������� false�� ��� ���� �޼����� ������
 �� �� �� : bool type
 �� �� �� : 2008.01.08
 �� �� �� : ������(usy79@lge.com)
===============================================================================
//*/
//bool CMesDb::Mes_ExcuteSql_Test(CString strDsn, CString strUserID, CString strPassWD, CString strSql, CString &strRtn)
//{
//	CString			strConn, strTmp;
//	//+del kwmoon 080501
////	ADODB::_ConnectionPtr	m_pConn = NULL;
//	ADODB::_CommandPtr		pCmd  = NULL;
//	ADODB::_ParameterPtr	pPara = NULL;
//	ADODB::_RecordPtr		pRec  = NULL;
//	HRESULT			hRst = S_OK;
//
//	CString sString;
//
//
//	//Coinitialize�� �ȵǾ� �ִٸ� �ٽ� �Ѵ�.
//	if(m_bCoInit == false)
//	{
//		if(FAILED(::CoInitialize(NULL))) 
//		{
//			m_bCoInit = false;
////			sString.LoadString(IDS_MES_MSG);
////			strRtn.Format(sString);
//			strRtn.Format("MES Connection failed(1)!");
//
//			return false;
//		}
//		else{
//			m_bCoInit = true;
//		}
//	}
//
//	
//	//DB ����
//	
//	//+add kwmoon 080501
//	if(!m_bDBconnection || m_pConn == NULL)
//	{
//		try
//		{	
//			//+change kwmoon 080501		
//			TESTHR(hRst = m_pConn.CreateInstance(__uuidof(ADODB::Connection)));
//
//			//Oracle DB ���� ���ڿ�
//			strConn = "";
//			strConn = strConn + "Provider=MSDAORA;";
//			strConn = strConn + "Data Source=" + strDsn + ";";
//			
//			//+change kwmoon 080501		
//			TESTHR(m_pConn->Open((_bstr_t)strConn,(_bstr_t)strUserID,(_bstr_t)strPassWD,NULL));
//		}
//
//		//����ó��
//		catch (_com_error &e) 
//		{
//			//������ �����ߴٴ� �޼����� Mes_ComErr_Make�� ���� �����޼����� 
//			//strRtn�� ������ �� false ����
//			strRtn.Format("MES Connection failed(2)!\n");
//			strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//			strRtn += strTmp;
//
//			return false;
//		}
//		//+add kwmoon 080501
//		m_bDBconnection = TRUE;
//		//-
//	}	
//	
//	try
//	{
//		TESTHR(hRst = pCmd.CreateInstance(__uuidof(ADODB::Command)));
//
//		//MDB ���� ���ڿ�
//		pCmd->ActiveConnection = m_pConn;
//
//		pCmd->CommandText = _bstr_t(strSql);
//
//		pCmd->CommandType = ADODB::adCmdText;		
//
//		pRec = pCmd->Execute(NULL, NULL, ADODB::adCmdText);
//
//		return true;
//	}
//
//	//����ó��
//	catch (_com_error &e) 
//	{	
//		strRtn.Format("MES Excute-Sql failed!\n");
//		strTmp.Format("[%s]", (const char*)Mes_ComErr_Make(e));
//		strRtn += strTmp;
//		return false;
//	}
//	//-
//}
//
//CString CMesDb::GetCmd_StepCheck()
//{
//	CString sCmd;
//
//	switch(CurrentSet.nAvnCommandListID)
//	{
//		case CMD_REN_MM2014:
//			sCmd = "MES_SPC_PKG_MM2014.STEP_CHECK";
//			break;
//
//		case CMD_REN_ULC:
//			sCmd = "MES_SPC_PKG_ULC.STEP_CHECK";
//			break;
//
//		case CMD_HMC_HMC:
//		case CMD_GM_BYOM:
//			sCmd = "MES_SPC_PKG.STEP_CHECK";
//			break;
//
//		case CMD_GM_GEN10:
//			sCmd = "MES_SPC_PKG_GEN10.STEP_CHECK";
//			break;
//
//		case CMD_GM_TMU:
//			sCmd = "MES_SPC_PKG_TMU.STEP_CHECK";
//			break;
//
//		case CMD_VW_MIB:
//			sCmd = "MES_SPC_PKG_VWMIB.STEP_CHECK";
//			break;
//
//		default:
//			sCmd = "MES_SPC_PKG.STEP_CHECK";
//	}
//
//	return sCmd;
//}
//
//CString CMesDb::GetCmd_StepComplete()
//{
//	CString sCmd;
//
//	switch(CurrentSet.nAvnCommandListID)
//	{
//		case CMD_REN_MM2014:
//			sCmd = "MES_SPC_PKG_MM2014.STEP_COMPLETE";
//			break;
//
//		case CMD_REN_ULC:
//			sCmd = "MES_SPC_PKG_ULC.STEP_COMPLETE";
//			break;
//
//		case CMD_HMC_HMC:
//		case CMD_GM_BYOM:
//		case CMD_GM_TMU:
//			sCmd = "MES_SPC_PKG.STEP_COMPLETE";
//			break;
//
//		case CMD_GM_GEN10:
//			sCmd = "MES_SPC_PKG_GEN10.STEP_COMPLETE";
//			break;
//
//		case CMD_VW_MIB:
//			sCmd = "MES_SPC_PKG_VWMIB.STEP_COMPLETE";
//			break;
//
//		default:
//			sCmd = "MES_SPC_PKG.STEP_COMPLETE";
//	}
//
//	return sCmd;
//}
//
//void CMesDb::AddStringToStatus(CString sMsg)
//{
//	m_strMessage = sMsg;
//}
////
////CString CMesDb::GetCmd_MasterInsert()
////{
////	CString sCmd;
////
////	switch(CurrentSet.nAvnCommandListID)
////	{
////		case CMD_REN_MM2014:
////			sCmd = "MES_SPC_PKG_MM2014.MASTER_INSERT";
////			break;
////
////		case CMD_REN_ULC:
////			sCmd = "MES_SPC_PKG_ULC.MASTER_INSERT";
////			break;
////
////		case CMD_HMC_HMC:
////		case CMD_GM_BYOM:
////			sCmd = "MES_SPC_PKG.MASTER_INSERT";
////			break;
////
////		case CMD_GM_TMU:
////			sCmd = "MES_SPC_PKG_TMU.MASTER_INSERT";
////			break;
////
////		case CMD_VW_MIB:
////			sCmd = "MES_SPC_PKG_VWMIB.MASTER_INSERT";
////			break;
////
////		default:
////			sCmd = "MES_SPC_PKG.MASTER_INSERT";
////	}
////
////	return sCmd;
////}
////
////CString CMesDb::GetCmd_DetailInsert()
////{
////	CString sCmd;
////
////	switch(CurrentSet.nAvnCommandListID)
////	{
////		case CMD_REN_MM2014:
////			sCmd = "MES_SPC_PKG_MM2014.DETAIL_INSERT";
////			break;
////
////		case CMD_REN_ULC:
////			sCmd = "MES_SPC_PKG_ULC.DETAIL_INSERT";
////			break;
////
////		case CMD_HMC_HMC:
////		case CMD_GM_BYOM:
////			sCmd = "MES_SPC_PKG.DETAIL_INSERT";
////			break;
////
////		case CMD_GM_TMU:
////			sCmd = "MES_SPC_PKG_TMU.DETAIL_INSERT";
////			break;
////
////		case CMD_VW_MIB:
////			sCmd = "MES_SPC_PKG_VWMIB.DETAIL_INSERT";
////			break;
////
////		default:
////			sCmd = "MES_SPC_PKG.DETAIL_INSERT";
////	}
////
////	return sCmd;
////}
////CString CMesDb::GetCmd_KeyInfoWip()
////{
////	CString sCmd;
////
////	switch(CurrentSet.nAvnCommandListID)
////	{
////		case CMD_REN_MM2014:
////			sCmd = "MES_SPC_PKG_MM2014.ULC_GET_KEY_INFO_WIP";
////			break;
////
////		case CMD_REN_ULC:
////			sCmd = "MES_SPC_PKG_ULC.ULC_GET_KEY_INFO_WIP";
////			break;
////
////		case CMD_HMC_HMC:
////		case CMD_GM_BYOM:
////			sCmd = "";
////			break;
////
////		case CMD_GM_TMU:
////			sCmd = "MES_SPC_PKG_TMU.TMU_GET_KEY_INFO_WIP";
////			break;
////
////		case CMD_VW_MIB:
////			sCmd = "MES_SPC_PKG_VWMIB.VWMIB_GET_KEY_INFO_WIP";
////			break;
////
////		default:
////			sCmd = "";
////	}
////
////	return sCmd;
////}
////
////CString CMesDb::GetCmd_KeyInfoSerial()
////{
////	CString sCmd;
////
////	switch(CurrentSet.nAvnCommandListID)
////	{
////		case CMD_REN_MM2014:
////			sCmd = "MES_SPC_PKG_MM2014.ULC_GET_KEY_INFO_SERIAL";
////			break;
////
////		case CMD_REN_ULC:
////			sCmd = "MES_SPC_PKG_ULC.ULC_GET_KEY_INFO_SERIAL";
////			break;
////
////		case CMD_HMC_HMC:
////		case CMD_GM_BYOM:
////			sCmd = "";
////			break;
////
////		case CMD_GM_TMU:
////			sCmd = "MES_SPC_PKG_TMU.TMU_GET_KEY_INFO_SERIAL";
////			break;
////
////		case CMD_VW_MIB:
////			sCmd = "MES_SPC_PKG_VWMIB.VWMIB_GET_KEY_INFO_SERIAL";
////			break;
////
////		default:
////			sCmd = "";
////	}
////
////	return sCmd;
////}
////
////CString CMesDb::GetCmd_KeyInfoWip2()
////{
////	CString sCmd;
////
////	switch(CurrentSet.nAvnCommandListID)
////	{
////		case CMD_REN_MM2014:
////			sCmd = "MES_SPC_PKG_MM2014.ULC_GET_KEY_INFO_WIP_2";
////			break;
////
////		case CMD_REN_ULC:
////			sCmd = "MES_SPC_PKG_ULC.ULC_GET_KEY_INFO_WIP_2";
////			break;
////
////		case CMD_VW_MIB:
////		case CMD_HMC_HMC:
////		case CMD_GM_BYOM:
////			sCmd = "";
////			break;
////
////		case CMD_GM_TMU:
////			sCmd = "MES_SPC_PKG_TMU.TMU_GET_KEY_INFO_WIP2";
////			break;
////
////		default:
////			sCmd = "";
////	}
////
////	return sCmd;
////}
////CString CMesDb::GetCmd_KeyInfoSerial2()
////{
////	CString sCmd;
////
////	switch(CurrentSet.nAvnCommandListID)
////	{
////		case CMD_REN_MM2014:
////			sCmd = "MES_SPC_PKG_MM2014.ULC_GET_KEY_INFO_SERIAL_2";
////			break;
////
////		case CMD_REN_ULC:
////			sCmd = "MES_SPC_PKG_ULC.ULC_GET_KEY_INFO_SERIAL_2";
////			break;
////
////		case CMD_HMC_HMC:
////		case CMD_GM_BYOM:
////		case CMD_GM_TMU:
////		case CMD_VW_MIB:
////			sCmd = "";
////			break;
////
////		default:
////			sCmd = "";
////	}
////
////	return sCmd;
////}
////CString CMesDb::GetCmd_OobGetInfo()
////{
////	CString sCmd;
////
////	switch(CurrentSet.nAvnCommandListID)
////	{
////		case CMD_REN_MM2014:
////			sCmd = "MES_SPC_PKG_MM2014.ULC_OOB_GET_INFO";
////			break;
////
////		case CMD_REN_ULC:
////			sCmd = "MES_SPC_PKG_ULC.ULC_OOB_GET_INFO";
////			break;
////
////		case CMD_HMC_HMC:
////		case CMD_GM_BYOM:
////		case CMD_GM_TMU:
////		case CMD_VW_MIB:
////			sCmd = "";
////			break;
////
////		default:
////			sCmd = "";
////	}
////
////	return sCmd;
////}
////CString CMesDb::GetCmd_OobSetInfo()
////{
////	CString sCmd;
////
////	switch(CurrentSet.nAvnCommandListID)
////	{
////		case CMD_REN_MM2014:
////			sCmd = "MES_SPC_PKG_MM2014.ULC_OOB_SET_INFO";
////			break;
////
////		case CMD_REN_ULC:
////			sCmd = "MES_SPC_PKG_ULC.ULC_OOB_SET_INFO";
////			break;
////
////		case CMD_HMC_HMC:
////		case CMD_GM_BYOM:
////		case CMD_GM_TMU:
////		case CMD_VW_MIB:
////			sCmd = "";
////			break;
////
////		default:
////			sCmd = "";
////	}
////
////	return sCmd;
////}
//
#endif