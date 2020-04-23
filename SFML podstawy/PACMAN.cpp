#include "pch.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "player.h"
#include "ghost.h"
#include "map_block.h"
#include "helpers.h"

using namespace sf;
using namespace std;

template <class T1> bool isintersecting_right(map_block& A, T1& B) { return A.right() >= B.left() && A.left() - B.getvelocity() <= B.right() && A.bottom() >= B.top() && A.top() <= B.bottom(); } // Pacman and walls
template <class T1> bool isintersecting_left(map_block& A, T1& B) { return A.right() + B.getvelocity() >= B.left() && A.left() <= B.right() && A.bottom() >= B.top() && A.top() <= B.bottom(); } // Pacman and walls
template <class T1> bool isintersecting_top(map_block& A, T1& B) { return A.right() >= B.left() && A.left() <= B.right() && A.bottom() + B.getvelocity() >= B.top() && A.top() <= B.bottom(); } // Pacman and walls
template <class T1> bool isintersecting_bottom(map_block& A, T1& B) { return A.right() >= B.left() && A.left() <= B.right() && A.bottom() >= B.top() && A.top() - B.getvelocity() <= B.bottom(); } // Pacman and walls

bool should_i_help_you(helpers& H, player& P) {	return sqrt((H.getposition().x - P.getposition().x) * (H.getposition().x - P.getposition().x) + (H.getposition().y - P.getposition().y) * (H.getposition().y - P.getposition().y)) <= 4; } // Pacman and "helpers"
bool should_i_help_you(helpers& H, ghost& G) { return sqrt((H.getposition().x - G.getposition().x) * (H.getposition().x - G.getposition().x) + (H.getposition().y - G.getposition().y) * (H.getposition().y - G.getposition().y)) < G.getvelocity(); } // Ghosts and "helpers"

bool iscathed(ghost& G, player P) {	return sqrt((P.getposition().x - G.getposition().x) * (P.getposition().x - G.getposition().x) + (P.getposition().y - G.getposition().y) * (P.getposition().y - G.getposition().y)) < 5; } // Pacman and Ghosts
bool behind_wall(ghost& G, int Width) {
	if (G.right() >= Width && G.left() >= Width) G.teleportleft(Width);
	else if (G.left() <= 0 && G.right() <= 0) G.teleportright(Width);
	else return false;
}

bool isoposite(int dir, int nextdir) {
	if ((dir == 1 && nextdir == 18) || (dir == 18 && nextdir == 1)) return true;
	if ((dir == 35 && nextdir == 52) || (dir == 35 && nextdir == 52)) return true;
	return false;
}

int direction_randomizer(int * buff, int ile) {
	int wynik = 0 + rand() % ile;
	//cout << wynik << ", ";
	wynik = buff[wynik];
	return wynik;
}

int randomizer(ghost& G,vector<map_block> blocks) {
	cout << "rand ";
	int ile = 0;
	int buff[4];
	for (auto& block : blocks) {
		if (!isintersecting_right(block, G)) buff[ile] = 1;
		else {
			ile--;
			break;
		}
	}
	ile++;
	for (auto& block : blocks) {
		if (!isintersecting_left(block, G)) buff[ile] = 17;
		else {
			ile--;
			break;
		}
	}
	ile++;
	for (auto& block : blocks) {
		if (!isintersecting_top(block, G)) buff[ile] = 33;
		else {
			ile--;
			break;
		}
	}
	ile++;
	for (auto& block : blocks) {
		if (!isintersecting_bottom(block, G)) buff[ile] = 49;
		else {
			ile--;
			break;
		}
	}
	ile++;
	int wynik = direction_randomizer(buff, ile);
	ile = 0;
	return wynik;
}

void moveghost(ghost& G, vector<map_block> blocks, vector<helpers> Help) {
	for (auto&helper : Help) {
		if (should_i_help_you(helper, G)) {
			G.setdir(randomizer(G, blocks));
			break;
		}
	}
	for (auto&block : blocks){
		if (G.getdir() == 1 && isintersecting_right(block, G)){
			G.setdir(randomizer(G, blocks));
			break;
		}
		if (G.getdir() == 17 && isintersecting_left(block, G)) {
			G.setdir(randomizer(G, blocks));
			break;
		}
		if (G.getdir() == 33 && isintersecting_top(block, G)) {
			G.setdir(randomizer(G, blocks));
			break;
		}
		if (G.getdir() == 49 && isintersecting_bottom(block, G)) {
			G.setdir(randomizer(G, blocks));
			break;
		}
	}
	if (G.getdir() == 1) G.moveright();
	if (G.getdir() == 17) G.moveleft();
	if (G.getdir() == 33) G.moveup();
	if (G.getdir() == 49) G.movedown();
}

int main()
{
	srand(time(NULL));
	int fps = 0;
	int dir = 1;
	int nextdir = dir;
	const unsigned int scr_width = 270;
	const unsigned int scr_height = 299;

	Texture map;
	map.loadFromFile("res//img//map.bmp");
	Sprite maps;
	maps.setTexture(map);

	player P(160, 227);

	Texture red;
	red.loadFromFile("res//img//ghost1//red.png");
	ghost G_R(135, 227, red);

	Texture blue;
	blue.loadFromFile("res//img//Blue_ghost//blue.png");
	ghost G_B(135, 227, blue);

	Texture orange;
	orange.loadFromFile("res//img//Orange_ghost//orange.png");
	ghost G_O(135, 227, orange);

	Texture pink;
	pink.loadFromFile("res//img//Pink_ghost//pink.png");
	ghost G_P(135, 227, pink);

	RenderWindow window{ VideoMode {scr_width,scr_height}, "PAC-MAN" };
	vector<map_block> blocks;

	blocks.emplace_back(5.0f, 5.0f, 265.0f, 6.0f);
	blocks.emplace_back(24.0f, 24.0f, 54.0f, 44.0f);
	blocks.emplace_back(72.0f, 24.0f, 112.0f, 44.0f);
	blocks.emplace_back(130.0f, 4.0f, 141.0f, 44.0f);
	blocks.emplace_back(159.0f, 24.0f, 199.0f, 44.0f);
	blocks.emplace_back(217.0f, 24.0f, 247.0f, 44.0f);
	blocks.emplace_back(24.0f, 62.0f, 54.0f, 73.0f);
	blocks.emplace_back(72.0f, 62.0f, 83.0f, 131.0f);
	blocks.emplace_back(83.0f, 91.0f, 112.0f, 102.0f);
	blocks.emplace_back(101.0f, 62.0f, 170.0f, 73.0f);
	blocks.emplace_back(130.0f, 73.0f, 141.0f, 102.0f);
	blocks.emplace_back(188.0f, 62.0f, 199.0f, 131.f);
	blocks.emplace_back(159.0f, 91.0f, 188.0f, 102.f);
	blocks.emplace_back(217.0f, 62.0f, 247.0f, 73.0f);
	blocks.emplace_back(4.0f, 4.0f, 6.0f, 92.0f);
	blocks.emplace_back(0.0f, 91.0f, 54.0f, 131.0f);
	blocks.emplace_back(265.0f, 4.0f, 266.0f, 92.0f);
	blocks.emplace_back(217.0f, 91.0f, 270.0f, 131.0f);
	blocks.emplace_back(101.0f, 120.0f, 170.0f, 160.0f);
	blocks.emplace_back(0.0f, 149.0f, 54.0f, 189.0f);
	blocks.emplace_back(217.0f, 149.0f, 270.0f, 189.0f);
	blocks.emplace_back(72.0f, 149.0f, 83.0f, 189.0f);
	blocks.emplace_back(188.0f, 149.0f, 199.0f, 189.0f);
	blocks.emplace_back(101.0f, 178.0f, 170.0f, 189.0f);
	blocks.emplace_back(130.0f, 189.0f, 141.0f, 218.0f);
	blocks.emplace_back(24.0f, 207.0f, 54.0f, 218.0f);
	blocks.emplace_back(43.0f, 218.0f, 54.0f, 247.0f);
	blocks.emplace_back(72.0f, 207.0f, 112.0f, 218.0f);
	blocks.emplace_back(159.0f, 207.0f, 199.0f, 218.0f);
	blocks.emplace_back(217.0f, 207.0f, 247.0f, 218.0f);
	blocks.emplace_back(217.0f, 218.0f, 227.0f, 247.0f);
	blocks.emplace_back(3.0f, 189.0f, 6.0f, 294.0f);
	blocks.emplace_back(3.0f, 236.0f, 25.0f, 247.0f);
	blocks.emplace_back(101.0f, 236.0f, 170.0f, 247.0f);
	blocks.emplace_back(245.0f, 236.0f, 265.0f, 247.0f);
	blocks.emplace_back(265.0f, 189.0f, 266.0f, 294.0f);
	blocks.emplace_back(3.0f, 294.0f, 266.0f, 295.0f);
	blocks.emplace_back(130.0f, 247.0f, 141.0f, 276.0f);
	blocks.emplace_back(24.0f, 265.0f, 112.0f, 276.0f);
	blocks.emplace_back(72.0f, 236.0f, 83.0f, 265.0f);
	blocks.emplace_back(159.0f, 265.0f, 247.0f, 276.0f);
	blocks.emplace_back(188.0f, 236.0f, 199.0f, 265.0f);

	vector<helpers> Help;
	
	Help.emplace_back(63.0f, 15.0f);
	Help.emplace_back(63.0f, 53.0f);
	Help.emplace_back(15.0f, 53.0f);
	Help.emplace_back(92.0f, 53.0f);
	Help.emplace_back(121.0f, 53.0f);
	Help.emplace_back(150.0f, 53.0f);
	Help.emplace_back(179.0f, 53.0f);
	Help.emplace_back(63.0f, 82.0f);
	Help.emplace_back(63.0f, 140.0f);
	Help.emplace_back(121.0f, 111.0f);
	Help.emplace_back(150.0f, 111.0f);
	Help.emplace_back(208.0f, 15.0f);
	Help.emplace_back(256.0f, 53.0f);
	Help.emplace_back(208.0f, 53.0f);
	Help.emplace_back(208.0f, 82.0f);
	Help.emplace_back(208.0f, 140.0f);
	Help.emplace_back(179.0f, 140.0f);
	Help.emplace_back(92.0f, 140.0f);
	Help.emplace_back(63.0f, 198.0f);
	Help.emplace_back(92.0f, 169.0f);
	Help.emplace_back(92.0f, 198.0f);
	Help.emplace_back(121.0f, 227.0f);
	Help.emplace_back(150.0f, 227.0f);
	Help.emplace_back(92.0f, 227.0f);
	Help.emplace_back(63.0f, 227.0f);
	Help.emplace_back(179.0f, 227.0f);
	Help.emplace_back(208.0f, 227.0f);
	Help.emplace_back(179.0f, 198.0f);
	Help.emplace_back(208.0f, 198.0f);
	Help.emplace_back(179.0f, 169.0f);
	Help.emplace_back(34.0f, 256.0f);
	Help.emplace_back(34.0f, 256.0f);
	Help.emplace_back(121.0f, 285.0f);
	Help.emplace_back(150.0f, 285.0f);
	Help.emplace_back(236.0f, 256.0f);

	window.setFramerateLimit(60);
	clock_t begin = clock();
	Event event;
	while (true) {
		window.clear(Color::Black);
		window.pollEvent(event);
		if (event.type == Event::Closed){
			window.close();
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))	nextdir = 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))	nextdir = 18;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) nextdir = 35;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) nextdir = 52;
		if (dir != nextdir) {
			if (isoposite(dir, nextdir)) {
				dir = nextdir;
			}
			else {
				bool was = 0;
				switch (nextdir) {
				case 1: {
					for (auto& block : blocks) {
						if (isintersecting_right(block, P)) {
							was = 1;
							break;
						}
						else was = 0;
					}
					break;
				}
				case 18: {
					for (auto& block : blocks) {
						if (isintersecting_left(block, P)) {
							was = 1;
							break;
						}
						else was = 0;
					}
					break;
				}
				case 35: {
					for (auto& block : blocks) {
						if (isintersecting_top(block, P)) {
							was = 1;
							break;
						}
						else was = 0;
					}
					break;
				}
				case 52: {
					for (auto& block : blocks) {
						if (isintersecting_bottom(block, P)) {
							was = 1;
							break;
						}
						else was = 0;
					}
					break;
				}
				default:
					break;
				}
				if (was != 1) dir = nextdir;
			}
		}
		switch (dir) {
		case 1: {
			if (P.right() >= scr_width && P.left() >= scr_width) P.teleportleft(scr_width);
			else P.erase();
			P.moveright();
			for (auto& block : blocks) {
				if (isintersecting_right(block, P)) {
					P.stop();
					break;
				}
			}
			break;
		}
		case 18: {
			if (P.left() <= 0 && P.right() <= 0) P.teleportright(scr_width);
			else P.erase();
			P.moveleft();
			for (auto& block : blocks) {
				if (isintersecting_left(block, P)) {
					P.stop();
					break;
				}
			}
			break;
		}
		case 35: {
			if (P.top() <= 0 && P.bottom() <= 0) P.telepotrdown(scr_height);
			P.moveup();
			for (auto& block : blocks) {
				if (isintersecting_top(block, P)) {
					P.stop();
					break;
				}
			}
			break;
		}
		case 52: {
			if (P.bottom() >= scr_height && P.top() >= scr_height) P.telepotrup(scr_height);
			P.movedown();
			for (auto& block : blocks) {
				if (isintersecting_bottom(block, P)) {
					P.stop();
					break;
				}
			}
			break;
		}
		default: break;
		}
		P.scale(scr_width);
		for (auto& helper : Help) {
			if (should_i_help_you(helper, P)) {
				if (!helper.movement_dir(dir)) { // must to optimize distance
					P.setpoisition(helper.getposition().x, helper.getposition().y);
					break;
				}
			}
			else helper.mov_clear();
		}
		fps++;
		if (fps % 8 == 0) G_R.change_sprite(fps, G_R.getdir());
		if (fps % 8 == 0) G_B.change_sprite(fps, G_B.getdir());
		if (fps % 8 == 0) G_O.change_sprite(fps, G_O.getdir());
		if (fps % 8 == 0) G_P.change_sprite(fps, G_P.getdir());
		if (fps % 8 == 0) P.change_sprite(fps, dir);
		if (fps == 32) fps = 0;
		P.update();
		moveghost(G_R, blocks, Help);
		G_R.scale(scr_width);
		behind_wall(G_R, scr_width);
		moveghost(G_B, blocks, Help);
		G_B.scale(scr_width);
		behind_wall(G_B, scr_width);
		moveghost(G_O, blocks, Help);
		G_O.scale(scr_width);
		behind_wall(G_O, scr_width);
		moveghost(G_P, blocks, Help);
		G_P.scale(scr_width);
		behind_wall(G_P, scr_width);
		window.draw(maps);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			for (auto& block : blocks) {
				window.draw(block);
			}
			for (auto& helper : Help) {
				window.draw(helper);
			}
		}
		G_R.update();
		if (clock() - begin > 10000) G_B.update();
		if (clock() - begin > 20000) G_O.update();
		if (clock() - begin > 30000) G_P.update();
		//cout << dir << " -> " << nextdir << endl;
		if (iscathed(G_R, P) || iscathed(G_B, P) || iscathed(G_O, P) || iscathed(G_P, P)) {
			fps = 0;
			while (true) {
				window.clear(Color::Black);
				fps++;
				P.death(dir, fps);
				window.draw(maps);
				window.draw(P);
				window.display();
				if (fps == 120) break;
			}
			window.close();
			system("cls");
			cout << "Tobi pizda" << endl;
			system("pause");
			break;
		}
		//cout << "Pac-man's position : X - " << P.getposition().x << " Y - " << P.getposition().y << endl;
		window.draw(P);
		window.draw(G_R);
		window.draw(G_B);
		window.draw(G_O);
		window.draw(G_P);
		window.display();
	}
	return 0;
}