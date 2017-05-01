#include <iostream>
#include "node.h"
#include "Gracz.h"



void Gracz::walk_up(){
	if (source.y <= 4) {
		source.y = Up;
	}
	else source.y = Up_a;
	playerImage.move(0, -SPD);
	ruch = true;
}

void Gracz::walk_down() {
	if (source.y < 4) {
		source.y = Down;
	}
	else source.y = Down_a;
	playerImage.move(0, SPD);
	ruch = true;
}

void Gracz::walk_left(){
	if (source.y <= 4) {
		source.y = Left;
	}
	else source.y = Left_a;
	playerImage.move(-SPD, 0);
	ruch = true;
}

void Gracz::walk_right() {
	if (source.y <= 4) {
		source.y = Right;
	}
	else source.y = Right_a;
	playerImage.move(SPD, 0);
	ruch = true;
}

void Gracz::czy_ruch() {
	if (ruch) {
		if (source.x == 2)
			source.x = 0;
		else source.x++;
	}
	playerImage.setTextureRect(sf::IntRect(source.x * 60, source.y * 60, 60, 60));
}

void Gracz::Update() {
	box.left = playerImage.getPosition().x + 10;
	box.top = playerImage.getPosition().y + 10;

	hitbox.left = playerImage.getPosition().x - 10;
	hitbox.top = playerImage.getPosition().y - 10;
}

void Gracz::hit(Mob *mob) {
	if (hitbox.intersects(mob->box)) {
		int kierunek = source.y-4;
		//std::cout << "hit";
		mob->HP -= ATAK;
		mob->is_dead();
		//mob->hited(kierunek);
	}
}

void Gracz::hited(Mob *mob) {
	HP -= mob->ATAK;
	//std::cout << HP;
	is_dead();
}

bool Gracz::is_dead() {
	if (HP <= 0) {
		source.x = 0;
		source.y = 9;
		ruch = false;
		std::cout << "dead";
		return true;
	}
	return false;
}

std::ostream & operator<< (std::ostream &wyjscie, const Gracz &s) {
	return wyjscie << "HP: " << s.HP << std::endl << "SILA: " << s.ATAK << std::endl << "PUNKTY: " << s.PT << std::endl;
}