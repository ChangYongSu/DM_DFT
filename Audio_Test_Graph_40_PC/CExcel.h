#pragma once
#include <afxtempl.h>
#include "CApplication.h"
//#include "CPicture.h"
//#include "CPictures.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CShape.h"
#include "CShapes.h"

class CExcel
{

public :
	CExcel();

	
	CApplication app;
	CWorkbooks books;
    CWorkbook book;

    CWorksheets sheets;
    CWorksheet sheet;
    CRange range;
    CRange cols;


	COleVariant covTrue;
	COleVariant covFalse;
	COleVariant covOptional;

protected:
	//���� init�Ϸ����� üũ �ϴ� ����
	bool bInit;

public:
	LPCTSTR m_FileName;

	//���� ����
	BOOL InitExcel( LPCTSTR defname ,LPCTSTR saveName);

	//���� ����
	BOOL CloseExcel(BOOL bVisible, BOOL bSave);

	//��Ʈ �߰�
	BOOL AddSheet(LPCTSTR name);

	//��Ʈ ����
	BOOL SelectSheet( short nSheet );

	//���� �� �Է�
	//�� �ϳ��� �Է�
	BOOL SetCellValue( COleVariant cell, COleVariant value );

	//�迭 �Է�
	BOOL SetCellArray( char* cell_1, char* cell_2, COleVariant value );
	BOOL SetCellArray( char* cell_1, char* cell_2, COleSafeArray arr );

	//���� ���� �Է½� COleSafeArray�� �� �Է� �ϴ� �뵵
	void FillSafeArray(OLECHAR FAR* sz, int iRow, int iCol, COleSafeArray* sa);


	//�̹��� ����
	BOOL InsertImage( LPCTSTR FileName , COleVariant cell_1,  COleVariant cell_2 );

};
