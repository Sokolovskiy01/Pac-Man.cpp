#include "pch.h"
#include "ghost.h"

ghost::ghost(float g_X, float g_Y, sf::Texture& texture)
{
	ghost_shape.setPosition(g_X, g_Y);
	ghost_shape.setSize({ this->ghost_width ,this->ghost_height });
	ghost_shape.setOrigin(8.0f, 8.0f);

	ghost_sprite.setTexture(texture);
	ghost_illusion.setTexture(texture);

	ghost_sprite.setTextureRect(sf::IntRect(1, 1, 14, 14));
	ghost_illusion.setTextureRect(ghost_sprite.getTextureRect());

	ghost_sprite.setOrigin(7.5f, 7.5f);
	ghost_illusion.setOrigin(7.5f, 7.5f);

	ghost_illusion.setPosition(-16, -16);
}

void ghost::update() {
	ghost_sprite.setPosition(this->ghost_shape.getPosition());
	ghost_shape.move(this->direction);
}

void ghost::change_sprite(int w, int dir) {
	if (w == 0) ghost_sprite.setTextureRect(sf::IntRect(1, dir, 14, 14));
	if (w == 8) ghost_sprite.setTextureRect(sf::IntRect(17, dir, 14, 14));
	if (w == 16) ghost_sprite.setTextureRect(sf::IntRect(1, dir, 14, 14));
	if (w == 24) ghost_sprite.setTextureRect(sf::IntRect(17, dir, 15, 15));
	if (w == 32) ghost_sprite.setTextureRect(sf::IntRect(1, dir, 15, 15));
}

bool ghost::slow_down()
{
	return false;
}

void ghost::moveleft() {
	direction.x = -velocity;
	direction.y = 0;
}

void ghost::moveright(){
	direction.x = velocity;
	direction.y = 0;
}

void ghost::moveup() {
	direction.y = -velocity;
	direction.x = 0;
}

void ghost::movedown() {
	direction.y = velocity;
	direction.x = 0;
}

void ghost::teleportright(unsigned int Width) {	this->ghost_shape.setPosition(Width - this->ghost_shape.getOrigin().x, this->ghost_shape.getPosition().y); }
void ghost::teleportleft(unsigned int Width) { this->ghost_shape.setPosition(0 + this->ghost_shape.getOrigin().x, this->ghost_shape.getPosition().y); }

int ghost::getdir() { return this->gdir; }
void ghost::setdir(int D) { this->gdir = D; }

sf::Vector2f ghost::getposition() {	return this->ghost_shape.getPosition(); }
void ghost::setpoisition(float X, float Y) { this->ghost_shape.setPosition(X, Y); }

void ghost::erase()	{ this->ghost_illusion.setPosition(-16, -16); }

void ghost::scale(unsigned int Width) {
	if (this->left() <= 0) this->ghost_illusion.setPosition(Width + left() + this->ghost_shape.getOrigin().x, this->ghost_shape.getPosition().y);
	else if (this->right() >= Width) this->ghost_illusion.setPosition(0 + right() - Width - this->ghost_sprite.getOrigin().x, this->ghost_sprite.getPosition().y);
	else this->ghost_illusion.setPosition(-16, -16);
}

float ghost::getvelocity() { return this->velocity; }

float ghost::left() { return this->ghost_shape.getPosition().x - this->ghost_shape.getOrigin().x; }
float ghost::right() { return this->ghost_shape.getPosition().x + this->ghost_shape.getOrigin().x; }
float ghost::top() { return this->ghost_shape.getPosition().y - this->ghost_shape.getOrigin().y; }
float ghost::bottom() { return this->ghost_shape.getPosition().y + this->ghost_shape.getOrigin().y; }

float ghost::fake_left() { return this->ghost_illusion.getPosition().x - this->ghost_shape.getOrigin().x; }
float ghost::fake_right() {	return this->ghost_illusion.getPosition().x + this->ghost_shape.getOrigin().x; }

void ghost::draw(sf::RenderTarget & target, sf::RenderStates state) const {
	target.draw(this->ghost_sprite, state);
	target.draw(this->ghost_illusion, state);;
}
