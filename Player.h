#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	//where is the player
	Vector2f m_Position;

	//need a stprite 
	Sprite m_Sprite;

	// !!Mira este espacio - Cambios interesantes aquí pronto!!
	//add a texture
	Texture m_Texture;

	//what is the screen resolution
	Vector2f m_Resolution;

	//how big is the current arena
	IntRect m_Arena;

	//how big is each tile of the arena
	int m_TileSize;

	//which direction is the player currently moving
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	//how much health has the player got
	int m_Health;

	//what is the maximum health the player can have
	int m_MaxHealth;

	//when was the player last hit
	Time m_LastHit;

	//speed in pixels per second
	float m_Speed;

public:
	Player();

	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	//call this at the end of every game
	void resetPlayerState();

	//handle the player getting hit by a zombie
	bool hit(Time hit);

	//how long ago was the player last hit
	Time getLastTimeHit();

	//where is the player
	FloatRect getPosition();

	//where is the center of the player
	Vector2f getCenter();

	//which angle is the player facing
	float getRotation();

	//send a copy of the sprite to main
	Sprite getSprite();

	//move the player
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	//stop the player moving in a specific direction
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	//we will call this function once every frame
	void update(float elapsedTime, Vector2i mousePosition);

	//give the player a speed boost
	void upgradeSpeed();

	//give the player some health
	void upgradeHealth();

	//increase the maximum amount of health the player can have
	void increaseHealthLevel(int amount);

	//how much health has the player currently got
	int getHealth();
};	