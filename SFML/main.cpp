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

// ===================== gracz i mob ============
	Gracz Heros("gracz.png", 120, 120, sf::Vector2i(1, Down));
	
// ===================== gracz ============

	

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
			// ========================= lista obiektow mapki ===========
			if (str[4] == '1') {
				new Node(str, sf::Vector2f((float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f), sf::Vector2f(60.0f, 60.0f));
			}

			if (str[4] == '2') {
				new Moneta(sf::Vector2f((float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f), sf::Vector2f(60.0f, 60.0f),1,"pieniazek.png");
			}

			if (str[4] == '3') {
				new Miecz(sf::Vector2f((float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f), sf::Vector2f(60.0f, 60.0f), 0,"mieczyk.png",1);
			}

			if (str[4] == '4') {
				new Mob ("gracz.png", (float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f, sf::Vector2i(1, Up));
			}

			if (str[4] == '5') {
				new Drzwi(sf::Vector2f((float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f), sf::Vector2f (60.0f, 60.0f));
			}

			if (str[4] == '6') {
				new Klucz(sf::Vector2f((float)loadCounter.x * 60.0f, (float)loadCounter.y * 60.0f), sf::Vector2f(60.0f, 60.0f));
			}
			// ========================= lista obiektow mapki ===========
			
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
		while (Window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;

			case::sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::Space) {
					Heros.source.y += 4;
					for (int i = 0; i < Mob::mobki.size(); i++)
					{
						Heros.hit(Mob::mobki.at(i));
					}
				}
				break;
			case::sf::Event::KeyReleased:
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
				else if (Event.key.code == sf::Keyboard::Space) {
					if (Heros.source.y > 3)
						Heros.source.y -= 4;
				}
				break;
			}
		}
		//=================== eventy ======================

		//=================== Ruch ===================
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) Heros.walk_up();

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) Heros.walk_down();

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Heros.walk_right();

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) Heros.walk_left();

		Heros.czy_ruch();

		//====================== kolizje ==================
		Heros.Update();
		for (int i = 0; i < Drzwi::drzwia.size(); i++)
			if (Heros.box.intersects(Drzwi::drzwia.at(i)->box) && Drzwi::key == 1) {
				if (Heros.source.y == Down) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + 60);
				else if (Heros.source.y == Up) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - 60);
				else if (Heros.source.y == Down_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + 60);
				else if (Heros.source.y == Up_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - 60);
			}
		Heros.Update();
		for (int i = 0; i < Node::nodes.size(); i++)
			if (Heros.box.intersects(Node::nodes.at(i)->box)) {
				if (Heros.source.y == Down) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - 1);
				else if (Heros.source.y == Up) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + 1);
				else if (Heros.source.y == Left) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x + 1, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Right) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x - 1, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Down_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - 1);
				else if (Heros.source.y == Up_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + 1);
				else if (Heros.source.y == Left_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x + 1, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Right_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x - 1, Heros.playerImage.getPosition().y);
			}

		for (int i = 0; i < Mob::mobki.size(); i++) {
			Mob::mobki.at(i)->Update();
			for (int j = 0; j < Node::nodes.size(); j++)
				if (Mob::mobki.at(i)->box.intersects(Node::nodes.at(j)->box)) {
					if (Mob::mobki.at(i)->source.y == Down) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x, Mob::mobki.at(i)->mobImage.getPosition().y - 1);
					else if (Mob::mobki.at(i)->source.y == Up) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x, Mob::mobki.at(i)->mobImage.getPosition().y + 1);
					else if (Mob::mobki.at(i)->source.y == Left) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x + 1, Mob::mobki.at(i)->mobImage.getPosition().y);
					else if (Mob::mobki.at(i)->source.y == Right) Mob::mobki.at(i)->mobImage.setPosition(Mob::mobki.at(i)->mobImage.getPosition().x - 1, Mob::mobki.at(i)->mobImage.getPosition().y);
				}
		}

		for (int i = 0; i < Moneta::monety.size(); i++) {
			if (Heros.box.intersects(Moneta::monety.at(i)->box)) {
				Moneta::monety.at(i)->find_m(&(Heros.PT));
				zmiana = 1;
				//cout << Heros.PT;
			}
		}
		for (int i = 0; i < Klucz::klucze.size(); i++) {
			if (Heros.box.intersects(Klucz::klucze.at(i)->box)) {
				Klucz::klucze.at(i)->find_m();
				//cout << Heros.PT;
			}
		}

		for (int i = 0; i < Miecz::miecze.size(); i++) {
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
				if (Heros.source.y == Down) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - 1);
				else if (Heros.source.y == Up) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + 1);
				else if (Heros.source.y == Left) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x + 1, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Right) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x - 1, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Down_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y - 1);
				else if (Heros.source.y == Up_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, Heros.playerImage.getPosition().y + 1);
				else if (Heros.source.y == Left_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x + 1, Heros.playerImage.getPosition().y);
				else if (Heros.source.y == Right_a) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x - 1, Heros.playerImage.getPosition().y);

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

		//====================== kolizje ==================

		//=================== Ruch ===================

		//// ==================== ograniczenie chodzenia =================
		//if (Heros.playerImage.getPosition().x <= 20) Heros.playerImage.setPosition(21, Heros.playerImage.getPosition().y);
		//if (Heros.playerImage.getPosition().x >= 1500) Heros.playerImage.setPosition(1499, Heros.playerImage.getPosition().y);
		//if (Heros.playerImage.getPosition().y <= 20) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, 21);
		//if (Heros.playerImage.getPosition().y >= 1100) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, 1099);
		//// ==================== ograniczenie chodzenia =================

		////////////////// przewijanie t³a ///////////////////


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
		
		//=================== wyswietlanie ======================
		if (zmiana != 0) {
			system("cls");
			cout << Heros;
			zmiana = 0;
		}
		view.setCenter(position);
		Window.setView(view);

		Window.clear();

		for (int i = 0; i < loadCounter.x; i++) {
			for (int j = 0; j < loadCounter.y; j++) {
				if (map[i][j].x != -1 && map[i][j].y != -1) {
					tiles.setPosition(i * 60, j * 60);
					tiles.setTextureRect(sf::IntRect(map[i][j].x * 60, map[i][j].y * 60, 60, 60));
					Window.draw(tiles);
				}
			}
		}
		for (int i = 0; i < Mob::mobki.size(); i++)
		{
			Window.draw(Mob::mobki.at(i)->mobImage);
		}
		Window.draw(Heros.playerImage);
		for (int i = 0; i < Moneta::monety.size(); i++)
		{
			Window.draw(Moneta::monety.at(i)->mmImage);
		}
		for (int i = 0; i < Miecz::miecze.size(); i++)
		{
			Window.draw(Miecz::miecze.at(i)->mmImage);
		}
		for (int i = 0; i < Drzwi::drzwia.size(); i++)
		{
			Window.draw(Drzwi::drzwia.at(i)->mmImage);
		}
		for (int i = 0; i < Klucz::klucze.size(); i++)
		{
			Window.draw(Klucz::klucze.at(i)->mmImage);
		}
		//Window.draw(text);
		
		Window.display();
		if (Heros.is_dead()) {
			string sentence = "Umarles, koniec gry!";
			sf::Text text(sentence, font, 60);
			text.setFillColor(sf::Color::Black);
			text.setPosition(sf::Vector2f(200, 100));
			cout << "umarles, koniec gry!" << endl;
			Window.draw(Heros.playerImage);
			Window.draw(text);
			Window.display();
			sf::Event Event;
			while (Window.pollEvent(Event))
			{
				switch (Event.type)
				{
					case sf::Event::Closed:
						Window.close();
					break;

					case::sf::Event::KeyPressed:
						if (Event.key.code == sf::Keyboard::Space) {
							Window.close();
						}
					break;
				}
			}
			system("pause");
			return 0;
		}
		//=================== wyswietlanie ======================
	}
//==================== petla glowna ======================
	return 0;
}