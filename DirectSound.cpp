//////////////////////////////////////////////////////
// DirectSound.cpp
//////////////////////////////////////////////////////

#include "directsound.h"

//////////////////////////////////////////////////////
// CDirectSound()
//////////////////////////////////////////////////////
CDirectSound::CDirectSound(void)
{
    m_pDirectSoundObj = NULL;
	m_pHitBatSound = NULL;
	m_pHitWallSound = NULL;
    m_pCheerSound = NULL;
    m_pBooSound = NULL;
    m_pStartSound = NULL;
    m_pLoadingSound = NULL;
}

//////////////////////////////////////////////////////
// ~CDirectSound()
//////////////////////////////////////////////////////
CDirectSound::~CDirectSound(void)
{
    CleanUp();
}

//////////////////////////////////////////////////////
// CleanUp()
//////////////////////////////////////////////////////
void CDirectSound::CleanUp()
{
    if (m_pHitBatSound)
        m_pHitBatSound->Release();
	if (m_pHitWallSound)
		m_pHitWallSound->Release();
    if (m_pCheerSound)
        m_pCheerSound->Release();
    if (m_pBooSound)
        m_pBooSound->Release();
    if (m_pStartSound)
        m_pStartSound->Release();
    if (m_pLoadingSound)
        m_pLoadingSound->Release();

    if (m_pDirectSoundObj)
        m_pDirectSoundObj->Release();
}

//////////////////////////////////////////////////////
// SetWindowHandle()
//////////////////////////////////////////////////////
void CDirectSound::SetWindowHandle(HWND hWnd)
{
    m_hWnd = hWnd;
}

//////////////////////////////////////////////////////
// InitDirectSound()
//////////////////////////////////////////////////////
HRESULT CDirectSound::InitDirectSound()
{
    HRESULT hResult = DirectSoundCreate8(NULL, &m_pDirectSoundObj, NULL);
    if (hResult != DS_OK)
        return hResult;

    hResult = m_pDirectSoundObj->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL);
    if (hResult != DS_OK)
        return hResult;

	hResult = CreateSoundBuffers();
    if (hResult != DS_OK)
        return hResult;

    return DS_OK;
}

//////////////////////////////////////////////////////
// CreateSoundBuffers()
//////////////////////////////////////////////////////
HRESULT CDirectSound::CreateSoundBuffers(void)
{
	HRESULT hResult = LoadSoundEffect("Sounds\\HitBat.wav", &m_pHitBatSound);
    if (hResult != DS_OK)
        return hResult;
	hResult = LoadSoundEffect("Sounds\\HitWall.wav", &m_pHitWallSound);
    if (hResult != DS_OK)
        return hResult;
    hResult = LoadSoundEffect("Sounds\\Cheer.wav", &m_pCheerSound);
    if (hResult != DS_OK)
        return hResult;
    hResult = LoadSoundEffect("Sounds\\Boo.wav", &m_pBooSound);
    if (hResult != DS_OK)
        return hResult;
    hResult = LoadSoundEffect("Sounds\\Start.wav", &m_pStartSound);
    if (hResult != DS_OK)
        return hResult;
    hResult = LoadSoundEffect("Sounds\\Loading.wav", &m_pLoadingSound);
	return hResult;
}

//////////////////////////////////////////////////////
// PlaySound()
//////////////////////////////////////////////////////
HRESULT CDirectSound::PlaySound(IDirectSoundBuffer* pBuf)
{
    HRESULT hResult = pBuf->SetCurrentPosition(0);
    if (hResult != DS_OK)
        return hResult;

	hResult = pBuf->Play(0, 0, 0);
    if (hResult != DS_OK)
        return hResult;

    return hResult;
}

//////////////////////////////////////////////////////
// LoadSoundEffect()
//////////////////////////////////////////////////////
HRESULT CDirectSound::LoadSoundEffect(char* pstrFileName, 
    IDirectSoundBuffer** ppSoundBuf)
{
    CWave* pWave = new CWave(pstrFileName);
	if (!pWave->WaveOK())
	{
		MessageBox(m_hWnd, "Could not load wave file.", "Error", MB_OK);
        PostQuitMessage(WM_QUIT);
		return 0;
	}

    LPWAVEFORMATEX pWaveFormatEx = pWave->GetWaveFormatPtr();
    char* pWaveData = pWave->GetWaveDataPtr();
    DWORD dwWaveSize = pWave->GetWaveSize();

    DSBUFFERDESC dsBufferDesc;
    memset(&dsBufferDesc, 0, sizeof(DSBUFFERDESC));
    dsBufferDesc.dwSize = sizeof(DSBUFFERDESC);
    dsBufferDesc.dwBufferBytes = dwWaveSize;
    dsBufferDesc.lpwfxFormat = (LPWAVEFORMATEX) pWaveFormatEx;

    IDirectSoundBuffer* pDSBuf;
	HRESULT hResult = m_pDirectSoundObj->
		CreateSoundBuffer(&dsBufferDesc, &pDSBuf, NULL);
    if (hResult != DS_OK)
        return hResult;

    LPVOID pSoundBlock1;
    LPVOID pSoundBlock2;
    DWORD dwBytesSoundBlock1;
    DWORD dwBytesSoundBlock2;
    hResult = pDSBuf->Lock(0, dwWaveSize,
        &pSoundBlock1, &dwBytesSoundBlock1,
        &pSoundBlock2, &dwBytesSoundBlock2, 0);
    if (hResult != DS_OK)
        return hResult;

    memcpy((void*)pSoundBlock1, pWaveData, dwWaveSize);

	pDSBuf->Unlock(pSoundBlock1, dwBytesSoundBlock1,
            pSoundBlock2, dwBytesSoundBlock2);

	delete pWave;
    *ppSoundBuf = pDSBuf;
    return hResult;
}

//////////////////////////////////////////////////////
// GetErrorString()
//////////////////////////////////////////////////////
char* CDirectSound::GetErrorString(void)
{
    return m_szErrorMsg;
}

//////////////////////////////////////////////////////
// GetSound()
//////////////////////////////////////////////////////
IDirectSoundBuffer* CDirectSound::GetSound(CDirectSound::SOUNDTYPE soundType)
{
	switch (soundType)
    {
	case CDirectSound::HITBAT:
        return m_pHitBatSound;
        break;
	case CDirectSound::HITWALL:
        return m_pHitWallSound;
        break;
	case CDirectSound::CHEER:
        return m_pCheerSound;
        break;
	case CDirectSound::BOO:
        return m_pBooSound;
        break;
	case CDirectSound::START:
        return m_pStartSound;
        break;
	case CDirectSound::LOADING:
        return m_pLoadingSound;
        break;
    }

    return NULL;
}