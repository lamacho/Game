#include <string>
#include <vector>
#include "moneta.h"

std::vector<Moneta*> Moneta::monety;

void Moneta::Update() {
	box.left = rect.getPosition().x;
	box.top = rect.getPosition().y;
}


void Moneta::find_m(int *g) {
		
	*g +=value;
	monety.erase(monety.begin() + ID);
	for (int i = ID; i < Moneta::monety.size(); i++) {
		if (monety.at(i)->ID != 0)
			monety.at(i)->ID--;
	}
	
	if (monety.empty()) std::cout << "koniec";
}
