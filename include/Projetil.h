#ifndef PROJETIL_H
#define PROJETIL_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Projetil {
public:
	Projetil(float velocidade, double dano) : velocidade(velocidade), dano(dano) 
	{
		ProjetilSprite.setPosition(-1000, -1000);
		/*boundingRectangle.setFillColor(Color::Transparent);
		boundingRectangle.setOutlineColor(Color::Red);
		boundingRectangle.setOutlineThickness(1);
		boundingRectangle.setSize(Vector2f(64, 64));*/
	}
	~Projetil() {

	}

	void setDano(double dano) {
		this->dano = dano;
		cout << "Dano: " << this->dano << endl;
	}

	void setVelocidade(float velocidade) {
		this->velocidade = velocidade;
	}

	float getdano() const {
		return dano;
	}

	float getvelocidade() const {
		return velocidade;
	}

	void setAngulo(float angulo) {
		this->angulo = angulo;
	}

	Sprite& getSprite() {
		return ProjetilSprite;
	}

	Texture define_textura(string arquivo) {
		arquivo_projetil = arquivo;
		if (ProjetilTexture.loadFromFile(arquivo_projetil)) 
		{
			cout << "Projetil texture loaded successfully" << endl;
			ProjetilSprite.setTexture(ProjetilTexture);

			int Xindex = 0;
			int Yindex = 0;

			ProjetilSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 64, 64));
			ProjetilSprite.setScale(Vector2f(1, 1));
			ProjetilSprite.setOrigin(ProjetilSprite.getGlobalBounds().width / 2, ProjetilSprite.getGlobalBounds().height / 2);
			/*boundingRectangle.setOrigin(ProjetilSprite.getOrigin());*/
		}
		else {
			cout << "Projetil texture failed to load" << endl;
		}
		return ProjetilTexture;
	}

	void move(float deltaTime) {

		float radiano = angulo * (3.14 / 180.0f);
		ProjetilSprite.setRotation(angulo);

		float dx = velocidade * cos(radiano) * deltaTime;
		float dy = velocidade * sin(radiano) * deltaTime;

		ProjetilSprite.move(dx, dy);
		/*boundingRectangle.setPosition(ProjetilSprite.getPosition());*/
	}

	void render(RenderWindow& janela) {
		//janela.draw(boundingRectangle);
		if(ProjetilSprite.getTexture())
			janela.draw(ProjetilSprite);
	}

private:
	float velocidade;
	double dano;
	float angulo;

	/*RectangleShape boundingRectangle;*/

	string arquivo_projetil;
	Texture ProjetilTexture;
	Sprite ProjetilSprite;
};


#endif