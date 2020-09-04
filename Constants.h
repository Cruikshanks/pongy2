//////////////////////////////////////////////////////
// Constants.h
//////////////////////////////////////////////////////

#pragma once

// Window details
const WINDOW_WIDTH = 640;
const WINDOW_HEIGHT = 480;

// Sprite and image constants
const BAT_WIDTH = 10;
const BAT_HEIGHT = 75;
const BALL_WIDTH = 32;
const BALL_HEIGHT = 32;
const MAINTITLE_WIDTH = 300;
const MAINTITLE_HEIGHT = 148;
const SUBTITLE_WIDTH = 300;
const SUBTITLE_HEIGHT = 42;
const SPLASH_WIDTH = 484;
const SPLASH_HEIGHT = 194;

const BAT_EDGE_SPACER = 10;
const SHADOW_OFFSET = 3;

// Human and computer bat speeds/modifiers
const float HUMAN_YVEL = 8.0;
const float CMP_YVEL = 6.0;
const float BALL_SPEED_INC = 0.5;

// Computer level modifiers/constants
const MAX_CMPLEVEL = -(WINDOW_WIDTH) + (3 * 20);
const MIN_CMPLEVEL = (WINDOW_WIDTH / 2) + (3 * 20);
const CMPLEVEL_INC = 20;

// Delay constants
const GAME_STOP = 100;
const LOADING_DELAY = 100;
const SPLASH_DELAY = 250;

