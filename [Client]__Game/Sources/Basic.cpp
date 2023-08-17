#define STRICT
#include "pch.h"
//#include <vld.h> // vld.h ��������� stdafx.h ������ ��ġ�ؾ� �մϴ�.

#include "SUBPATH.h"
#include "StringUtils.h"
#include "../[Lib]__EngineUI/Sources/Cursor.h"

#include "RANPARAM.h"
#include "dxparamset.h"

#include "Basic.h"
#include "BasicWnd.h"
#include "gassert.h"
#include "getdxver.h"

#include "DaumGameParameter.h"
#include "../[Lib]__RanClientUI/Sources/TextUI/GameTextControl.h"
#include "../[Lib]__MfcEx/Sources/MinBugTrap.h"

#include <afxdisp.h>

#include "Protection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CBasicApp

DO_RTC_CATCH _rtc_catch;

BEGIN_MESSAGE_MAP(CBasicApp, CWinApp)
	//{{AFX_MSG_MAP(CBasicApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBasicApp construction

CBasicApp::CBasicApp() :
	m_bIsActive(TRUE),
	m_bRedrawScreen(FALSE),
	m_bShutDown(FALSE)
{	
	BUG_TRAP::BugTrapInstall( std::string(_T("Game")));

	RANPARAM::emSERVICE_TYPE = EMSERVICE_KOREA;
	SecureZeroMemory( m_szAppPath, sizeof(m_szAppPath) );
}

CBasicApp::~CBasicApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBasicApp object

CBasicApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBasicApp initialization

BOOL CBasicApp::InitInstance()
{
	AfxEnableControlContainer();

	// Note : ���������� ��θ� ã�Ƽ� �����Ѵ�. - �ݵ�� CBasicWnd(CD3dApp) ������ �����ؾ� �Ѵ�.
	//
	SetAppPath();

	RANPARAM::LOAD ( m_szAppPath );
	DXPARAMSET::INIT ();

	CString StrCmdLine = m_lpCmdLine;

	STRUTIL::ClearSeparator ();
	STRUTIL::RegisterSeparator ( "/" );
	STRUTIL::RegisterSeparator ( " " );

	BOOL bAPM = FALSE;
	CString strCommand = CString("app") + "_" + "run";

	CStringArray strCmdArray;
	STRUTIL::StringSeparate ( StrCmdLine, strCmdArray );
	
	for ( int i=0; i<strCmdArray.GetCount(); i++ )
	{
		CString strTemp = strCmdArray.GetAt(i);

		if ( strTemp == strCommand )
		{
			bAPM = TRUE;
		}

		if ( strTemp == _T("windowed") )
		{
			RANPARAM::bScrWndHalfSize = TRUE;
			RANPARAM::bScrWndFullSize = FALSE;
		}

		CString strVALUE;
		int nPos(-1);
		CString strKEY;

		strKEY = "TID:";
		nPos = strTemp.Find( strKEY );
		if ( nPos!=-1 )
		{
			strVALUE = strTemp.Right ( strTemp.GetLength()-strKEY.GetLength() );

			//	�� ����.
			RANPARAM::SETIDPARAM ( strVALUE.GetString() );
			
			//	userid�� ���Ƿ� ����. ( ���� �ɼ� �����. )
			RANPARAM::SETUSERID ( "userid" );
		}

		strKEY = "U=";
		nPos = strTemp.Find( strKEY );
		if ( nPos!=-1 )
		{
			strVALUE = strTemp.Right ( strTemp.GetLength()-strKEY.GetLength() );

			//	�� ����.
			RANPARAM::SETIDPARAM ( strVALUE.GetString() );
			
			//	userid�� ���Ƿ� ����. ( ���� �ɼ� �����. )
			RANPARAM::SETUSERID ( "userid" );
		}

		strKEY = "UUID=";
		nPos = strTemp.Find( strKEY );
		if ( nPos!=-1 )
		{
			strVALUE = strTemp.Right ( strTemp.GetLength()-strKEY.GetLength() );

			//	�� ����.
			RANPARAM::SETIDPARAM ( strVALUE.GetString() );

			//	userid�� ���Ƿ� ����. ( ���� �ɼ� �����. )
			RANPARAM::SETUSERID ( "userid" );
		}

		strKEY = "T=";
		nPos = strTemp.Find( strKEY );
		if ( nPos!=-1 )
		{
			strVALUE = strTemp.Right ( strTemp.GetLength()-strKEY.GetLength() );

			//	�� ����.
			RANPARAM::SETIDPARAM2 ( strVALUE.GetString() );
		}

		strKEY = "MD=";
		nPos = strTemp.Find( strKEY );
		if ( nPos!=-1 )
		{
			strVALUE = strTemp.Right ( strTemp.GetLength()-strKEY.GetLength() );

			//	�� ����.
			RANPARAM::SETIDPARAM3 ( strVALUE.GetString() );
		}
	}

	//	Note : ���α����̰� cmd line param ���� ���޵Ǵ� ���� ���� ���.
	//		���� ��Ȯ�ϰ� ����Ǿ� �ִ��� üũ.
	if( RANPARAM::emSERVICE_TYPE==EMSERVICE_MALAYSIA_CN || 
		RANPARAM::emSERVICE_TYPE==EMSERVICE_MALAYSIA_EN ||
//		RANPARAM::emSERVICE_TYPE==EMSERVICE_JAPAN ||	// JAPAN �α��� ��� ����
		RANPARAM::emSERVICE_TYPE==EMSERVICE_PHILIPPINES ||
		RANPARAM::emSERVICE_TYPE==EMSERVICE_VIETNAM )
	{
		if ( !RANPARAM::VALIDIDPARAM() )
		{
			MessageBox ( NULL, "Invalid web account.", "error", MB_OK );
			return FALSE;
		}
	}

	// geger009 | Bypass execution parameter
	bAPM = TRUE;

	#if defined(NDEBUG)
	if ( !bAPM )
	{
		MessageBox ( NULL, "This Exe don't execute independent.", "error", MB_OK );
		return FALSE;
	}
	#endif // !NDEBUG

    DWORD dwDirectXVersion = 0;
    TCHAR strDirectXVersion[10];
	HRESULT hr = getdxversion ( &dwDirectXVersion, strDirectXVersion, 10 );

	if ( hr==S_OK && dwDirectXVersion<0x00090003 )
	{
		MessageBox ( NULL, "DirectX Version too old. must install DirectX 9.0c", "error", MB_OK );
		return FALSE;
	}

	{	// Note : �������̽� ��ų �ؽ�Ʈ �ε�
		TCHAR szFullPath[MAX_PATH] = {0};

		StringCchCopy( szFullPath, MAX_PATH, ((CBasicApp*)AfxGetApp())->m_szAppPath );
		StringCchCat( szFullPath, MAX_PATH, SUBPATH::GUI_FILE_ROOT);
		CGameTextMan::GetInstance().SetPath(szFullPath);

		CGameTextMan::GetInstance().LoadText(RANPARAM::strGameWord.GetString(), CGameTextMan::EM_GAME_WORD, RANPARAM::bXML_USE );
		CGameTextMan::GetInstance().LoadText(RANPARAM::strGameInText.GetString(), CGameTextMan::EM_GAME_IN_TEXT, RANPARAM::bXML_USE );
		CGameTextMan::GetInstance().LoadText(RANPARAM::strGameExText.GetString(), CGameTextMan::EM_GAME_EX_TEXT, RANPARAM::bXML_USE );
	}

	CBasicWnd* pWnd = new CBasicWnd();
	if ( pWnd->Create() == FALSE )	return FALSE;

	m_pWnd = pWnd;

	return TRUE;
}


void CBasicApp::SetAppPath()
{
	CString strAppPath;

	TCHAR szPath[MAX_PATH] = {0};
	GetModuleFileName(::AfxGetInstanceHandle(), szPath, MAX_PATH);
	strAppPath = szPath;

	if ( !strAppPath.IsEmpty() )
	{
		DWORD dwFind = strAppPath.ReverseFind ( '\\' );
		if ( dwFind != -1 )
		{
			m_strAppPath = strAppPath.Left ( dwFind );
			
			if ( !m_strAppPath.IsEmpty() )
			if ( m_strAppPath.GetAt(0) == '"' )
				m_strAppPath = m_strAppPath.Right ( m_strAppPath.GetLength()-1 );

			StringCchCopy ( m_szAppPath, MAX_PATH, m_strAppPath.GetString() );
		}
	}
	else 
	{
		MessageBox ( NULL, "SetAppPath Error", "Error", MB_OK );
		return;
	}
}

/////////////////////////////////////////////////////////////////////////////

int CBasicApp::ExitInstance() 
{
	m_pWnd = NULL;

	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////

int CBasicApp::Run() 
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE );

	CProtection& cProtection = CProtection::GetInstance();

	cProtection.Init();

	while( WM_QUIT != msg.message )
	{

#if defined(NDEBUG)	
		// software breakpoint check
		if (cProtection.Pesudo_IsDebuggerPresent())	
		{
			m_pWnd->PostMessage ( WM_CLOSE, 0, 0 );
		}

		// hardware breakpoint check
		GetThreadContext(GetCurrentThread(), &cProtection.CONTEXTDebug);	
		if ( cProtection.CONTEXTDebug.Dr0 || cProtection.CONTEXTDebug.Dr1 ||
			 cProtection.CONTEXTDebug.Dr2 || cProtection.CONTEXTDebug.Dr3 )	
		{
			m_pWnd->PostMessage ( WM_CLOSE, 0, 0 );
		}
#endif


		if ( m_bShutDown == TRUE || m_pWnd == NULL )
		{
			ExitInstance ();
			return 0;
		}
		
		
		if( m_bIsActive )
			bGotMsg = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );
		else
			bGotMsg = GetMessage( &msg, NULL, 0, 0 );

		if( bGotMsg )
		{
			TranslateMessage (&msg);
			DispatchMessage (&msg);

			if ( !m_bIsActive && !m_bShutDown )
			{
				if ( FAILED ( m_pWnd->FrameMove3DEnvironment() ) )
					m_pWnd->PostMessage ( WM_CLOSE, 0, 0 );
			}
		}
		else
		{
			if ( m_bIsActive )
			{
				if ( FAILED ( m_pWnd->Render3DEnvironment() ) )
					m_pWnd->PostMessage ( WM_CLOSE, 0, 0 );
			}
		}		
	}

	ExitInstance ();
	return static_cast<int>(msg.wParam);
}

void CBasicApp::SetActive ( BOOL bActive )
{
	m_bIsActive = bActive;
	m_bRedrawScreen = bActive;
}