//////////////////////////////////////////////////////
// Engine.cpp
//////////////////////////////////////////////////////

#include "engine.h"

//////////////////////////////////////////////////////
// CEngine()
//////////////////////////////////////////////////////
CEngine::CEngine(void)
{
	m_pBackground = new CSprite(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pSubTitle = new CSprite(SUBTITLE_WIDTH, SUBTITLE_HEIGHT);
	m_pMainTitle = new CBallSprite(MAINTITLE_WIDTH, MAINTITLE_HEIGHT);
	m_pHumanSprite = new CHumanSprite(BAT_WIDTH, BAT_HEIGHT);
	m_pComputerSprite = new CComputerSprite(BAT_WIDTH, BAT_HEIGHT);
	m_pBallSprite = new CBallSprite(BALL_WIDTH, BALL_HEIGHT);
	m_iPlayerScore = 0;
	m_iComputerScore = 0;
	m_iCounter = 0;
	m_iComputerLevel = WINDOW_WIDTH / 2;
	m_GameState = CEngine::GS_LOADING;
	srand((unsigned)time(NULL));

	m_pBackground->SetPosition(0,0);
	m_pBackground->CalculateVertices();
	m_pMainTitle->SetPosition(170, 100);
	m_pMainTitle->SetXVelocity(1.0f);
	m_pMainTitle->SetYVelocity(1.0f);
	m_pMainTitle->CalculateVertices();
	m_pSubTitle->SetPosition(170, 275);
	m_pSubTitle->CalculateVertices();
}

//////////////////////////////////////////////////////
// ~CEngine()
//////////////////////////////////////////////////////
CEngine::~CEngine(void)
{
	CleanUp();
}

//////////////////////////////////////////////////////
// CleanUp()
//////////////////////////////////////////////////////
void CEngine::CleanUp(void)
{
	delete m_pBackground;
	delete m_pSubTitle;
	delete m_pMainTitle;
	delete m_pHumanSprite;
	delete m_pComputerSprite;
	delete m_pBallSprite;
}

//////////////////////////////////////////////////////
// SetWindowHandle()
//////////////////////////////////////////////////////
void CEngine::SetWindowHandle(HWND hWnd)
{
    m_hWnd = hWnd;
	m_Direct3D.SetWindowHandle(hWnd);
	m_DirectSound.SetWindowHandle(hWnd);
}

//////////////////////////////////////////////////////
// ProcessGame()
//////////////////////////////////////////////////////
void CEngine::ProcessGame(void)
{
	HRESULT hResult = m_Direct3D.GetDevice()->TestCooperativeLevel();
    if (hResult == D3DERR_DEVICELOST)
        m_bGamePaused = TRUE;
    else if (hResult == D3DERR_DEVICENOTRESET)
    {
        ResetDirect3D();
        m_bGamePaused = FALSE;
    }
    else
    {
        // Perform normal game operation
		switch (m_GameState)
		{
		case CEngine::GS_LOADING:
			HandleLoading();
			break;
		case CEngine::GS_TITLE:
			HandleTitle();
			break;
		case CEngine::GS_NEWGAME:
			HandleNewGame();
			break;
		case CEngine::GS_RUNNING:
			HandleRunning();
			break;
		case CEngine::GS_STOPPED:
			HandleStopped();
			break;
		case CEngine::GS_EXIT:
			PostQuitMessage(WM_QUIT);
			break;
		}
		PaintBackBuffer();
    }
}

//////////////////////////////////////////////////////
// HandleLoading()
//////////////////////////////////////////////////////
void CEngine::HandleLoading(void)
{	
	m_iCounter++;
	if (m_iCounter == LOADING_DELAY)
	{
		m_DirectSound.PlaySound(m_DirectSound.GetSound(m_DirectSound.LOADING));
	}
	if (m_iCounter >= SPLASH_DELAY)
		m_GameState = CEngine::GS_TITLE;
}

//////////////////////////////////////////////////////
// HandleTitle()
//////////////////////////////////////////////////////
void CEngine::HandleTitle(void)
{
	// Move title and bounce it if it hits the top, bottom, or sides
	m_pMainTitle->SetXPosition(m_pMainTitle->GetXPosition() + m_pMainTitle->GetXVelocity());
	m_pMainTitle->SetYPosition(m_pMainTitle->GetYPosition() + m_pMainTitle->GetYVelocity());

	// Hit Top
    if(m_pMainTitle->GetYPosition() < 0)
    {
		m_DirectSound.PlaySound(m_DirectSound.GetSound(m_DirectSound.HITWALL));
        m_pMainTitle->SetYPosition(0);
		m_pMainTitle->SetYVelocity(-(m_pMainTitle->GetYVelocity()));
    }
	// Hit bottom
	else if((m_pMainTitle->GetYPosition() + m_pMainTitle->GetHeight()) > (m_pSubTitle->GetYPosition() - 10))
    {
		m_DirectSound.PlaySound(m_DirectSound.GetSound(m_DirectSound.HITWALL));
        m_pMainTitle->SetYPosition(((m_pSubTitle->GetYPosition() - 10) - m_pMainTitle->GetHeight()));
        m_pMainTitle->SetYVelocity(-(m_pMainTitle->GetYVelocity()));
    }
	// Hit right
	else if(m_pMainTitle->GetXPosition() <= 0)
	{
		m_DirectSound.PlaySound(m_DirectSound.GetSound(m_DirectSound.HITWALL));
		m_pMainTitle->SetXPosition(0);
		m_pMainTitle->SetXVelocity(-(m_pMainTitle->GetXVelocity()));
	}
	// Hit left
	else if(m_pMainTitle->GetXPosition() > (WINDOW_WIDTH - m_pMainTitle->GetWidth()))
	{
		m_DirectSound.PlaySound(m_DirectSound.GetSound(m_DirectSound.HITWALL));
		m_pMainTitle->SetXPosition((float)(WINDOW_WIDTH - m_pMainTitle->GetWidth()));
		m_pMainTitle->SetXVelocity(-(m_pMainTitle->GetXVelocity()));
	}
	m_pMainTitle->CalculateVertices();
}

//////////////////////////////////////////////////////
// HandleNewGame()
//////////////////////////////////////////////////////
void CEngine::HandleNewGame(void)
{
	m_iPlayerScore = 0;
	m_iComputerScore = 0;
	m_iCounter = 0;
	m_iComputerLevel = WINDOW_WIDTH / 2;

	m_pHumanSprite->SetYVelocity(HUMAN_YVEL);
	m_pComputerSprite->SetYVelocity(CMP_YVEL);

	InitGame();
	m_GameState = CEngine::GS_RUNNING;
}

//////////////////////////////////////////////////////
// HandleRunning()
//////////////////////////////////////////////////////
void CEngine::HandleRunning(void)
{	
	// If ball past computer level, update computer position
	if (m_pBallSprite->GetXPosition() > m_iComputerLevel)
		m_pComputerSprite->UpdateSprite(m_pBallSprite->GetYPosition());
	
	// Update ball position
	m_pBallSprite->UpdateSprite(
		m_pHumanSprite->GetXPosition(),
		m_pHumanSprite->GetYPosition(),
		m_pComputerSprite->GetXPosition(),
		m_pComputerSprite->GetYPosition());
	
	// Play impact sounds
	if (m_pBallSprite->GetHitFlag() == m_pBallSprite->HITHUMAN || 
		m_pBallSprite->GetHitFlag() == m_pBallSprite->HITCOMPUTER)
		m_DirectSound.PlaySound(m_DirectSound.GetSound(m_DirectSound.HITBAT));
	if (m_pBallSprite->GetHitFlag() == m_pBallSprite->HITWALL)
		m_DirectSound.PlaySound(m_DirectSound.GetSound(m_DirectSound.HITWALL));

	// Check if player or computer has scored a point
	if (m_pBallSprite->GetXPosition() < m_pHumanSprite->GetXPosition())
	{
		m_DirectSound.PlaySound(m_DirectSound.GetSound(m_DirectSound.BOO));
		m_iComputerScore++;
		m_GameState = CEngine::GS_STOPPED;
	}
	else if (m_pBallSprite->GetXPosition() > (m_pComputerSprite->GetXPosition() + m_pComputerSprite->GetWidth()))
	{
		m_DirectSound.PlaySound(m_DirectSound.GetSound(m_DirectSound.CHEER));
		m_iPlayerScore++;
		m_GameState = CEngine::GS_STOPPED;
	}
}

//////////////////////////////////////////////////////
// HandleStopped()
//////////////////////////////////////////////////////
void CEngine::HandleStopped(void)
{
	m_iCounter++;
	if (m_iCounter > GAME_STOP)
	{
		InitGame();
		m_iCounter = 0;
		m_GameState = CEngine::GS_RUNNING;
	}
}

//////////////////////////////////////////////////////
// InitGame()
//////////////////////////////////////////////////////
void CEngine::InitGame(void)
{
	m_DirectSound.PlaySound(m_DirectSound.GetSound(m_DirectSound.START));

	m_pHumanSprite->SetPosition(10.0f, (WINDOW_HEIGHT / 2.0f) - (10.0f / 2.0f));
	m_pHumanSprite->CalculateVertices();

	m_pComputerSprite->SetPosition((WINDOW_WIDTH - 20.0f), (WINDOW_HEIGHT / 2.0f) - (10.0f / 2.0f));
	m_pComputerSprite->CalculateVertices();

	m_pBallSprite->SetPosition((WINDOW_WIDTH / 2.0) - (32.0 / 2.0), 0.0f);
	m_pBallSprite->CalculateVertices();
	m_pBallSprite->InitSpriteVelocity();

	ComputerLevelModifier();
}

//////////////////////////////////////////////////////
// ComputerLevelModifier()
//////////////////////////////////////////////////////
void CEngine::ComputerLevelModifier(void)
{
	int iDiff = m_iPlayerScore - m_iComputerScore;

	if (iDiff > 1)
		m_iComputerLevel -= CMPLEVEL_INC;
	else
	{
		iDiff = iDiff * -1;

		if (iDiff > 1)
			m_iComputerLevel += CMPLEVEL_INC;
	}

	if (m_iComputerLevel <= MAX_CMPLEVEL)
		m_iComputerLevel = MAX_CMPLEVEL;
	else if (m_iComputerLevel >= MIN_CMPLEVEL)
		m_iComputerLevel = MIN_CMPLEVEL;
}

//////////////////////////////////////////////////////
// HandleKeys()
//////////////////////////////////////////////////////
void CEngine::HandleKeys(WPARAM wParam)
{
    switch(wParam)
    {
	case VK_ESCAPE:
		HandleEscape();		
		break;
	case VK_UP:
		HandleUpArrow();
		break;
	case VK_DOWN:
		HandleDownArrow();
		break;
	case VK_SPACE:
		HandleSpace();
		break;
    }
}

//////////////////////////////////////////////////////
// HandleEscape()
//////////////////////////////////////////////////////
void CEngine::HandleEscape(void)
{
	if (m_GameState == CEngine::GS_TITLE)
		m_GameState = CEngine::GS_EXIT;
	if (m_GameState == CEngine::GS_RUNNING || m_GameState == CEngine::GS_STOPPED)
	{
		m_pMainTitle->SetPosition(170, 100);
		m_GameState = CEngine::GS_TITLE;
	}
}

//////////////////////////////////////////////////////
// HandleSpace()
//////////////////////////////////////////////////////
void CEngine::HandleSpace(void)
{
	if (m_GameState != CEngine::GS_TITLE) return;
	m_GameState = CEngine::GS_NEWGAME;
}

//////////////////////////////////////////////////////
// HandleUpArrow()
//////////////////////////////////////////////////////
void CEngine::HandleUpArrow(void)
{
	if (m_GameState != CEngine::GS_RUNNING) return;
	m_pHumanSprite->UpdateSprite(m_pHumanSprite->GetYPosition() - m_pHumanSprite->GetYVelocity());
}

//////////////////////////////////////////////////////
// HandleDownArrow()
//////////////////////////////////////////////////////
void CEngine::HandleDownArrow(void)
{
	if (m_GameState != CEngine::GS_RUNNING) return;
	m_pHumanSprite->UpdateSprite(m_pHumanSprite->GetYPosition() + m_pHumanSprite->GetYVelocity());
}

//////////////////////////////////////////////////////
// PaintBackBuffer()
//////////////////////////////////////////////////////
void CEngine::PaintBackBuffer(void)
{
	m_Direct3D.ClearBackBuffer(D3DCOLOR_XRGB(0,0,0));

	switch (m_GameState)
	{
	case CEngine::GS_LOADING:
		PaintSplash();
		break;
	case CEngine::GS_TITLE:
		PaintTitle();
		break;
	case CEngine::GS_RUNNING:
		PaintSprite(m_pBackground, m_Direct3D.GetTexture(m_Direct3D.BACKGROUND));

		PaintSpriteShadow(m_pHumanSprite, m_Direct3D.GetTexture(m_Direct3D.BATSHADOW));
		PaintSpriteShadow(m_pComputerSprite, m_Direct3D.GetTexture(m_Direct3D.BATSHADOW));
		PaintSpriteShadow(m_pBallSprite, m_Direct3D.GetTexture(m_Direct3D.BALLSHADOW));

		PaintSprite(m_pHumanSprite, m_Direct3D.GetTexture(m_Direct3D.BAT));
		PaintSprite(m_pComputerSprite, m_Direct3D.GetTexture(m_Direct3D.BAT));
		PaintSprite(m_pBallSprite, m_Direct3D.GetTexture(m_Direct3D.BALL));
		PaintScore(0xFF000000);
		break;
	case CEngine::GS_STOPPED:
		PaintScore(D3DCOLOR_ARGB(0xff,221,0,0));
	}
		
	m_Direct3D.GetDevice()->Present(NULL, NULL, NULL, NULL);
}

//////////////////////////////////////////////////////
// PaintSplash()
//////////////////////////////////////////////////////
void CEngine::PaintSplash(void)
{
	RECT SrcRect;
	SrcRect.left = 0;
	SrcRect.right = SPLASH_WIDTH;
	SrcRect.top = 0;
	SrcRect.bottom = SPLASH_HEIGHT;

	POINT DstPoint;
	DstPoint.x = (WINDOW_WIDTH / 2) - (SPLASH_WIDTH / 2) + 20;
	DstPoint.y = (WINDOW_HEIGHT / 2) - (SPLASH_HEIGHT / 2);

	HRESULT hResult = m_Direct3D.GetDevice()->CopyRects(
		m_Direct3D.GetSurface(m_Direct3D.SPLASH),
		&SrcRect,
		1,
		m_Direct3D.GetBackBuffer(),
		&DstPoint);
}

//////////////////////////////////////////////////////
// PaintTitle()
//////////////////////////////////////////////////////
void CEngine::PaintTitle(void)
{
	PaintSprite(m_pBackground, m_Direct3D.GetTexture(m_Direct3D.BACKGROUND));
	PaintSprite(m_pSubTitle, m_Direct3D.GetTexture(m_Direct3D.SUBTITLE));
	PaintSprite(m_pMainTitle, m_Direct3D.GetTexture(m_Direct3D.MAINTITLE));

	char pstrMsg[MAX_PATH];
	wsprintf(pstrMsg, "Press 'SPACE' to play - Press 'ESCAPE' to quit");

	// Create a font.
    LPD3DXFONT pFont = NULL;
    LOGFONT LogFont = {20, 0, 0, 0, FW_BOLD, false, false, false,
        DEFAULT_CHARSET,OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
        PROOF_QUALITY, DEFAULT_PITCH, "Arial"};
    D3DXCreateFontIndirect(m_Direct3D.GetDevice(), &LogFont, &pFont);
	
	RECT r;
	r.left = 0; r.top = 0; r.right = 0; r.bottom = 0;
	
	// Calculate the size of a rectangle that can hold the text.
    pFont->DrawText(pstrMsg, -1, &r, DT_CALCRECT, 0xFF000000);

	int iWidth = r.right - r.left;
    int iHeight = r.bottom - r.top;
	r.left = (WINDOW_WIDTH - iWidth) / 2;
	r.right = r.left + iWidth;
	r.top = WINDOW_HEIGHT * 0.75;
	r.bottom = r.top + iHeight;
	PaintText(pFont, pstrMsg, r, D3DCOLOR_ARGB(0xff,221,0,0), TRUE);
	pFont->Release();
}

//////////////////////////////////////////////////////
// PaintSpriteShadow()
//////////////////////////////////////////////////////
void CEngine::PaintSpriteShadow(CSprite* pSprite, IDirect3DTexture8* pTexture)
{
	CSprite* pShadowSprite = new CSprite(pSprite->GetWidth(), pSprite->GetHeight());

	pShadowSprite->SetPosition((pSprite->GetXPosition() - 3), (pSprite->GetYPosition() + 3));
	pShadowSprite->CalculateVertices();
	PaintSprite(pShadowSprite, pTexture);

	delete pShadowSprite;
}

//////////////////////////////////////////////////////
// PaintScore()
//////////////////////////////////////////////////////
void CEngine::PaintScore(D3DCOLOR color)
{
	char pstrMsg[MAX_PATH];
	wsprintf(pstrMsg, "Player %d - %d Computer", m_iPlayerScore, m_iComputerScore);

	// Create a font.
    LPD3DXFONT pFont = NULL;
    LOGFONT LogFont = {20, 0, 0, 0, FW_BOLD, false, false, false,
        DEFAULT_CHARSET,OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
        PROOF_QUALITY, DEFAULT_PITCH, "Arial"};
    D3DXCreateFontIndirect(m_Direct3D.GetDevice(), &LogFont, &pFont);
	
	RECT r;
	r.left = 0; r.top = 0; r.right = 0; r.bottom = 0;
	
	// Calculate the size of a rectangle that can hold the text.
    pFont->DrawText(pstrMsg, -1, &r, DT_CALCRECT, 0xFF000000);

	int iWidth = r.right - r.left;
    int iHeight = r.bottom - r.top;
	r.left = (WINDOW_WIDTH - iWidth) / 2;
	r.right = r.left + iWidth;
	r.top = (WINDOW_HEIGHT - iHeight) / 2;
	r.bottom = r.top + iHeight;
	PaintText(pFont, pstrMsg, r, color, TRUE);
	pFont->Release();
}

//////////////////////////////////////////////////////
// PaintText()
//////////////////////////////////////////////////////
void CEngine::PaintText(LPD3DXFONT pFont, char* pstrMsg, RECT r, D3DCOLOR color, BOOL bShadow)
{
	if (SUCCEEDED(m_Direct3D.GetDevice()->BeginScene()))
    {
		if (bShadow)
		{
			pFont->DrawText(pstrMsg, -1, &r, DT_CENTER, D3DCOLOR_ARGB(0xff,53,53,44));

			r.left += SHADOW_OFFSET;
			r.right += SHADOW_OFFSET;
			r.top -= SHADOW_OFFSET;
			r.bottom -= SHADOW_OFFSET;
		}
		pFont->DrawText(pstrMsg, -1, &r, DT_CENTER, color);
		m_Direct3D.GetDevice()->EndScene();
	}
}

//////////////////////////////////////////////////////
// GetCDirect3DObj()
//////////////////////////////////////////////////////
CDirect3D* CEngine::GetCDirect3DObj(void)
{
	return &m_Direct3D;
}

//////////////////////////////////////////////////////
// GetCDirectSoundObj()
//////////////////////////////////////////////////////
CDirectSound* CEngine::GetCDirectSoundObj(void)
{
	return &m_DirectSound;
}

//////////////////////////////////////////////////////
// ResetDirect3D()
//////////////////////////////////////////////////////
void CEngine::ResetDirect3D(void)
{
    m_Direct3D.CleanUp();
    m_Direct3D.InitD3D();
}

//////////////////////////////////////////////////////
// GetSprite()
//////////////////////////////////////////////////////
CSprite* CEngine::GetSprite(SPRITETYPE type)
{
	switch (type)
	{
	case HUMAN:
		return m_pHumanSprite;
	case COMPUTER:
		return m_pComputerSprite;
	case BALL:
		return m_pBallSprite;
	case BACKGROUND:
		return m_pBackground;
	case MAINTITLE:
		return m_pMainTitle;
	case SUBTITLE:
		return m_pSubTitle;
	}
	return NULL;
}

//////////////////////////////////////////////////////
// PaintSprite()
//////////////////////////////////////////////////////
void CEngine::PaintSprite(CSprite* pSprite, IDirect3DTexture8* pTexture)
{
	unsigned char *vb_vertices;
	IDirect3DVertexBuffer8* pSquare;
	CUSTOMVERTEX vertices[VERTICESSIZE];
	for (int i=0; i < VERTICESSIZE; ++i)
	{
		vertices[i] = pSprite->GetVertex(i);
	}

	// Create and load the vertex buffer
	HRESULT hResult = m_Direct3D.GetDevice()->CreateVertexBuffer(
		4 * sizeof(CUSTOMVERTEX),
		D3DUSAGE_WRITEONLY,
		D3D8T_CUSTOMVERTEX,
		D3DPOOL_MANAGED,
		&pSquare);
	hResult = pSquare->Lock(
		0,
		0,
		&vb_vertices,
		0);
	memcpy(vb_vertices, vertices, sizeof(vertices));
	pSquare->Unlock();

	// Display the sprite
	m_Direct3D.GetDevice()->SetTextureStageState(
		0,
        D3DTSS_COLOROP,
		D3DTOP_SELECTARG1);
    m_Direct3D.GetDevice()->SetTextureStageState(
		0,
        D3DTSS_COLORARG1,
		D3DTA_TEXTURE);
    m_Direct3D.GetDevice()->SetTextureStageState(
		0,
        D3DTSS_ALPHAOP,
		D3DTOP_SELECTARG1);
    m_Direct3D.GetDevice()->SetTextureStageState(
		0,
        D3DTSS_ALPHAARG1,
		D3DTA_TEXTURE);
    m_Direct3D.GetDevice()->SetRenderState(
		D3DRS_SRCBLEND,
        D3DBLEND_SRCALPHA);
    m_Direct3D.GetDevice()->SetRenderState(
		D3DRS_DESTBLEND,
        D3DBLEND_INVSRCALPHA);
    m_Direct3D.GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    if(SUCCEEDED(m_Direct3D.GetDevice()->BeginScene()))
    {
        m_Direct3D.GetDevice()->SetVertexShader(D3D8T_CUSTOMVERTEX);
        m_Direct3D.GetDevice()->SetStreamSource(0, pSquare, sizeof(CUSTOMVERTEX));
        m_Direct3D.GetDevice()->SetTexture(0, pTexture);
        m_Direct3D.GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
        m_Direct3D.GetDevice()->EndScene();
    }
    pSquare->Release();
}