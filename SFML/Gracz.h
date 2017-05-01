#ifndef Gracz_h
#define Gracz_h

#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include "node.h"
#include "Mob.h"


enum Direction { Down, Left, Right, Up, Down_a, Left_a, Right_a, Up_a };
class Mob;

class Gracz {
public:
	sf::Texture pTexture;
	sf::Sprite playerImage;
	sf::FloatRect hitbox;
	int HP, ATAK, PT, a,SPD;
	sf::Vector2i source;
	bool ruch;
	sf::FloatRect box;

	void Update();

	Gracz(std::string graczTex, int x, int y, sf::Vector2i source1) {
		playerImage.setPosition(x,y);
		if (!pTexture.loadFromFile(graczTex)) 
			std::cout << "nie udalo sie zaladowc textury gracza" << std::endl;
			playerImage.setTexture(pTexture);
		source = source1;

		box.height = 40;
		box.width = 40;
		box.left = playerImage.getPosition().x+10;
		box.top = playerImage.getPosition().y+10;
		
		hitbox.height = 100;
		hitbox.width = 100;
		hitbox.left = playerImage.getPosition().x - 10;
		hitbox.top = playerImage.getPosition().y - 10;
		 
		ruch = false;
		HP = 3;
		ATAK = 1;
		PT = 0;
		a = 0;
		SPD = 3;
	}
	
	void walk_up();
	void walk_down();
	void walk_left();
	void walk_right();
	void czy_ruch();
	void hit(Mob *mob);
	void hited(Mob *mob);
	bool is_dead();

	friend std::ostream & operator<< (std::ostream &wyjscie, const Gracz &g);

	
};

#endif
