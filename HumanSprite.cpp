//////////////////////////////////////////////////////
// HumanSprite.cpp
//////////////////////////////////////////////////////

#include "humansprite.h"

//////////////////////////////////////////////////////
// HumanSprite()
//////////////////////////////////////////////////////
CHumanSprite::CHumanSprite(int iWidth, int iHeight) :
    CSprite(iWidth, iHeight)
{
	m_fYVel = 0;
}

//////////////////////////////////////////////////////
// ~HumanSprite()
//////////////////////////////////////////////////////
CHumanSprite::~CHumanSprite(void)
{
}

//////////////////////////////////////////////////////
// UpdateSprite()
//////////////////////////////////////////////////////
void CHumanSprite::UpdateSprite(float newYPos)
{
	// Check sprite not going beyond screen borders
    if( newYPos < 0 )
        newYPos = 0;

    if( newYPos > WINDOW_HEIGHT - GetHeight())
        newYPos = (float)WINDOW_HEIGHT - GetHeight();

	SetYPosition(newYPos);
	CalculateVertices();
}

//////////////////////////////////////////////////////
// SetYVelocity()
//////////////////////////////////////////////////////
void CHumanSprite::SetYVelocity(float fVel)
{
	m_fYVel = fVel;
}

//////////////////////////////////////////////////////
// GetYVelocity()
//////////////////////////////////////////////////////
float CHumanSprite::GetYVelocity(void)
{
	return m_fYVel;
}