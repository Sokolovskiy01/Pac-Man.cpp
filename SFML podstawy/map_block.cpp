#include "pch.h"
#include "map_block.h"

map_block::map_block(float X_1, float Y_1, float X_2, float Y_2)
{
	block.setPosition((X_1 + X_2) /2, (Y_1 + Y_2) /2);
	float b_width = X_2 - X_1;
	float b_height = Y_2 - Y_1;
	block.setSize({ b_width, b_height });
	block.setOrigin(b_width / 2, b_height / 2);
	block.setFillColor(sf::Color::Green); // test
}

sf::Vector2f map_block::getposition() {	return block.getPosition(); }

float map_block::left() { return this->block.getPosition().x - this->block.getSize().x / 2.0f; }
float map_block::right() { return this->block.getPosition().x + this->block.getSize().x / 2.0f; }
float map_block::top() { return this->block.getPosition().y - this->block.getSize().y / 2.0f; }
float map_block::bottom() { return this->block.getPosition().y + this->block.getSize().y / 2.0f; }

void map_block::draw(sf::RenderTarget & target, sf::RenderStates state) const //test draw
{
	target.draw(this->block, state);
}
