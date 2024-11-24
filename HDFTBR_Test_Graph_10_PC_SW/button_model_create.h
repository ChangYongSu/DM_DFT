#pragma once

// ��ǻ�Ϳ��� Microsoft Visual C++�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// ����: �� ������ ������ �������� ���ʽÿ�. Microsoft Visual C++����
//  �� Ŭ������ �ٽ� ������ �� ������ ������ ����ϴ�.

/////////////////////////////////////////////////////////////////////////////
// CButton_Ctrl ���� Ŭ�����Դϴ�.

class CButton_Ctrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CButton_Ctrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xD7053240, 0xCE69, 0x11CD, { 0xA7, 0x77, 0x0, 0xDD, 0x1, 0x14, 0x3C, 0x57 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Ư���Դϴ�.
public:
enum
{
    fmDropEffectNone = 0,
    fmDropEffectCopy = 1,
    fmDropEffectMove = 2,
    fmDropEffectCopyOrMove = 3
}fmDropEffect;
enum
{
    fmActionCut = 0,
    fmActionCopy = 1,
    fmActionPaste = 2,
    fmActionDragDrop = 3
}fmAction;
enum
{
    fmModeInherit = -2,
    fmModeOn = -1,
    fmModeOff = 0
}fmMode;
enum
{
    fmMousePointerDefault = 0,
    fmMousePointerArrow = 1,
    fmMousePointerCross = 2,
    fmMousePointerIBeam = 3,
    fmMousePointerSizeNESW = 6,
    fmMousePointerSizeNS = 7,
    fmMousePointerSizeNWSE = 8,
    fmMousePointerSizeWE = 9,
    fmMousePointerUpArrow = 10,
    fmMousePointerHourGlass = 11,
    fmMousePointerNoDrop = 12,
    fmMousePointerAppStarting = 13,
    fmMousePointerHelp = 14,
    fmMousePointerSizeAll = 15,
    fmMousePointerCustom = 99
}fmMousePointer;
enum
{
    fmScrollBarsNone = 0,
    fmScrollBarsHorizontal = 1,
    fmScrollBarsVertical = 2,
    fmScrollBarsBoth = 3
}fmScrollBars;
enum
{
    fmScrollActionNoChange = 0,
    fmScrollActionLineUp = 1,
    fmScrollActionLineDown = 2,
    fmScrollActionPageUp = 3,
    fmScrollActionPageDown = 4,
    fmScrollActionBegin = 5,
    fmScrollActionEnd = 6,
    _fmScrollActionAbsoluteChange = 7,
    fmScrollActionPropertyChange = 8,
    fmScrollActionControlRequest = 9,
    fmScrollActionFocusRequest = 10
}fmScrollAction;
enum
{
    fmCycleAllForms = 0,
    fmCycleCurrentForm = 2
}fmCycle;
enum
{
    fmZOrderFront = 0,
    fmZOrderBack = 1
}fmZOrder;
enum
{
    fmBorderStyleNone = 0,
    fmBorderStyleSingle = 1
}fmBorderStyle;
enum
{
    fmTextAlignLeft = 1,
    fmTextAlignCenter = 2,
    fmTextAlignRight = 3
}fmTextAlign;
enum
{
    fmAlignmentLeft = 0,
    fmAlignmentRight = 1
}fmAlignment;
enum
{
    fmBordersNone = 0,
    fmBordersBox = 1,
    fmBordersLeft = 2,
    fmBordersTop = 3
}fmBorders;
enum
{
    fmBackStyleTransparent = 0,
    fmBackStyleOpaque = 1
}fmBackStyle;
enum
{
    fmButtonStylePushButton = 0,
    fmButtonStyleToggleButton = 1
}fmButtonStyle;
enum
{
    fmPicPositionCenter = 0,
    fmPicPositionTopLeft = 1,
    fmPicPositionTopCenter = 2,
    fmPicPositionTopRight = 3,
    fmPicPositionCenterLeft = 4,
    fmPicPositionCenterRight = 5,
    fmPicPositionBottomLeft = 6,
    fmPicPositionBottomCenter = 7,
    fmPicPositionBottomRight = 8
}fmPicPosition;
enum
{
    fmVerticalScrollBarSideRight = 0,
    fmVerticalScrollBarSideLeft = 1
}fmVerticalScrollBarSide;
enum
{
    fmLayoutEffectNone = 0,
    fmLayoutEffectInitiate = 1,
    _fmLayoutEffectRespond = 2
}fmLayoutEffect;
enum
{
    fmSpecialEffectFlat = 0,
    fmSpecialEffectRaised = 1,
    fmSpecialEffectSunken = 2,
    fmSpecialEffectEtched = 3,
    fmSpecialEffectBump = 6
}fmSpecialEffect;
enum
{
    fmDragStateEnter = 0,
    fmDragStateLeave = 1,
    fmDragStateOver = 2
}fmDragState;
enum
{
    fmPictureSizeModeClip = 0,
    fmPictureSizeModeStretch = 1,
    fmPictureSizeModeZoom = 3
}fmPictureSizeMode;
enum
{
    fmPictureAlignmentTopLeft = 0,
    fmPictureAlignmentTopRight = 1,
    fmPictureAlignmentCenter = 2,
    fmPictureAlignmentBottomLeft = 3,
    fmPictureAlignmentBottomRight = 4
}fmPictureAlignment;
enum
{
    fmButtonEffectFlat = 0,
    fmButtonEffectSunken = 2
}fmButtonEffect;
enum
{
    fmOrientationAuto = -1,
    fmOrientationVertical = 0,
    fmOrientationHorizontal = 1
}fmOrientation;
enum
{
    fmSnapPointTopLeft = 0,
    fmSnapPointTopCenter = 1,
    fmSnapPointTopRight = 2,
    fmSnapPointCenterLeft = 3,
    fmSnapPointCenter = 4,
    fmSnapPointCenterRight = 5,
    fmSnapPointBottomLeft = 6,
    fmSnapPointBottomCenter = 7,
    fmSnapPointBottomRight = 8
}fmSnapPoint;
enum
{
    fmPicturePositionLeftTop = 0,
    fmPicturePositionLeftCenter = 1,
    fmPicturePositionLeftBottom = 2,
    fmPicturePositionRightTop = 3,
    fmPicturePositionRightCenter = 4,
    fmPicturePositionRightBottom = 5,
    fmPicturePositionAboveLeft = 6,
    fmPicturePositionAboveCenter = 7,
    fmPicturePositionAboveRight = 8,
    fmPicturePositionBelowLeft = 9,
    fmPicturePositionBelowCenter = 10,
    fmPicturePositionBelowRight = 11,
    fmPicturePositionCenter = 12
}fmPicturePosition;
enum
{
    fmDisplayStyleText = 1,
    fmDisplayStyleList = 2,
    fmDisplayStyleCombo = 3,
    fmDisplayStyleCheckBox = 4,
    fmDisplayStyleOptionButton = 5,
    fmDisplayStyleToggle = 6,
    fmDisplayStyleDropList = 7
}fmDisplayStyle;
enum
{
    fmShowListWhenNever = 0,
    fmShowListWhenButton = 1,
    fmShowListWhenFocus = 2,
    fmShowListWhenAlways = 3
}fmShowListWhen;
enum
{
    fmShowDropButtonWhenNever = 0,
    fmShowDropButtonWhenFocus = 1,
    fmShowDropButtonWhenAlways = 2
}fmShowDropButtonWhen;
enum
{
    fmMultiSelectSingle = 0,
    fmMultiSelectMulti = 1,
    fmMultiSelectExtended = 2
}fmMultiSelect;
enum
{
    fmListStylePlain = 0,
    fmListStyleOption = 1
}fmListStyle;
enum
{
    fmEnterFieldBehaviorSelectAll = 0,
    fmEnterFieldBehaviorRecallSelection = 1
}fmEnterFieldBehavior;
enum
{
    fmDragBehaviorDisabled = 0,
    fmDragBehaviorEnabled = 1
}fmDragBehavior;
enum
{
    fmMatchEntryFirstLetter = 0,
    fmMatchEntryComplete = 1,
    fmMatchEntryNone = 2
}fmMatchEntry;
enum
{
    fmDropButtonStylePlain = 0,
    fmDropButtonStyleArrow = 1,
    fmDropButtonStyleEllipsis = 2,
    fmDropButtonStyleReduce = 3
}fmDropButtonStyle;
enum
{
    fmStyleDropDownCombo = 0,
    fmStyleDropDownList = 2
}fmStyle;
enum
{
    fmTabOrientationTop = 0,
    fmTabOrientationBottom = 1,
    fmTabOrientationLeft = 2,
    fmTabOrientationRight = 3
}fmTabOrientation;
enum
{
    fmTabStyleTabs = 0,
    fmTabStyleButtons = 1,
    fmTabStyleNone = 2
}fmTabStyle;
enum
{
    fmIMEModeNoControl = 0,
    fmIMEModeOn = 1,
    fmIMEModeOff = 2,
    fmIMEModeDisable = 3,
    fmIMEModeHiragana = 4,
    fmIMEModeKatakana = 5,
    fmIMEModeKatakanaHalf = 6,
    fmIMEModeAlphaFull = 7,
    fmIMEModeAlpha = 8,
    fmIMEModeHangulFull = 9,
    fmIMEModeHangul = 10,
    fmIMEModeHanziFull = 11,
    fmIMEModeHanzi = 12
}fmIMEMode;
enum
{
    fmTransitionEffectNone = 0,
    fmTransitionEffectCoverUp = 1,
    fmTransitionEffectCoverRightUp = 2,
    fmTransitionEffectCoverRight = 3,
    fmTransitionEffectCoverRightDown = 4,
    fmTransitionEffectCoverDown = 5,
    fmTransitionEffectCoverLeftDown = 6,
    fmTransitionEffectCoverLeft = 7,
    fmTransitionEffectCoverLeftUp = 8,
    fmTransitionEffectPushUp = 9,
    fmTransitionEffectPushRight = 10,
    fmTransitionEffectPushDown = 11,
    fmTransitionEffectPushLeft = 12
}fmTransitionEffect;
enum
{
    _fmListBoxStylesNone = 0,
    _fmListBoxStylesListBox = 1,
    _fmListBoxStylesComboBox = 2
}fmListBoxStyles;
enum
{
    _fmRepeatDirectionHorizontal = 0,
    _fmRepeatDirectionVertical = 1
}fmRepeatDirection;
enum
{
    _fmEnAutoSizeNone = 0,
    _fmEnAutoSizeHorizontal = 1,
    _fmEnAutoSizeVertical = 2,
    _fmEnAutoSizeBoth = 3
}fmEnAutoSize;


// �۾��Դϴ�.
public:

// ICommandButton

// Functions
//

	void put_AutoSize(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(DISPID_AUTOSIZE, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AutoSize()
	{
		BOOL result;
		InvokeHelper(DISPID_AUTOSIZE, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_BackColor(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BackColor()
	{
		long result;
		InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_BackStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(DISPID_BACKSTYLE, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BackStyle()
	{
		long result;
		InvokeHelper(DISPID_BACKSTYLE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Caption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(DISPID_CAPTION, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Caption()
	{
		CString result;
		InvokeHelper(DISPID_CAPTION, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Enabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Enabled()
	{
		BOOL result;
		InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put__Font_Reserved(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x7ffffdff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void putref_Font(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Font()
	{
		LPDISPATCH result;
		InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_FontBold(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_FontBold()
	{
		BOOL result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_FontItalic(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_FontItalic()
	{
		BOOL result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_FontName(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_FontName()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_FontSize(CY newValue)
	{
		static BYTE parms[] = VTS_CY ;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	CY get_FontSize()
	{
		CY result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
		return result;
	}
	void put_FontStrikethru(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_FontStrikethru()
	{
		BOOL result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_FontUnderline(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_FontUnderline()
	{
		BOOL result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ForeColor(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ForeColor()
	{
		long result;
		InvokeHelper(DISPID_FORECOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_TakeFocusOnClick(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_TakeFocusOnClick()
	{
		BOOL result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Locked(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Locked()
	{
		BOOL result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_MouseIcon(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0xfffffdf6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void putref_MouseIcon(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0xfffffdf6, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_MouseIcon()
	{
		LPDISPATCH result;
		InvokeHelper(0xfffffdf6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_MousePointer(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xfffffdf7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MousePointer()
	{
		long result;
		InvokeHelper(0xfffffdf7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Picture(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0xfffffdf5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void putref_Picture(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0xfffffdf5, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Picture()
	{
		LPDISPATCH result;
		InvokeHelper(0xfffffdf5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_PicturePosition(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_PicturePosition()
	{
		long result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Accelerator(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xfffffde1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Accelerator()
	{
		CString result;
		InvokeHelper(0xfffffde1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_WordWrap(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xfffffde8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_WordWrap()
	{
		BOOL result;
		InvokeHelper(0xfffffde8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Value(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Value()
	{
		BOOL result;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_FontWeight(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_FontWeight()
	{
		short result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}

// Properties
//



};
