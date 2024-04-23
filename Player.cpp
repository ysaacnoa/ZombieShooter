#include "Player.h"

// The constructor ****************************************************
Player::Player() {
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	// Associate a texture with the sprite
	m_Texture.loadFromFile("graphics/player.png");
	m_Sprite.setTexture(m_Texture);
	// Set the origin of the sprite to the center, for smooth rotation
	m_Sprite.setOrigin(25, 25);
		
}

// The player will be spawned at the center of the arena ***************
void Player::spawn(
	IntRect arena,
	Vector2f resolution,
	int tileSize) 
{
	//Place the player in the middle of the arena
	m_Position.x = arena.width / 2.0f;
	m_Position.y = arena.height / 2.0f;

	//Copy the details of the arena to the player's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	//Remember how big the tiles are in this arena
	m_TileSize = tileSize;

	//Store the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;	
}

void Player::resetPlayerState() {
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

// Handle the player getting hit by a zombie **************************
Time Player::getLastTimeHit() {
	return m_LastHit;
}

bool Player::hit(Time timeHit) {
	if (timeHit.asMilliseconds() - m_LastHit.asMicroseconds() > 200) {
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else {
		return false;
	}
}
 
// Getters for player position, rotation, sprite and health ************
FloatRect Player::getPosition() { 
	return m_Sprite.getGlobalBounds(); 
}

Vector2f Player::getCenter(){
	return m_Position;
}

float Player::getRotation() {
	return m_Sprite.getRotation();
}

Sprite Player::getSprite() {
	return m_Sprite;
}

int Player::getHealth() {
	return m_Health;
}

//Move the player based on the input this frame ************************

void Player::moveLeft() {
	m_LeftPressed = true;
}

void Player::moveRight(){
	m_RightPressed = true;
}

void Player::moveUp() {
	m_UpPressed = true;
}

void Player::moveDown() {
	m_DownPressed = true;
}

void Player::stopLeft() {
	m_LeftPressed = false;
}

void Player::stopRight() {
	m_RightPressed = false;
}

void Player::stopUp() {
	m_UpPressed = false;
}

void Player::stopDown() {
	m_DownPressed = false;
}

void Player::update(float elapsedTime, Vector2i mousePosition) {
	if (m_UpPressed) {
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_DownPressed) {
		m_Position.y += m_Speed * elapsedTime;
	}

	if (m_LeftPressed) {
		m_Position.x -= m_Speed * elapsedTime;
	}

	if (m_RightPressed) {
		m_Position.x += m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);

	// Keep the player in the arena
	if (m_Position.x > m_Arena.width - m_TileSize) {
		m_Position.x = m_Arena.width - m_TileSize;
	}

	if (m_Position.x < m_Arena.left + m_TileSize) {
		m_Position.x = m_Arena.left + m_TileSize;
	}

	if (m_Position.y > m_Arena.height - m_TileSize) {
		m_Position.y = m_Arena.height - m_TileSize;
	}

	if (m_Position.y < m_Arena.top + m_TileSize) {
		m_Position.y = m_Arena.top + m_TileSize;
	}

	//sincronize mouse and player position
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2, mousePosition.x - m_Resolution.x / 2) * 180) / 3.14159f;

	m_Sprite.setRotation(angle);
}

void Player::upgradeSpeed() {
	// 20% speed upgrade
	m_Speed += (START_SPEED * .2);
}

void Player::upgradeHealth() {
	// 20% health upgrade
	m_Health += (START_HEALTH * .2);
}

void Player::increaseHealthLevel( int amount ) {
	m_Health += amount;

	// But not beyond the maximum
	if (m_Health > m_MaxHealth) {
		m_Health = m_MaxHealth;
	}
}

