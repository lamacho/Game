#ifndef Gracz_h
#define Gracz_h

#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include "Mob.h"


enum Direction { Down, Left, Right, Up, Down_a, Left_a, Right_a, Up_a };
class Mob;

class Gracz {
public:
	sf::Texture pTexture;
	sf::Sprite playerImage;
	sf::FloatRect hitbox;
	int HP, ATAK, PT, SPD;
	sf::Vector2i source;
	bool ruch;
	bool dead;
	sf::FloatRect box;

	void Update();

	Gracz(std::string graczTex, int x, int y, sf::Vector2i source1) {
		playerImage.setPosition(x,y);
		dead = false;
		if (!pTexture.loadFromFile(graczTex)) 
			std::cout << "nie udalo sie zaladowc textury gracza" << std::endl;
			playerImage.setTexture(pTexture);
		source = source1;

		box.height = 40;
		box.width = 40;
		box.left = playerImage.getPosition().x;
		box.top = playerImage.getPosition().y;
		
		hitbox.height = 100;
		hitbox.width = 100;
		hitbox.left = playerImage.getPosition().x;
		hitbox.top = playerImage.getPosition().y;
		 
		ruch = false;
		HP = 3;
		ATAK = 1;
		PT = 0;
		//a = 0;
		SPD = 1;
	}
	
	void walk_up();
	void walk_down();
	void walk_left();
	void walk_right();
	void czy_ruch();
	void hit(Mob *mob);
	void hited(Mob *mob);
	bool is_dead();
	Gracz* getter();

	friend std::ostream & operator<< (std::ostream &wyjscie, const Gracz &g);

	
};

#endif
