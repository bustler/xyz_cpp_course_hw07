#pragma once

const unsigned char randnumberapple = 0x01;
const unsigned char infiniteapple = 0x02;
const unsigned char speedup = 0x04;
const unsigned char randnumberrock = 0x08;
const unsigned char rockoff = 0x10;
const unsigned char diagonalmovement = 0x20;
const unsigned char noborder = 0x40;
const unsigned char havesound = 0x80;

const unsigned char allSetings[] = {randnumberapple, infiniteapple, speedup, randnumberrock, rockoff, diagonalmovement, noborder, havesound};


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const float INITIAL_SPEED = 100.f;
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 20.f;
const float ANGLE_MOVEMENT = 0.707106781f;// sin45 || cos45
const float MIN_ROCK_SIZE = 5.f;
const float MAX_ROCK_SIZE = 25.f;
const int NUM_ROCK = 18;
const int NUM_APPLE = 20;
const float APPLE_SIZE = 20.f;