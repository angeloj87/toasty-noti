
// TestToastDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TestToast.h"
#include "TestToastDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace WinToastLib;



// CTestToastDlg dialog



CTestToastDlg::CTestToastDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_TESTTOAST_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}

void CTestToastDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestToastDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_SHOW_TOAST, &CTestToastDlg::OnBnClickedBtnShowToast)
END_MESSAGE_MAP()


// CTestToastDlg message handlers

BOOL CTestToastDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);            // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    // TODO: Add extra initialization here
    WinToast::WinToastError error;
    WinToast::instance()->setAppName(L"TestToastExample");
    const auto aumi = WinToast::configureAUMI(L"company", L"wintoast", L"wintoastexample", L"20201012");
    WinToast::instance()->setAppUserModelId(aumi);

    if (!WinToast::instance()->initialize(&error)) {
        wchar_t buf[250];
        swprintf_s(buf, L"Failed to initialize WinToast :%d", error);
        MessageBox(buf, L"Error");
    }

    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestToastDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestToastDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



void CTestToastDlg::OnBnClickedBtnShowToast()
{
    TCHAR path[_MAX_PATH];
    GetModuleFileName(NULL, path, _countof(path));
    std::wstring pathString = path;
    auto pos = pathString.find_last_of(L'\\');
    if (pos != std::wstring::npos)
        pathString = pathString.substr(0, pos + 1);

    WinToastTemplate templ;
    if (WinToast::isWin10AnniversaryOrHigher())
    {
        templ = WinToastTemplate(WinToastTemplate::HeroImageAndImageAndText02);
        bool inlineImage = false;
        templ.setHeroImagePath(pathString + L"hero.jpg", inlineImage);
    }
    else
    {
        templ = WinToastTemplate(WinToastTemplate::ImageAndText02);
    }
    templ.setImagePath(
        pathString + L"gal.jpg",
        WinToastTemplate::CropHint::Circle);

    templ.setTextField(L"My First Toast", WinToastTemplate::FirstLine);
    templ.setTextField(L"Say Hello?", WinToastTemplate::SecondLine);

    templ.addAction(L"Yes");
    templ.addAction(L"No");

    templ.setDuration(WinToastTemplate::Duration::Short);
    templ.setAudioOption(WinToastTemplate::AudioOption::Default);
    templ.setAudioPath(WinToastTemplate::AudioSystemFile::Call1);

    if (WinToast::instance()->showToast(templ, new WinToastHandler(this)) == -1L)
    {
        MessageBox(L"Could not launch your toast notification!", L"Error");
    }
}
