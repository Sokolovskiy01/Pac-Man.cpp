#pragma once
#include <SFML/Graphics.hpp>

class map_block : public sf::Drawable
{
public:
	map_block(float X_1, float Y_1, float X_2, float Y_2);
	map_block() = default;
	~map_block() = default;

	sf::Vector2f getposition();

	float left();
	float right();
	float top();
	float bottom();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::RectangleShape block;
};
