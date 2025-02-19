#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Config {
private:
	Font font;
	string arquivo_font;
	Text titulo;
	Text volumeText;
	Text botaoVoltar;
	RectangleShape barraVol;
	RectangleShape indicadorVol;

	float volume;
	bool ativa;
	bool botaoVoltarHover = false;
public:
	Config(float width, float height, string arquivo_font) {

		if (!font.loadFromFile(arquivo_font)) {
			cerr << "Failed to load font texture" << endl;
		}

		ativa = false;
		volume = 20.f;

		titulo.setFont(font);
		titulo.setString("Configuração");
		titulo.setCharacterSize(90);
		titulo.setFillColor(Color::White);
		titulo.setOrigin(titulo.getLocalBounds().width / 2, titulo.getLocalBounds().height / 2);
		titulo.setPosition(width / 2 + 20, 350);

		volumeText.setFont(font);
		volumeText.setString("Volume:");
		volumeText.setCharacterSize(50);
		volumeText.setFillColor(Color::White);
		volumeText.setOrigin(volumeText.getLocalBounds().width / 2, volumeText.getLocalBounds().height / 2);
		volumeText.setPosition(width / 2 + 20, 490);

		barraVol.setSize(sf::Vector2f(200, 10));
		barraVol.setFillColor(Color::White);
		barraVol.setPosition(width / 2 - 80, 550);

		indicadorVol.setSize(sf::Vector2f(20, 20));
		indicadorVol.setFillColor(sf::Color::Red);
		indicadorVol.setPosition(width / 2 - 100 + (volume * 2), 545);

		botaoVoltar.setFont(font);
		botaoVoltar.setString("Voltar");
		botaoVoltar.setCharacterSize(90);
		botaoVoltar.setFillColor(Color::White);
		botaoVoltar.setOrigin(botaoVoltar.getLocalBounds().width / 2, botaoVoltar.getLocalBounds().height / 2);
		botaoVoltar.setPosition(width / 2 - 20 + (volume * 2), 650);
	}

	~Config() {}

	void eventos(Event& event, RenderWindow& window, Music& musicMenu, Music& musicGame) {

		Vector2i mousePos = Mouse::getPosition(window);
		FloatRect areaBotao = botaoVoltar.getGlobalBounds();

		if (areaBotao.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
			if (!botaoVoltarHover) {
				botaoVoltar.setFillColor(Color::Yellow);
				botaoVoltarHover = true;
			}
		}
		else {
			if (botaoVoltarHover) {
				botaoVoltar.setFillColor(Color::White);
				botaoVoltarHover = false;
			}
		}


		if (event.type == Event::MouseButtonPressed) {
			if (event.mouseButton.button == Mouse::Left) {
				int mouseX = event.mouseButton.x;
				int mouseY = event.mouseButton.y;

				if (mouseX >= barraVol.getPosition().x && mouseX <= barraVol.getPosition().x + barraVol.getSize().x
					&& mouseY >= barraVol.getPosition().y - 10 && mouseY <= barraVol.getPosition().y + 20) {

					volume = (mouseX - barraVol.getPosition().x) / 2;
					indicadorVol.setPosition(barraVol.getPosition().x + volume * 2, indicadorVol.getPosition().y);

					musicMenu.setVolume(volume);
					musicGame.setVolume(volume);
				}

				FloatRect areaBotao = botaoVoltar.getGlobalBounds();
				if (areaBotao.contains(mouseX, mouseY)) {
					cout << "Voltando para o menu..." << endl;
					desativar();
				}
			}
		}
	}

	bool getStatus() {
		return ativa;
	}

	void ativar() {
		ativa = true;
	}

	void desativar() {
		ativa = false;
	}

	void draw(RenderWindow& window) {
		window.draw(titulo);
		window.draw(volumeText);
		window.draw(barraVol);
		window.draw(indicadorVol);
		window.draw(botaoVoltar);
	}
};

#endif 