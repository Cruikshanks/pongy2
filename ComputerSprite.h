//////////////////////////////////////////////////////
// ComputerSprite.h
//////////////////////////////////////////////////////

#pragma once

#include "sprite.h"
#include "Constants.h"

class CComputerSprite : public CSprite
{
public:
	// Constructor - initializes the sprites width and height
	CComputerSprite(int iWidth, int iHeight);
	// Destructor
	~CComputerSprite(void);

	//  Updates the sprites position
	void UpdateSprite(float fBallYPos);
	// Sets the sprites Y velocity
	void SetYVelocity(float fVel);
	// Returns the sprites Y velocity
	float GetYVelocity(void);
	
private:
	float m_fYVel;
};
