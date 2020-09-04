//////////////////////////////////////////////////////
// Engine.h
//////////////////////////////////////////////////////

#pragma once

#include <windows.h>
#include <time.h>
#include <d3d8.h>

#include "Constants.h"
#include "Direct3D.h"
#include "DirectSound.h"

#include "Sprite.h"
#include "HumanSprite.h"
#include "ComputerSprite.h"
#include "BallSprite.h"

class CEngine
{
public:
	
	enum SPRITETYPE {HUMAN, COMPUTER, BALL, BACKGROUND, MAINTITLE, SUBTITLE};
	enum GAMESTATE {GS_LOADING, GS_TITLE, GS_NEWGAME, GS_RUNNING, GS_STOPPED, GS_EXIT};

	// Constructor
	CEngine(void);
	// Destructor
	~CEngine(void);

	// Sets the class's copy of the window handle
	void SetWindowHandle(HWND hWnd);
	// Processes game data during the appilication's idle time
	void ProcessGame(void);
	// Handles keystrokes for the application
	void HandleKeys(WPARAM wParam);
	// Returns a pointer to the class's CDirect3D object
	CDirect3D* GetCDirect3DObj();
	// Returns a pointer to the class's CDirectSound object
	CDirectSound* GetCDirectSoundObj();
	// Returns a sprite based on the sprite type ID
	CSprite* GetSprite(SPRITETYPE type);
	// Renders the back buffer ready for display
	void PaintBackBuffer();

protected:
	HWND m_hWnd;				// Holds the application's window handle
	CDirect3D m_Direct3D;		// Holds the class's CDirect3D object
	CDirectSound m_DirectSound;	// Holds the class's CDirectSound object
	BOOL m_bGamePaused;			// Indicates whether the game is paused due to having lost its Direct3D device
	CSprite* m_pBackground;
	CSprite* m_pSubTitle;
	CBallSprite* m_pMainTitle;
	CHumanSprite* m_pHumanSprite;
	CComputerSprite* m_pComputerSprite;
	CBallSprite* m_pBallSprite;

	int m_iPlayerScore;
	int m_iComputerScore;
	int m_iCounter;
	int m_iComputerLevel;
	GAMESTATE m_GameState;

	// 
	void HandleLoading(void);
	//
	void HandleTitle(void);
	// 
	void HandleNewGame(void);
	//
	void HandleRunning(void);
	//
	void HandleStopped(void);
	//
	void InitGame(void);
	// Handle down arrow key
	void HandleDownArrow(void);
	// Handle up arrow key
	void HandleUpArrow(void);
	// Handle space key
	void HandleSpace(void);
	// Handle escape key
	void HandleEscape(void);
	//
	void ComputerLevelModifier(void);

private:	
	//
	void CleanUp(void);
	// Restores the Direct3D device and its surfaces/textures
	void ResetDirect3D(void);
	//
	void PaintSplash(void);
	//
	void PaintTitle();
	// 
	void PaintSprite(CSprite* pSprite, IDirect3DTexture8* pTexture);
	// 
	void PaintSpriteShadow(CSprite* pSprite, IDirect3DTexture8* pTexture);
	//
	void PaintScore(D3DCOLOR color);
	//
	void PaintText(LPD3DXFONT pFont, char* pstrMsg, RECT r, D3DCOLOR color, BOOL bShadow = FALSE);
};
