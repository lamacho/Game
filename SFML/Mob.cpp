#include <iostream>
#include "node.h"
#include "Mob.h"

int Mob::act_id_mob = 0;
std::vector <Mob*> Mob::mobki;


void Mob::walk_up() {
	source.y = Up;
	mobImage.move(0, -1*SPD);
	ruch = true;
}

void Mob::walk_down() {
	source.y = Down;
	mobImage.move(0, 1*SPD);
	ruch = true;
}

void Mob::walk_left() {
	source.y = Left;
	mobImage.move(-1 * SPD, 0);
	ruch = true;
}

void Mob::walk_right() {
	source.y = Right;
	mobImage.move(1 * SPD, 0);
	ruch = true;
}

void Mob::czy_ruch() {
	if (ruch) {
		if (source.x == 2)
			source.x = 0;
		else source.x++;
	}
	mobImage.setTextureRect(sf::IntRect(source.x * 60, source.y * 60, 60, 60));
}

void Mob::Update() {
	box.left = mobImage.getPosition().x;
	box.top = mobImage.getPosition().y;
}

bool Mob::is_dead() {
	if (HP <= 0) {
		//std::cout << "dead" << std::endl;
		mobki.erase(mobki.begin() +ID);
		for (int i = ID; i < mobki.size(); i++) {
			if (mobki.at(i)->ID != 0)
				mobki.at(i)->ID--;
		}
	}
	return false;
}
void Mob::hited(int kierunek) {
	if (kierunek == Down) {
		for (int i = 0; i <= 100; i++) {
			int copy = source.y;
			source.y = kierunek;
			ruch = false;
			mobImage.move(0, 0.1);
			source.y = copy;
			//ruch = true;
		}
	}
	else if (kierunek == Up) {
		for (int i = 0; i <= 100; i++) {
			int copy = source.y;
			source.y = kierunek;
			ruch = false;
			mobImage.move(0, -0.1);
			source.y = copy;
			//ruch = true;
		}
	}
	else if (kierunek == Right) {
		for (int i = 0; i <= 100; i++) {
			int copy = source.y;
			source.y = kierunek;
			ruch = false;
			mobImage.move(0.1, 0);
			source.y = copy;
			//ruch = true;
		}
	}
	else if (kierunek == Left) {
		for (int i = 0; i <= 100; i++) {
			int copy = source.y;
			source.y = kierunek;
			ruch = false;
			mobImage.move(0, -0.1);
			source.y = copy;
			//ruch = true;
		}
	}
	else std::cout << "blad" << std::endl;
}

void Mob::AI() {

}