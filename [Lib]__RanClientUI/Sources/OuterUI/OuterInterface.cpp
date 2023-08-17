#include "pch.h"
#include "OuterInterface.h"
#include "GameTextControl.h"
#include "../[Lib]__Engine/Sources/DxTools/DxFontMan.h"
#include "UITextControl.h"
#include "../[Lib]__EngineUI/Sources/BasicTextBox.h"

#include "RANPARAM.h"
#include "SelectServerPage.h"
#include "SelectChinaAreaPage.h"
#include "LoginPage.h"
#include "PassKeyboard.h"
#include "SelectCharacterPage.h"
#include "SelectCharacterLeftPage.h"
#include "CreateCharacterPage.h"
#include "DxGlobalStage.h"
#include "ModalWindow.h"
#include "WaitDialogue.h"
#include "CreateCharacterWeb.h"
#include "CommonWeb.h"
#include "SecPassSetPage.h"
#include "SecPassCheckPage.h"
#include "MessageWindow.h"
#include "NewCreateCharPage.h"
#include "../[Lib]__Engine/Sources/Common/SubPath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

COuterInterface& COuterInterface::GetInstance()
{
	static COuterInterface Instance;
	return Instance;
}

const	float	COuterInterface::fLIST_LINE_INTERVAL = 5.0f;

CBasicScrollBarEx* g_pScrollBar = NULL;

COuterInterface::COuterInterface ()	:
	m_bUseWaitTime ( FALSE ),
	m_bBlockProgramFound ( false ),
	m_nServerGroup ( 0 ),
	m_nServerChannel ( 0 ),
	m_bCHANNEL ( false ),
	m_bLoginCancel( FALSE ),
	m_lResolutionBack( 0 ),
	m_uidMoalCallWindow(NO_ID)
{
	ResetControl();
}

COuterInterface::~COuterInterface ()
{
}

void COuterInterface::ResetControl()
{
	m_pModalWindow = NULL;
	m_pSelectServerPage = NULL;
	m_pLoginPage = NULL;
	m_pSecPassSetPage = NULL;
	m_pSecPassCheckPage = NULL;
	m_pMessageWindow = NULL;
	m_pMessageWindowDummy = NULL;
	m_pPassKeyboard = NULL;
	m_pCreateCharacterWeb = NULL;
	m_pSelectCharacterPage = NULL;
	m_pSelectCharacterLeftPage = NULL;
	m_pCreateCharacterPage = NULL;
	m_pFullScreenButton = NULL;
	m_pFullScreenButtonDummy = NULL;
	m_pUpImage = NULL;
	m_pDownImage = NULL;
	m_pNewCreateCharPage = NULL;

	m_pWaitDisplay = NULL;
	m_pDxLobyStage = NULL;
}

HRESULT COuterInterface::OneTimeSceneInit ()
{
	switch ( RANPARAM::emSERVICE_TYPE )
	{
	case EMSERVICE_INDONESIA:
	case EMSERVICE_MALAYSIA_CN:
	case EMSERVICE_MALAYSIA_EN:
	case EMSERVICE_THAILAND:
	case EMSERVICE_PHILIPPINES:
	case EMSERVICE_VIETNAM:
	case EMSERVICE_DEFAULT:
		CLoginPage::nLIMIT_ID = 14;
		CLoginPage::nLIMIT_PW = 14;
		m_bCHANNEL = true;
		break;
	case EMSERVICE_FEYA:
		CLoginPage::nLIMIT_ID = 20;
		CLoginPage::nLIMIT_PW = 20;
		m_bCHANNEL = true;
		break;
	case EMSERVICE_KOREA:
		CLoginPage::nLIMIT_ID = 12;
		CLoginPage::nLIMIT_PW = 12;
		m_bCHANNEL = true;
		break;
	case EMSERVICE_CHINA:
		CLoginPage::nLIMIT_ID = 12;
		CLoginPage::nLIMIT_PW = 19;
		m_bCHANNEL = true;
		break;

	case EMSERVICE_JAPAN:
		CLoginPage::nLIMIT_ID = 16;
		CLoginPage::nLIMIT_PW = 16;
		m_bCHANNEL = true;
		break;

	case EMSERVICE_GLOBAL:
		CLoginPage::nLIMIT_ID = 20;
		CLoginPage::nLIMIT_PW = 20;
		m_bCHANNEL = true;
		break;

	default:
		CLoginPage::nLIMIT_ID = 12;
		CLoginPage::nLIMIT_PW = 12;
		m_bCHANNEL = false;
		break;
	};

	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_FLAG );

	{
		m_pSelectServerPage = new CSelectServerPage;
		m_pSelectServerPage->CreateEx ( SELECT_SERVER_PAGE, "OUTER_WINDOW" );
		m_pSelectServerPage->CreateBaseWidnow ( "SELECT_SERVER_PAGE", (char*) ID2GAMEWORD ( "SELECT_SERVER" ) );
		m_pSelectServerPage->CreateSubControl ();
		m_pSelectServerPage->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pSelectServerPage );	
		ShowGroupFocus ( SELECT_SERVER_PAGE );
	}

	{
		m_pLoginPage = new CLoginPage;
		m_pLoginPage->CreateEx ( LOGIN_PAGE, "OUTER_WINDOW" );
		m_pLoginPage->CreateBaseWidnow ( "LOGIN_PAGE", (char*) ID2GAMEWORD ( "LOGIN_PAGE" ) );
		m_pLoginPage->CreateSubControl ();
		m_pLoginPage->SetAlignFlag ( UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		RegisterControl ( m_pLoginPage );
		ShowGroupFocus ( LOGIN_PAGE );
	}

	{
		m_pMessageWindow = new CMessageWindow;
		m_pMessageWindow->Create ( MESSAGE_WINDOW, "BASIC_MESSAGE_DISPLAY", UI_FLAG_CENTER_X );
		m_pMessageWindow->CreateSubControl ();
		RegisterControl ( m_pMessageWindow );
		ShowGroupTop ( MESSAGE_WINDOW );
		HideGroup ( MESSAGE_WINDOW );

		m_pMessageWindowDummy = new CUIControl;
		m_pMessageWindowDummy->Create ( MESSAGE_WINDOW_DUMMY, "BASIC_MESSAGE_DISPLAY", UI_FLAG_CENTER_X );
        RegisterControl ( m_pMessageWindowDummy );
	}

	{
		m_pPassKeyboard = new CPassKeyboard;
		m_pPassKeyboard->Create( PASS_KEYBOARD, "PASS_KEYBOARD", UI_FLAG_CENTER_X );
		m_pPassKeyboard->CreateSubControl();
		RegisterControl( m_pPassKeyboard );
		ShowGroupFocus( PASS_KEYBOARD );
	}

	{
		m_pSelectCharacterPage = new CSelectCharacterPage;
		m_pSelectCharacterPage->Create ( SELECT_CHARACTER_PAGE, "SELECT_CHARACTER_PAGE" );
		m_pSelectCharacterPage->CreateSubControl ();
		m_pSelectCharacterPage->SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		RegisterControl ( m_pSelectCharacterPage );
		ShowGroupFocus ( SELECT_CHARACTER_PAGE );

		m_pSelectCharacterLeftPage = new CSelectCharacterLeftPage;
		m_pSelectCharacterLeftPage->Create ( SELECT_CHARACTER_LEFTPAGE, "SELECT_CHARACTER_LEFTPAGE" );
		m_pSelectCharacterLeftPage->CreateSubControl ();
		m_pSelectCharacterLeftPage->SetAlignFlag ( UI_FLAG_YSIZE );
		RegisterControl ( m_pSelectCharacterLeftPage );
		ShowGroupFocus ( SELECT_CHARACTER_LEFTPAGE );
	}

	{
		m_pNewCreateCharPage = new CNewCreateCharPage;
		m_pNewCreateCharPage->Create ( CREATE_CHARACTER_PAGE, "NEW_CREATE_CHAR_PAGE", UI_FLAG_DEFAULT );
		m_pNewCreateCharPage->CreateSubControl ();
		RegisterControl ( m_pNewCreateCharPage );
		ShowGroupFocus ( CREATE_CHARACTER_PAGE );
		HideGroup ( CREATE_CHARACTER_PAGE );
		
	}

	{
		m_pModalWindow = new CModalWindow;
		m_pModalWindow->Create ( MODAL_WINDOW_OUTER, "BASIC_MODAL_WINDOW", UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		m_pModalWindow->CreateSubControl ();
		RegisterControl ( m_pModalWindow );
		ShowGroupFocus ( MODAL_WINDOW_OUTER );
	}

	{
		m_pUpImage = new CUIControl;
		m_pUpImage->Create ( OUTER_UP_IMAGE, "OUTER_UP_IMAGE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );		
		RegisterControl ( m_pUpImage );
		ShowGroupBottom ( OUTER_UP_IMAGE );

		m_pDownImage = new CUIControl;
		m_pDownImage ->Create ( OUTER_DN_IMAGE, "OUTER_DN_IMAGE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		RegisterControl ( m_pDownImage  );
		ShowGroupBottom ( OUTER_DN_IMAGE );

		{
			CBasicTextBox* pTextBox = new CBasicTextBox;
			pTextBox->Create ( COPYRIGHT, "COPYRIGHT", UI_FLAG_XSIZE | UI_FLAG_BOTTOM );
			pTextBox->SetFont ( pFont9 );
			pTextBox->SetTextAlign ( TEXT_ALIGN_CENTER_X );
			pTextBox->SetLineInterval ( fLIST_LINE_INTERVAL );
			RegisterControl ( pTextBox );		
			pTextBox->AddText ( ID2GAMEWORD ( "COPYRIGHT_TITLE" ) );
			pTextBox->AddText ( ID2GAMEWORD ( "COPYRIGHT_COMPANY" ) );
			ShowGroupBottom ( COPYRIGHT );
		}
	}

	{
		m_pFullScreenButton = new CUIControl;
		m_pFullScreenButton->Create ( FULLSCREEN_OUTER, "FULLSCREEN_OUTER", UI_FLAG_RIGHT );
		RegisterControl ( m_pFullScreenButton );
		ShowGroupTop ( FULLSCREEN_OUTER );

		m_pFullScreenButtonDummy = new CUIControl;
		m_pFullScreenButtonDummy->Create ( FULLSCREEN_OUTER_DUMMY, "FULLSCREEN_OUTER", UI_FLAG_RIGHT );
		m_pFullScreenButtonDummy->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pFullScreenButtonDummy );
	}

	{		
		m_pWaitDisplay = new CWaitDialogue;
		m_pWaitDisplay->Create ( WAIT_DISPLAY, "WAITSERVER_DISPLAY", UI_FLAG_CENTER_X | UI_FLAG_CENTER_Y );
		m_pWaitDisplay->CreateSubControl ();
		RegisterControl ( m_pWaitDisplay );
		ShowGroupFocus ( WAIT_DISPLAY );
	}

	CloseAllWindow ();
	ShowGroupFocus(SELECT_SERVER_PAGE);

	return S_OK;
}

HRESULT COuterInterface::FrameMove ( LPDIRECT3DDEVICEQ pd3dDevice, float fElapsedTime )
{
	ResetOnTheInterface ();

	bool bFULLSCREEN = RANPARAM::bScrWindowed && RANPARAM::bScrWndHalfSize;
	if ( bFULLSCREEN )	ShowGroupTop ( FULLSCREEN_OUTER );
	else				HideGroup ( FULLSCREEN_OUTER );

	if ( IsVisibleGroup ( FULLSCREEN_OUTER ) )
	{
		const UIRECT& rcGlobalPos = m_pFullScreenButtonDummy->GetGlobalPos ();
		m_pFullScreenButton->SetGlobalPos ( D3DXVECTOR2(rcGlobalPos.left,rcGlobalPos.top) );
	}

	HRESULT hr;
	hr = CUIMan::FrameMove ( pd3dDevice, fElapsedTime );
	if ( FAILED ( hr ) ) return hr;

	//	TIME UPDATE
	UPDATE_WAIT_TIME ( fElapsedTime );

	CNetClient* pNetClient = DxGlobalStage::GetInstance().GetNetClient ();
	if ( !pNetClient->IsOnline() )		//��Ʈ��ũ ������ ������ ���
	{
		if ( !COuterInterface::GetInstance().IsVisibleGroup ( MODAL_WINDOW_OUTER ) )
		{
			if( !IsLoginCancel() )
			{
				DoModalOuter ( ID2GAMEEXTEXT ("CHARACTERSTAGE_2"), MODAL_INFOMATION, OK, OUTER_MODAL_CONNECTCLOSED );
			}
			else
			{
				if ( DxGlobalStage::GetInstance().GetNetClient()->ConnectLoginServer(RANPARAM::LoginAddress) > NET_ERROR )
				{
					DxGlobalStage::GetInstance().GetNetClient()->SndReqServerInfo();				
				}
				else
				{
					DoModalOuter( ID2GAMEEXTEXT ( "SERVERSTAGE_3" ), MODAL_INFOMATION, OKCANCEL, OUTER_MODAL_CLOSEGAME );
				}
			}
		}
	}

	if ( IsBlockProgramFound() )
	{
		DoModalOuter ( ID2GAMEINTEXT("BLOCK_PROGRAM_FOUND"), MODAL_INFOMATION, OK, OUTER_MODAL_CLOSEGAME );
	}

	if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU ) & DXKEY_PRESSED )
	{
		if ( DxInputDevice::GetInstance().GetKeyState ( DIK_F4 ) & DXKEY_DOWN )
		{
			DoModalOuter ( ID2GAMEINTEXT("CLOSE_GAME"), MODAL_QUESTION, OKCANCEL, OUTER_MODAL_CLOSEGAME );
		}
	}

	if ( IsVisibleGroup ( SELECT_CHARACTER_PAGE ) )
	{
		CUIFocusContainer::UICONTROL_FOCUSLIST focus_list = GetFocusList()->GetFocusList();
		CUIFocusContainer::UICONTROL_FOCUSLIST_RITER riter = focus_list.rbegin ();
		CUIFocusContainer::UICONTROL_FOCUSLIST_RITER riter_end = focus_list.rend ();

		bool bLeftPageShow = false;
		for ( ; riter != riter_end; ++riter )
		{
			UIGUID cID = riter->cID;
			if ( SELECT_CHARACTER_PAGE == cID )
			{
				if ( bLeftPageShow )
				{
					GetFocusList()->InsertAfter ( SELECT_CHARACTER_LEFTPAGE, SELECT_CHARACTER_PAGE, riter->pUIControl );
				}
				break;
			}
			else if ( SELECT_CHARACTER_LEFTPAGE == cID )
			{
				bLeftPageShow = true;
			}
		}
	}

	{
		// Note : ���Ʒ� ���� ũ�⸦ �����Ѵ�. 
		LONG lResolution = CUIMan::GetResolution ();

		//if( m_lResolutionBack != lResolution )
		{
			WORD X_RES = HIWORD( lResolution );
			WORD Y_RES = LOWORD( lResolution );

			INT nHeight = static_cast<INT>(Y_RES * 0.1f);
			INT nTop = Y_RES - nHeight;

			if ( m_pUpImage && m_pDownImage )
			{
				m_pUpImage->SetGlobalPos( UIRECT( 0, 0, (float)X_RES, (float)nHeight ) );
				m_pDownImage->SetGlobalPos( UIRECT( 0, (float)nTop, (float)X_RES, (float)nHeight ) );
			}

			// Note : ĳ���� ����, ���� �������� ��ġ�� �����Ѵ�.
			UIRECT rcLocalPos;

			if( m_pSelectCharacterLeftPage->IsVisible() )
			{
				rcLocalPos = m_pSelectCharacterLeftPage->GetLocalPos();
				rcLocalPos.top = nTop - rcLocalPos.sizeY - 6.0f;
				m_pSelectCharacterLeftPage->SetGlobalPos( rcLocalPos );
			}

			if( m_pSelectCharacterPage->IsVisible() )
			{
				rcLocalPos = m_pSelectCharacterPage->GetLocalPos();
				rcLocalPos.left = X_RES - rcLocalPos.sizeX - 6.0f;
				rcLocalPos.top = nTop - rcLocalPos.sizeY - 6.0f;
				m_pSelectCharacterPage->SetGlobalPos( rcLocalPos );
			}

			if( m_pCreateCharacterPage && m_pCreateCharacterPage->IsVisible() )
			{
				rcLocalPos = m_pCreateCharacterPage->GetLocalPos();
				rcLocalPos.left = X_RES - rcLocalPos.sizeX - 6.0f;
				rcLocalPos.top = nTop - rcLocalPos.sizeY - 6.0f;
				m_pCreateCharacterPage->SetGlobalPos( rcLocalPos );
			}

			if( m_pNewCreateCharPage && m_pNewCreateCharPage->IsVisible() )
			{
				UIRECT rcGlobalPosNew, rcGlobalPosOld;
				rcLocalPos = m_pNewCreateCharPage->GetLocalPos();


				LONG lResolutionBack = COuterInterface::GetInstance().GetResolutionBack ();
				WORD X_RES_BACK = HIWORD( lResolutionBack );
				WORD Y_RES_BACK = LOWORD( lResolutionBack );

				if ( X_RES_BACK != X_RES || Y_RES_BACK != Y_RES )
				{		

					rcGlobalPosOld.left = 0;								
					rcGlobalPosOld.top = 0;
					rcGlobalPosOld.right = X_RES_BACK;
					rcGlobalPosOld.bottom = Y_RES_BACK;
					rcGlobalPosOld.sizeX = X_RES_BACK;
					rcGlobalPosOld.sizeY = Y_RES_BACK;

					rcGlobalPosNew.left = 0;			
					rcGlobalPosNew.right = X_RES;
					rcGlobalPosNew.sizeX = X_RES;
					rcGlobalPosNew.top = 0;
					rcGlobalPosNew.bottom = Y_RES;
					rcGlobalPosNew.sizeY = Y_RES;

					m_pNewCreateCharPage->ReSizeControl( rcGlobalPosOld, rcGlobalPosNew );

					COuterInterface::GetInstance().SetResolutionBack ( MAKELONG(Y_RES, X_RES) );
				}
				

			}

			if( m_pCreateCharacterWeb && m_pCreateCharacterWeb->IsVisible() )
			{
				rcLocalPos = m_pCreateCharacterWeb->GetLocalPos();
				rcLocalPos.left = X_RES - rcLocalPos.sizeX - 6.0f;
				rcLocalPos.top = nTop - rcLocalPos.sizeY - 167.0f;
				m_pCreateCharacterWeb->SetGlobalPos( rcLocalPos );
				m_pCreateCharacterWeb->AlignWeb();
			}

			// Note : �н����� Ű������ ��ġ�� �����Ѵ�.
			if( m_pPassKeyboard->IsVisible() )
			{
				rcLocalPos = m_pPassKeyboard->GetGlobalPos();
				if ( m_pLoginPage->IsVisible() )
					rcLocalPos.top = m_pLoginPage->GetGlobalPos().bottom + 13.0f;

				m_pPassKeyboard->SetGlobalPos( rcLocalPos );
			}
		}
	}

	return S_OK;
}

HRESULT COuterInterface::DeleteDeviceObjects()
{
	ResetControl();
	return CUIMan::DeleteDeviceObjects ();
}

// �߱� MMOSPEED
// �߱� ��Ʈ��ũ üũ ���α׷� ����
void COuterInterface::RunMMOSpeed()
{
	CString str;
	str.Format ( "%s\\%s", SUBPATH::APP_ROOT, "mmospeed.exe");
	
	CString strCmd;
	std::string strUserID = RANPARAM::GETUSERID_DEC();

	// UserID, ���� �ĺ���ȣ, ������ȣ
	strCmd.Format( "%s %d %d", strUserID.c_str(), 1, RANPARAM::nChinaRegion+1 );

	int result = (int)ShellExecute( NULL , "open", str.GetString() ,strCmd.GetString(), NULL, SW_SHOW );

	if( result < 32  )
	{
		// ����ó��
		return;
	}
	
	return;
}