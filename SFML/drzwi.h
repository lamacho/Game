#ifndef Drzwi_h
#define Drzwi_h

#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include <vector>
#include "node.h"

class Drzwi
	:public Node
{
public:
	static std::vector<Drzwi*> drzwia;
	static int key;
	sf::Texture mmTexture;
	sf::Sprite mmImage;

	Drzwi() {
		drzwia.push_back(this);
	}

	Drzwi(sf::Vector2f position, sf::Vector2f size) {
		drzwia.push_back(this);
		rect.setSize(size);
		rect.setPosition(position);

		mmImage.setPosition(position.x, position.y);
		if (!mmTexture.loadFromFile("drzwi.png"))
			std::cout << "nie udalo sie zaladowc textury monety" << std::endl;
		mmImage.setTexture(mmTexture);

		box.height = 60;
		box.width = 60;
		box.left = rect.getPosition().x;
		box.top = rect.getPosition().y;
	}
	virtual void Update();
	friend class Klucz;
};



#endif
