#ifndef Node_h
#define Node_h

#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include <vector>

class Node {
public:
	static std::vector<Node*> nodes;
	sf::RectangleShape rect;
	sf::FloatRect box;

	Node() {
		nodes.push_back(this);
	}

	Node(std::string wpis, sf::Vector2f position, sf::Vector2f size) {
		nodes.push_back(this);
		rect.setSize(size);
		rect.setPosition(position);

		box.height = 60;
		box.width = 60;
		box.left = rect.getPosition().x;
		box.top = rect.getPosition().y;
	}
	 
	virtual void Update();

};



#endif