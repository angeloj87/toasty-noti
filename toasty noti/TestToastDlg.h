
// TestToastDlg.h : header file
//

#pragma once
#include "wintoastlib.h"


// CTestToastDlg dialog
class CTestToastDlg : public CDialogEx
{
// Construction
public:
    CTestToastDlg(CWnd* pParent = nullptr);    // standard constructor

    class WinToastHandler : public WinToastLib::IWinToastHandler
    {
    public:
        WinToastHandler(CDialogEx* pDialog) : m_pDialog(pDialog) {}
        // Public interfaces
        void toastActivated() const override {
            //m_pDialog->MessageBox(L"toastActivated: No button clicked!", L"info", MB_OK);
        }
        void toastActivated(int actionIndex) const override {
            wchar_t buf[250];
            swprintf_s(buf, L"Button clicked: %d\n", actionIndex);
            OutputDebugStringW(buf);
            m_pDialog->MessageBox(buf, L"info", MB_OK);
        }
        void toastDismissed(WinToastDismissalReason state) const override {
            std::string reason = "Dismissal error!";
            if (state == UserCanceled)
                reason = "Toast dismissed: UserCanceled\n";
            else if (state == ApplicationHidden)
                reason = "Toast dismissed: ApplicationHidden\n";
            else if (state == TimedOut)
                reason = "Toast dismissed: TimedOut\n";
            OutputDebugStringA(reason.c_str());
        }
        void toastFailed() const override {
            OutputDebugStringA("toastFailed() called\n");
        }
    private:
        CDialogEx* m_pDialog;
    };

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_TESTTOAST_DIALOG };
#endif

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnShowToast();
};
