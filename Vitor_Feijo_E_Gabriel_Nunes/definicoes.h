#include <stdio.h>
#include "raylib.h"

#ifndef DEFINICOES_H
#define DEFINICOES_H

//Estados do GameScreen
#define MENU 0
#define GAMEPLAY 1
#define LEADERBOARD 2

//Definições do tamanho da tela
#define COMPRIMENTO 800
#define LARGURA 800
#define ALTURA 450

//Definições do leaderboard
#define STRTAMANHO 30
#define NUMJOGADORES 3

//Definições do jogador
#define LIM_SUPERIOR 40
#define LIM_INFERIOR 380
#define JET_SPEED_Y 260
#define POSICAO_X_JOGADOR 150
#define TAMANHO_BLOCO 38
#define GRAVIDADE 230
#define SECONDS 0.02


//Definições do background
#define VELOCITY 2
#define ACELERACAO 0.002

//Definições do mapa
#define COLUNAS_MATRIZ_MENOR 30
#define LINHAS 12
#define COLUNAS 240
#define TAM 300
#define NUM_SUBMAPAS 8


typedef struct {
    float pontuacao;
    char nome[STRTAMANHO];
} Jogador;

typedef struct {
  Rectangle ret;
  Color cor;
} Botao;


#endif
