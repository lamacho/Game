// wsk na obiekt klasy

#ifndef Moneta_h
#define Moneta_h

#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include <vector>
#include "Gracz.h"


class Moneta;

static int act_id;

class Moneta {
public:
	static std::vector<Moneta*> monety;
	sf::RectangleShape rect;
	sf::FloatRect box;
	sf::Texture mmTexture;
	sf::Sprite mmImage;
	int value, ID;

	Moneta() {
		monety.push_back(this);
	}

	Moneta(sf::Vector2f position, sf::Vector2f size, int wartosc, std::string str) {
		rect.setSize(size);
		rect.setPosition(position);
		mmImage.setPosition(position.x, position.y);
		if (!mmTexture.loadFromFile(str))
			std::cout << "nie udalo sie zaladowc textury monety" << std::endl;
		mmImage.setTexture(mmTexture);

		monety.push_back(this);
		box.height = 30;
		box.width = 30;
		box.left = rect.getPosition().x + 15;
		box.top = rect.getPosition().y + 15;
		value = wartosc;
		ID = act_id;
		act_id++;
	}

	void Update();
	void find_m(int *g);
};



#endif