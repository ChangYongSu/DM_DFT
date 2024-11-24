// COptMesPage.cpp: 구현 파일
//

#include "stdafx.h"
#include "AcqVoltageSamples_IntClk.h"
#include "AcqVoltageSamples_IntClkDlg.h"
#include "COptMesPage.h"


// COptMesPage
IMPLEMENT_DYNCREATE(COptMesPage, CPropertyPage)

COptMesPage::COptMesPage() : CPropertyPage(COptMesPage::IDD)
{
	//{{AFX_DATA_INIT(COptMesPage)

	//}}AFX_DATA_INIT
}

COptMesPage::~COptMesPage()
{
}

void COptMesPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptGrabberPage)

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptMesPage, CPropertyPage)
	//{{AFX_MSG_MAP(COptGrabberPage)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void COptMesPage::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	//OnBtnApply();

	CPropertyPage::OnOK();
}

//
//IMPLEMENT_DYNAMIC(COptMesPage, CMFCPropertyPage)
//
//COptMesPage::COptMesPage()
//{
//
//}
//
//COptMesPage::~COptMesPage()
//{
//}
//
//
//BEGIN_MESSAGE_MAP(COptMesPage, CMFCPropertyPage)
//END_MESSAGE_MAP()
//
//
//
//// COptMesPage 메시지 처리기


