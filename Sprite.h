//////////////////////////////////////////////////////
// Sprite.h
//////////////////////////////////////////////////////

#pragma once

#include <windows.h>
#include <d3d8.h>

const int VERTICESSIZE = 4;

#define D3D8T_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_TEX1)
struct CUSTOMVERTEX
{
	float x, y, z, rhw;
	float tu, tv;
};

class CSprite
{
public:
	// Constructor - initializes the sprites width and height
	CSprite(int iWidth, int iHeight);
	// Destructor
	~CSprite(void);

	// Calculates the vertices, based on the sprites current position and size
	void CalculateVertices();
	// Sets the sprites X and Y position
	void SetPosition(float fXPos, float fYPos);
	// Sets the sprites X position
	void SetXPosition(float fXPos);
	// Returns the sprites X position
	float GetXPosition(void);
	// Sets the sprites Y position
	void SetYPosition(float fYPos);
	// Returns the sprites Y position
	float GetYPosition(void);
	// Returns the sprites width
	int GetWidth(void);
	// Returns the sprites height
	int GetHeight(void);
	// Returns the indexed Vertex from the class's vertices array
	CUSTOMVERTEX GetVertex(int iNum);

protected:
	CUSTOMVERTEX m_Vertices[VERTICESSIZE];

private:
	int m_iWidth;
	int m_iHeight;
	float m_fXPos;
	float m_fYPos;
	
};