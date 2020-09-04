//////////////////////////////////////////////////////
// BallSprite.h
//////////////////////////////////////////////////////

#pragma once

#include "sprite.h"
#include "Constants.h"

class CBallSprite : public CSprite
{
public:
	enum HITFLAG {HITHUMAN, HITCOMPUTER, HITWALL, NOHIT};

	// Constructor - initializes the sprites width and height
	CBallSprite(int iWidth, int iHeight);
	// Destructor
	~CBallSprite(void);

	// Initialise ball X and Y velocity
	void InitSpriteVelocity(void);
	// Updates the sprites position and hit flag in the case of an impact
	void UpdateSprite(float fPlyXPos, float fPlyYPos, float fCmpXPos, float fCmpYPos);
	// Sets the sprites X velocity
	void SetXVelocity(float fNewXVel);
	// Returns the sprites X velocity
	float GetXVelocity(void);
	// Sets the sprites Y velocity
	void SetYVelocity(float fNewYVel);
	// Returns the sprites Y velocity
	float GetYVelocity(void);
	// Returns the sprites hit flag
	HITFLAG GetHitFlag();

private:
	float m_fXVel;		// The sprites X velocity
	float m_fYVel;		// The sprites Y velocity
	HITFLAG m_HitFlag;	// The sprites hit flag - used when an impact occurs
};
