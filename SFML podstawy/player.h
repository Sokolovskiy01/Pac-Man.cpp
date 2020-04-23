#pragma once
#include <SFML/Graphics.hpp>

class player : public sf::Drawable
{
public:
	player(float X, float Y);
	player() = default;
	~player() = default;

	void update();
	void change_sprite(int w, int dir);
	void stop();

	void moveup();
	void movedown();
	void moveright();
	void moveleft();

	void teleportright(unsigned int Width);
	void teleportleft(unsigned int Width);
	void telepotrup(unsigned int Height);
	void telepotrdown(unsigned int Height);

	sf::Vector2f getposition();
	void setpoisition(float X, float Y);

	void erase();
	void scale(unsigned int Width);

	void death(int dir, int fps);

	float getvelocity();

	float left();
	float right();
	float top();
	float bottom();

	float fake_left();
	float fake_right();
private:
	sf::CircleShape Pac;
	const float PacRadius{ 7.5f };
	const float Velocity{ 1.0f };
	int screen_width;
	int screen_height;
	sf::Texture pact;
	sf::Sprite pac_sprite;
	sf::Sprite pac_illusion;
	sf::Vector2f direction{ 0,0 };
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

