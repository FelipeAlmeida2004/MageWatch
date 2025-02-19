#include "Torre.h"
#include <math.h>


Torre::Torre(int Dano, int Dinheiro, string arquivo_projetil) : Dano(Dano), Dinheiro(Dinheiro), arquivo_projetil(arquivo_projetil), R(R){
	this->ultimoDisparo = 0;
}

Torre::~Torre() {
	if (projetil) {
		delete projetil;
		cout << "deletendo projetil";
	}
}

void Torre::adicionaHabilidade(int escolha_jogador) {
	adiciona_arvore(R, escolha_jogador);
}

Vector2f Torre::detectaInimigo(Vector2f posicao_inimigo) {
	direction = posicao_inimigo - TorreSprite.getPosition();
	return direction;
}

void Torre::setCooldown(float tempo) {
	this->cooldown = tempo;
}

void Torre::atira(Vector2f direction, bool inimigo_presente) {
	ultimoDisparo += clock.getElapsedTime().asSeconds();
	if (ultimoDisparo >= cooldown && inimigo_presente) {
		cout << "Dano da torre: " << this->getDano() << endl;
		projetil = new Projetil(0, 0);
		projetil->define_textura(arquivo_projetil);
		projetil->setVelocidade(40.0f);
		projetil->setDano(this->getDano());
		projetil->getSprite().setPosition(TorreSprite.getPosition());

		rotacao = atan2f(direction.y, direction.x) * 180 / 3.14;
		disparo = true;
		ultimoDisparo = 0;
	}
}

void Torre::atualizaProjetil(bool FilaVazia) {
	if (FilaVazia) {
		delete projetil;
		projetil = nullptr;
	}
	
	if (projetil != nullptr) {
		projetil->move(clock.getElapsedTime().asSeconds());

		if (projetil->getSprite().getPosition().x > 1920 || projetil->getSprite().getPosition().y > 1080 || projetil->getSprite().getPosition().x < 0 || projetil->getSprite().getPosition().y < 0) {
			delete projetil;
			disparo = false;
			projetil = nullptr;
		}
	}
}

bool Torre::colidiu_matou_inimigo(Vector2f pos_inimigo, float& vida_inimigo, Vector2f direction) {
	if (projetil != nullptr) {
		FloatRect boundsProjetil = projetil->getSprite().getGlobalBounds();
		FloatRect boundsInimigo(pos_inimigo.x - 4, pos_inimigo.y - 6, 4, 8);

		if (boundsProjetil.intersects(boundsInimigo)) {
			vida_inimigo -= projetil->getdano();
			delete projetil;
			projetil = nullptr;
			disparo = false;

			cout << vida_inimigo << endl;

			if (vida_inimigo <= 0) {
				return true;
			}
		}
	}
	return false;
}

void Torre::rotaciona() {
	rotacao = atan2f(direction.y, direction.x) * 180 / 3.14;
	TorreSprite.setRotation(rotacao);
	if (projetil != nullptr)
		projetil->setAngulo(rotacao);

}

void Torre::render(RenderWindow& janela) {
	if (projetil != nullptr)
		projetil->render(janela);
	janela.draw(TorreSprite);
}