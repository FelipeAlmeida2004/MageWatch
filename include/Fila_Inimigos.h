#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

struct Inimigo {
    float x, y;
    float vida;
    int Destino_Atual = 0;
    Inimigo* next;
    Texture EnemyTexture;
    Sprite EnemySprite;
    RectangleShape boundingRectangle;
};

class FilaInimigos {
private:

    Inimigo* Last;
    string arquivo_inimigo;
    vector<Vector2f> Caminhos = {
        {805.0f, 490.0f}, {805.0f, 165.0f}, {585.0f, 165.0f}, {585.0f, 860.0f},
        {370.0f, 860.0f}, {370.0f, 645.0f}, {1140.0f, 645.0f}, {1140.0f, 290.0f},
        {1420.0f, 290.0f}, {1420.0f, 765.0f}, {1950.0f, 775.0f}
    };

public:
    Inimigo* First;
    
    FilaInimigos(string arquivo) : First(nullptr), Last(nullptr), arquivo_inimigo(arquivo) {
        
    }
    
    ~FilaInimigos() {
        Destroi();
    }

    bool Vazia() {
        return (First == nullptr);
    }

    void Insere(float vida) {
        Inimigo* novo = new Inimigo;
        novo->x = 16.0f;
        novo->y = 490.0f;
        novo->vida = vida;
        novo->next = nullptr;
        /*novo->boundingRectangle.setFillColor(Color::Transparent);
        novo->boundingRectangle.setOutlineColor(Color::Red);
        novo->boundingRectangle.setOutlineThickness(1);
        novo->boundingRectangle.setSize(Vector2f(64, 64));*/
        define_textura(novo, arquivo_inimigo);
        novo->EnemySprite.setPosition(novo->x, novo->y);

        if (Vazia()) {
            First = novo;
            Last = novo;
        }
        else {
            novo->x = Last->x - 50.0f;
            Last->next = novo;
            Last = novo;
        }
    }

    void Remove() {
        if (Vazia()) {
            return;
        }

        cout << "Removendo Inimigo" << endl;
        Inimigo* removido = First;
        First = First->next;
        delete removido;
        if (!First) {
            Last = nullptr;
        }
    }

    void Destroi() {
        while (!Vazia()) {
            Remove();
        }
    }

    void define_textura(Inimigo* inimigo, string arquivo) {
        if (inimigo->EnemyTexture.loadFromFile(arquivo)) {
            inimigo->EnemySprite.setTexture(inimigo->EnemyTexture);
            inimigo->EnemySprite.setTextureRect(IntRect(0, 0, 64, 64));
            inimigo->EnemySprite.setScale(Vector2f(0.75, 0.75));
            inimigo->EnemySprite.setOrigin(inimigo->EnemySprite.getGlobalBounds().width / 2, inimigo->EnemySprite.getGlobalBounds().height / 2);
            /*inimigo->boundingRectangle.setOrigin(inimigo->EnemySprite.getOrigin());*/


        }
    }

    void desenha_inimigo(RenderWindow& janela) {
        Inimigo* atual = First;
        while (atual) {
            janela.draw(atual->EnemySprite);
            //janela.draw(atual->boundingRectangle);
            atual = atual->next;
        }
    }

    Vector2f getPosicaoInimigoAtual() {
        if (!Vazia()) {
            return Vector2f(First->EnemySprite.getPosition());
        }
        else
            return Vector2f(16.0f, 490.0f);
    }

    void move_inimigo(float velocidade) {
        if (!Vazia()) {
            Inimigo* atual = First;
            bool ainda_n_acabou = true;
            while (atual) {
                if (atual->Destino_Atual < Caminhos.size()) {
                    Vector2f destino = Caminhos[atual->Destino_Atual];
                    Vector2f direcao = destino - Vector2f(atual->x, atual->y);
                    float distancia = sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
                    if (distancia > 0.1f) {
                        direcao.x /= distancia;
                        direcao.y /= distancia;
                    }

                    atual->x += direcao.x * velocidade;
                    atual->y += direcao.y * velocidade;
                    atual->EnemySprite.setPosition(atual->x, atual->y);
                    atual->boundingRectangle.setPosition(atual->EnemySprite.getPosition());


                    if (distancia < velocidade) {
                        atual->Destino_Atual++;
                    }
                } 

                atual = atual->next;
            }
        }
    }
};