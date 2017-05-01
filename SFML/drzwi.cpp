#include <string>
#include "drzwi.h"

std::vector<Drzwi*> Drzwi::drzwia;
int Drzwi::key;

void Drzwi::Update() {
	box.left = rect.getPosition().x;
	box.top = rect.getPosition().y;
}