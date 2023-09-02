
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
		BUTTON_LOAD,
		BUTTON_WRITE,
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

	void ControlToolBoxItem(TOOLBOX_ITEM toolbox, bool visible = false);
	void SetToolboxItem(TOOLBOX_ITEM toolbox, CString value = 0, HTREEITEM htree = 0);
	string GetToolboxItem(TOOLBOX_ITEM toolbox);

public:
	void UpdatetoolboxItem(FILE_HANDLER& treeData);
	afx_msg void OnTvnSelchangedTreeItem(NMHDR* pNMHDR, LRESULT* pResult);
};

