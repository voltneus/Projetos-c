#ifndef FUNCOES_H
#define FUNCOES_H

#include "raylib.h"   // Se voc� estiver usando tipos da raylib como Rectangle e Color
#include "definicoes.h"

// Declara��es das fun��es

// Fun��es para o bot�o
void Init_botao(Botao *botao, Rectangle ret, Color cor);
bool MouseNoBotao(Botao botao);

// Fun��o para controlar a tela do jogo
void TesteGamescreen(int *GameScreen);

// Fun��o para verificar se o jetpack pode se mover
int deve_Mover(int dy, int jetpack_y);

// Fun��o para desenhar o menu
void DesenhaMenu(Botao botaoJogo, Botao botaoLeaderboard, int *GameScreen);

// Fun��o para determinar a cor do personagem
Color CorDoChar(char c);

// Fun��o para desenhar o ret�ngulo da matriz
int DesenhaRetanguloeColisao(int x, int y, int jetpack_x, int jetpack_y, char matriz[LINHAS][COLUNAS_MATRIZ_MENOR], int *moedas, Jogador jogadores[]);

// Fun��o para desenhar o leaderboard
void DesenhaLeaderboard(Jogador *jogadores, Botao botaoMenu, int *GameScreen);

// Fun��o para gravar o leaderboard em um arquivo bin�rio
int GravaLeaderboard(Jogador *jogadores);

//Fun��o para adicionar o novo jogador ao leaderboard
int GravaNovoJogador(Jogador jogadores[]);

//Fun��es para a matriz
int leMapa(char matriz[][COLUNAS], char nome[STRTAMANHO]);
void PegaSubdivisaoAleatoriaMapa(char submapa[][COLUNAS_MATRIZ_MENOR], char mapa[][COLUNAS]);
void PegaSubdivisao1Mapa(char submapa[][COLUNAS_MATRIZ_MENOR], char mapa[][COLUNAS]);

//Fun��o do pause
void PauseJogo(bool *pausado);

//Fun��o de escolha da fase
int TelaFases(int *fases, Botao botaoMapa1, Botao botaoMapa2, Botao botaoMapa3, Jogador jogadores[], float *pontuacao);

//Fun��o de fim de jogo
void TelaFimJogo(Jogador jogadores[]);

//Movimenta��o do jogador
void Movimentacao(int *jetpack_y, int *dy);

#endif
