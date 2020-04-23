#include "pch.h"
#include "helpers.h"
#include "player.h"

helpers::helpers(float X, float Y)
{
	helper.setRadius(3.5f);
	helper.setOrigin(4.0f, 4.0f);
	helper.setFillColor(sf::Color::Red);
	helper.setPosition(X, Y);
}

sf::Vector2f helpers::getposition() { return this->helper.getPosition(); }

bool helpers::movement_dir(int dir)
{
	char buff;
	if (dir == 1) buff = 'd';
	if (dir == 18) buff = 'a';
	if (dir == 35) buff = 'w';
	if (dir == 52) buff = 's';
	if (move == '0') {
		move = buff;
		return true;
	}
	else {
		if (move == buff){
			return true;
		}
		else {
			move = buff;
			return false;
		}
	}
}

bool helpers::movement_dir_g(int gdir)
{
	char buff;
	if (gdir == 1) buff = 'd';
	if (gdir == 17) buff = 'a';
	if (gdir == 33) buff = 'w';
	if (gdir == 49) buff = 's';
	if (move == '0') {
		move = buff;
		return true;
	}
	else {
		if (move == buff) {
			return true;
		}
		else {
			move = buff;
			return false;
		}
	}
}

void helpers::mov_clear(){ move = '0'; }

float helpers::left() {	return this->helper.getPosition().y - this->helper.getRadius(); }
float helpers::right() { return this->helper.getPosition().y + this->helper.getRadius(); }
float helpers::top() { return this->helper.getPosition().x - this->helper.getRadius(); }
float helpers::bottom() { return this->helper.getPosition().x + this->helper.getRadius(); }

void helpers::draw(sf::RenderTarget & target, sf::RenderStates state) const // test draw
{
	target.draw(this->helper, state);
}
