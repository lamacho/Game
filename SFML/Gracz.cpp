#include <iostream>
#include "node.h"
#include "Gracz.h"



void Gracz::walk_up() {
	if (!dead) {
		if (source.y <= 4) {
			source.y = Up;
		}
		else source.y = Up_a;
		playerImage.move(0, -SPD);
		ruch = true;
	}
}

void Gracz::walk_down() {
	if (!dead) {
		if (source.y < 4) {
			source.y = Down;
		}
		else source.y = Down_a;
		playerImage.move(0, SPD);
		ruch = true;
	}
}

void Gracz::walk_left() {
	if (!dead) {
		if (source.y <= 4) {
			source.y = Left;
		}
		else source.y = Left_a;
		playerImage.move(-SPD, 0);
		ruch = true;
	}
}

void Gracz::walk_right() {
	if (!dead) {
		if (source.y <= 4) {
			source.y = Right;
		}
		else source.y = Right_a;
		playerImage.move(SPD, 0);
		ruch = true;
	}
}

void Gracz::czy_ruch() {
	if (!dead) {
		if (ruch) {
			if (source.x == 2)
				source.x = 0;
			else source.x++;
		}
		playerImage.setTextureRect(sf::IntRect(source.x * 60, source.y * 60, 60, 60));
	}
	setG(HP, ATAK, SPD);
}

void Gracz::Update() {
	if (!dead) {
		box.left = playerImage.getPosition().x;
		box.top = playerImage.getPosition().y;

		hitbox.left = playerImage.getPosition().x;
		hitbox.top = playerImage.getPosition().y;

	}
	setG(HP, ATAK, SPD);
}

Gracz* Gracz::getter() { return this; }

void Gracz::hit(Mob *mob) {
	if (hitbox.intersects(mob->box)) {
		int kierunek = source.y-4;
		//std::cout << "hit";
		mob->HP -= ATAK;
		mob->is_dead();
		setG(HP, ATAK, SPD);
		//mob->hited(kierunek);
	}
}
void Gracz::hit(Gracz* mob) {
	if (hitbox.intersects(mob->box)) {
		int kierunek = source.y - 4;
		//std::cout << "hit";
		mob->HP -= ATAK;
		mob->is_dead();
		setG(HP, ATAK, SPD);
		//mob->hited(kierunek);
	}
}

void Gracz::hited(Mob *mob) {
	HP -= mob->ATAK;
	setG(HP, ATAK, SPD);
	//std::cout << HP;
	is_dead();
}

bool Gracz::is_dead() { //obs³uga œmierci gracza
	if (HP <= 0) {
		if (!pTexture.loadFromFile("grave.png"))
			std::cout << "nie udalo sie zaladowc textury gracza" << std::endl;
		playerImage.setTexture(pTexture);
		source.x = 0;
		source.y = 0;
		playerImage.setTextureRect(sf::IntRect(source.x * 60, source.y * 60, 60, 60));
		setG(HP, ATAK, SPD);
		ruch = false;
		Update();
		//std::cout << "dead";
		dead = true;
		return true;

	}
	return false;
}

std::ostream & operator<< (std::ostream &wyjscie, const Gracz &s) {
	return wyjscie << "HP: " << s.HP << std::endl << "SILA: " << s.ATAK << std::endl << "PUNKTY: " << s.PT << std::endl;
}