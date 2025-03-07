#ifndef FUNCOES_H
#define FUNCOES_H

#include "raylib.h"   // Se você estiver usando tipos da raylib como Rectangle e Color
#include "definicoes.h"

// Declarações das funções

// Funções para o botão
void Init_botao(Botao *botao, Rectangle ret, Color cor);
bool MouseNoBotao(Botao botao);

// Função para controlar a tela do jogo
void TesteGamescreen(int *GameScreen);

// Função para verificar se o jetpack pode se mover
int deve_Mover(int dy, int jetpack_y);

// Função para desenhar o menu
void DesenhaMenu(Botao botaoJogo, Botao botaoLeaderboard, int *GameScreen);

// Função para determinar a cor do personagem
Color CorDoChar(char c);

// Função para desenhar o retângulo da matriz
int DesenhaRetanguloeColisao(int x, int y, int jetpack_x, int jetpack_y, char matriz[LINHAS][COLUNAS_MATRIZ_MENOR], int *moedas, Jogador jogadores[]);

// Função para desenhar o leaderboard
void DesenhaLeaderboard(Jogador *jogadores, Botao botaoMenu, int *GameScreen);

// Função para gravar o leaderboard em um arquivo binário
int GravaLeaderboard(Jogador *jogadores);

//Função para adicionar o novo jogador ao leaderboard
int GravaNovoJogador(Jogador jogadores[]);

//Funções para a matriz
int leMapa(char matriz[][COLUNAS], char nome[STRTAMANHO]);
void PegaSubdivisaoAleatoriaMapa(char submapa[][COLUNAS_MATRIZ_MENOR], char mapa[][COLUNAS]);
void PegaSubdivisao1Mapa(char submapa[][COLUNAS_MATRIZ_MENOR], char mapa[][COLUNAS]);

//Função do pause
void PauseJogo(bool *pausado);

//Função de escolha da fase
int TelaFases(int *fases, Botao botaoMapa1, Botao botaoMapa2, Botao botaoMapa3, Jogador jogadores[], float *pontuacao);

//Função de fim de jogo
void TelaFimJogo(Jogador jogadores[]);

//Movimentação do jogador
void Movimentacao(int *jetpack_y, int *dy);

#endif
