//////////////////////////////////////////////////////
// Direct3D.h
//////////////////////////////////////////////////////

#pragma once

#include <d3d8.h>
#include <D3dx8tex.h>

#include "Constants.h"

class CDirect3D
{
public:
	enum TEXTURETYPE {BACKGROUND, BAT, BATSHADOW, BALL, BALLSHADOW, MAINTITLE, SUBTITLE};
	enum SURFACETYPE {SPLASH};

	// Constructor
    CDirect3D(void);
	// Destructor
    ~CDirect3D(void);

	// Sets the class's copy of the application's window handle
    void SetWindowHandle(HWND hWnd);
	// Initializes Direct3D for the application, including creating
	// the Direct3D object, checking the display mode, creating
	// the Direct3D device object, and creating the various
	// required surfaces
    HRESULT InitD3D(void);
	// Clears the backbuffer to color given
	void ClearBackBuffer(D3DCOLOR color);
	// Returns a pointer to the application's Direct3D device
    LPDIRECT3DDEVICE8 GetDevice(void);
	// Returns a pointer to the application's back buffer
    IDirect3DSurface8* GetBackBuffer(void);
	// Returns the current error message
    char* GetErrorString(void);
	// Releases all Direct3D objects created by the class
    void CleanUp(void);

	// Returns a texture based on the texture type ID
	IDirect3DTexture8* GetTexture(TEXTURETYPE txtType);
	// Returns a surface based on the surface type ID
	IDirect3DSurface8* GetSurface(SURFACETYPE surType);

protected:
    LPDIRECT3D8 m_pD3D;							// Holds a pointer to the class's Direct3D object
    LPDIRECT3DDEVICE8 m_pD3DDevice;				// Holds a pointer to the application's Direct3D device
    IDirect3DSurface8* m_pBackBuffer;			// Holds a pointer to the application's back buffer
	HWND m_hWnd;								// Holds the application's window handle
    char m_szErrorMsg[256];						// Holds the current error message

private:
	IDirect3DSurface8* m_pSplashSurface;		// Holds a pointer to the splash screen surface 
	IDirect3DTexture8* m_pBatTexture;			// Holds a pointer to the bat texture
	IDirect3DTexture8* m_pBatShadowTexture;		// Holds a pointer to the bat shawdow texture
	IDirect3DTexture8* m_pBallTexture;			// Holds a pointer to the ball texture
	IDirect3DTexture8* m_pBallShadowTexture;	// Holds a pointer to the ball shadow texture
	IDirect3DTexture8* m_pBackgroundTexture;	// Holds a pointer to the background texture
	IDirect3DTexture8* m_pMainTitleTexture;		// Holds a pointer to the main title image texture
	IDirect3DTexture8* m_pSubTitleTexture;		// Holds a pointer to the sub title image texture


	// Creates the application's Direct3D object
    HRESULT CreateD3DObject(void);
	// Verifies that the user's system supports the required display
    HRESULT CheckDisplayMode(void);
	// Creates the application's Direct3D device
    HRESULT CreateD3DDevice(void);
	// Creates the application's texture surfaces
	HRESULT CreateTextures(void);
	// Creates the application's image surfaces
    HRESULT CreateSurfaces(void);
};