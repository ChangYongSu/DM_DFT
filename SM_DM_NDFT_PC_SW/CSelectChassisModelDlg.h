#pragma once



#include "ListCtrlEx.h"

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
//// SelectChassisModelDlg.h : header file
//
#define CHASSIS_GRID	0
#define MODEL_GRID		1

// CSelectChassisModelDlg 대화 상자

class CSelectChassisModelDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectChassisModelDlg)

public:
	CSelectChassisModelDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelectChassisModelDlg();


	//CString	m_szCurrentSeqFilePath;
	//CString	m_szModelInfoFilePath;
	//CString	m_szRefImgFolder;
	//CString	m_szSeqFilePath;
	//CString	m_szCurrentRefFilePath;
	////}}AFX_DATA

	int		m_nNoModel;
	CString m_sSelChassis;
	CString m_sSelModel;
	int		m_nChaassis_SelectRow;
	int		m_nModel_SelectRow;
	int		m_nDivision_Sel;

	void	InitGrid();
	void	UpdateGrid();
	BOOL	IsSameChassis(CString szChassisName);
	void	ChangeRowColor(int nRow, int nGridType);
	BOOL	CheckModel(CString sChassis, CString sModel);



// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELECT_CHASSIS_MODEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	void OnClickChassisGrid();
	void OnClickModelGrid();

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_szCurrentSeqFilePath;
	CString m_szModelInfoFilePath;
	CString m_szRefImgFolder;
	CString m_szSeqFilePath;
	CString m_szCurrentRefFilePath;
	CListCtrl m_cListChassis;
	CListCtrl m_cListModel;

	//CListCtrlEx		m_cListChassisEx;
	//CListCtrlEx		m_cListModelEx;


	CComboBox m_ctrlComboDivision;
	afx_msg void OnCbnSelchangeComboDivision();
	afx_msg void OnNMClickListChassis(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListChassis(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListModel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListModel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
