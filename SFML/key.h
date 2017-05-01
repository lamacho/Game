#ifndef key_h
#define key_h

#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include "key.h"


class Klucz
{
public:
	static int act_id_klucz;
	static std::vector<Klucz*> klucze;
	sf::RectangleShape rect;
	sf::FloatRect box;
	sf::Texture mmTexture;
	sf::Sprite mmImage;
	int ID;

	Klucz(sf::Vector2f position, sf::Vector2f size) {
		rect.setSize(size);
		rect.setPosition(position);
		mmImage.setPosition(position.x, position.y);
		if (!mmTexture.loadFromFile("klucz.png"))
			std::cout << "nie udalo sie zaladowc textury miecza" << std::endl;
		mmImage.setTexture(mmTexture);
		mmImage.setColor(sf::Color::Yellow);
		klucze.push_back(this);
		box.height = 30;
		box.width = 30;
		box.left = rect.getPosition().x + 15;
		box.top = rect.getPosition().y + 15;
		ID = act_id_klucz;
		act_id_klucz++;
	}

	void Klucz::find_m();
	void Klucz::Update();

};

#endif
