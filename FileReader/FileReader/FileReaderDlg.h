
// FileReaderDlg.h: 헤더 파일
#pragma once
#include "OwnUtility.h"
#include "ItemController.h"

// CFileReaderDlg 대화 상자
class CFileReaderDlg : public CDialogEx
{
// 생성입니다.
public:
	CFileReaderDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEREADER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	enum TOOLBOX_ITEM {
		BUTTON_WRITE,
		BUTTON_SEARCH,
		STATIC_ITEM_NAME,
		EDIT_ITEM_VALUE,
		EDIT_SEARCH_NAME,
		EDIT_ITEM_VALUE_INDEX,
		COMBO_MODE,
		TREE_ITEM_LIST,
		TOOLBOX_ITEM_SIZE
	};
public:
	CTreeCtrl treeItemList;
	CStatic staticItemName;
	CEdit editItemValue;
	CButton buttonWrite;
	CButton buttonLoad;
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnTvnSelchangedTreeItem(NMHDR* pNMHDR, LRESULT* pResult);

	void ControlToolBoxItem(TOOLBOX_ITEM toolbox, bool visible = false, CString value=0);
	void InitializeToolBox(void);
	void SetToolboxItem(TOOLBOX_ITEM toolbox, CString value = 0, HTREEITEM htree = 0);
	string GetToolboxItem(TOOLBOX_ITEM toolbox, HTREEITEM htree = 0);

public:
	void UpdatetoolboxItem(FILE_HANDLER& treeData);
	CComboBox comboMode;
	CEdit editSearchName;
	CButton buttonSearch;
	CEdit editItemValueIdex;
};

