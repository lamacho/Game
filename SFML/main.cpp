#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <fstream>
#include "node.h"
#include "Gracz.h"
#include "Mob.h"
#include "moneta.h"
#include "Mieczyk.h"
#include "drzwi.h"
#include "key.h"

using namespace std;

int main() {
	act_id = 0;
	int zmiana = 1;
	sf::Font font;
	if (!font.loadFromFile("Sketch Gothic School.ttf"))
		cout << "nie zaladowano czcionki!" << endl;
//================ Dane o graczach ====================
	sf::Vector2f position1;
	position1.x = 0;
	position1.y = 0;

	sf::Vector2f position2;
	position2.x = 10;
	position2.y = 30;

	sf::Vector2f position3;
	position3.x = 660;
	position3.y = 30;

	sf::Text asd2("Niebieski", font, 30);
	asd2.setFillColor(sf::Color::White);
	asd2.setPosition(sf::Vector2f(position2.x, position2.y - 30));

	sf::Text asd3("Czerwony", font, 30);
	asd3.setFillColor(sf::Color::White);
	asd3.setPosition(sf::Vector2f(position3.x, position3.y - 30));
//================ Dane o graczach ====================

//=================== dzwiek ======================
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	if (!soundBuffer.loadFromFile("beep.ogg")) cout << "nie zaladowano beep" << endl;
	sound.setBuffer(soundBuffer);
	sound.setPitch(1.0f);
	sound.setVolume(50);

	sf::Music music;
	if (!music.openFromFile("piosenka.ogg")) cout << "nie za³adowano piosenki" << endl;
	music.setVolume(30);

	//music.play();
//=================== dzwiek ======================

	sf::Vector2i screenDimensions(800, 600);

// ===================== gracze ============
	Gracz Heros("gracz.png", 180, 120, sf::Vector2i(1, Right));
	Heros.playerImage.setColor(sf::Color::Blue);
	Gracz Heros1("gracz.png", 360, 120, sf::Vector2i(1, Left));
	Heros1.playerImage.setColor(sf::Color::Red);
// ===================== gracze ============

	

// ===================== view =====================
	sf::View view;
	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
// ===================== view =====================

//=================== ladowanie mapki ======================
	std::ifstream openfile("Map.txt");

	sf::Texture tileTexture;
	sf::Sprite tiles;


	sf::Vector2i map[100][100];
	sf::Vector2i loadCounter = sf::Vector2i(0, 0);

	if (openfile.is_open())
	{
		string tileLocation;
		openfile >> tileLocation;
		tileTexture.loadFromFile(tileLocation);
		tiles.setTexture(tileTexture);

		while (!openfile.eof())
		{
			
			string str;
			openfile >> str;
			char x = str[0], y = str[2];
			// ========================= listy obiektow mapki ===========
			if (str[4] == '1') { //œciany
				new Node(str, sf::Vector2f((float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f), sf::Vector2f(60.0f, 60.0f));
			}

			if (str[4] == '2') { //pieni¹¿ki
				new Moneta(sf::Vector2f((float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f), sf::Vector2f(60.0f, 60.0f),1,"pieniazek.png");
			}

			if (str[4] == '3') { //Mieczyki
				new Miecz(sf::Vector2f((float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f), sf::Vector2f(60.0f, 60.0f), 0,"mieczyk.png",1);
			}

			if (str[4] == '4') { //Mobki
				new Mob ("gracz.png", (float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f, sf::Vector2i(1, Up));
			}

			if (str[4] == '5') { //Drzwi
				new Drzwi(sf::Vector2f((float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f), sf::Vector2f (60.0f, 60.0f));
			}

			if (str[4] == '6') { //Klucze
				new Klucz(sf::Vector2f((float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f), sf::Vector2f(60.0f, 60.0f));
			}
			// ========================= listy obiektow mapki ===========
			
			if (!isdigit(x) || !isdigit(y)) {
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
			}
			else
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');

			if (openfile.peek() == '\n')
			{
				loadCounter.x = 0;
				loadCounter.y++;
			}
			else
				loadCounter.x++;

		}
		loadCounter.y++; 
	}
//=================== ladowanie mapki ======================


	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "mapka");
	Window.setKeyRepeatEnabled(false);
//==================== petla glowna ======================
	while (Window.isOpen())
	{
		
		//=================== eventy ======================
		sf::Event Event;
		if (Heros.dead || Heros1.dead) { //eventy jeœli ktoœ umrze
			while (Window.pollEvent(Event))
			{
				switch (Event.type)
				{
				case sf::Event::Closed: //zamkniêcie okna
					Window.close();
					break;
				}
			}
		}
		else {
			while (Window.pollEvent(Event))
			{
				switch (Event.type)
				{
				case sf::Event::Closed: //zamkniêcie okna
					Window.close();
					break;

				case::sf::Event::KeyPressed:
					if (Event.key.code == sf::Keyboard::P) {
						Heros.source.y += 4; //atak 
						for (int i = 0; i < Mob::mobki.size(); i++)
						{
							Heros.hit(Mob::mobki.at(i));
						}
						Heros.hit(&Heros1);
						if (Heros.hitbox.intersects(Heros1.box)) {
							sound.play();
						}
					}
					if (Event.key.code == sf::Keyboard::C) {
						Heros1.source.y += 4; //atak 
						for (int i = 0; i < Mob::mobki.size(); i++)
						{
							Heros1.hit(Mob::mobki.at(i));
						}
						Heros1.hit(&Heros);
						if (Heros1.hitbox.intersects(Heros.box)) {
							sound.play();
						}
					}
					break;
				case::sf::Event::KeyReleased: //przerwanie poruszania siê i podniesienie miecza po ataku
					if (Event.key.code == sf::Keyboard::Up) {
						Heros.ruch = false;
						Heros.source.x = 1;
					}
					else if (Event.key.code == sf::Keyboard::Down) {
						Heros.ruch = false;
						Heros.source.x = 1;
					}
					else if (Event.key.code == sf::Keyboard::Right) {
						Heros.ruch = false;
						Heros.source.x = 1;
					}
					else if (Event.key.code == sf::Keyboard::Left) {
						Heros.ruch = false;
						Heros.source.x = 1;
					}
					else if (Event.key.code == sf::Keyboard::P) {
						if (Heros.source.y > 3)
							Heros.source.y -= 4;
					}
					if (Event.key.code == sf::Keyboard::W) {
						Heros1.ruch = false;
						Heros1.source.x = 1;
					}
					else if (Event.key.code == sf::Keyboard::S) {
						Heros1.ruch = false;
						Heros1.source.x = 1;
					}
					else if (Event.key.code == sf::Keyboard::D) {
						Heros1.ruch = false;
						Heros1.source.x = 1;
					}
					else if (Event.key.code == sf::Keyboard::A) {
						Heros1.ruch = false;
						Heros1.source.x = 1;
					}
					else if (Event.key.code == sf::Keyboard::C) {
						if (Heros1.source.y > 3)
							Heros1.source.y -= 4;
					}
					break;
				}
			}
		}
		//=================== eventy ======================

		//=================== Ruch ===================
		if (!Heros.dead && !Heros1.dead) { //obs³uga przytrzymania klawiszy ruchu
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) Heros.walk_up();

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Heros.walk_down();

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Heros.walk_right();

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) Heros.walk_left();

			Heros.czy_ruch();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) Heros1.walk_up();

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) Heros1.walk_down();

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) Heros1.walk_right();

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) Heros1.walk_left();

			Heros1.czy_ruch();
		}
		//====================== kolizje ==================
		Heros.Update();
		for (int i = 0; i < Drzwi::drzwia.size(); i++) //gracz z drzwiami
			if (Heros.box.intersects(Drzwi::drzwia.at(i)->box) && Drzwi::key == 1) {
				if (Heros.source.y == Down) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + 60);
				else if (Heros.source.y == Up) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - 60);
				else if (Heros.source.y == Down_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + 60);
				else if (Heros.source.y == Up_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - 60);
			}
		Heros.Update();
		for (int i = 0; i < Node::nodes.size(); i++) //gracz ze œcianami
			if (Heros.box.intersects(Node::nodes.at(i)->box)) {
				if (Heros.source.y == Down) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - Heros.SPD);
				else if (Heros.source.y == Up) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + Heros.SPD);
				else if (Heros.source.y == Left) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x + Heros.SPD, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Right) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x - Heros.SPD, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Down_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - Heros.SPD);
				else if (Heros.source.y == Up_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + Heros.SPD);
				else if (Heros.source.y == Left_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x + Heros.SPD, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Right_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x - Heros.SPD, Heros.playerImage.getPosition().y);
			}

		for (int i = 0; i < Mob::mobki.size(); i++) { //mobki ze œcianami
			Mob::mobki.at(i)->Update();
			for (int j = 0; j < Node::nodes.size(); j++)
				if (Mob::mobki.at(i)->box.intersects(Node::nodes.at(j)->box)) {
					if (Mob::mobki.at(i)->source.y == Down) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x, Mob::mobki.at(i)->mobImage.getPosition().y - Heros.SPD);
					else if (Mob::mobki.at(i)->source.y == Up) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x, Mob::mobki.at(i)->mobImage.getPosition().y + Heros.SPD);
					else if (Mob::mobki.at(i)->source.y == Left) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x + Heros.SPD, Mob::mobki.at(i)->mobImage.getPosition().y);
					else if (Mob::mobki.at(i)->source.y == Right) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x - Heros.SPD, Mob::mobki.at(i)->mobImage.getPosition().y);
				}
		}

		for (int i = 0; i < Moneta::monety.size(); i++) { //gracz z monet¹
			if (Heros.box.intersects(Moneta::monety.at(i)->box)) {
				Moneta::monety.at(i)->find_m(&(Heros.PT));
				zmiana = 1;
				//cout << Heros.PT;
			}
		}
		for (int i = 0; i < Klucz::klucze.size(); i++) { //gracz z kluczem
			if (Heros.box.intersects(Klucz::klucze.at(i)->box)) {
				Klucz::klucze.at(i)->find_m();
				//cout << Heros.PT;
			}
		}

		for (int i = 0; i < Miecz::miecze.size(); i++) { //gracz z mieczem
			if (Heros.box.intersects(Miecz::miecze.at(i)->box)) {
				Miecz::miecze.at(i)->find_m(&(Heros.ATAK));
				zmiana = 1;
			}
		}

		//obrazenia i nie przechodzenie przez mobki
		for (int i = 0; i < Mob::mobki.size(); i++) {
			if (Heros.box.intersects(Mob::mobki.at(i)->box)) {
				Mob::mobki.at(i)->hitting--;
				if (Mob::mobki.at(i)->hitting <= 0) {
					Heros.hited(Mob::mobki.at(i));
					Mob::mobki.at(i)->hitting = 100;
					zmiana = 1;
				}
				if (Heros.source.y == Down) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - Heros.SPD);
				else if (Heros.source.y == Up) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + Heros.SPD);
				else if (Heros.source.y == Left) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x + Heros.SPD, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Right) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x - Heros.SPD, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Down_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - Heros.SPD);
				else if (Heros.source.y == Up_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + Heros.SPD);
				else if (Heros.source.y == Left_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x + Heros.SPD, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Right_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x - Heros.SPD, Heros.playerImage.getPosition().y);

			}
		}
		for (int i = 0; i < Mob::mobki.size(); i++) {
			if (Heros.box.intersects(Mob::mobki.at(i)->boxat)) {
				Mob::mobki.at(i)->hitting--;
				if (Mob::mobki.at(i)->hitting <= 0) {
					Heros.hited(Mob::mobki.at(i));
					Mob::mobki.at(i)->hitting = 1000;
					zmiana = 1;
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////////////

		//jak wy¿ej dla drugiego gracza

		Heros1.Update();
		for (int i = 0; i < Drzwi::drzwia.size(); i++)
			if (Heros1.box.intersects(Drzwi::drzwia.at(i)->box) && Drzwi::key == 1) {
				if (Heros1.source.y == Down) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y + 60);
				else if (Heros1.source.y == Up) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y - 60);
				else if (Heros1.source.y == Down_a) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y + 60);
				else if (Heros1.source.y == Up_a) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y - 60);
			}
		Heros1.Update();
		for (int i = 0; i < Node::nodes.size(); i++)
			if (Heros1.box.intersects(Node::nodes.at(i)->box)) {
				if (Heros1.source.y == Down) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y -Heros1.SPD);
				else if (Heros1.source.y == Up) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y +Heros1.SPD);
				else if (Heros1.source.y == Left) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x +Heros1.SPD, Heros1.playerImage.getPosition().y);
				else if (Heros1.source.y == Right) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x -Heros1.SPD, Heros1.playerImage.getPosition().y);
				else if (Heros1.source.y == Down_a) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y -Heros1.SPD);
				else if (Heros1.source.y == Up_a) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y +Heros1.SPD);
				else if (Heros1.source.y == Left_a) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x +Heros1.SPD, Heros1.playerImage.getPosition().y);
				else if (Heros1.source.y == Right_a) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x -Heros1.SPD, Heros1.playerImage.getPosition().y);
			}

		for (int i = 0; i < Mob::mobki.size(); i++) {
			Mob::mobki.at(i)->Update();
			for (int j = 0; j < Node::nodes.size(); j++)
				if (Mob::mobki.at(i)->box.intersects(Node::nodes.at(j)->box)) {
					if (Mob::mobki.at(i)->source.y == Down) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x, Mob::mobki.at(i)->mobImage.getPosition().y -Heros1.SPD);
					else if (Mob::mobki.at(i)->source.y == Up) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x, Mob::mobki.at(i)->mobImage.getPosition().y +Heros1.SPD);
					else if (Mob::mobki.at(i)->source.y == Left) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x +Heros1.SPD, Mob::mobki.at(i)->mobImage.getPosition().y);
					else if (Mob::mobki.at(i)->source.y == Right) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x -Heros1.SPD, Mob::mobki.at(i)->mobImage.getPosition().y);
				}
		}

		for (int i = 0; i < Moneta::monety.size(); i++) {
			if (Heros1.box.intersects(Moneta::monety.at(i)->box)) {
				Moneta::monety.at(i)->find_m(&(Heros1.PT));
				zmiana = 1;
				//cout << Heros1.PT;
			}
		}
		for (int i = 0; i < Klucz::klucze.size(); i++) {
			if (Heros1.box.intersects(Klucz::klucze.at(i)->box)) {
				Klucz::klucze.at(i)->find_m();
				//cout << Heros1.PT;
			}
		}

		for (int i = 0; i < Miecz::miecze.size(); i++) {
			if (Heros1.box.intersects(Miecz::miecze.at(i)->box)) {
				Miecz::miecze.at(i)->find_m(&(Heros1.ATAK));
				zmiana = 1;
			}
		}

		//obrazenia i nie przechodzenie przez mobki
		for (int i = 0; i < Mob::mobki.size(); i++) {
			if (Heros1.box.intersects(Mob::mobki.at(i)->box)) {
				Mob::mobki.at(i)->hitting--;
				if (Mob::mobki.at(i)->hitting <= 0) {
					Heros1.hited(Mob::mobki.at(i));
					Mob::mobki.at(i)->hitting = 100;
					zmiana = 1;
				}
				if (Heros1.source.y == Down) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y -Heros1.SPD);
				else if (Heros1.source.y == Up) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y +Heros1.SPD);
				else if (Heros1.source.y == Left) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x +Heros1.SPD, Heros1.playerImage.getPosition().y);
				else if (Heros1.source.y == Right) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x -Heros1.SPD, Heros1.playerImage.getPosition().y);
				else if (Heros1.source.y == Down_a) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y -Heros1.SPD);
				else if (Heros1.source.y == Up_a) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x, Heros1.playerImage.getPosition().y +Heros1.SPD);
				else if (Heros1.source.y == Left_a) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x +Heros1.SPD, Heros1.playerImage.getPosition().y);
				else if (Heros1.source.y == Right_a) Heros1.playerImage.setPosition(Heros1.playerImage.getPosition().x -Heros1.SPD, Heros1.playerImage.getPosition().y);

			}
		}
		for (int i = 0; i < Mob::mobki.size(); i++) {
			if (Heros1.box.intersects(Mob::mobki.at(i)->boxat)) {
				Mob::mobki.at(i)->hitting--;
				if (Mob::mobki.at(i)->hitting <= 0) {
					Heros1.hited(Mob::mobki.at(i));
					Mob::mobki.at(i)->hitting = 1000;
					zmiana = 1;
				}
			}
		}

		//====================== kolizje ==================

		//=================== Ruch ===================

		//// ==================== ograniczenie chodzenia =================
		//niepotrzebne ze wzglêdu na kolizje ze œcianami
		//if (Heros.playerImage.getPosition().x <= 20) Heros.playerImage.setPosition(21, Heros.playerImage.getPosition().y);
		//if (Heros.playerImage.getPosition().x >= 1500) Heros.playerImage.setPosition(1499, Heros.playerImage.getPosition().y);
		//if (Heros.playerImage.getPosition().y <= 20) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, 21);
		//if (Heros.playerImage.getPosition().y >= 1100) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, 1099);
		//// ==================== ograniczenie chodzenia =================

		////////////////// przewijanie t³a /////////////////// - aktualnie wy³¹czone ze wzglêdu na to i¿ dwoje graczy gra na jednym ekranie
		if (Heros.playerImage.getPosition().x + 60 > (screenDimensions.x / 2))
			position.x = Heros.playerImage.getPosition().x + 60;
		else position.x = screenDimensions.x / 2;

		if (Heros.playerImage.getPosition().y + 60 > (screenDimensions.y / 2))
			position.y = Heros.playerImage.getPosition().y + 60;
		else position.y = screenDimensions.y / 2;

		for (int i = 0; i < Mob::mobki.size(); i++)
		{
			Mob::mobki.at(i)->czy_ruch();
		}
		////////////////// przewijanie t³a ///////////////////

		//=================== wyswietlanie ======================
		if (zmiana != 0) {
			system("cls");
			cout << Heros<<endl<<endl<<Heros1;
			zmiana = 0;
		}
		//view.setCenter(position); //wy³¹czenie przewijania ekranu (jeœli zakomentowane to ekran siê nie przewija)
		//Window.setView(view); //wy³¹czenie przewijania ekranu (jeœli zakomentowane to ekran siê nie przewija)

		Window.clear();

		for (int i = 0; i < loadCounter.x; i++) { //narysowanie mapki
			for (int j = 0; j < loadCounter.y; j++) {
				if (map[i][j].x != -1 && map[i][j].y != -1) {
					tiles.setPosition(i * 60, j * 60);
					tiles.setTextureRect(sf::IntRect(map[i][j].x * 60, map[i][j].y * 60, 60, 60));
					Window.draw(tiles);
				}
			}
		}

		for (int i = 0; i < Mob::mobki.size(); i++)//narysowanie mobków
		{
			Window.draw(Mob::mobki.at(i)->mobImage);
		}

		Window.draw(Heros.playerImage); //naryswanie bohatera1
		Window.draw(Heros1.playerImage); //naryswanie bohatera2

		for (int i = 0; i < Moneta::monety.size(); i++)//rysowanie monet
		{
			Window.draw(Moneta::monety.at(i)->mmImage);
		}

		for (int i = 0; i < Miecz::miecze.size(); i++) //rysowanie mieczy
		{
			Window.draw(Miecz::miecze.at(i)->mmImage);
		}

		for (int i = 0; i < Drzwi::drzwia.size(); i++) //rysowanie drzwi
		{
			Window.draw(Drzwi::drzwia.at(i)->mmImage);
		}

		for (int i = 0; i < Klucz::klucze.size(); i++) //rysowanie kluczy
		{
			Window.draw(Klucz::klucze.at(i)->mmImage);
		}
		//Window.draw(text);
		
		position1.x = 70;
		position1.y = 70;

			// ============= wyswietlanie danych graczy na ekranie ==============
			Window.draw(asd2);
			Window.draw(asd3);

			sf::Text asd4(Heros.health, font, 25);
			asd4.setFillColor(sf::Color::Blue);
			asd4.setPosition(sf::Vector2f(Heros.playerImage.getPosition().x+10, Heros.playerImage.getPosition().y-5));
			Window.draw(asd4);

			sf::Text asd5(Heros1.health, font, 25);
			asd5.setFillColor(sf::Color::Red);
			asd5.setPosition(sf::Vector2f(Heros1.playerImage.getPosition().x + 10, Heros1.playerImage.getPosition().y-5));
			Window.draw(asd5);

			sf::Text asd(Heros.g, font, 30);
			asd.setFillColor(sf::Color::White);
			asd.setPosition(position2);
			Window.draw(asd);

			sf::Text asd1(Heros1.g, font, 30);
			asd1.setFillColor(sf::Color::White);
			asd1.setPosition(position3);
			Window.draw(asd1);
			// ============= wyswietlanie danych graczy na ekranie ==============


		if (Heros.is_dead()) {
			string sentence = "Umarl gracz niebieski, koniec gry!";
			sf::Text text(sentence, font, 60);
			text.setFillColor(sf::Color::Black);
			text.setPosition(position1);
			Window.draw(Heros.playerImage);
			Window.draw(text);
		}
		else if (Heros1.is_dead()) {
			string sentence = "Umarl gracz czerwony, koniec gry!";
			sf::Text text(sentence, font, 60);
			text.setFillColor(sf::Color::Black);
			text.setPosition(position1);
			Window.draw(Heros1.playerImage);
			Window.draw(text);
		}
		Window.display();
		//=================== wyswietlanie ======================
	}
//==================== petla glowna ======================
	return 0;
}