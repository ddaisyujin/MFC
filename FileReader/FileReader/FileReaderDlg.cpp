
// FileReaderDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "FileReader.h"
#include "FileReaderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CFileReaderDlg::CFileReaderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEREADER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_ITEM, treeItemList);
	DDX_Control(pDX, IDC_STATIC_ITEM_NAME, staticItemName);
	DDX_Control(pDX, IDC_EDIT_ITEM_VALUE, editItemValue);
	DDX_Control(pDX, IDC_BUTTON_WRITE, buttonWrite);
	DDX_Control(pDX, IDC_BUTTON_LOAD, buttonLoad);
	DDX_Control(pDX, IDC_COMBO_MODE, comboMode);
	DDX_Control(pDX, IDC_EDIT_SEARCH_NAME, editSearchName);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, buttonSearch);
	DDX_Control(pDX, IDC_EDIT_ITEM_VALUE_INDEX, editItemValueIdex);
}

BEGIN_MESSAGE_MAP(CFileReaderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CFileReaderDlg::OnBnClickedButtonLoad)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_ITEM, &CFileReaderDlg::OnTvnSelchangedTreeItem)
END_MESSAGE_MAP()


// CFileReaderDlg 메시지 처리기
INFO selectItem;
FILE_HANDLER trees;

BOOL CFileReaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitializeToolBox();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFileReaderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFileReaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFileReaderDlg::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	////BackEnd
	//1. initialize
	treeItemList.DeleteAllItems();
	comboMode.Clear();
	trees.item.clear();
	selectItem.ClearInfo();
	InitializeToolBox();

	//2. Load FileReaderDataFile
	trees.UpdateItemMap();

	//3. Tree에 업데이트
	UpdatetoolboxItem(trees);

	////FrontEnd
	//1. Display
	/*ControlToolBoxItem(BUTTON_WRITE,true);
	ControlToolBoxItem(STATIC_ITEM_NAME, true, L"");
	ControlToolBoxItem(EDIT_ITEM_VALUE, true, L"");*/
}


void CFileReaderDlg::InitializeToolBox(void)
{
	ControlToolBoxItem(BUTTON_WRITE);
	//ControlToolBoxItem(BUTTON_SEARCH);
	ControlToolBoxItem(STATIC_ITEM_NAME);
	ControlToolBoxItem(EDIT_ITEM_VALUE);
	ControlToolBoxItem(EDIT_ITEM_VALUE_INDEX);
	//ControlToolBoxItem(EDIT_SEARCH_NAME);
	//ControlToolBoxItem(COMBO_MODE);
}

void CFileReaderDlg::ControlToolBoxItem(TOOLBOX_ITEM toolbox, bool visible, CString value)
{
	switch (toolbox)
	{
	case BUTTON_WRITE:
		buttonWrite.EnableWindow(visible);
		break;
	case BUTTON_SEARCH:
		buttonSearch.EnableWindow(visible);
		break;
	case STATIC_ITEM_NAME:
		staticItemName.EnableWindow(visible);
		SetToolboxItem(STATIC_ITEM_NAME, value);
		break;
	case EDIT_ITEM_VALUE:
		editItemValue.EnableWindow(visible);
		SetToolboxItem(EDIT_ITEM_VALUE, value);
		break;
	case EDIT_ITEM_VALUE_INDEX:
		editItemValueIdex.EnableWindow(visible);
		SetToolboxItem(EDIT_ITEM_VALUE_INDEX, value);
		break;
	case EDIT_SEARCH_NAME:
		editSearchName.EnableWindow(visible);
		SetToolboxItem(EDIT_SEARCH_NAME, value);
		break;
	case COMBO_MODE:
		comboMode.EnableWindow(visible);
		comboMode.SetCurSel(comboMode.FindString(0, value));
		break;
	default:
		break;
	}
}

void CFileReaderDlg::SetToolboxItem(TOOLBOX_ITEM toolbox, CString value, HTREEITEM htree)
{
	switch (toolbox)
	{
	case TREE_ITEM_LIST:
		// htree 
		break;
	case STATIC_ITEM_NAME:
		staticItemName.SetWindowTextW(value);
		break;
	case EDIT_ITEM_VALUE:
		editItemValue.SetWindowTextW(value);
		break;
	case EDIT_ITEM_VALUE_INDEX:
		editItemValueIdex.SetWindowTextW(value);
		break;
	case EDIT_SEARCH_NAME:
		editSearchName.SetWindowTextW(value);
		break;
	case COMBO_MODE:
		comboMode.AddString(value);
		break;
	default:
		break;
	}
}

string CFileReaderDlg::GetToolboxItem(TOOLBOX_ITEM toolbox, HTREEITEM htree)
{
	string retString = "";
	switch (toolbox)
	{
	case TREE_ITEM_LIST:
	{
		CString curStr = treeItemList.GetItemText(htree);
		CString curWordStr;
		AfxExtractSubString(curWordStr, curStr, 0, ' ');
		retString = CStringToString(curWordStr);
		break;
	}
	case COMBO_MODE:
	{
		CString curStr;
		comboMode.GetDlgItemTextW(comboMode.GetCurSel(), curStr);
		retString = CStringToString(curStr);
		break;
	}
	case EDIT_ITEM_VALUE_INDEX:
	{
		CString curStr;
		editItemValueIdex.GetWindowTextW(curStr);
		retString = CStringToString(curStr);
		break;
	}
	default:
		break;
	}
	return retString;
}

void CFileReaderDlg::UpdatetoolboxItem(FILE_HANDLER& treeData)
{
	HTREEITEM root, modeChild, nameChild;

	root = treeItemList.InsertItem(TEXT("root"), TVI_ROOT, TVI_SORT);

	for (auto& mode : treeData.item)
	{
		modeChild = treeItemList.InsertItem(StringToCString(mode.first), root, TVI_SORT);
		SetToolboxItem(COMBO_MODE, StringToCString(mode.first));
		treeItemList.Expand(treeItemList.GetParentItem(modeChild), TVE_EXPAND);
		for (auto& parameter : mode.second)
		{
			string strName = parameter.first;
			string strValues = "";
			for (auto value : parameter.second)
			{
				strValues += " | " + value;
			}
			nameChild = treeItemList.InsertItem(StringToCString(strName + strValues), modeChild, TVI_SORT);
		}
	}
}

void CFileReaderDlg::OnTvnSelchangedTreeItem(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	HTREEITEM curItemName = treeItemList.GetSelectedItem();
	HTREEITEM curItemMode = treeItemList.GetParentItem(curItemName);
	string curItemModeStr = GetToolboxItem(TREE_ITEM_LIST, curItemMode);
	string curItemNameStr = GetToolboxItem(TREE_ITEM_LIST, curItemName);

	////BackEnd
	//1. selectItem instance Update
	if ((!(curItemModeStr.empty())&& (curItemModeStr!="root")) && !(curItemNameStr.empty()))
	{
		selectItem.mode = curItemModeStr;
		selectItem.name = curItemNameStr;
		selectItem.value.addr = &(trees.item[selectItem.mode][selectItem.name][0]);
		selectItem.value.size = (int)(trees.item[selectItem.mode][selectItem.name].size());
		selectItem.hItem = curItemName;

		////FrontEnd
		//1. Display
		ControlToolBoxItem(STATIC_ITEM_NAME, true, StringToCString(selectItem.name));
		ControlToolBoxItem(COMBO_MODE, true, StringToCString(selectItem.mode));
		ControlToolBoxItem(EDIT_ITEM_VALUE, true, StringToCString(*(selectItem.value.addr)));
		ControlToolBoxItem(EDIT_SEARCH_NAME, true, StringToCString(selectItem.name));
		ControlToolBoxItem(BUTTON_SEARCH, true);
		if (selectItem.value.size > 1)
		{
			ControlToolBoxItem(EDIT_ITEM_VALUE_INDEX, true, StringToCString("0"));
		}
		else
		{
			ControlToolBoxItem(EDIT_ITEM_VALUE_INDEX);
		}
	}
	else
	{
		InitializeToolBox();
	}

	*pResult = 0;
}
