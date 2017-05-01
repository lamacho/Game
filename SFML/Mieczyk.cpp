#include "Mieczyk.h"

std::vector<Miecz*> Miecz::miecze;
int Miecz::act_id_miecz = 0;

void Miecz::find_m(int *g) {

	*g +=bon_atk;
	miecze.erase(miecze.begin() + ID);
	for (int i = ID; i < Miecz::miecze.size(); i++) {
		if (miecze.at(i)->ID != 0)
			miecze.at(i)->ID--;
	}
}
void Miecz::Update() {
	box.left = rect.getPosition().x;
	box.top = rect.getPosition().y;
}