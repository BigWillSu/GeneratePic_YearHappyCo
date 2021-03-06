
// GeneratePicDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "GeneratePic.h"
#include "GeneratePicDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TEXT_START_X	L"520"
#define TEXT_START_Y	L"636"
#define	TEXT_SPACING	L"75"

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGeneratePicDlg 对话框



CGeneratePicDlg::CGeneratePicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GENERATEPIC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGeneratePicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGeneratePicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGeneratePicDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CGeneratePicDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CGeneratePicDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGeneratePicDlg 消息处理程序

BOOL CGeneratePicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	GetDlgItem(IDC_EDIT_POSITION_X)->SetWindowText(TEXT_START_X);
	GetDlgItem(IDC_EDIT_POSITION_Y)->SetWindowText(TEXT_START_Y);
	GetDlgItem(IDC_EDIT_SPACING)->SetWindowText(TEXT_SPACING);

	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGeneratePicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGeneratePicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGeneratePicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

std::wstring	utf8_to_unicode(const std::string& str) {
	std::wstring result;
	int size = ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), 0, 0);
	if (size <= 0) {
		return result;
	}

	result.assign(size, 0);
	::MultiByteToWideChar(CP_UTF8, NULL, str.data(), str.size(), (wchar_t*)result.data(), size);
	return result;
}

std::string		unicode_to_utf8(const std::wstring& str) {
	std::string result;
	int size = ::WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), str.size(), NULL, 0, NULL, NULL);
	if (size <= 0) {
		return result;
	}

	result.assign(size, 0);
	::WideCharToMultiByte(CP_UTF8, NULL, str.data(), str.size(), (char*)result.data(), size, NULL, NULL);
	return result;
}

void CGeneratePicDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	CString csPricePerfect = L"";
	CString csPriceNice = L"";
	CString csPriceGood = L"";
	CString csTextStart_X = L"";
	CString csTextStart_Y = L"";
	CString csTextSpacing = L"";

	GetDlgItem(IDC_EDIT_PERFECT)->GetWindowText(csPricePerfect);
	GetDlgItem(IDC_EDIT_NICE)->GetWindowText(csPriceNice);
	GetDlgItem(IDC_EDIT_GOOD)->GetWindowText(csPriceGood);
	if (csPricePerfect.IsEmpty() || csPriceNice.IsEmpty() || csPriceGood.IsEmpty())
	{
		AfxMessageBox(L"价格不可以为空");
		return;
	}
	string sPricePerfect = unicode_to_utf8(csPricePerfect.GetBuffer(csPricePerfect.GetLength()));
	string sPriceNice = unicode_to_utf8(csPriceNice.GetBuffer(csPriceNice.GetLength()));
	string sPriceGood = unicode_to_utf8(csPriceGood.GetBuffer(csPriceGood.GetLength()));
	csPricePerfect.ReleaseBuffer();
	csPriceNice.ReleaseBuffer();
	csPriceGood.ReleaseBuffer();

	GetDlgItem(IDC_EDIT_POSITION_X)->GetWindowText(csTextStart_X);
	GetDlgItem(IDC_EDIT_POSITION_Y)->GetWindowText(csTextStart_Y);
	GetDlgItem(IDC_EDIT_SPACING)->GetWindowText(csTextSpacing);

	int nStartX = _ttoi(csTextStart_X);
	int nStartY = _ttoi(csTextStart_Y);
	int nSpacing = _ttoi(csTextSpacing);

	CPicGenerater* pGenerater = new CPicGenerater();
	if (pGenerater->OpenBackgroundPic("backgroundpic.jpg"))
	{	
		int textHeight = pGenerater->RenderText(sPricePerfect, nStartX, nStartY);
		pGenerater->RenderText(sPriceNice, nStartX, nStartY + nSpacing + textHeight);
		pGenerater->RenderText(sPriceGood, nStartX, nStartY + (nSpacing + textHeight) *2);
		COleDateTime tmCurTime;
		tmCurTime = COleDateTime::GetCurrentTime();
		CString strDate = tmCurTime.Format(L"%Y%m%d%H%M%S");
		CString csFileName = L"Price_" + strDate;
		csFileName += L".jpg";

		CString csPath = L".//PricePic//" + csFileName;
	    ::CreateDirectory(L".//PricePic//", NULL);
		if (pGenerater->OutputGeneraterPic((char *)unicode_to_utf8(csPath.GetBuffer(csPath.GetLength())).c_str()))
		{
			CString msg = L"";
			msg.Format(L"价格图片成功生成到：%s", csPath);
			AfxMessageBox(msg);
		}
		else
		{
			AfxMessageBox(L"图片生成失败,错误码:100");
		}
	}
	else
	{
		AfxMessageBox(L"图片生成失败,错误码:101");
	}
	delete pGenerater;
	CDialogEx::OnOK();
}

/////////////////////////////////////////////////////



CPicGenerater::CPicGenerater()
{

}

CPicGenerater::~CPicGenerater()
{

}

int CPicGenerater::OpenBackgroundPic(char* filename, int mono )
{
	image = imread(filename, (mono == 1) ? 0 : 1);
	if (image.empty())
	{
		cerr << "LoadPic: " << filename << "error" << endl;
		return 0;
	}

	return 1;
}

int CPicGenerater::OutputGeneraterPic(char* filename)
{
	bool ret = imwrite(filename, image);
	if (!ret)
	{
		cerr << "Write to  file" << filename << "Failed";
		return 0;
	}

	return 1;
}

void CPicGenerater::ShowPic(string title)
{
	imshow(title, image);
	waitKey(0);
}

int CPicGenerater::RenderText(string Text,int x, int y)
{
	std::string watermarkText = Text;
	int font_face = cv::FONT_HERSHEY_DUPLEX;
	double font_scale = 2;
	int thickness = 4;
	int baseline;
	cv::Size text_size = cv::getTextSize(watermarkText, font_face, font_scale, thickness, &baseline);
	cv::Point origin;
	origin.x = x - text_size.width;//image.cols / 4 - text_size.width / 2;
	origin.y = y;//image.rows / 4 + text_size.height / 2;

	// 添加文本
	putText(image, watermarkText, origin, FONT_HERSHEY_DUPLEX, font_scale, cv::Scalar(0, 0, 230), LINE_4,true);
	//flip(image, image, -1);
	return text_size.height;
}


void CGeneratePicDlg::OnBnClickedButton2()
{
	GetDlgItem(IDC_EDIT_POSITION_X)->SetWindowText(TEXT_START_X);
	GetDlgItem(IDC_EDIT_POSITION_Y)->SetWindowText(TEXT_START_Y);
	GetDlgItem(IDC_EDIT_SPACING)->SetWindowText(TEXT_SPACING);

	UpdateData(FALSE);
}


void CGeneratePicDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	CString csPricePerfect = L"";
	CString csPriceNice = L"";
	CString csPriceGood = L"";
	CString csTextStart_X = L"";
	CString csTextStart_Y = L"";
	CString csTextSpacing = L"";

	GetDlgItem(IDC_EDIT_PERFECT)->GetWindowText(csPricePerfect);
	GetDlgItem(IDC_EDIT_NICE)->GetWindowText(csPriceNice);
	GetDlgItem(IDC_EDIT_GOOD)->GetWindowText(csPriceGood);
	if (csPricePerfect.IsEmpty() || csPriceNice.IsEmpty() || csPriceGood.IsEmpty())
	{
		AfxMessageBox(L"价格不可以为空");
		return;
	}
	string sPricePerfect = unicode_to_utf8(csPricePerfect.GetBuffer(csPricePerfect.GetLength()));
	string sPriceNice = unicode_to_utf8(csPriceNice.GetBuffer(csPriceNice.GetLength()));
	string sPriceGood = unicode_to_utf8(csPriceGood.GetBuffer(csPriceGood.GetLength()));
	csPricePerfect.ReleaseBuffer();
	csPriceNice.ReleaseBuffer();
	csPriceGood.ReleaseBuffer();

	GetDlgItem(IDC_EDIT_POSITION_X)->GetWindowText(csTextStart_X);
	GetDlgItem(IDC_EDIT_POSITION_Y)->GetWindowText(csTextStart_Y);
	GetDlgItem(IDC_EDIT_SPACING)->GetWindowText(csTextSpacing);

	int nStartX = _ttoi(csTextStart_X);
	int nStartY = _ttoi(csTextStart_Y);
	int nSpacing = _ttoi(csTextSpacing);

	CPicGenerater* pGenerater = new CPicGenerater();
	if (pGenerater->OpenBackgroundPic("backgroundpic.jpg"))
	{
		int textHeight = pGenerater->RenderText(sPricePerfect, nStartX, nStartY);
		pGenerater->RenderText(sPriceNice, nStartX, nStartY + nSpacing + textHeight);
		pGenerater->RenderText(sPriceGood, nStartX, nStartY + (nSpacing + textHeight) * 2);
		pGenerater->ShowPic("Preview");
	}
	delete pGenerater;
}
