//////////////////////////////////////////////////////
// ComputerSprite.cpp
//////////////////////////////////////////////////////

#include "computersprite.h"

//////////////////////////////////////////////////////
// ComputerSprite()
//////////////////////////////////////////////////////
CComputerSprite::CComputerSprite(int iWidth, int iHeight) :
    CSprite(iWidth, iHeight)
{
	m_fYVel = 0;
}

//////////////////////////////////////////////////////
// ~ComputerSprite()
//////////////////////////////////////////////////////
CComputerSprite::~CComputerSprite(void)
{
}

//////////////////////////////////////////////////////
// UpdateSprite()
//////////////////////////////////////////////////////
void CComputerSprite::UpdateSprite(float fBallYPos)
{
	float newYPos = GetYPosition();

	// Update the computers bat position based on ball position
	if(newYPos < fBallYPos)
		newYPos = newYPos + GetYVelocity();

	if(newYPos > fBallYPos)
		newYPos = newYPos - GetYVelocity();

	// Check sprite not going beyond screen borders
    if( newYPos < 0 )
        newYPos = 0;

    if( newYPos > WINDOW_HEIGHT - GetHeight())
        newYPos = (float)WINDOW_HEIGHT - GetHeight();

	SetYPosition(newYPos);
	CalculateVertices();
}

//////////////////////////////////////////////////////
// SetSpriteVelocity()
//////////////////////////////////////////////////////
void CComputerSprite::SetYVelocity(float fVel)
{
	m_fYVel = fVel;
}

//////////////////////////////////////////////////////
// GetYVelocity()
//////////////////////////////////////////////////////
float CComputerSprite::GetYVelocity(void)
{
	return m_fYVel;
}