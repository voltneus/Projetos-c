#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "definicoes.h"
#include "funcoes.h"




void Gameplayloop(int *GameScreen, Jogador *jogadores, int *fases) {

  //Personagem
  int jetpack_x = POSICAO_X_JOGADOR;       // posicao x do personagem
  int jetpack_y = ALTURA / 2;              // posicao y do personagem
  int dy = 0;
  Texture2D spritepersonagem = LoadTexture("foguetao.png");  //Textura do personagem
  Vector2 posicoes = {jetpack_x, jetpack_y};
  Rectangle retangulo_personagem = {0, 0, TAMANHO_BLOCO, TAMANHO_BLOCO};


  //colisoes, uma para cada função de colisão
  int colisao1 = 0; // Se colisão == 1, então colidiu
  int colisao2 = 0; // Se colisão == 1, então colidiu

  //Pontuação
  int moedas = 0; //Numero de moedas coletadas
  float contadorframes = 60; //Contador de frames para calcular a distancia(velocidade/tempo == distancia)
  float distancia = 0; //Distancia mostrada na tela

  // mapa
  float deslocamentoX1 = 0;          //Coordenada do primeiro retângulo
  float deslocamentoX2 = COLUNAS_MATRIZ_MENOR * TAMANHO_BLOCO; //Coordenada do segundo retângulo
  float velocidade = VELOCITY;   //velocidade usada para mover os mapas na tela

  float somaAceleracao = 0; //Soma da aceleração, usada pra consertar um problema dos
                            //retangulos ficarem com um espaço não desenhado no meio


  //Mapa
  char matrizMapa[LINHAS][COLUNAS] = {0};            //Matriz principal
  char submapa1[LINHAS][COLUNAS_MATRIZ_MENOR] = {0}; //Primeiro submapa usado para ser desenhado
  char submapa2[LINHAS][COLUNAS_MATRIZ_MENOR] = {0}; //Segundo submapa usado para ser desenhado
  char nome_arquivo1[STRTAMANHO] = "mapa1.txt";
  char nome_arquivo2[STRTAMANHO] = "mapa2.txt";
  char nome_arquivo3[STRTAMANHO] = "mapa3.txt";
  char nome_arquivo[STRTAMANHO] = {0}; //String usada para armazenar o nome do arquivo do mapa escolhido


  //Menu de Pausa
  bool pausado = false;

  //Copia o nome do arquivo do mapa escolhido para a string nome_arquivo
  if(*fases == 1){
    strcpy(nome_arquivo, nome_arquivo1);
  }
  else if(*fases == 2){
    strcpy(nome_arquivo, nome_arquivo2);
  }
  else if(*fases == 3){
    strcpy(nome_arquivo, nome_arquivo3);
  }


  //Inicialização da variavel do novo jogador
  jogadores[3].pontuacao = 0;

  //leitura do mapa
  leMapa(matrizMapa, nome_arquivo);

  //Pega o
  PegaSubdivisao1Mapa(submapa1, matrizMapa);
  PegaSubdivisaoAleatoriaMapa(submapa2, matrizMapa);

  while(colisao1 == 0 && colisao2 == 0){ //se não colidiu, continua

      Movimentacao(&jetpack_y, &dy); //função de movimentação do personagem

      posicoes.x = jetpack_x;
      posicoes.y = jetpack_y;

      velocidade += ACELERACAO; //Adição da aceleração na velocidade

      somaAceleracao += ACELERACAO + 0.01; //Concerto no desenho dos retangulos na tela

      contadorframes += 1.0/60.0; // Incremento do tempo para o calculo da distancia


      //Incremento colisões
      jogadores[3].pontuacao = jogadores[3].pontuacao + ((velocidade / contadorframes) * 10); //Incremento da pontuação do jogador
      distancia = distancia + (velocidade / contadorframes); //Incremento da distancia


      //Incremento do deslocamento(coordenada x dos retangulos desenhados na tela
      deslocamentoX1 -= velocidade;
      deslocamentoX2 -= velocidade;

      //Teste para reposiocionar o mapa desenhado quando ele sai da tela + troca da matriz
      if (deslocamentoX1 <= -COLUNAS_MATRIZ_MENOR * TAMANHO_BLOCO) {
          deslocamentoX1 = COLUNAS_MATRIZ_MENOR * TAMANHO_BLOCO - somaAceleracao;
          PegaSubdivisaoAleatoriaMapa(submapa1, matrizMapa);
      }
      if (deslocamentoX2 <= -COLUNAS_MATRIZ_MENOR * TAMANHO_BLOCO) {
          deslocamentoX2 = COLUNAS_MATRIZ_MENOR * TAMANHO_BLOCO - somaAceleracao;
          PegaSubdivisaoAleatoriaMapa(submapa2, matrizMapa);
      }


      BeginDrawing();
      ClearBackground(RAYWHITE);


      // Desenho da matriz em repetição + teste de colisão
      colisao1 = DesenhaRetanguloeColisao(deslocamentoX1, 0, jetpack_x, jetpack_y, submapa1, &moedas, jogadores);
      colisao2 = DesenhaRetanguloeColisao(deslocamentoX2, 0, jetpack_x, jetpack_y, submapa2, &moedas, jogadores);

      //Desenho da distancia e moedas
      DrawText(TextFormat("Distancia: %.0fm", distancia), 40, 10, 30, BLUE);
      DrawText(TextFormat("Moedas: %d", moedas), 40, 40, 30, BLUE);


      // desenho do personagem
      DrawTextureRec(spritepersonagem, retangulo_personagem, posicoes, WHITE);


      EndDrawing();

      //Menu de pausa
      PauseJogo(&pausado);

  }

  *fases = 0; //reseta a fase para poder reescolher


}




int main () {

  //Menu = 0, Gameplay = 1, Leaderboard = 2,
  int GameScreen = 0;

  //Jogadores do Leaderboard
  Jogador jogadores[NUMJOGADORES+1] = {0}; //3 ja presentes no leaderboard + o novo jogador

  //Maior pontuação de um jogador
  float pontuacao = 0;

  //Botões - Estrutura: botao + (onde levam)
  Botao botaoJogo = {0};
  Botao botaoLeaderboard = {0};
  Botao botaoMenu = {0};
  Botao botaoMapa1 = {0};
  Botao botaoMapa2 = {0};
  Botao botaoMapa3 = {0};

  //Inicializa a janela
  InitWindow(LARGURA, ALTURA, "Jogo");

  //Inicializa os botôes
  Init_botao(&botaoJogo, (Rectangle){40, 100, 200, 100}, RED);
  Init_botao(&botaoLeaderboard, (Rectangle){40, 250, 250, 100}, RED);
  Init_botao(&botaoMenu, (Rectangle){500, 300, 200, 100}, RED);

  //Fases
  int fases = 0;  //Fases == 1, então mapa1, Fases == 2, então mapa2, Fases == 3, então mapa3

  SetTargetFPS(60);

  while (!WindowShouldClose() && !IsKeyPressed(KEY_Q)){

    TesteGamescreen(&GameScreen); //Testa se a tela mostrada devia mudar por inputs

    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch(GameScreen){ //GameScreen é a variavel que controla qual tela será mostrada
    case MENU:{
      //Função de desenho do menu
      DesenhaMenu(botaoJogo, botaoLeaderboard, &GameScreen);
    } break;
    case GAMEPLAY:{
      //Se a função entregou 1, saiu do loop por clicar no ESC
      if(TelaFases(&fases, botaoMapa1, botaoMapa2, botaoMapa3, jogadores, &pontuacao) == 0){

      //Loop de gameplay principal
      Gameplayloop(&GameScreen, jogadores, &fases);

      //Tela de fim de jogo na qual se pega o nome do novo jogador
      TelaFimJogo(jogadores);

      //Grava os jogadores do arquivo binario em uma estrutura
      GravaLeaderboard(jogadores);

      //Grava no leaderboard.bin o novo jogador
      GravaNovoJogador(jogadores);
      }
      //Muda a tela para o menu
      GameScreen = 0;
    } break;
    case LEADERBOARD:{
      //Grava os jogadores do arquivo binario em uma estrutura
      GravaLeaderboard(jogadores);
      //Desenha o leaderboard com a estrutura dada
      DesenhaLeaderboard(jogadores, botaoMenu, &GameScreen);
    } break;
    }
    EndDrawing();
  }


  return 0;
}
