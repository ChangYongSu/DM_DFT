// DlgModelSetup.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "DlgModelSetup.h"
#include "afxdialogex.h"
#include "DlgNewModelName.h"
#include "FileControl.h"
#include "DlgPassword.h"
#include "DlgConfig.h"
#include "DlgReadyCodeSetup.h"


// CDlgModelSetup ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgModelSetup, CDialogEx)

CDlgModelSetup::CDlgModelSetup(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgModelSetup::IDD, pParent)
	//, m_EditSeqData[0](_T(""))
	//, m_CheckPortEn(FALSE)	
	//, m_CheckMesEnable(FALSE)
	//
	//, m_LevelSkip1(FALSE)
	//, m_LevelSkip2(FALSE)
	//, m_LevelSkip3(FALSE)
	//, m_LevelSkip4(FALSE)
{

}

CDlgModelSetup::~CDlgModelSetup()
{
}
