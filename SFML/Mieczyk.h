#ifndef miecz_h
#define miecz_h

#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include "moneta.h"


class Miecz 
{
public:
	static int act_id_miecz;
	static std::vector<Miecz*> miecze;
	sf::RectangleShape rect;
	sf::FloatRect box;
	sf::Texture mmTexture;
	sf::Sprite mmImage;
	int value, ID;
	int bon_atk;
	
	Miecz(sf::Vector2f position, sf::Vector2f size, int wartosc, std::string str, int bonus) {
		rect.setSize(size);
		rect.setPosition(position);
		mmImage.setPosition(position.x, position.y);
		if (!mmTexture.loadFromFile(str))
			std::cout << "nie udalo sie zaladowc textury miecza" << std::endl;
		mmImage.setTexture(mmTexture);

		bon_atk = bonus;
		
		miecze.push_back(this);
		box.height = 30;
		box.width = 30;
		box.left = rect.getPosition().x + 15;
		box.top = rect.getPosition().y + 15;
		value = wartosc;
		ID = act_id_miecz;
		std::cout << "miecz: " << ID << " bon= " << bon_atk << std::endl;
		act_id_miecz++;
	}

	void Miecz::find_m(int *g);
	void Miecz::Update();
};

#endif