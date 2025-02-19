#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Menu {
public:

	Text mainmenu[3];

	Menu(float width, float heigth, string arquivo_background, string arquivo_font, string arquivo_music) :
		arquivo_background(arquivo_background), arquivo_font(arquivo_font), arquivo_music(arquivo_music) {

		define_textura();

		font.loadFromFile(arquivo_font);

		mainmenu[0].setFont(font);
		mainmenu[0].setFillColor(Color::White);
		mainmenu[0].setString("Play");
		mainmenu[0].setCharacterSize(90);
		mainmenu[0].setOrigin(mainmenu[0].getGlobalBounds().width / 2, mainmenu[0].getGlobalBounds().height / 2);
		mainmenu[0].setPosition(Vector2f(960, (heigth / (3)) + 150));

		mainmenu[1].setFont(font);
		mainmenu[1].setString("Config");
		mainmenu[1].setFillColor(Color::White);
		mainmenu[1].setCharacterSize(90);
		mainmenu[1].setOrigin(mainmenu[1].getGlobalBounds().width / 2, mainmenu[1].getGlobalBounds().height / 2);
		mainmenu[1].setPosition(Vector2f(960, heigth / (3) + 250));

		mainmenu[2].setFont(font);
		mainmenu[2].setString("Exit");
		mainmenu[2].setFillColor(Color::White);
		mainmenu[2].setCharacterSize(90);
		mainmenu[2].setOrigin(mainmenu[2].getGlobalBounds().width / 2, mainmenu[2].getGlobalBounds().height / 2);
		mainmenu[2].setPosition(Vector2f(960, heigth / (3) + 350));


		music.openFromFile(arquivo_music);
		music.setVolume(10);
		ControlaMusica(true);

		selected = 0;
	}

	~Menu() {}

	Texture define_textura() {
		if (BgTexture.loadFromFile(arquivo_background)) {
			cout << "Backgorund texture loaded successfully" << endl;
			BgSprite.setTexture(BgTexture);
			BgSprite.setScale(Vector2f(1, 1));
			BgSprite.setColor(Color(200, 200, 200, 128));
		}
		else {
			cout << "Torre texture failed to load" << endl;
		}
		return BgTexture;
	}

	void draw(RenderWindow& window, bool configAtivo) {
		window.draw(BgSprite);
		for (int i = 0; i < 3; i++) {
			if (configAtivo) {
				continue;
			}
			window.draw(mainmenu[i]);
		}
	}

	void handleMouseHover(Vector2f mousePos) {
		bool hovered = false;

		for (int i = 0; i < 3; i++) {
			FloatRect bounds = mainmenu[i].getGlobalBounds();
			if (bounds.contains(mousePos)) {
				mainmenu[i].setFillColor(Color::Yellow);
				selected = i;
				hovered = true;
			}
			else {
				mainmenu[i].setFillColor(Color::White);
			}
		}

		if (!hovered) {
			selected = -1;
		}
	}

	void MoveUp() {
		if (selected + 1 <= 3) {
			mainmenu[selected].setFillColor(Color::Yellow);
			selected++;

			if (selected == 3) {
				selected = 0;
			}

			mainmenu[selected].setFillColor(Color::Yellow);
		}
	}

	void MoveDown() {
		if (selected - 1 >= -1) {
			mainmenu[selected].setFillColor(Color::Yellow);
			selected--;

			if (selected == -1) {
				selected = 1;
			}

			mainmenu[selected].setFillColor(Color::Yellow);
		}
	}

	void setSelected(int n) {
		selected = n;
	}

	int pressed() {
		return selected;
	}

	void ControlaMusica(bool LigaDesliga) {
		if (LigaDesliga)
			music.play();
		else
			music.pause();
	}

	Music& getMusica() {
		return music;
	}

private:
	int selected;
	Font font;
	Texture BgTexture;
	Sprite BgSprite;
	Music music;

	string arquivo_background;
	string arquivo_font;
	string arquivo_music;
};


#endif