// MainFrm.h : interface of the CLevelMainFrame class
//


#pragma once

#include "CoolDialogBar.h"
#include "ToolBarEx.h"
#include "DlgLevelEdit.h"

class GLGaeaServer;

class CLevelMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CLevelMainFrame();
	DECLARE_DYNCREATE(CLevelMainFrame)

// Attributes
public:
	CString			m_strAppPath;
	char			m_szAppPath[MAX_PATH];

// Operations
public:
	CToolBarWithCombo		m_wndToolBar;
	CDlgLevelEdit			m_DlgLevelEdit;
	CCoolDialogBar			m_wndDialogBar;

private:
	GLGaeaServer* m_pGLGaeaServer;

public:
	GLGaeaServer* GetGLGaeaServer() { return m_pGLGaeaServer; }
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CLevelMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar				m_wndStatusBar;
	//CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEditMenuNone();
	afx_msg void OnEditMenuSelect();
	afx_msg void OnEditMenuMove();
	afx_msg void OnEditMenuRotate();
	afx_msg void OnEditMenuScale();
	afx_msg void OnEditMenuSelectMobsch();
	afx_msg void OnFileToolbarAll90();
	afx_msg void OnFileCamMoveTo();
};


