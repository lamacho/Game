#include <iostream>

#include "Gracz.h"



void Gracz::walk_up(){
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
		if (source.y < 4 ) {
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
}

void Gracz::Update() {
	if (!dead) {
		box.left = playerImage.getPosition().x;
		box.top = playerImage.getPosition().y;

		hitbox.left = playerImage.getPosition().x;
		hitbox.top = playerImage.getPosition().y;
	}
}

void Gracz::hit(Mob *mob) {
	if (!dead) {
		if (hitbox.intersects(mob->box)) {
			int kierunek = source.y - 4;
			//std::cout << "hit";
			mob->HP -= ATAK;
			mob->is_dead();
			//mob->hited(kierunek);
		}
	}
}

void Gracz::hited(Mob *mob) {
	HP -= mob->ATAK;
	is_dead();
}

Gracz* Gracz::getter() { return this; }

bool Gracz::is_dead() {
	if (HP <= 0 ) {
		if (!pTexture.loadFromFile("grave.png"))
			std::cout << "nie udalo sie zaladowc textury gracza" << std::endl;
		playerImage.setTexture(pTexture);
		source.x = 0;
		source.y = 0;
		playerImage.setTextureRect(sf::IntRect(source.x * 60, source.y * 60, 60, 60));
		
		ruch = false;
		Update();
		std::cout << "dead";
		dead = true;
		return true;
	
	}
	return false;
}

std::ostream & operator<< (std::ostream &wyjscie, const Gracz &s) {
	return wyjscie << "HP: " << s.HP << std::endl << "SILA: " << s.ATAK << std::endl << "PUNKTY: " << s.PT << std::endl << "x: " << s.playerImage.getPosition().x<<" y: "<< s.playerImage.getPosition().y<<std::endl;
}