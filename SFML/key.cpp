#include "key.h"
#include"drzwi.h"
std::vector<Klucz*> Klucz::klucze;
int Klucz::act_id_klucz = 0;

void Klucz::find_m() {
	Drzwi::key = 1;
	klucze.erase(klucze.begin() + ID);
	for (int i = ID; i < Klucz::klucze.size(); i++) {
		if (klucze.at(i)->ID != 0)
			klucze.at(i)->ID--;
	}
}
void Klucz::Update() {
	box.left = rect.getPosition().x;
	box.top = rect.getPosition().y;
}