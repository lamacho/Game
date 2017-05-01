#ifndef Mob_h
#define Mob_h

#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include "node.h"
#include "Gracz.h"


class Mob{
public:
	static int act_id_mob;
	static std::vector <Mob*> mobki;
	sf::Texture mTexture;
	sf::Sprite mobImage;
	int HP, ATAK, ID, SPD, hitting;
	sf::Vector2i source;
	bool ruch;
	sf::FloatRect box;
	sf::FloatRect boxat;


	void Update();

	Mob(std::string graczTex, int x, int y, sf::Vector2i source1) {
		mobki.push_back(this);
		mobImage.setPosition(x, y);
		if (!mTexture.loadFromFile(graczTex))
			std::cout << "nie udalo sie zaladowc textury gracza" << std::endl;
		mobImage.setTexture(mTexture);
		source = source1;
		mobImage.setColor(sf::Color::Blue);

		ID = act_id_mob;
		SPD = 0.5;
		act_id_mob++;
		hitting = 100;


		box.height = 60;
		box.width = 60;
		box.left = mobImage.getPosition().x;
		box.top = mobImage.getPosition().y;
		boxat.height = 70;
		boxat.width = 70;
		boxat.left = mobImage.getPosition().x-5;
		boxat.top = mobImage.getPosition().y-5;

		ruch = false;
		HP = 3;
		ATAK = 1;

	}

	void walk_up();
	void walk_down();
	void walk_left();
	void walk_right();
	void czy_ruch();
	void AI();
	void hited(int kierunek);

	bool is_dead();
};

#endif