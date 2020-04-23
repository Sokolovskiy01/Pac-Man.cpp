#pragma once
#include <SFML/Graphics.hpp>

class helpers : public sf::Drawable
{
public:
	helpers(float X, float Y);
	helpers() = default;
	~helpers() = default;

	sf::Vector2f getposition();

	bool movement_dir(int dir);
	bool movement_dir_g(int gdir);
	void mov_clear();

	float left();
	float right();
	float top();
	float bottom();
private:
	char move = '0';
	sf::CircleShape helper;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

