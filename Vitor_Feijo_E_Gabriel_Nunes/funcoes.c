#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "funcoes.h"

//Implementação das funções

int leMapa(char matriz[][COLUNAS], char nome[STRTAMANHO]) {

  //Abre o arquivo
  FILE *arq = fopen(nome, "r");

  //Testa a abertura correta do arquivo
  if (arq == NULL) {
    printf("Erro/n");
    return 1;
  }

  //Definições para a trasposição da matriz
  char parte;
  int linha = 0;
  int coluna = 0;

  while ((parte = fgetc(arq)) != EOF){  //Testa se o final do arquivo foi chego
                                          //junto da atribuição do caractere no char parte

    if (parte == '\n') {
      // Ignora quebras de linha
    }

    if (parte == 'C' || parte == 'X' || parte == ' ' || parte == 'Z') {
      // Preenche a matriz com os caracteres válidos
      matriz[linha][coluna] = parte;
      coluna++;
      if (coluna == COLUNAS) {
        coluna = 0;
        linha++;  // Avança para a próxima linha quando a coluna atingir 240
      }
    }
  }

  //Fecha o arquivo
  fclose(arq);

  return 0;
}


void PegaSubdivisao1Mapa(char submapa[][COLUNAS_MATRIZ_MENOR], char mapa[][COLUNAS]){
  int numero = 0;
  int i,j;

  //Pega a primeira submatriz 12x30 pelo numero ser sempre 0
  for(i = 0;i < LINHAS;i++){
    for(j = 0;j < COLUNAS_MATRIZ_MENOR;j++){
      submapa[i][j] = mapa[i][(numero*COLUNAS_MATRIZ_MENOR) + j];
    }
  }

}


void PegaSubdivisaoAleatoriaMapa(char submapa[][COLUNAS_MATRIZ_MENOR], char mapa[][COLUNAS]){
  int numero;
  int i,j;

  //Pega um numero aleatorio entre 0 e 7
  numero = (rand() % NUM_SUBMAPAS);

  //Usa o numero aleatorio para escolher uma das 8 submatrizes para ser o mapa do jogo
  for(i = 0;i < LINHAS;i++){
    for(j = 0;j < COLUNAS_MATRIZ_MENOR;j++){
      submapa[i][j] = mapa[i][(numero*COLUNAS_MATRIZ_MENOR) + j]; //j é somado ao numero aleatorio vezes o
                                                                   //numero de colunas da matriz menor
    }
  }

}





void Init_botao(Botao *botao, Rectangle ret, Color cor) {
  //Coloca as dimensoes do retangulo dado como argumento
  botao->ret = ret;
  //Coloca a cor dada como argumento
  botao->cor = cor;
}

bool MouseNoBotao(Botao botao){

  //checa se o mouse esta no botão
  return CheckCollisionPointRec(GetMousePosition(), botao.ret);

}

void TesteGamescreen(int *GameScreen) {

  switch(*GameScreen){

    //Menu - Se GameScreen for 0
    case MENU: {

    if (IsKeyPressed(KEY_N)){ //Se o N clicado, devolve
      *GameScreen = GAMEPLAY;
    }
    if (IsKeyPressed(KEY_L)){
      *GameScreen = LEADERBOARD;
    }
    } break;



    //Jogo - Se GameScreen for 1
    case GAMEPLAY:{
    if (IsKeyPressed(KEY_END)){
      *GameScreen = MENU;
    }
    } break;



    //Leaderboard - Se GameScreen for 2
    case LEADERBOARD:{
    if (IsKeyPressed(KEY_ESCAPE)){
      *GameScreen = MENU;
    }
    } break;
    default: break;
}

}

int deve_Mover(int dy, int jetpack_y){

    if((dy == 1 && jetpack_y <= LIM_SUPERIOR) || (dy == -1 && jetpack_y >= LIM_INFERIOR)){
        return 0; // jetpack não pode se mover
    }else{
        return 1; // jetpack pode se mover
    }

    return 1;
}


void DesenhaMenu(Botao botaoJogo, Botao botaoLeaderboard, int *GameScreen) {

  if(MouseNoBotao(botaoJogo)) {
    botaoJogo.cor = PINK;
  } else {
    botaoJogo.cor = RED;
  }

  if(MouseNoBotao(botaoJogo) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    *GameScreen = GAMEPLAY;
  }

  if(MouseNoBotao(botaoLeaderboard)) {
    botaoLeaderboard.cor = PINK;
  } else {
    botaoLeaderboard.cor = RED;
  }

  if(MouseNoBotao(botaoLeaderboard) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    *GameScreen = LEADERBOARD;
  }



  DrawRectangle(0, 0, LARGURA, ALTURA, LIGHTGRAY);
        DrawText("Menu", 30, 20, 40, BLACK);
        DrawText("PRESSIONE N PARA COMECAR O JOGO\n"
                 "PRESSIONE L PARA ACESSAR O LEADERBOARD\n"
                 "PRESSIONE Q PARA SAIR DO JOGO", 30, 375, 20, BLACK);
        DrawRectangleRec(botaoJogo.ret, botaoJogo.cor);
        DrawText("Jogo", 80, 130, 45, WHITE);
        DrawRectangleRec(botaoLeaderboard.ret, botaoLeaderboard.cor);
        DrawText("Leaderboard", 55, 290, 35, WHITE);



}


Color CorDoChar(char c) {
  //Dependendo da cor devolve uma cor diferente para o desenho do quadrado na função desenha retangulo
  switch (c) {
    case 'X': return BLACK;
    break;
    case 'C': return YELLOW;
    break;
    case 'Z': return RED;
    break;
    case ' ': return LIGHTGRAY;
    break;
    default: return DARKGRAY;
    break;
  }
}


int DesenhaRetanguloeColisao(int x, int y, int jetpack_x, int jetpack_y, char matriz[LINHAS][COLUNAS_MATRIZ_MENOR], int *moedas, Jogador jogadores[]) {
  int i,j;
  //Variaveis de colisão
  int colisao = 0;
  int colisaoMoeda = 0;
  int colisaoBomba = 0;

  for (i = 0; i < LINHAS; i++) {
    for (j = 0; j < COLUNAS_MATRIZ_MENOR; j++) {

      //Condições de colisão
      colisaoMoeda =
        jetpack_x >= (x + j * TAMANHO_BLOCO) &&
        jetpack_x <= (x + j * TAMANHO_BLOCO + TAMANHO_BLOCO) &&
        jetpack_y >= (y + i * TAMANHO_BLOCO - TAMANHO_BLOCO) &&
        jetpack_y <= (y + i * TAMANHO_BLOCO + TAMANHO_BLOCO);

      colisaoBomba =
        jetpack_x >= (x + j * TAMANHO_BLOCO) &&
        jetpack_x <= (x + j * TAMANHO_BLOCO + TAMANHO_BLOCO) &&
        jetpack_y >= (y + i * TAMANHO_BLOCO - TAMANHO_BLOCO) &&
        jetpack_y <= (y + i * TAMANHO_BLOCO + TAMANHO_BLOCO);

      Color squareColor = CorDoChar(matriz[i][j]); //Analisa o char da matriz e determina a cor do quadrado

      //Teste colisão das moedas
      /*
      if (colisaoMoeda) {
        squareColor = RED; // Marca o quadrado em vermelho, por exemplo
      }
      */

      //Teste colisão das bombas
      /*
      if (colisaoBomba) {
        squareColor = BLUE; // Marca o quadrado em vermelho, por exemplo
      }
      */

      DrawRectangle(x + j * TAMANHO_BLOCO, y + i * TAMANHO_BLOCO, TAMANHO_BLOCO, TAMANHO_BLOCO, squareColor);  //Desenha o quadrado


      //Teste das colisões
      if(colisaoMoeda){
        if(matriz[i][j] == 'C'){
          matriz[i][j] = ' ';
          *moedas += 1; //Soma uma a quantidade de moedas
          jogadores[3].pontuacao += 1; //Soma um a pontuação do jogador
        }
      }
      if(colisaoBomba){
        if(matriz[i][j] == 'Z'){
          //matriz[i][j] = ' ';
          colisao = 1;
        }
      }


    }
  }
  return colisao;
}

void PauseJogo(bool *pausado){

  if(IsKeyPressed(KEY_ESCAPE)){
        *pausado = !(*pausado);
      }

      while(*pausado){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Pause", 40, 40, 40, BLACK);
        EndDrawing();

        if(IsKeyPressed(KEY_ESCAPE)){
          *pausado = !(*pausado);
        }
      }
}

void Movimentacao(int *jetpack_y, int *dy){

  if(IsKeyDown(KEY_SPACE) || IsKeyDown(MOUSE_BUTTON_LEFT)){
    *dy = 1;
    if(deve_Mover(*dy,* jetpack_y)){
      *jetpack_y -= JET_SPEED_Y * GetFrameTime();   // aumenta ou diminui a distância que se move o personagem em funcao do fps
      WaitTime(SECONDS);
    }
    }
    else if(IsKeyUp(KEY_SPACE) || IsKeyUp(MOUSE_BUTTON_LEFT)){
      if(*jetpack_y < LIM_INFERIOR)
      *jetpack_y += GRAVIDADE * GetFrameTime();  // aplicar a gravidade se a tecla para cima nao esta sendo pressionada
    }

}

void TelaFimJogo(Jogador jogadores[]){
//Tela de fim de jogo
  Rectangle textBox = { LARGURA/2.0f - 300, 180, 600, 60}; //Caixa de texto
  int ContaLetras = 0; //Contador de letras
  int letra;

  while (!WindowShouldClose()  && !IsKeyPressed(KEY_ENTER)){


      letra = GetCharPressed(); // Pega o char e armazena em letra

      // Teste de mais de uma tecla sendo pressionada ao mesmo tempo
      while (letra > 0){

      if ((letra >= 32) && (letra <= 125) && (ContaLetras < 22)){ //Só permite chars entre 22 e 125 e no maximo 22 caracteres
        jogadores[3].nome[ContaLetras] = (char)letra;
        jogadores[3].nome[ContaLetras+1] = '\0'; // Adiciona o \0 no fim da string
        ContaLetras++;
      }

      letra = GetCharPressed();  // Pega o próximo char
      }

      if (IsKeyPressed(KEY_BACKSPACE)){ // Caso o Backspace seja pressionado apaga o ultimo char
        ContaLetras--;
        if (ContaLetras < 0) ContaLetras = 0; //Caso de contaletras negativo
          jogadores[3].nome[ContaLetras] = '\0';
      }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Digite o seu Nome", 40, 40, 30, BLACK);
            DrawText(TextFormat("Pontuacao: %.0f", jogadores[3].pontuacao), 500, 300, 30, BLUE); //Desenho da pontuação do jogador

            DrawRectangleRec(textBox, LIGHTGRAY); //Caixa de texto

            DrawText(jogadores[3].nome, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON); //Desenha o nome em tempo real

        EndDrawing();
    }
}

int TelaFases(int *fases, Botao botaoMapa1, Botao botaoMapa2, Botao botaoMapa3, Jogador jogadores[], float *pontuacao){

  int flag1 = 0;
  int flag2 = 0;
  int contadorframes = 0;
  int flagFimLoop = 0;

  //Atualização da pontuação caso a nova pontuação seja maior que a antiga
  if(*pontuacao < jogadores[3].pontuacao){
    *pontuacao = jogadores[3].pontuacao;
  }

  //inicialização dos botões
  Init_botao(&botaoMapa1, (Rectangle){80, 200, 200, 100}, RED);
  Init_botao(&botaoMapa2, (Rectangle){300, 200, 200, 100}, RED);
  Init_botao(&botaoMapa3, (Rectangle){520, 200, 200, 100}, RED);

  while(*fases == 0 && flagFimLoop == 0){

    BeginDrawing();
    DrawRectangle(0, 0, LARGURA, ALTURA, LIGHTGRAY);
    DrawText("Fases", 20, 20, 40, BLACK);

    //Teste para mudar a cor do botão caso o cursor esteja sobre o botão
    if(MouseNoBotao(botaoMapa1)) {
      botaoMapa1.cor = PINK;
    } else {
      botaoMapa1.cor = RED;
    }

    if(MouseNoBotao(botaoMapa2)) {
      botaoMapa2.cor = PINK;
    } else {
      botaoMapa2.cor = RED;
    }

    if(MouseNoBotao(botaoMapa3)) {
      botaoMapa3.cor = PINK;
    } else {
      botaoMapa3.cor = RED;
    }


    //Botão 1 - Fase 1

    //Desenho
    DrawText("  PONTUACAO \nNECESSARIA: 0", 80, 90, 23, BLACK);
    DrawRectangleRec(botaoMapa1.ret, botaoMapa1.cor);
    DrawText("Fase 1", 110, 230, 40, BLACK);

    //Teste de clique no botão
    if(MouseNoBotao(botaoMapa1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      *fases = 1;
    }


    //Botão 2 - Fase 2

    //Desenho
    DrawText("  PONTUACAO \nNECESSARIA: 500", 300, 90, 23, BLACK);
    DrawRectangleRec(botaoMapa2.ret, botaoMapa2.cor);
    DrawText("Fase 2", 330, 230, 40, BLACK);

    //Teste de clique no botão
    if(MouseNoBotao(botaoMapa2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && *pontuacao > 500){
      *fases = 2;
    }
    else if(MouseNoBotao(botaoMapa2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      flag1 = 1; //flag para mostrar a imagem de pontuação insuficiente
    }

    //Botão 3 - Fase 3

    //Desenho
    DrawText("  PONTUACAO \nNECESSARIA: 1000", 520, 90, 23, BLACK);
    DrawRectangleRec(botaoMapa3.ret, botaoMapa3.cor);
    DrawText("Fase 3", 550, 230, 40, BLACK);

    //Teste de clique no botão
    if(MouseNoBotao(botaoMapa3) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && *pontuacao > 1000){
      *fases = 3;
    }
    else if(MouseNoBotao(botaoMapa3) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      flag2 = 1; //flag para mostrar a imagem de pontuação insuficiente
    }

    DrawText(TextFormat("Pontuacao Atual: %.0f", *pontuacao), 40, 350, 30, BLUE);


    if(flag1 == 1){
      contadorframes++; //Temporizador para a mensagem
      DrawText("Pontuacao insuficiente", 400, 400, 30, BLACK);
      if(contadorframes > 60){
        //reset de variaveis
        flag1 = 0;
        contadorframes = 0;
      }
    }

    if(flag2 == 1){
      contadorframes++; //Temporizador para a mensagem
      DrawText("Pontuacao insuficiente", 400, 400, 30, BLACK);
      if(contadorframes > 60){
        //reset de variaveis
        flag2 = 0;
        contadorframes = 0;
      }
    }

    if(IsKeyPressed(KEY_ESCAPE)){ //Teste de saida da janela para voltar para o menu
      flagFimLoop = 1; //Se for igual a um não executa o jogo e volta pro menu
    }

    EndDrawing();

  }

  return flagFimLoop; //Se flagFimLoop == 1, não executa o jogo e volta pro menu, senão executa o jogo
}



void DesenhaLeaderboard(Jogador *jogadores, Botao botaoMenu, int *GameScreen) {
  // Declaração de strings para guardar as pontuações como texto
  char pontuacao1[8];
  char pontuacao2[8];
  char pontuacao3[8];

  // Pega as pontuações dos jogadores como strings para exibir na tela
  snprintf(pontuacao1, sizeof(pontuacao1), "%.0f", jogadores[0].pontuacao);
  snprintf(pontuacao2, sizeof(pontuacao2), "%.0f", jogadores[1].pontuacao);
  snprintf(pontuacao3, sizeof(pontuacao3), "%.0f", jogadores[2].pontuacao);

  // Analisa se o mouse está sobre o botão e muda a cor dele
  if(MouseNoBotao(botaoMenu)) {
    botaoMenu.cor = PINK; //Se estiver será rosa
  } else {
    botaoMenu.cor = RED; //Senão vermelho
  }

  //Se o botão for clicado volta ao menu
  if(MouseNoBotao(botaoMenu) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    *GameScreen = MENU;
  }

  //Desenho do Leaderboard e jogadores
  DrawRectangle(0, 0, LARGURA, ALTURA, LIGHTGRAY);
    DrawText("LEADERBOARD", 20, 20, 40, BLACK);

    //Desenho do primeiro melhor jogador e a sua pontuação
    DrawText(jogadores[0].nome, 50, 100, 25, BLACK);
    DrawText(pontuacao1, 300, 100, 25, BLACK);

    //Desenho do segundo melhor jogador e a sua pontuação
    DrawText(jogadores[1].nome, 50, 150, 25, BLACK);
    DrawText(pontuacao2, 300, 150, 25, BLACK);

    //Desenho do terceiro melhor jogador e a sua pontuação
    DrawText(jogadores[2].nome, 50, 200, 25, BLACK);
    DrawText(pontuacao3, 300, 200, 25, BLACK);

    //Desenho do botão para voltar para o menu
    DrawRectangleRec(botaoMenu.ret, botaoMenu.cor);
    DrawText("Menu", 530, 330, 45, WHITE);

    DrawText("PRESSIONE ESQ PARA VOLTAR PARA MENU", 20, 400, 20, BLACK);



}


int GravaLeaderboard(Jogador *jogadores) {
//Pega o arquivo binario com o top 3 jogadores e grava em uma estrutura dada

//4 bytes de int para a pontuação e depois mais 30 bytes de nome do cara(3 jogadores)
  FILE *arq = fopen("leaderboard.bin", "r+");

  //caso de erro na leitura do arquivo
  if(arq == NULL){
    printf("Leitura incorreta do arquivo de leitura");
    return 1;
  }

  int i;

  //Gravação de um novo leaderboard hardcoded, caso necessario
  /*
  Jogador jogadores1[3] = {
        {10000, "O Imperador"},
        {1000, "O Magico"},
        {100, "O Bobo da Corte"}
    };

  for (i = 0; i < NUMJOGADORES; i++) {
    fwrite(&jogadores1[i], sizeof(Jogador), 1, arq);
  }
  rewind(arq);
  */

  //Leitura de todos os jogadores do arquivo com o loop for
  for (i = 0; i < NUMJOGADORES; i++) {
    fread(&jogadores[i], sizeof(Jogador), 1, arq);
  }

  fclose(arq);
  return 0;
}


int GravaNovoJogador(Jogador jogadores[]){

  FILE *arq = fopen("leaderboard.bin", "w+");

  //caso de erro na leitura do arquivo
  if(arq == NULL){
    printf("Leitura incorreta do arquivo de escrita");
    return 1;
  }

  //Se o novo jogador tiver uma pontuação maior que o melhor do leaderboard,
  //colocar ele em primeiro e o resto atras
  if(jogadores[3].pontuacao >= jogadores[0].pontuacao){
    fwrite(&jogadores[3], sizeof(Jogador), 1, arq);
    fwrite(&jogadores[0], sizeof(Jogador), 1, arq);
    fwrite(&jogadores[1], sizeof(Jogador), 1, arq);
  }
  //Se o novo jogador tiver uma pontuação maior que o segundo melhor do leaderboard,
  //colocar ele em segundo, o primeiro se mantem e coloca o segundo anterior em ultimo
  else if(jogadores[3].pontuacao >= jogadores[1].pontuacao){
    fwrite(&jogadores[0], sizeof(Jogador), 1, arq);
    fwrite(&jogadores[3], sizeof(Jogador), 1, arq);
    fwrite(&jogadores[1], sizeof(Jogador), 1, arq);
  }
  //Se o novo jogador tiver uma pontuação maior que o terceiro melhor do leaderboard,
  //colocar ele em ultimo, o primeiro e o segundo se mantem
  else if(jogadores[3].pontuacao >= jogadores[2].pontuacao){
    fwrite(&jogadores[0], sizeof(Jogador), 1, arq);
    fwrite(&jogadores[1], sizeof(Jogador), 1, arq);
    fwrite(&jogadores[3], sizeof(Jogador), 1, arq);
  }
  //Senão escrever de novo os jogadores que ja estavam no podio
  else{
    fwrite(&jogadores[0], sizeof(Jogador), 1, arq);
    fwrite(&jogadores[1], sizeof(Jogador), 1, arq);
    fwrite(&jogadores[2], sizeof(Jogador), 1, arq);
  }

  fclose(arq);

  return 0;
}






