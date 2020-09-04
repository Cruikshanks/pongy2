//////////////////////////////////////////////////////
// BallSprite.cpp
//////////////////////////////////////////////////////

#include "ballsprite.h"

//////////////////////////////////////////////////////
// BallSprite()
//////////////////////////////////////////////////////
CBallSprite::CBallSprite(int iWidth, int iHeight) :
    CSprite(iWidth, iHeight)
{
	m_fXVel = 0;
	m_fYVel = 0;
}

//////////////////////////////////////////////////////
// ~BallSprite()
//////////////////////////////////////////////////////
CBallSprite::~CBallSprite(void)
{
}

//////////////////////////////////////////////////////
// InitSpriteVelocity()
//////////////////////////////////////////////////////
void CBallSprite::InitSpriteVelocity(void)
{
	// Keep changing the velocity until speed is realistic
	while (1)
	{
		m_fXVel = (float)(rand() % 4);
		m_fYVel = (float)(rand() % 5);
		if( m_fXVel >= 2.0)
			if( m_fYVel >= 3.0)
				break;
	}
	if ((rand() % 2) == 0)
		m_fXVel = m_fXVel * -1;
}

//////////////////////////////////////////////////////
// UpdateSprite()
//////////////////////////////////////////////////////
void CBallSprite::UpdateSprite(float fPlyXPos, float fPlyYPos, float fCmpXPos, float fCmpYPos)
{
	float newXPos = GetXPosition() + GetXVelocity();
	float newYPos = GetYPosition() + GetYVelocity();
	m_HitFlag = CBallSprite::NOHIT;
	
	// Bounce the ball if it hits the top or bottom
    if(newYPos < 0)
    {
        newYPos = 0;
		SetYVelocity(-(GetYVelocity()));
		m_HitFlag = CBallSprite::HITWALL;
    }
	else if(newYPos > (WINDOW_HEIGHT - GetHeight()))
    {
        newYPos = (float)(WINDOW_HEIGHT - GetHeight());
        SetYVelocity(-(GetYVelocity()));
		m_HitFlag = CBallSprite::HITWALL;
    }
	else
	{
		// Bounce the ball if it hits the players bat
		if(newXPos <= (fPlyXPos + BAT_WIDTH))
		{
			if((newYPos + GetHeight() >= fPlyYPos) && (newYPos <= fPlyYPos + BAT_HEIGHT))
			{
				newXPos = (float)(BAT_EDGE_SPACER + BAT_WIDTH);
				// Up the ball speed
				SetXVelocity(((GetXVelocity() * -1) + BALL_SPEED_INC));

				m_HitFlag = CBallSprite::HITHUMAN;
			}
		}

		// Bounce the ball if it hits the computers bat
		if((newXPos + GetWidth()) >= fCmpXPos)
		{
			if(((newYPos + GetHeight()) >= fCmpYPos) && (newYPos <= (fCmpYPos + BAT_HEIGHT)))
			{
				newXPos = (float)(WINDOW_WIDTH - (BAT_EDGE_SPACER + BAT_WIDTH + GetWidth()));
				// Up the ball speed
				SetXVelocity(((GetXVelocity() * -1) - BALL_SPEED_INC));

				m_HitFlag = CBallSprite::HITCOMPUTER;
			}
		}
	}
	
	SetXPosition(newXPos);
	SetYPosition(newYPos);
	CalculateVertices();
}

//////////////////////////////////////////////////////
// SetXVelocity()
//////////////////////////////////////////////////////
void CBallSprite::SetXVelocity(float fNewXVel)
{
	m_fXVel = fNewXVel;
}

//////////////////////////////////////////////////////
// GetXVelocity()
//////////////////////////////////////////////////////
float CBallSprite::GetXVelocity(void)
{
	return m_fXVel;
}

//////////////////////////////////////////////////////
// SetYVelocity()
//////////////////////////////////////////////////////
void CBallSprite::SetYVelocity(float fNewYVel)
{
	m_fYVel = fNewYVel;
}

//////////////////////////////////////////////////////
// GetYVelocity()
//////////////////////////////////////////////////////
float CBallSprite::GetYVelocity(void)
{
	return m_fYVel;
}

//////////////////////////////////////////////////////
// GetHitFlag()
//////////////////////////////////////////////////////
CBallSprite::HITFLAG CBallSprite::GetHitFlag(void)
{
	return m_HitFlag;
}