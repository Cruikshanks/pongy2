//////////////////////////////////////////////////////
// Direct3D.cpp
//////////////////////////////////////////////////////

#include "direct3d.h"

//////////////////////////////////////////////////////
// CDirect3D()
//////////////////////////////////////////////////////
CDirect3D::CDirect3D(void)
{
    m_pD3D = NULL;
    m_pD3DDevice = NULL;
    m_pBackBuffer = NULL;
	m_pSplashSurface = NULL;
	m_pBatTexture = NULL;
	m_pBatShadowTexture = NULL;
	m_pBallTexture = NULL;
	m_pBallShadowTexture = NULL;
	m_pBackgroundTexture = NULL;
	m_pMainTitleTexture = NULL;
	m_pSubTitleTexture = NULL;
    strcpy(m_szErrorMsg, "No Error");
}

//////////////////////////////////////////////////////
// ~CDirect3D()
//////////////////////////////////////////////////////
CDirect3D::~CDirect3D(void)
{
    CleanUp();
}

//////////////////////////////////////////////////////
// SetWindowHandle()
//////////////////////////////////////////////////////
void CDirect3D::SetWindowHandle(HWND hWnd)
{
    m_hWnd = hWnd;
}

//////////////////////////////////////////////////////
// InitD3D()
//////////////////////////////////////////////////////
HRESULT CDirect3D::InitD3D()
{
    HRESULT hResult = CreateD3DObject();
    if (hResult != D3D_OK)
        return hResult;
    hResult = CheckDisplayMode();
    if (hResult != D3D_OK)
        return hResult;
    hResult = CreateD3DDevice();
    if (hResult != D3D_OK)
        return hResult;
	hResult = CreateTextures();
	if (hResult != D3D_OK)
		return hResult;
    hResult = CreateSurfaces();
    if (hResult != D3D_OK)
        return hResult;
    hResult = m_pD3DDevice->GetBackBuffer(
		0,
        D3DBACKBUFFER_TYPE_MONO,
		&m_pBackBuffer);
    m_pD3DDevice->Clear(
		0,
		0,
		D3DCLEAR_TARGET,
        D3DCOLOR_XRGB(0,0,0),
		0,
		0);
    m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
    return hResult;
}

//////////////////////////////////////////////////////
// CreateD3DObject()
//////////////////////////////////////////////////////
HRESULT CDirect3D::CreateD3DObject()
{
    m_pD3D = Direct3DCreate8(D3D_SDK_VERSION);
    if (m_pD3D == NULL)
    {
        MessageBox(m_hWnd, "Couldn’t create DirectX object.",
            "DirectX Error", MB_OK);
        strcpy(m_szErrorMsg, "CreateD3DObject()");
        return E_FAIL;
    }
    return D3D_OK;
}

//////////////////////////////////////////////////////
// CheckDisplayMode()
//////////////////////////////////////////////////////
HRESULT CDirect3D::CheckDisplayMode()
{
    HRESULT hResult = m_pD3D->CheckDeviceType(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, FALSE);
    if (hResult != D3D_OK)
    {
        MessageBox(m_hWnd, "The required display mode is \
            not available on this system.",
            "DirectX Error", MB_OK);
        strcpy(m_szErrorMsg, "CheckDisplayMode()");
        return hResult;
    }
    return D3D_OK;
}

//////////////////////////////////////////////////////
// CreateD3DDevice()
//////////////////////////////////////////////////////
HRESULT CDirect3D::CreateD3DDevice()
{
    D3DPRESENT_PARAMETERS D3DPresentParams;
    ZeroMemory(&D3DPresentParams, sizeof(D3DPRESENT_PARAMETERS));
    D3DPresentParams.Windowed = FALSE;
    D3DPresentParams.BackBufferCount = 1;
    D3DPresentParams.BackBufferWidth = 640;
    D3DPresentParams.BackBufferHeight = 480;
    D3DPresentParams.BackBufferFormat = D3DFMT_X8R8G8B8;
    D3DPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    D3DPresentParams.hDeviceWindow = m_hWnd;
    HRESULT hResult = m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&D3DPresentParams,
		&m_pD3DDevice);
    if (FAILED(hResult))
    {
        MessageBox(m_hWnd, "Failed to create Direct3D device.",
            "DirectX Error", MB_OK);
            strcpy(m_szErrorMsg, "CreateD3DDevice()");
        return hResult;
    }
    return hResult;
}

//////////////////////////////////////////////////////
// CreateTextures()
//////////////////////////////////////////////////////
HRESULT CDirect3D::CreateTextures()
{
	HRESULT hResult = D3DXCreateTextureFromFileEx(
		m_pD3DDevice,
		"Graphics\\bat.bmp",
        D3DX_DEFAULT,
		D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
        NULL,
		NULL,
		&m_pBatTexture);
    if (FAILED(hResult))
    {
        strcpy(m_szErrorMsg, "Error loading human bat texture surface.");
        return hResult;
    }

	hResult = D3DXCreateTextureFromFileEx(
		m_pD3DDevice,
		"Graphics\\batshadow.bmp",
        D3DX_DEFAULT,
		D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
        NULL,
		NULL,
		&m_pBatShadowTexture);
    if (FAILED(hResult))
    {
        strcpy(m_szErrorMsg, "Error loading computer bat texture surface.");
        return hResult;
    }

	hResult = D3DXCreateTextureFromFileEx(
		m_pD3DDevice,
		"Graphics\\ball.bmp",
        D3DX_DEFAULT,
		D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
        NULL,
		NULL,
		&m_pBallTexture);
    if (FAILED(hResult))
    {
        strcpy(m_szErrorMsg, "Error loading DirectX ball texture surface.");
        return hResult;
    }

	hResult = D3DXCreateTextureFromFileEx(
		m_pD3DDevice,
		"Graphics\\ballshadow.bmp",
        D3DX_DEFAULT,
		D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
        NULL,
		NULL,
		&m_pBallShadowTexture);
    if (FAILED(hResult))
    {
        strcpy(m_szErrorMsg, "Error loading DirectX ball texture surface.");
        return hResult;
    }

	hResult = D3DXCreateTextureFromFileEx(
		m_pD3DDevice,
		"Graphics\\background.bmp",
        D3DX_DEFAULT,
		D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
        NULL,
		NULL,
		&m_pBackgroundTexture);
    if (FAILED(hResult))
    {
        strcpy(m_szErrorMsg, "Error loading background texture surface.");
        return hResult;
    }

	hResult = D3DXCreateTextureFromFileEx(
		m_pD3DDevice,
		"Graphics\\maintitle.bmp",
        D3DX_DEFAULT,
		D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
        NULL,
		NULL,
		&m_pMainTitleTexture);
    if (FAILED(hResult))
    {
        strcpy(m_szErrorMsg, "Error loading main title texture surface.");
        return hResult;
    }

	hResult = D3DXCreateTextureFromFileEx(
		m_pD3DDevice,
		"Graphics\\subtitle.bmp",
        D3DX_DEFAULT,
		D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0xFF000000,
        NULL,
		NULL,
		&m_pSubTitleTexture);
    if (FAILED(hResult))
    {
        strcpy(m_szErrorMsg, "Error loading sub title texture surface.");
        return hResult;
    }
	return D3D_OK;	
}

//////////////////////////////////////////////////////
// CreateSurfaces()
//////////////////////////////////////////////////////
HRESULT CDirect3D::CreateSurfaces()
{
	HRESULT hResult = m_pD3DDevice->CreateImageSurface(
		SPLASH_WIDTH,
		SPLASH_HEIGHT,
		D3DFMT_X8R8G8B8,
		&m_pSplashSurface);
	if (FAILED(hResult))
	{
		strcpy(m_szErrorMsg, "Splash surface not created.");
		return hResult;
	}

	hResult = D3DXLoadSurfaceFromFile(
		m_pSplashSurface,
		NULL,
		NULL,
		"Graphics\\startup.bmp",
		NULL,
		D3DX_DEFAULT,
		0,
		NULL);
	if (FAILED(hResult))
	{
		strcpy(m_szErrorMsg, "Error loading splash surface.");
		return hResult;
	}

	return D3D_OK;
}

//////////////////////////////////////////////////////
// CleanUp()
//////////////////////////////////////////////////////
void CDirect3D::CleanUp()
{
	if (m_pSplashSurface)
		m_pSplashSurface->Release();

	if (m_pMainTitleTexture)
		m_pMainTitleTexture->Release();

	if (m_pSubTitleTexture)
		m_pSubTitleTexture->Release();

	if (m_pBackgroundTexture)
		m_pBackgroundTexture->Release();

	if (m_pBallShadowTexture)
		m_pBallShadowTexture->Release();
	if (m_pBallTexture)
		m_pBallTexture->Release();

	if (m_pBatShadowTexture)
		m_pBatShadowTexture->Release();
	if (m_pBatTexture)
		m_pBatTexture->Release();

    if (m_pBackBuffer)
        m_pBackBuffer->Release();
    if (m_pD3DDevice)
        m_pD3DDevice->Release();
    if (m_pD3D)
        m_pD3D->Release();
}

//////////////////////////////////////////////////////
// ClearBackBuffer()
//////////////////////////////////////////////////////
void CDirect3D::ClearBackBuffer(D3DCOLOR color)
{
    GetDevice()->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET,
		color,
		1.0f,
		0);
}

//////////////////////////////////////////////////////
// GetBackBuffer()
//////////////////////////////////////////////////////
IDirect3DSurface8* CDirect3D::GetBackBuffer()
{
    return m_pBackBuffer;
}

//////////////////////////////////////////////////////
// GetDevice()
//////////////////////////////////////////////////////
LPDIRECT3DDEVICE8 CDirect3D::GetDevice()
{
    return m_pD3DDevice;
}

//////////////////////////////////////////////////////
// GetErrorString()
//////////////////////////////////////////////////////
char* CDirect3D::GetErrorString(void)
{
    return m_szErrorMsg;
}

//////////////////////////////////////////////////////
// GetTexture()
//////////////////////////////////////////////////////
IDirect3DTexture8* CDirect3D::GetTexture(TEXTURETYPE txtType)
{
	switch (txtType)
    {
	case CDirect3D::BACKGROUND:
        return m_pBackgroundTexture;
        break;
	case CDirect3D::BAT:
        return m_pBatTexture;
        break;
	case CDirect3D::BATSHADOW:
        return m_pBatShadowTexture;
        break;
	case CDirect3D::BALL:
        return m_pBallTexture;
        break;
	case CDirect3D::BALLSHADOW:
        return m_pBallShadowTexture;
        break;
	case CDirect3D::MAINTITLE:
        return m_pMainTitleTexture;
        break;
	case CDirect3D::SUBTITLE:
        return m_pSubTitleTexture;
        break;
	}

    return NULL;
}

//////////////////////////////////////////////////////
// GetSurface()
//////////////////////////////////////////////////////
IDirect3DSurface8* CDirect3D::GetSurface(SURFACETYPE surType)
{
	switch (surType)
    {
	case CDirect3D::SPLASH:
        return m_pSplashSurface;
        break;
	}

    return NULL;
}