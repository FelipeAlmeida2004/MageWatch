#ifndef TORRE_H
#define TORRE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <mutex>
#include "Projetil.h"


using namespace std;
using namespace sf;


//typedef struct {
//	string nome;
//	int tempoRegarga;
//	int ultimoUso;
//	string efeito;
//} Habilidade;

struct Bloco {
	string habilidade;
	Bloco* Dir;
	Bloco* Esq;
};

typedef struct Bloco* ADH;

class Torre {
public:
	Torre(int Dano, int Dinheiro, string arquivo_projetil);
	~Torre();

	void adicionaHabilidade(int escolha);
	void atualizaProjetil(bool FilaVazia);
	void setCooldown(float tempo);
	void rotaciona();
	void atira(Vector2f direction, bool inimigo_presente);


	bool getDisparo() {
		return disparo;
	}

	void setDisparo(bool disparo) {
		this->disparo = disparo;
	}

	Sprite& get_Sprite() {
		return TorreSprite;
	}

	Vector2f detectaInimigo(Vector2f inimigo);

	void setPosicao(Vector2f pos_atual) {
		return TorreSprite.setPosition(pos_atual);
	}

	Vector2f getPosicao() {
		return TorreSprite.getPosition();
	}

	double getDano() const {
		return Dano;
	}

	void setDano(int dano) {
		this->Dano = dano;
	}

	int getDinheiro() const {
		return Dinheiro;
	}

	void setDinheiro(int dinheiro) {
		this->Dinheiro = dinheiro;
	}

	bool colidiu_matou_inimigo(Vector2f pos_inimigo, float& vida_inimigo, Vector2f direction);

	void render(RenderWindow& janela);

	Texture define_textura(string arquivo) {
		arquivo_torre = arquivo;
		if (TorreTexture.loadFromFile(arquivo_torre)) {
			cout << "Torre texture loaded successfully" << endl;
			TorreSprite.setTexture(TorreTexture);
			int Xindex = 0;
			int Yindex = 0;
			TorreSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 90, 90));
			TorreSprite.setScale(Vector2f(1, 1));
			TorreSprite.setOrigin(TorreSprite.getGlobalBounds().width / 2, TorreSprite.getGlobalBounds().height / 2);
		}
		else {
			cout << "Torre texture failed to load" << endl;
		}
		return TorreTexture;
	}

	bool arvore_vazia(ADH& R) {
		if (R == NULL)
			return true;
		else
			return false;
	}

    void adiciona_arvore(ADH& R, int EscolhaJogador) {
        ADH Aux = new Bloco;
		Aux->Dir = NULL;
		Aux->Esq = NULL;
        if (arvore_vazia(R)) {
            R = Aux;
			if (EscolhaJogador == 1) {
				cout << "+Dano" << endl;
				Aux->habilidade = "Aumentou o dano";
				this->setDano(this->getDano() + 1.0f);
			}
			else if(EscolhaJogador == 2) {
				cout << "+Dinheiro" << endl;
				Aux->habilidade = "Aumentou o dinheiro";
				this->setDinheiro(this->getDinheiro() + 10);
			}
		}
		else {
			if (EscolhaJogador == 1)
				adiciona_arvore(R->Dir, EscolhaJogador);
			else if (EscolhaJogador == 2)
				adiciona_arvore(R->Esq, EscolhaJogador);
		}
    }

	void setArquivoProjetil(string novo_arquivo) {
		this->arquivo_projetil = novo_arquivo;
	}
	
	Clock clock;

private:
	Vector2f direction;
	float distancia;
	float rotacao;
	float cooldown;
	float ultimoDisparo;

	double Dano;
	int Dinheiro;

	bool disparo;

	ADH R = NULL;

	string arquivo_projetil;
	string arquivo_torre;
	Texture TorreTexture;
	Sprite TorreSprite;

	Projetil* projetil = nullptr;
};

#endif