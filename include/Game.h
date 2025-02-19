#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <list>
#include "Fila_inimigos.h"
#include "Projetil.h"
#include "Torre.h"
#include "Menu.h"
#include "Config.h"

string arquivo_fonte = "Assets/Gerais/Fonts/FonteOficial.ttf";

struct Rodada {
    int numeroRodada;
    int totalInimigos;
    float vidaInimigos;
    float velocidadeInimigos;
    float spawnDelay;
};


Rodada gerarRodada(int numeroRodada) {
    Rodada rodada;
    rodada.numeroRodada = numeroRodada;
    rodada.totalInimigos = 10 + (numeroRodada - 1) * 2;
    if (numeroRodada % 2 == 0)
        rodada.vidaInimigos = 50.0f + (numeroRodada - 1) * 2.0f;
    else
        rodada.vidaInimigos = 50.0f + (numeroRodada - 2) * 2.0f;

    rodada.velocidadeInimigos = 3.0f + (numeroRodada - 1) * 0.05f;
    rodada.spawnDelay = 1.0f - (numeroRodada - 1) * 0.01f;
    return rodada;
}

bool pausado = false;

void desenharMenuPausa(RenderWindow& window) {

    RectangleShape fundo(Vector2f(1920, 1080));
    fundo.setFillColor(Color(0, 0, 0, 150));
    window.draw(fundo);

    Font font;
    if (!font.loadFromFile(arquivo_fonte)) {
        cerr << "Erro ao carregar a fonte" << endl;
        return;
    }

    Text textoPausa("Jogo Pausado", font, 100);
    textoPausa.setFillColor(Color(255, 255, 255));
    textoPausa.setPosition(1920 / 2 - textoPausa.getGlobalBounds().width / 2, 300);
    window.draw(textoPausa);

    Text continuar("Continuar", font, 50);
    continuar.setFillColor(Color(255, 255, 255));
    continuar.setPosition(1920 / 2 - continuar.getGlobalBounds().width / 2, 500);
    window.draw(continuar);

    Text Restart("Restart", font, 50);
    Restart.setFillColor(Color(255, 255, 255));
    Restart.setPosition(1920 / 2 - Restart.getGlobalBounds().width / 2, 600);
    window.draw(Restart);

    Text sair("Sair", font, 50);
    sair.setFillColor(Color(255, 255, 255));
    sair.setPosition(1920 / 2 - sair.getGlobalBounds().width / 2, 700);
    window.draw(sair);
}

void desenharRodada(RenderWindow& window, int rodadaAtual, int alpha) {
    Font font;
    if (!font.loadFromFile(arquivo_fonte)) {
        cerr << "Erro ao carregar a fonte" << endl;
        return;
    }

    Text textoRodada("Rodada " + to_string(rodadaAtual), font, 100);
    textoRodada.setFillColor(Color(255, 255, 255, alpha));
    textoRodada.setPosition(1920 / 2 - textoRodada.getGlobalBounds().width / 2, 300);
    window.draw(textoRodada);
}

bool jogoFinalizado = false;

void desenharPerdeu(RenderWindow& window) {
    RectangleShape fundo(Vector2f(1920, 1080));
    fundo.setFillColor(Color(0, 0, 0, 150));
    window.draw(fundo);

    Font font;
    if (!font.loadFromFile(arquivo_fonte)) {
        std::cerr << "Erro ao carregar a fonte" << std::endl;
        return;
    }

    Text textoPausa("Você Perdeu", font, 100);
    textoPausa.setFillColor(Color(255, 255, 255));
    textoPausa.setPosition(1920 / 2 - textoPausa.getGlobalBounds().width / 2, 300);
    window.draw(textoPausa);

    Text Restart("Restart", font, 50);
    Restart.setFillColor(Color(255, 255, 255));
    Restart.setPosition(1920 / 2 - Restart.getGlobalBounds().width / 2, 450);
    window.draw(Restart);

    Text sair("Sair", font, 50);
    sair.setFillColor(Color(255, 255, 255));
    sair.setPosition(1920 / 2 - sair.getGlobalBounds().width / 2, 525);
    window.draw(sair);
}

void desenharGanhou(RenderWindow& window) {
    RectangleShape fundo(Vector2f(1920, 1080));
    fundo.setFillColor(Color(0, 0, 0, 150));
    window.draw(fundo);

    Font font;
    if (!font.loadFromFile(arquivo_fonte)) {
        cerr << "Erro ao carregar a fonte" << endl;
        return;
    }

    Text textoPausa("Você Ganhou", font, 100);
    textoPausa.setFillColor(Color(255, 255, 255));
    textoPausa.setPosition(1920 / 2 - textoPausa.getGlobalBounds().width / 2, 300);
    window.draw(textoPausa);

    Text Restart("Restart", font, 50);
    Restart.setFillColor(Color(255, 255, 255));
    Restart.setPosition(1920 / 2 - Restart.getGlobalBounds().width / 2, 600);
    window.draw(Restart);

    Text sair("Sair", font, 50);
    sair.setFillColor(Color(255, 255, 255));
    sair.setPosition(1920 / 2 - sair.getGlobalBounds().width / 2, 700);
    window.draw(sair);
}

void MostraInformacoes(RenderWindow& window, int PrecoTorre, int PrecoMelhoria) {
    Font font;
    if (!font.loadFromFile(arquivo_fonte)) {
        cerr << "Erro ao carregar a fonte" << endl;
        return;
    }

	Text PrecoMelhorias("Preço das Melhorias", font, 35);
	PrecoMelhorias.setFillColor(Color::Yellow);
    PrecoMelhorias.setOrigin(PrecoMelhorias.getGlobalBounds().width / 2, PrecoMelhorias.getGlobalBounds().height / 2);
	PrecoMelhorias.setPosition(1670, 870);
	window.draw(PrecoMelhorias);

	Text Info("Dano e Ganhos " + to_string(PrecoMelhoria) + " Moedas", font, 25);
    Info.setFillColor(Color(255, 255, 255));
    Info.setOrigin(Info.getGlobalBounds().width / 2, Info.getGlobalBounds().height / 2);
    Info.setPosition(1670, 910);
    window.draw(Info);

    Text PrecoTorres("Preço das Torres", font, 35);
    PrecoTorres.setFillColor(Color::Yellow);
    PrecoTorres.setOrigin(PrecoTorres.getGlobalBounds().width / 2, PrecoTorres.getGlobalBounds().height / 2);
    PrecoTorres.setPosition(1670, 950);
    window.draw(PrecoTorres);

	Text InfoTorres(to_string(PrecoTorre) + " Moedas", font, 25);
	InfoTorres.setFillColor(Color(255, 255, 255));
	InfoTorres.setOrigin(InfoTorres.getGlobalBounds().width / 2, InfoTorres.getGlobalBounds().height / 2);
	InfoTorres.setPosition(1670, 990);
	window.draw(InfoTorres);
    
}

class Game {
    private:

        string arquivo_torre = "Assets/Tower/Textures/TorreMago.png";
        string arquivo_mapa = "Assets/Mapas/Textures/Mapa1.png";
        string arquivo_inimigo = "Assets/Enemy/Textures/Enemy3.png";
        string arquivo_projetil = "Assets/Projetil/Textures/Projetil2.png";
        string arquivo_fundoCompra = "Assets/Gerais/Textures/FundoCompra.png";
        string arquivo_DetalheCompra = "Assets/Gerais/Textures/setaossocima.png";
        string arquivo_maisDano = "Assets/Gerais/Textures/dano.png";
        string arquivo_maisDinheiro = "Assets/Gerais/Textures/ganhos.png";
        string arquivo_mostraMelhorias = "Assets/Gerais/Textures/fundomelhoria.png";
        string arquivo_Opcao1compra = "Assets/Gerais/Textures/botaocomprar2.png";
        string arquiv_fundo_VidaDinheiro = "Assets/Gerais/Textures/fundovidadinheiro.png";
        string arquivo_Vida = "Assets/Gerais/Textures/coracao.png";
        string arquivo_Dinheiro = "Assets/Gerais/Textures/moeda.png";
        string arquivo_TorreDinheiro = "Assets/Tower/Textures/mago_ouro2.png";
        string arquivo_TorreDano = "Assets/Tower/Textures/mago_dano3.png";
        string arquivo_ProjetilDano = "Assets/Projetil/Textures/Projetil4.png";
        string arquivo_ProjetilDinheiro = "Assets/Projetil/Textures/Projetil3.png";
        string arquivo_Musica = "Assets/Gerais/Music/musica2.ogg";
        string arquivo_MusicaMenu = "Assets/Gerais/Music/musica.ogg";
        string arquivo_Background = "Assets/Background/Textures/background.png";
        string arquivo_mostra_rounds = "Assets/Gerais/Textures/bandejacomprafechada.png";
		string arquivo_mostra_informacoes = "Assets/Gerais/Textures/bandejainformacoes.png";


        double velocidadeInimigos = 3.0f;
        bool FilaVazia;

        bool mostrarRodada = false;

        Vector2f offset;
        bool cliqueRegistrado = false;
        bool isDragging = false;
        bool botaoDireito = false;
        bool botaoEsquerdo = false;
        bool Comprando = false;
        bool MostraTorres = true;

        RenderWindow window;
        VideoMode videMode;
        Menu menu;
        Config config;
        bool menuAtivo = true;

        float width, height;

        int ContadorDinheiro = 50;
        int ContadorVida = 100;

        int PrecoTorre = 50;
		int PrecoMelhoria = 25;

		int danoProjetil = 25;
        int dinheiroGanho = 5;

        Torre* TorreEmCompra = nullptr;
        Torre* torreAtual = nullptr;
        list<Torre> torres;
        vector<RectangleShape> desing_pista;
        vector<RectangleShape> Invalidos;

        FilaInimigos fila;

        Music Musica;

        Clock clock;
        Clock spawnClock;
        float spawnDelay = 1.0f;
        int inimigosInseridos = 0;
        int totalInimigos = 10;

        int alpha = 0;
        Clock fadeClock;

        Clock atrasoEntreRodadas;
        float tempoAtraso = 3.75f;
        bool esperandoProximaRodada = false;
        int rodadaAtual = 1;
        bool rodadaEmAndamento = false;

        Font font;

        Text Vida;
        Text Round;

        Text Dinheiro;

        Texture TorresParaCompraTexture;
        Sprite TorresParaCompraSprite;

        Texture DetalheCompraTexture;
        Sprite DetalheCompraSprite;

        Texture MaisDanoTexture;
        Sprite MaisDanoSprite;

        Texture MaisDinheiroTexture;
        Sprite MaisDinheiroSprite;

        Texture mostraMelhoriasTexture;
        Sprite mostraMelhoriasSprite;

        Texture Opcao1TorreTexture;
        Sprite Opcao1TorreSprite;

        Texture mapaTexture;
        Sprite mapaSprite;

        Texture VidaTexture;
        Sprite VidaSprite;

        Texture DinheiroTexture;
        Sprite DinheiroSprite;

        Texture MostraRoundsTexture;
        Sprite MostraRoundsSprite;

        Texture MostraInformacoesTexture;
        Sprite MostraInformacoesSprite;

        RectangleShape AreaTorreNova;

        void inicializarTrajetos() {
            vector<Vector2f> tamanhos = {
                {850, 70}, {80, 350}, {230, 80}, {80, 700}, {205, 70},
                {70, 210}, {780, 70}, {70, 350}, {300, 70}, {80, 490}, {440, 80}
            };

            vector<Vector2f> posicoes = {
                {0, 465}, {775, 115}, {545, 120}, {545, 200}, {340, 830},
                {340, 620}, {405, 615}, {1110, 270}, {1180, 270}, {1400, 325}, {1480, 735}
            };

            for (size_t i = 0; i < tamanhos.size(); i++) {
                RectangleShape trajeto(tamanhos[i]);
                trajeto.setOrigin(0, 0);
                trajeto.setPosition(posicoes[i]);
                trajeto.setFillColor(sf::Color::Red);
                desing_pista.push_back(trajeto);
            }
        }

        void carregarTexturas() {
            if (!font.loadFromFile(arquivo_fonte)) {
                cerr << "Failed to load font texture" << endl;
            }

            if (TorresParaCompraTexture.loadFromFile(arquivo_fundoCompra)) {
                cout << "TorresParaCompra texture loaded successfully" << endl;
                TorresParaCompraSprite.setTexture(TorresParaCompraTexture);
                int Xindex = 0;
                int Yindex = 0;
                TorresParaCompraSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 359, 519));
                TorresParaCompraSprite.setScale(Vector2f(1, 1));
                TorresParaCompraSprite.setOrigin(TorresParaCompraSprite.getGlobalBounds().width / 2, TorresParaCompraSprite.getGlobalBounds().height / 2);
                TorresParaCompraSprite.setPosition(Vector2f(1730.5f, 249.5f));
            }

            if (DetalheCompraTexture.loadFromFile(arquivo_DetalheCompra)) {
                cout << "DetalheCompraTexture texture loaded successfully" << endl;
                DetalheCompraSprite.setTexture(DetalheCompraTexture);
                int Xindex = 0;
                int Yindex = 0;
                DetalheCompraSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 100, 100));
                DetalheCompraSprite.setScale(Vector2f(1, 1));
                DetalheCompraSprite.setOrigin(DetalheCompraSprite.getGlobalBounds().width / 2, DetalheCompraSprite.getGlobalBounds().height / 2);
                DetalheCompraSprite.setPosition(Vector2f(TorresParaCompraSprite.getPosition().x, 465.5f));
            }

            if (MaisDanoTexture.loadFromFile(arquivo_maisDano)) {
                cout << "MaisDanoTexture texture loaded successfully" << endl;
                MaisDanoSprite.setTexture(MaisDanoTexture);
                int Xindex = 0;
                int Yindex = 0;
                MaisDanoSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 85, 35));
                MaisDanoSprite.setScale(Vector2f(1, 1));
                MaisDanoSprite.setOrigin(MaisDanoSprite.getGlobalBounds().width / 2, MaisDanoSprite.getGlobalBounds().height / 2);
                MaisDanoSprite.setPosition(Vector2f(-1000, -1000));
            }

            if (MaisDinheiroTexture.loadFromFile(arquivo_maisDinheiro)) {
                cout << "MaisDinheiroTexture texture loaded successfully" << endl;
                MaisDinheiroSprite.setTexture(MaisDinheiroTexture);
                int Xindex = 0;
                int Yindex = 0;
                MaisDinheiroSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 85, 35));
                MaisDinheiroSprite.setScale(Vector2f(1, 1));
                MaisDinheiroSprite.setOrigin(MaisDinheiroSprite.getGlobalBounds().width / 2, MaisDinheiroSprite.getGlobalBounds().height / 2);
                MaisDinheiroSprite.setPosition(Vector2f(-1000, -1000));
            }

            if (mostraMelhoriasTexture.loadFromFile(arquivo_mostraMelhorias)) {
                cout << "mostraMelhoriasTexture texture loaded successfully" << endl;
                mostraMelhoriasSprite.setTexture(mostraMelhoriasTexture);
                int Xindex = 0;
                int Yindex = 0;
                mostraMelhoriasSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 100, 100));
                mostraMelhoriasSprite.setScale(Vector2f(1, 1));
                mostraMelhoriasSprite.setOrigin(mostraMelhoriasSprite.getGlobalBounds().width / 2 - 50, mostraMelhoriasSprite.getGlobalBounds().height / 2 + 50);
            }

            if (Opcao1TorreTexture.loadFromFile(arquivo_Opcao1compra)) {
                cout << "Opcao1TorreTexture texture loaded successfully" << endl;
                Opcao1TorreSprite.setTexture(Opcao1TorreTexture);
                int Xindex = 0;
                int Yindex = 0;
                Opcao1TorreSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 250, 93));
                Opcao1TorreSprite.setScale(Vector2f(1, 1));
                Opcao1TorreSprite.setOrigin(Opcao1TorreSprite.getGlobalBounds().width / 2, Opcao1TorreSprite.getGlobalBounds().height / 2);
                Opcao1TorreSprite.setPosition(TorresParaCompraSprite.getPosition().x, TorresParaCompraSprite.getPosition().y - 185);
            }

            if (VidaTexture.loadFromFile(arquivo_Vida)) {
                cout << "Opcao1TorreTexture texture loaded successfully" << endl;
                VidaSprite.setTexture(VidaTexture);
                int Xindex = 0;
                int Yindex = 0;
                VidaSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 65, 65));
                VidaSprite.setScale(Vector2f(0.85, 0.85));
                VidaSprite.setOrigin(VidaSprite.getGlobalBounds().width / 2, VidaSprite.getGlobalBounds().height / 2);
                VidaSprite.setPosition(Vector2f(30, 30.5));
            }

            if (DinheiroTexture.loadFromFile(arquivo_Dinheiro)) {
                cout << "Opcao1TorreTexture texture loaded successfully" << endl;
                DinheiroSprite.setTexture(DinheiroTexture);
                int Xindex = 0;
                int Yindex = 0;
                DinheiroSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 65, 65));
                DinheiroSprite.setScale(Vector2f(0.85, 0.85));
                DinheiroSprite.setOrigin(DinheiroSprite.getGlobalBounds().width / 2, DinheiroSprite.getGlobalBounds().height / 2);
                DinheiroSprite.setPosition(Vector2f(150, 32.5));
            }

            if (MostraRoundsTexture.loadFromFile(arquivo_mostra_rounds)) {
                cout << "Opcao1TorreTexture texture loaded successfully" << endl;
                MostraRoundsSprite.setTexture(MostraRoundsTexture);
                int Xindex = 0;
                int Yindex = 0;
                MostraRoundsSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 359, 132));
                MostraRoundsSprite.setScale(Vector2f(0.85, 0.85));
                MostraRoundsSprite.setOrigin(MostraRoundsSprite.getGlobalBounds().width / 2, 0);
                MostraRoundsSprite.setPosition(Vector2f(960, 0));
            }

            if (MostraInformacoesTexture.loadFromFile(arquivo_mostra_informacoes)) {
                cout << "Opcao1TorreTexture texture loaded successfully" << endl;
                MostraInformacoesSprite.setTexture(MostraInformacoesTexture);
                int Xindex = 0;
                int Yindex = 0;
                MostraInformacoesSprite.setTextureRect(IntRect(Xindex * 64, Yindex * 64, 500, 249));
                MostraInformacoesSprite.setScale(Vector2f(1, 1));
                MostraInformacoesSprite.setOrigin(MostraInformacoesSprite.getGlobalBounds().width / 2, MostraInformacoesSprite.getGlobalBounds().height / 2);
                MostraInformacoesSprite.setPosition(Vector2f(1670, 945));
            }

            if (mapaTexture.loadFromFile(arquivo_mapa)) {
                cout << "Mapa texture loaded successfully" << endl;
                mapaSprite.setTexture(mapaTexture);
                mapaSprite.setScale(Vector2f(1, 1));
            }
            else {
                cout << "Mapa texture failed to load" << endl;
            }
        }

        void reiniciarJogo() {
            ContadorVida = 100;
            ContadorDinheiro = 200;
            rodadaAtual = 1;
            jogoFinalizado = false;
            pausado = false;
            esperandoProximaRodada = false;
            rodadaEmAndamento = false;
            inimigosInseridos = 0;
            totalInimigos = 10;

            fila.Destroi();

            torres.clear();

            Invalidos.clear();

            clock.restart();
            spawnClock.restart();
            fadeClock.restart();
            atrasoEntreRodadas.restart();

            Musica.stop();
            Musica.play();
        }

    public:
        Game(float width, float height)
            : menu(1920, 1080, arquivo_Background, arquivo_fonte, arquivo_MusicaMenu), fila(arquivo_inimigo),
            AreaTorreNova(Vector2f(100, 100)), width(width), height(height), Vida("Vida", font, 30),
            Dinheiro("Dinheiro", font, 30), Round("Round", font, 30), config(width, height, arquivo_fonte) {

            Vida.setFillColor(Color::White);
            Vida.setOrigin(Vector2f(0, Vida.getGlobalBounds().height / 2));
            Vida.setPosition(Vector2f(60, 20.5));

            Dinheiro.setFillColor(Color::White);
            Dinheiro.setOrigin(Vector2f(0, Dinheiro.getGlobalBounds().height / 2));
            Dinheiro.setPosition(Vector2f(180, 20.5));

            Round.setFillColor(Color::White);
            Round.setOrigin(Round.getGlobalBounds().width / 2, 0);
            Round.setPosition(Vector2f(960, 0));

            Musica.openFromFile(arquivo_Musica);
            Musica.setVolume(10);

            window.create(VideoMode(width, height), "Tower Defense", Style::Fullscreen);
            window.setFramerateLimit(60);

            if (!window.isOpen()) {
                cerr << "Erro ao abrir a janela do jogo!" << std::endl;
            }

            inicializarTrajetos();
            carregarTexturas();

            AreaTorreNova.setOrigin(AreaTorreNova.getGlobalBounds().width / 2, AreaTorreNova.getGlobalBounds().height / 2);
            AreaTorreNova.setFillColor(Color::Transparent);
            AreaTorreNova.setOutlineThickness(1);
        }

        ~Game() {}

        void run() {
            while (window.isOpen()) {
                processarEventos();
                atualizar();
                render();
            }
        }

        void iniciarJogo() {
            menuAtivo = false;
            menu.ControlaMusica(false);
            Musica.play();
            torres.clear();
            fila.Destroi();
        }

        void processarEventos() {
            Text continuar("Continuar", font, 50);
            continuar.setPosition(1920 / 2 - continuar.getGlobalBounds().width / 2, 500);

            Text sair("Sair", font, 50);
            sair.setPosition(1920 / 2 - sair.getGlobalBounds().width / 2, 700);
            
            Text sairGanhou("Sair", font, 50);
            sairGanhou.setPosition(1920 / 2 - sairGanhou.getGlobalBounds().width / 2, 700);

            Text Restart("Restart", font, 50);
            Restart.setPosition(1920 / 2 - Restart.getGlobalBounds().width / 2, 450);

            Text RestartPause("Restart", font, 50);
            RestartPause.setPosition(1920 / 2 - RestartPause.getGlobalBounds().width / 2, 600);

            Text RestartFinal("Restart", font, 50);
            RestartFinal.setPosition(1920 / 2 - RestartFinal.getGlobalBounds().width / 2, 450);

            Text sairJogoFinal("Sair", font, 50);
            sairJogoFinal.setPosition(1920 / 2 - sairJogoFinal.getGlobalBounds().width / 2, 525);

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (menuAtivo) {
                    if (event.type == Event::MouseMoved) {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                        menu.handleMouseHover(mousePos);
                    }

                    if (config.getStatus()) {
                        config.eventos(event, window, menu.getMusica(), Musica);
                        return;
                    }

                    if (event.type == Event::MouseButtonPressed) {
                        if (event.mouseButton.button == Mouse::Left) {
                            if (menu.pressed() == 0) {
                                cout << "Iniciar Jogo" << std::endl;
                                iniciarJogo();
                            }
                            else if (menu.pressed() == 1) {
                                cout << "Configuracoes" << std::endl;
                                config.ativar();
                            }

                            else if (menu.pressed() == 2) {
                                cout << "Sair" << std::endl;
                                window.close();
                            }
                        }
                    }
                }
                else {
                    if (event.type == Event::MouseButtonPressed) {
                        if (event.mouseButton.button == Mouse::Left) {

                            int mouseX = event.mouseButton.x;
                            int mouseY = event.mouseButton.y;

                            IntRect area1(MaisDanoSprite.getPosition().x - 42.5, MaisDanoSprite.getPosition().y - 17.5, 85, 35);
                            IntRect area2(MaisDinheiroSprite.getPosition().x - 42.5, MaisDinheiroSprite.getPosition().y - 17.5, 85, 35);
                            IntRect areaMostraHabilidades(mostraMelhoriasSprite.getPosition().x, mostraMelhoriasSprite.getPosition().y - 100, 100, 100);
                            IntRect areaOpcaoCompra1(Opcao1TorreSprite.getPosition().x - 125, Opcao1TorreSprite.getPosition().y - 46.5, 250, 93);
                            IntRect areaDetalhe(DetalheCompraSprite.getPosition().x - 33, DetalheCompraSprite.getPosition().y - 39, 66, 78);



                            if (torreAtual) {
                                if (areaMostraHabilidades.contains(mouseX, mouseY)) {
                                    botaoDireito = true;
                                    if (area1.contains(mouseX, mouseY) && ContadorDinheiro >= PrecoMelhoria) {
                                        ContadorDinheiro -= PrecoMelhoria;
                                        torreAtual->adicionaHabilidade(1);
                                        MaisDanoSprite.setScale(Vector2f(0.75, 0.75));
                                        torreAtual->define_textura(arquivo_TorreDano);
                                        torreAtual->get_Sprite().setOrigin((torreAtual->get_Sprite().getGlobalBounds().width / 2) - 15, (torreAtual->get_Sprite().getGlobalBounds().height / 2) - 15);
                                        torreAtual->setArquivoProjetil(arquivo_ProjetilDano);
                                        cliqueRegistrado = true;
                                    }
                                    else if (area2.contains(mouseX, mouseY) && ContadorDinheiro >= PrecoMelhoria) {
                                        ContadorDinheiro -= PrecoMelhoria;
                                        torreAtual->adicionaHabilidade(2);
                                        MaisDinheiroSprite.setScale(Vector2f(0.75, 0.75));
                                        torreAtual->define_textura(arquivo_TorreDinheiro);
                                        torreAtual->get_Sprite().setOrigin((torreAtual->get_Sprite().getGlobalBounds().width / 2), (torreAtual->get_Sprite().getGlobalBounds().height / 2));
                                        torreAtual->setArquivoProjetil(arquivo_ProjetilDinheiro);
                                        cliqueRegistrado = true;
                                    }
                                }
                                else {
                                    botaoDireito = false;
                                    torreAtual = nullptr;
                                }
                            }

                            if (areaDetalhe.contains(mouseX, mouseY)) {
                                MostraTorres = !MostraTorres;
                            }

                            if (areaOpcaoCompra1.contains(mouseX, mouseY) && ContadorDinheiro >= 50) {
                                ContadorDinheiro -= PrecoTorre;
                                TorreEmCompra = new Torre(danoProjetil, dinheiroGanho, arquivo_projetil);
                                TorreEmCompra->define_textura(arquivo_torre);
                                TorreEmCompra->setCooldown(1.0f);
                                Comprando = true;

                            }
                        }
                    }

                    if (Comprando && TorreEmCompra) {
                        Vector2i mousePos = Mouse::getPosition(window);
                        TorreEmCompra->get_Sprite().setPosition(mousePos.x, mousePos.y);
                        cout << "Posicao da torre: (" << mousePos.x << ", " << mousePos.y << ")" << endl;

                        AreaTorreNova.setPosition(TorreEmCompra->get_Sprite().getPosition());

                        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                            bool posicaoValida = true;
                            for (auto& trajeto : desing_pista) {
                                if (trajeto.getGlobalBounds().intersects(TorreEmCompra->get_Sprite().getGlobalBounds())) {
                                    cout << "Posicao invalida: dentro do trajeto!" << endl;
                                    posicaoValida = false;
                                    break;
                                }
                            }

                            if (posicaoValida) {
                                for (auto& torre : torres) {
                                    if (torre.get_Sprite().getGlobalBounds().intersects(TorreEmCompra->get_Sprite().getGlobalBounds())) {
                                        cout << "Posicao invalida: dentro da area de outra torre!" << endl;
                                        posicaoValida = false;
                                        break;
                                    }
                                }
                            }

                            if (posicaoValida) {
                                AreaTorreNova.setOutlineColor(Color::Green);
                            }
                            else {
                                AreaTorreNova.setOutlineColor(Color::Red);
                            }

                            if (posicaoValida) {
                                torres.push_back(*TorreEmCompra);
                                torres.back().define_textura(arquivo_torre);
                                delete TorreEmCompra;
                                TorreEmCompra = nullptr;
                                Comprando = false;
                                RectangleShape boundingRectangle;
                                boundingRectangle.setFillColor(Color::Transparent);
                                boundingRectangle.setOutlineColor(Color::Red);
                                boundingRectangle.setOutlineThickness(1);
                                boundingRectangle.setSize(Vector2f(torres.back().get_Sprite().getGlobalBounds().width + 10, torres.back().get_Sprite().getGlobalBounds().height + 10));
                                boundingRectangle.setOrigin(boundingRectangle.getLocalBounds().width / 2, boundingRectangle.getLocalBounds().height / 2);
                                boundingRectangle.setPosition(torres.back().getPosicao());
                                cout << "Posicao invalida centro: " << boundingRectangle.getPosition().x << ", " << boundingRectangle.getPosition().y << endl;
                                Invalidos.push_back(boundingRectangle);
                            }
                            else {
                                ContadorDinheiro += 50;
                                delete TorreEmCompra;
                                TorreEmCompra = nullptr;
                                Comprando = false;
                            }
                        }
                    }
                    else
                        AreaTorreNova.setOutlineColor(Color::Green);

                    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
                        if (TorreEmCompra) {
                            ContadorDinheiro += 50;
                            delete TorreEmCompra;
                            TorreEmCompra = nullptr;
                            Comprando = false;
                        }
                    }

                    if (event.type == Event::MouseButtonPressed) {
                        if (event.mouseButton.button == Mouse::Right) {

                            int mouseX = event.mouseButton.x;
                            int mouseY = event.mouseButton.y;

                            bool cliqueEmTorre = false;

                            for (auto& torre : torres) {
                                IntRect areaTorre(torre.get_Sprite().getPosition().x - 32, torre.get_Sprite().getPosition().y - 32, 64, 64);
                                if (areaTorre.contains(mouseX, mouseY)) {
                                    torreAtual = &torre;
                                    botaoDireito = true;
                                    botaoEsquerdo = false;
                                    cliqueEmTorre = true;
                                    break;
                                }
                                else {
                                    botaoEsquerdo = false;
                                    botaoDireito = false;
                                }
                            }

                            if (!cliqueEmTorre) {
                                torreAtual = nullptr;
                            }
                        }
                    }

                    if (torreAtual) {
                        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Delete) {
                            auto it = torres.begin();
                            auto itInvalidos = Invalidos.begin();
                            while (it != torres.end()) {
                                if (&(*it) == torreAtual) {
                                    it = torres.erase(it);
                                    Invalidos.erase(itInvalidos);
                                    torreAtual = nullptr;
								    mostraMelhoriasSprite.setPosition(Vector2f(-1000, 1000));
								    MaisDanoSprite.setPosition(Vector2f(-1000, -1000));
								    MaisDinheiroSprite.setPosition(Vector2f(-1000, -1000));
								    ContadorDinheiro += 50;
                                    break;
                                }
                                ++it;
                                ++itInvalidos;
                            }
                        }
                    }

                    if (event.type == Event::MouseButtonReleased) {
                        if (event.mouseButton.button == Mouse::Left) {
                            botaoEsquerdo = false;
                            MaisDanoSprite.setScale(Vector2f(1, 1));
                            MaisDinheiroSprite.setScale(Vector2f(1, 1));
                            cliqueRegistrado = false;
                            Comprando = false;
                        }
                    }

                    if (event.type == Event::KeyPressed) {
                        if (event.key.code == Keyboard::Escape && !jogoFinalizado) {
                            pausado = !pausado;
                            if (pausado) {
                                Musica.pause();
                                fadeClock.restart();
                                alpha = 0;
                            }
                            else {
                                Musica.play();
                            }
                        }
                    }

                    if (jogoFinalizado) {
                        Musica.pause();
                        fadeClock.restart();
                        alpha = 0;
                    }

                    if(pausado && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                        if (sair.getGlobalBounds().contains(mousePos))
                            window.close();
                    }
                    
                    if(pausado && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                        if (RestartPause.getGlobalBounds().contains(mousePos))
                            reiniciarJogo();
                    }

                    if (pausado && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                        if (continuar.getGlobalBounds().contains(mousePos)) {
                            pausado = !pausado;
							Musica.play();
                        }
                    }

                    if (jogoFinalizado && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                        if (sairJogoFinal.getGlobalBounds().contains(mousePos))
                            window.close();
                    }

                    if (jogoFinalizado && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                        if (Restart.getGlobalBounds().contains(mousePos))
                            reiniciarJogo();
                    }
                    
                    if (jogoFinalizado && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                        if (RestartFinal.getGlobalBounds().contains(mousePos))
                            reiniciarJogo();
                    }
                    
                    if (jogoFinalizado && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                        if (sairGanhou.getGlobalBounds().contains(mousePos))
                            window.close();
                    }
                }
            }
        }

        void atualizar() {
            if (!menuAtivo) {
                if (!pausado && !jogoFinalizado) {
                    if (!rodadaEmAndamento && !esperandoProximaRodada) {
                        Rodada rodada = gerarRodada(rodadaAtual);
                        fila.Destroi();
                        inimigosInseridos = 0;
                        totalInimigos = rodada.totalInimigos;
                        velocidadeInimigos = rodada.velocidadeInimigos;
                        spawnDelay = rodada.spawnDelay;

                        for (inimigosInseridos; inimigosInseridos < totalInimigos; inimigosInseridos++) {
                            fila.Insere(rodada.vidaInimigos);
                        }

                        for (auto& torre : torres) {
                            torre.setDisparo(false);
                            torre.clock.restart();
                        }


                        rodadaEmAndamento = true;
                        mostrarRodada = true;
                        fadeClock.restart();
                        alpha = 0;
                        cout << "Rodada " << rodadaAtual << " iniciada!" << endl;
                    }

                    if (fila.Vazia() && rodadaEmAndamento) {
                        rodadaEmAndamento = false;
                        esperandoProximaRodada = true;
                        atrasoEntreRodadas.restart();
                        cout << "Rodada " << rodadaAtual << " conclu�da!" << endl;
                    }

                    if (esperandoProximaRodada && atrasoEntreRodadas.getElapsedTime().asSeconds() >= tempoAtraso) {
                        esperandoProximaRodada = false;
                        rodadaAtual++;
                        if (rodadaAtual % 5 == 0) {
							dinheiroGanho += 5;
                            PrecoTorre += 10;
							PrecoMelhoria += 5;
                        }
                        cout << "Preparando para a rodada " << rodadaAtual << "..." << endl;
                    }

                    DetalheCompraSprite.setPosition(TorresParaCompraSprite.getPosition().x, TorresParaCompraSprite.getPosition().y + 200.0f);
                    Opcao1TorreSprite.setPosition(TorresParaCompraSprite.getPosition().x, TorresParaCompraSprite.getPosition().y - 185);

                    for (auto& torre : torres) {
                        if(torreAtual) {
                            if (botaoDireito) {
                                mostraMelhoriasSprite.setPosition(torreAtual->get_Sprite().getPosition().x + 45, torreAtual->get_Sprite().getPosition().y - 45);
                                if (mostraMelhoriasSprite.getPosition().y - 50 <= 0)
                                    mostraMelhoriasSprite.setPosition(torreAtual->get_Sprite().getPosition().x + 45, torreAtual->get_Sprite().getPosition().y + 135);
                                MaisDanoSprite.setPosition(mostraMelhoriasSprite.getPosition().x + 50, mostraMelhoriasSprite.getPosition().y - 70);
                                MaisDinheiroSprite.setPosition(mostraMelhoriasSprite.getPosition().x + 50, mostraMelhoriasSprite.getPosition().y - 30);
                            }
                            else {
                                mostraMelhoriasSprite.setPosition(Vector2f(-1000, 1000));
                                MaisDanoSprite.setPosition(Vector2f(-1000, -1000));
                                MaisDinheiroSprite.setPosition(Vector2f(-1000, -1000));
                            }
                        }
                        else {
                            mostraMelhoriasSprite.setPosition(Vector2f(-1000, 1000));
                            MaisDanoSprite.setPosition(Vector2f(-1000, -1000));
                            MaisDinheiroSprite.setPosition(Vector2f(-1000, -1000));
                        }
                    }

                    if (MostraTorres) {
                        TorresParaCompraSprite.setPosition(Vector2f(1730.5f, 249.5f));
                        DetalheCompraSprite.setRotation(0);
                        if (Comprando) {
                            Opcao1TorreSprite.setScale(0.85, 0.85);
                        }
                        else
                            Opcao1TorreSprite.setScale(1, 1);
                    }
                    else {
                        TorresParaCompraSprite.setPosition(Vector2f(1730.5f, -150.0f));
                        DetalheCompraSprite.setRotation(180);
                    }

                    if (!fila.Vazia())
                        fila.move_inimigo(velocidadeInimigos);

                    if (inimigosInseridos < totalInimigos && spawnClock.getElapsedTime().asSeconds() > spawnDelay) {
                        fila.Insere(1.0f);
                        inimigosInseridos++;
                        spawnClock.restart();
                        cout << "inimigo criado" << inimigosInseridos << endl;
                    }

                    FilaVazia = fila.Vazia();
                    for (auto& torre : torres) {
                        torre.atualizaProjetil(FilaVazia);
                    }

                    if (!fila.Vazia()) {
                        Vector2f inimigoPos = fila.getPosicaoInimigoAtual();
                        float& vida_inimigo = fila.First->vida;
                        for (auto& torre : torres) {
                            torre.detectaInimigo(inimigoPos);
                            torre.rotaciona();

                            if (!torre.getDisparo()) {
                                torre.atira(torre.detectaInimigo(inimigoPos), true);
                                torre.clock.restart();
                            }

                            if (torre.colidiu_matou_inimigo(inimigoPos, vida_inimigo, torre.detectaInimigo(inimigoPos))) {
                                ContadorDinheiro += torre.getDinheiro();
                                cout << "Dinheiro do Jogador: " << ContadorDinheiro << endl;
                                fila.Remove();
                            }
                        }
                    }
                }

                if (mostrarRodada) {
                    float tempoPassado = fadeClock.getElapsedTime().asSeconds();
                    if (tempoPassado < 1.0f) {
                        alpha = static_cast<int>(255 * (tempoPassado / 1.0f));
                    }
                    else if (tempoPassado < 3.0f) {
                        alpha = 255;
                    }
                    else if (tempoPassado < 4.0f) {
                        alpha = static_cast<int>(255 * (1.0f - (tempoPassado - 3.0f) / 1.0f));
                    }
                    else {
                        mostrarRodada = false;
                    }
                }

                if (fila.getPosicaoInimigoAtual().x > 1920) {
                    ContadorVida -= 10;
                    cout << "Vida da torre do jogador: " << ContadorVida << endl;
                    fila.Remove();
                }

                if (rodadaAtual > 40 && fila.Vazia()) {
                    cout << "Parab�ns, voc� venceu o jogo!" << endl;
                    window.close();
                }

                if (ContadorVida <= 0) {
                    desenharPerdeu(window);
                    jogoFinalizado = true;
                }

                if (rodadaAtual > 40 && fila.Vazia()) {
                    desenharGanhou(window);
                    jogoFinalizado = true;
                }

                string VidaText;
                VidaText = to_string(ContadorVida);
                Vida.setString(VidaText);
                Vida.setScale(1.2, 1.2);

                string DinheiroText;
                DinheiroText = to_string(ContadorDinheiro);
                Dinheiro.setString(DinheiroText);
                Dinheiro.setScale(1.2, 1.2);

                string RoundText;
                RoundText = to_string(rodadaAtual);
                Round.setString("Rodada\n" + RoundText + " de 40");
                Round.setPosition(Vector2f(920, 0));
                Round.setScale(1.4, 1.4);

            

                window.clear(Color::Black);
            }
        }


        void render() {

            if (menuAtivo) {
                menu.draw(window, config.getStatus());
            }
            else {
                window.draw(mapaSprite);
                fila.desenha_inimigo(window);

                for (auto& torre : torres) {
                    torre.render(window);
                }
           
                if (TorreEmCompra) {
                    for (auto& invalido : Invalidos)
                        window.draw(invalido);
                    window.draw(AreaTorreNova);
                }

                window.draw(mostraMelhoriasSprite);
                window.draw(MaisDanoSprite);
                window.draw(MaisDinheiroSprite);
                window.draw(TorresParaCompraSprite);
                window.draw(DetalheCompraSprite);
                window.draw(Opcao1TorreSprite);
                window.draw(DinheiroSprite);
                window.draw(VidaSprite);
                window.draw(Vida);
                window.draw(Dinheiro);
                window.draw(MostraRoundsSprite);
                window.draw(Round);

                Vector2i mousePos = Mouse::getPosition(window);

                if (torreAtual) {
                    window.draw(MostraInformacoesSprite);
                    MostraInformacoes(window, PrecoTorre, PrecoMelhoria);
                }

                if (Opcao1TorreSprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.draw(MostraInformacoesSprite);
                    MostraInformacoes(window, PrecoTorre, PrecoMelhoria);
                }

                if (pausado) {
                    desenharMenuPausa(window);
                }

                if (mostrarRodada) {
                    desenharRodada(window, rodadaAtual, alpha);
                }

                if (pausado && !jogoFinalizado) {
                    desenharMenuPausa(window);
                }
                if (jogoFinalizado) {
                    if (ContadorVida <= 0) {
                        desenharPerdeu(window);
                    }
                    else if (rodadaAtual > 40 && fila.Vazia()) {
                        desenharGanhou(window);
                    }
                }
            }

            if (config.getStatus()) {
                config.draw(window);
            }

            window.display();
        }
};

#endif