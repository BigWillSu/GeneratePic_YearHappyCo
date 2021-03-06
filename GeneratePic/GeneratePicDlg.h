
// GeneratePicDlg.h: 头文件
//

#pragma once


// CGeneratePicDlg 对话框
class CPicGenerater;
class CGeneratePicDlg : public CDialogEx
{
// 构造
public:
	CGeneratePicDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GENERATEPIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};

class CPicGenerater
{
public:
	CPicGenerater();
	virtual ~CPicGenerater();

	int OpenBackgroundPic(char* filename, int mono = 0);
	int OutputGeneraterPic(char* filename);
	void ShowPic(string title);
	int RenderText(string Text, int x, int y);
protected:
	Mat image;//图像数据矩阵
};