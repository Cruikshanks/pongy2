//////////////////////////////////////////////////////
// HumanSprite.h
//////////////////////////////////////////////////////

#pragma once

#include "sprite.h"
#include "Constants.h"

class CHumanSprite : public CSprite
{
public:
	// Constructor - initializes the sprites width and height
	CHumanSprite(int iWidth, int iHeight);
	// Destructor
	~CHumanSprite(void);

	// Updates the sprites position
	void UpdateSprite(float newYPos);
	// Sets the sprites Y velocity
	void SetYVelocity(float fVel);
	// Returns the sprites Y velocity
	float GetYVelocity(void);

private:
	float m_fYVel;
};
