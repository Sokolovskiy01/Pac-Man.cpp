#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class ghost : public sf::Drawable
{
public:
	ghost(float g_X, float g_Y, sf::Texture& texture);
	ghost() = default;
	~ghost() = default;

	void update();
	void change_sprite(int w, int dir);
	bool slow_down(); //in tunnels

	void moveleft();
	void moveright();
	void moveup();
	void movedown();

	void teleportright(unsigned int Width);
	void teleportleft(unsigned int Width);

	int getdir();
	void setdir(int D);

	sf::Vector2f getposition();
	void setpoisition(float X, float Y);

	void erase();
	void scale(unsigned int Width);

	float getvelocity();

	float left();
	float right();
	float top();
	float bottom();

	float fake_left();
	float fake_right();
private:
	sf::RectangleShape ghost_shape;
	const float ghost_width{ 15.0f };
	const float ghost_height{ 15.0f };
	float velocity{ 1.0f };
	int gdir = 1;
	sf::Texture ghostt;
	sf::Texture texture;
	sf::Sprite ghost_sprite;
	sf::Sprite ghost_illusion;
	sf::Vector2f direction{ 1,0 };
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};