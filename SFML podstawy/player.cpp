#include "pch.h"
#include "player.h"

player::player(float X, float Y)
{
	Pac.setPosition(X, Y);
	Pac.setRadius(this->PacRadius);
	Pac.setOrigin(8, 8);

	pact.loadFromFile("res//img//Pacman//Pac2.png");

	pac_sprite.setTexture(pact);
	pac_illusion.setTexture(pact);

	pac_sprite.setTextureRect(sf::IntRect(1, 1, 15, 15));
	pac_illusion.setTextureRect(sf::IntRect(pac_sprite.getTextureRect()));

	pac_sprite.setOrigin(8, 8);
	pac_illusion.setOrigin(8, 8);

	pac_illusion.setPosition(-8, -8);
}

void player::update() { 
	pac_sprite.setPosition(this->Pac.getPosition());
	Pac.move(this->direction);
	pac_illusion.setTextureRect(sf::IntRect(pac_sprite.getTextureRect()));
}

void player::change_sprite(int w, int dir)
{
	if (w == 0) pac_sprite.setTextureRect(sf::IntRect(18, dir, 15, 15));
	if (w == 8) pac_sprite.setTextureRect(sf::IntRect(35, dir, 15, 15));
	if (w == 16) pac_sprite.setTextureRect(sf::IntRect(18, dir, 15, 15));
	if (w == 24) pac_sprite.setTextureRect(sf::IntRect(1, dir, 15, 15));
	if (w == 32) pac_sprite.setTextureRect(sf::IntRect(18, dir, 15, 15));
}

void player::stop(){
	direction.x = 0.0f;
	direction.y = 0.0f;
}

void player::moveup() { 
	direction.x = 0;
	direction.y = -Velocity;
}
void player::movedown() {
	direction.x = 0;
	direction.y = Velocity; 
}
void player::moveright() {
	direction.x = Velocity;
	direction.y = 0;
}
void player::moveleft(){
	direction.x = -Velocity;
	direction.y = 0;
}

void player::teleportright(unsigned int Width) { this->Pac.setPosition(Width - this->Pac.getOrigin().x, this->Pac.getPosition().y); }
void player::teleportleft(unsigned int Width) { this->Pac.setPosition(0 + this->Pac.getOrigin().x, this->Pac.getPosition().y); }
void player::telepotrup(unsigned int Height) { this->Pac.setPosition(this->Pac.getPosition().x, 0 + this->Pac.getOrigin().y); }
void player::telepotrdown(unsigned int Height) { this->Pac.setPosition(this->Pac.getPosition().x, Height - this->Pac.getOrigin().y); }

sf::Vector2f player::getposition() { return Pac.getPosition(); }

void player::setpoisition(float X, float Y) { this->Pac.setPosition(X, Y); }

void player::erase() { pac_illusion.setPosition(-8, -8); }

void player::scale(unsigned int Width) {
	if (this->left() <= 0) this->pac_illusion.setPosition(Width + left() + this->Pac.getOrigin().x, this->Pac.getPosition().y);
	else if (this->right() >= Width) this->pac_illusion.setPosition(0 + right() - Width - this->Pac.getOrigin().x, this->Pac.getPosition().y);
	else this->pac_illusion.setPosition(-8, -8);
}

void player::death(int dir, int fps) {
	if (fps == 40) pac_sprite.setTextureRect(sf::IntRect(52, dir, 15, 15));
	if (fps == 80) pac_sprite.setTextureRect(sf::IntRect(69, dir, 15, 15));
	if (fps == 120) pac_sprite.setTextureRect(sf::IntRect(86, dir, 15, 15));
}

float player::getvelocity() { return this->Velocity; }

float player::left() { return this->Pac.getPosition().x - Pac.getOrigin().x; }
float player::right() { return this->Pac.getPosition().x + Pac.getOrigin().x; }
float player::top() { return this->Pac.getPosition().y - Pac.getOrigin().y; }
float player::bottom() { return this->Pac.getPosition().y + Pac.getOrigin().y; }

float player::fake_left() { return this->pac_illusion.getPosition().x - this->Pac.getOrigin().x; }
float player::fake_right() { return this->pac_illusion.getPosition().x + this->Pac.getOrigin().x; }

void player::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->pac_sprite, state);
	target.draw(this->pac_illusion, state);
}