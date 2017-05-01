#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <fstream>
#include "Gracz.h"
#include "Mob.h"


using namespace std;

int main() {
	
	int zmiana = 1, asd = 0;
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

		
		//=================== Ruch ===================

		//// ==================== ograniczenie chodzenia =================
		if (Heros.playerImage.getPosition().x <= 20) Heros.playerImage.setPosition(21, Heros.playerImage.getPosition().y);
		if (Heros.playerImage.getPosition().x >= 1500) Heros.playerImage.setPosition(1499, Heros.playerImage.getPosition().y);
		if (Heros.playerImage.getPosition().y <= 20) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, 21);
		if (Heros.playerImage.getPosition().y >= 1100) Heros.playerImage.setPosition(Heros.playerImage.getPosition().x, 1099);
		//// ==================== ograniczenie chodzenia =================

		////////////////// przewijanie t³a ///////////////////


		if (Heros.playerImage.getPosition().x + 60 > (screenDimensions.x / 2))
			position.x = Heros.playerImage.getPosition().x + 60;
		else position.x = screenDimensions.x / 2;

		if (Heros.playerImage.getPosition().y + 60 > (screenDimensions.y / 2))
			position.y = Heros.playerImage.getPosition().y + 60;
		else position.y = screenDimensions.y / 2;

		
		
		//=================== wyswietlanie ======================
		if (zmiana != 0) {
			system("cls");
			cout << Heros;
			zmiana = 0;
		}
		if (asd == 10) {
			system("cls");
			cout << Heros;
			asd = 0;
		}
		asd++;
		view.setCenter(position);
		Window.setView(view);
		if (Heros.playerImage.getPosition().x <= 119) { Heros.getter()->HP = 0; }
		Window.clear();

		if (Heros.is_dead()) 
			cout << "umarles, koniec gry!" << endl;
		
		Window.draw(Heros.playerImage);

		Window.display();
		
		//=================== wyswietlanie ======================
	}
//==================== petla glowna ======================
	return 0;
}