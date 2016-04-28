#include "biblaureano.h"

void imprimePecaMatriz(short xPeca, short yPeca, short peca, short posicao, bool matriz[21][11], const bool PECAS[7][4][4][4]);
void imprimePeca(short xPeca, short yPeca, short peca, short posicao, const bool matriz[7][4][4][4]);
void apagaRastroPecaMatrizPrincipal(short xPeca, short yPeca, short peca, short posicao, bool matriz[21][11], const bool PECAS[7][4][4][4]);
void apagaRastroPecaTela(short xPeca, short yPeca, short peca, short posicao, const bool matriz[7][4][4][4]);
void moveLados(short& xPeca, short yPeca, short peca, short posicao, bool matriz[21][11],const bool PECAS[7][4][4][4], char lado);
inline void mudaPosicao(short& xPeca, short yPeca, short peca, short& posicao, bool matriz[21][11], const bool PECAS[7][4][4][4], char lado);
void desceTudo(short& xPeca, short& yPeca, short& peca, short& posicao, bool matriz[21][11], const bool PECAS[7][4][4][4], bool& nova);
bool linhaPreenchida(bool matriz[21][11],short i);
void desceLinha(bool matriz[21][11],int& pontos,short i);
void imprimeMatriz(bool matriz[21][11]);
void criaLayout();
void imprimeProximaPeca(short proximaPeca);
void perdeuJogo(bool matriz[21][11]);

const bool PECAS[7][4][4][4] =//matriz que armazena as peças
{
    //peça 1
    {
        {
            //posição vertical
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0},
        },

        {
            //posição horizontal
            {0,0,0,0},
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0}
        }
    },

    //peça 2
    {
        {
            //posição '4'
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },

        {
            //posição 's'
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        }
    },

    //peça 3
    {
        {
            //posição quadrado
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        }
    },

    //peça 4
    {
        {
            //posição "dedo médio"
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },

        {
            //posição '3'
            {0,1,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },

        {
            //posição 'T'
            {0,0,0,0},
            {1,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },

        {
            //posição 'E'
            {0,1,0,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },

    //peça 5
    {
        {
            //posição "'4' invertido"
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },

        {
            //posição 'z'
            {0,1,1,0},
            {0,0,1,1},
            {0,0,0,0},
            {0,0,0,0}
        }
    },

    //peça 6
    {
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,1,0}
        },

        {
            {0,0,0,0},
            {0,0,0,1},
            {0,1,1,1},
            {0,0,0,0}
        },

        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },

        {
            {0,0,0,0},
            {0,1,1,1},
            {0,1,0,0},
            {0,0,0,0}
        }
    }
};


int main()
{
    int jogoNovo;

    do
    {
        criaLayout();

        ///declara matriz principal (para verificar o jogo)
        bool matrizPrincipal[21][11];

        ///preenche a matriz da tela com '0'
        for(int i = 0; i < 21; ++i)
        {
            for(int j = 0; j < 11; ++j)
            {
                matrizPrincipal[i][j] = 0;
            }
        }

        clock_t contagem;

        int pontuacao = 0;

        bool perdeu = 0;

        ///para auxiliar na contagem dos pontos
        short linhasApagadas = 0;

        short totalLinhasApagadas = 0;

        ///para sortear a peça
        short peca;
        short proximaPeca = randomico(0,5);

        ///para controlar a velocidade do jogo
        short nivel = 1;

        ///velocidade de caída da peça
        short tempo;

        ///início do jogo
        while(true)
        {
            imprimeMatriz(matrizPrincipal);

            ///escolhe aleatoriamente uma peça
            peca = proximaPeca;
            proximaPeca = randomico(0,5);

            imprimeProximaPeca(proximaPeca);

            ///posiçoes de impressão da peça
            short xPeca = 5, yPeca = 2;

            ///posição da peça
            short posicao = 0;

            ///inicia cada peça
            while(true)
            {
                bool nova = 0;//para saber quando chamar uma nova peça

                ///inicia a contagem do tempo
                contagem = tempoInicio();

                ///tempo entre o movimento de cada peça, de acordo com o nível
                if(nivel == 1) tempo = 20;
                if(nivel == 2) tempo = 15;
                if(nivel == 3) tempo = 10;
                if(nivel == 4) tempo = 5;
                if(nivel == 5) tempo = 2;

                ///faz o movimento da peça atual
                while(true)
                {
                    ///movimentação para os lados, mudança de posição da peça ou velocidade da peça
                    if(kbhit())//se algo for pressionado
                    {
                        char tecla = getch();//pega a tecla pressionada

                        ///mudança de posição da peça
                        switch(tecla)
                        {
                        case K_UP:
                            mudaPosicao(xPeca,yPeca,peca,posicao,matrizPrincipal,PECAS,tecla);
                            break;
                        case K_DOWN:
                            tempo = 0.05;
                            break;
                        case '\n':
                            desceTudo(xPeca,yPeca,peca,posicao,matrizPrincipal,PECAS,nova);
                            break;
                        default:
                            moveLados(xPeca,yPeca,peca,posicao,matrizPrincipal,PECAS,tecla);
                            break;
                        }
                    }

                    ///impressão da peça
                    imprimePeca(xPeca,yPeca,peca,posicao,PECAS);

                    ///coloca a peça na matriz da tela
                    imprimePecaMatriz(xPeca,yPeca,peca,posicao,matrizPrincipal,PECAS);

                    ///move a peça para baixo
                    if(tempoPassado(contagem) > tempo)
                    {
                        ///apaga a peça da matriz da tela
                        apagaRastroPecaMatrizPrincipal(xPeca,yPeca,peca,posicao,matrizPrincipal,PECAS);

                        ///apaga a peça da tela
                        apagaRastroPecaTela(xPeca,yPeca,peca,posicao,PECAS);

                        ++yPeca;//aumenta 1 linha
                        break;
                    }
                    if(peca == 0 && (posicao == 0 && (matrizPrincipal[yPeca+2][xPeca-2] || yPeca == 18) ||
                                     posicao == 1 && (matrizPrincipal[yPeca+1][xPeca-1] ||
                                                      matrizPrincipal[yPeca+1][xPeca] ||
                                                      matrizPrincipal[yPeca+1][xPeca+1] || yPeca == 19)) ||

                            peca == 1 && (posicao == 0 && (matrizPrincipal[yPeca+1][xPeca] ||///pronto
                                                           matrizPrincipal[yPeca][xPeca-1] || yPeca == 19) ||
                                          posicao == 1 && (matrizPrincipal[yPeca-1][xPeca] ||
                                                           matrizPrincipal[yPeca][xPeca-1] ||
                                                           matrizPrincipal[yPeca][xPeca-2] || yPeca == 20)) ||
                            peca == 2 && (posicao == 0 && (matrizPrincipal[yPeca+1][xPeca] ||///pronto
                                                           matrizPrincipal[yPeca+1][xPeca-1] || yPeca == 19)) ||
                            peca == 3 && (posicao == 0 && (matrizPrincipal[yPeca][xPeca-2] ||///pronto
                                                           matrizPrincipal[yPeca][xPeca-1] ||
                                                           matrizPrincipal[yPeca][xPeca]) || yPeca == 20 ||
                                          posicao == 1 && (matrizPrincipal[yPeca][xPeca-2] ||
                                                           matrizPrincipal[yPeca+1][xPeca-1] || yPeca == 19) ||
                                          posicao == 2 && (matrizPrincipal[yPeca][xPeca-2] ||
                                                           matrizPrincipal[yPeca+1][xPeca-1] ||
                                                           matrizPrincipal[yPeca][xPeca] || yPeca == 19) ||
                                          posicao == 3 && (matrizPrincipal[yPeca+1][xPeca-1] ||
                                                           matrizPrincipal[yPeca][xPeca] || yPeca == 19)) ||
                            peca == 4 && (posicao == 0 && (matrizPrincipal[yPeca+1][xPeca-1] ||///pronto
                                                           matrizPrincipal[yPeca][xPeca] || yPeca == 19) ||
                                          posicao == 1 && (matrizPrincipal[yPeca-1][xPeca-1] ||
                                                           matrizPrincipal[yPeca][xPeca+1] ||
                                                           matrizPrincipal[yPeca][xPeca] || yPeca == 20)) ||
                            peca == 5 && (posicao == 0 && (matrizPrincipal[yPeca][xPeca-1] ||///pronto
                                                           matrizPrincipal[yPeca+2][xPeca] || yPeca == 18) ||
                                          posicao == 1 && (matrizPrincipal[yPeca+1][xPeca-1] ||
                                                           matrizPrincipal[yPeca+1][xPeca] ||
                                                           matrizPrincipal[yPeca+1][xPeca+1] || yPeca == 19) ||
                                          posicao == 2 && (matrizPrincipal[yPeca+1][xPeca-1] ||
                                                           matrizPrincipal[yPeca+1][xPeca] || yPeca == 19) ||
                                          posicao == 3 && (matrizPrincipal[yPeca+1][xPeca-1] ||
                                                           matrizPrincipal[yPeca][xPeca] ||
                                                           matrizPrincipal[yPeca][xPeca+1] || yPeca == 19)))
                    {
                        nova = 1;
                        if(yPeca == 2) perdeu = 1;
                        break;
                    }

                }

                for(int p = 19; p >=0; --p)
                {
                    if(linhaPreenchida(matrizPrincipal,p))
                    {
                        desceLinha(matrizPrincipal,pontuacao,p);
                        ++linhasApagadas;
                    }
                }
                pontuacao += 1000 * linhasApagadas;
                gotoXY(13,12);
                cout << pontuacao;
                totalLinhasApagadas += linhasApagadas;
                linhasApagadas = 0;
                gotoXY(13,14);
                cout << nivel;
                gotoXY(13,16);
                cout << totalLinhasApagadas;

                if(totalLinhasApagadas >= 45) nivel = 5;
                else if(totalLinhasApagadas >= 30) nivel = 4;
                else if(totalLinhasApagadas >= 15) nivel = 3;
                else if(totalLinhasApagadas >= 5) nivel = 2;

                ///acaba o loop da peça atual para começar uma nova
                if(nova) break;
            }
            if(perdeu) break;
        }

        if(perdeu) perdeuJogo(matrizPrincipal);

        string menuNovoJogo[] = {"Sim","Não"};
        limpaArea(13,18,27,20);
        gotoXY(14,18);
        cout << "Jogar de novo?";
        jogoNovo = mostraMenuV(15,20,menuNovoJogo,2);
        if(jogoNovo == 2) break;
        limpaArea(13,18,27,21);
    }
    while(true);

    return 0;
}

void imprimePecaMatriz(short xPeca, short yPeca, short peca, short posicao, bool matriz[21][11], const bool PECAS[7][4][4][4])
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            if(PECAS[peca][posicao][i][j])
            {
                matriz[yPeca+i-2][xPeca+j-2] = PECAS[peca][posicao][i][j];
            }
        }
    }

    return;
}

void imprimePeca(short xPeca, short yPeca, short peca, short posicao, const bool matriz[7][4][4][4])
{
    ///muda cor da peça
    if(peca == 1) mudaCor(BLUE,BLUE);
    if(peca == 2) mudaCor(GREEN,GREEN);
    if(peca == 3) mudaCor(RED,RED);
    if(peca == 4) mudaCor(PURPLE,PURPLE);
    if(peca == 5) mudaCor(YELLOW,YELLOW);
    if(peca == 0) mudaCor(CYAN,CYAN);

    ///impressão da peça
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            if(PECAS[peca][posicao][i][j])
            {
                gotoXY(xPeca+j,yPeca+i);
                cout << " ";
            }
        }
    }
    limpaEfeito();

    return;
}

void apagaRastroPecaMatrizPrincipal(short xPeca, short yPeca, short peca, short posicao, bool matriz[21][11], const bool PECAS[7][4][4][4])
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            if(PECAS[peca][posicao][i][j])
            {
                matriz[yPeca+i-2][xPeca+j-2] = 0;
            }
        }
    }

    return;
}

void apagaRastroPecaTela(short xPeca, short yPeca, short peca, short posicao, const bool matriz[7][4][4][4])
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            if(PECAS[peca][posicao][i][j])
            {
                gotoXY(xPeca+j,yPeca+i);
                cout << " ";
            }
        }
    }

    return;
}

void moveLados(short& xPeca, short yPeca, short peca, short posicao, bool matrizPrincipal[21][11], const bool PECAS[7][4][4][4], char lado)
{
    ///não deixa a peça atravessar as paredes
    if(!(peca == 0 && ((posicao == 0 && (xPeca == 2 && lado == K_LEFT || xPeca == 11 && lado == K_RIGHT)) ||
                       (posicao == 1 && (xPeca == 2 && lado == K_LEFT || xPeca == 8 && lado == K_RIGHT)))) &&
            !(peca == 1 && ((posicao == 0 && (xPeca == 1 && lado == K_LEFT || xPeca == 9 && lado == K_RIGHT)) ||
                            (posicao == 1 && (xPeca == 2 && lado == K_LEFT || xPeca == 9 && lado == K_RIGHT)))) &&
            !(peca == 2 && (xPeca == 1 && lado == K_LEFT || xPeca == 9 && lado == K_RIGHT)) &&
            !(peca == 3 && (((posicao == 0 || posicao == 2) && (xPeca == 2 && lado == K_LEFT || xPeca == 9 && lado == K_RIGHT)) ||
                            (posicao == 1 && (xPeca == 2 && lado == K_LEFT || xPeca == 10 && lado == K_RIGHT)) ||
                            (posicao == 3 && (xPeca == 1 && lado == K_LEFT || xPeca == 9 && lado == K_RIGHT)))) &&
            !(peca == 4 && ((posicao == 0 && (xPeca == 1 && lado == K_LEFT || xPeca == 9 && lado == K_RIGHT)) ||
                            (posicao == 1 && (xPeca == 1 && lado == K_LEFT || xPeca == 8 && lado == K_RIGHT)))) &&
            !(peca == 5 && (((posicao == 0 || posicao == 2) && (xPeca == 1 && lado == K_LEFT || xPeca == 9 && lado == K_RIGHT)) ||
                            ((posicao == 1 || posicao == 3) && (xPeca == 1 && lado == K_LEFT || xPeca == 8 && lado == K_RIGHT))))
      )
    {
        ///apaga a peça da matriz da tela
        apagaRastroPecaMatrizPrincipal(xPeca,yPeca,peca,posicao,matrizPrincipal,PECAS);
        apagaRastroPecaTela(xPeca,yPeca,peca,posicao,PECAS);
        if(lado == K_LEFT) --xPeca;
        else if(lado == K_RIGHT) ++xPeca;
    }

    return;
}

inline void mudaPosicao(short& xPeca, short yPeca, short peca, short& posicao, bool matriz[21][11], const bool PECAS[7][4][4][4], char lado)
{
    if(!(peca == 0 && posicao == 0 && (xPeca >= 9 && xPeca <= 11)) &&
            !(peca == 1 && posicao == 0 && xPeca == 1) &&
            !(peca == 3 && (posicao == 1 && xPeca == 10 ||
                            posicao == 3 && xPeca == 1)) &&
            !(peca == 4 && posicao == 0 && xPeca == 9) &&
            !(peca == 5 && (posicao == 0 && (xPeca == 1 || xPeca == 9) ||
                            posicao == 2 && xPeca == 9)))
    {
        apagaRastroPecaMatrizPrincipal(xPeca,yPeca,peca,posicao,matriz,PECAS);
        apagaRastroPecaTela(xPeca,yPeca,peca,posicao,PECAS);

        if(((peca == 3 || peca == 5 ) && posicao == 3) ||
                ((peca == 0 || peca == 1 || peca == 4) && posicao == 1)) posicao = 0;
        else if(peca == 2);//não faz nada, porque é o quadrado
        else ++posicao;
    }

    return;
}

void desceTudo(short& xPeca, short& yPeca, short& peca, short& posicao, bool matrizPrincipal[21][11], const bool PECAS[7][4][4][4], bool& nova)
{
    while(true)
    {
        ///impressão da peça
        imprimePeca(xPeca,yPeca,peca,posicao,PECAS);

        ///coloca a peça na matriz da tela
        imprimePecaMatriz(xPeca,yPeca,peca,posicao,matrizPrincipal,PECAS);

        ///apaga a peça da matriz da tela
        apagaRastroPecaMatrizPrincipal(xPeca,yPeca,peca,posicao,matrizPrincipal,PECAS);

        ///apaga a peça da tela
        apagaRastroPecaTela(xPeca,yPeca,peca,posicao,PECAS);

        ++yPeca;//aumenta 1 linha

        if(peca == 0 && (posicao == 0 && (matrizPrincipal[yPeca+2][xPeca-2] || yPeca == 18) ||
                         posicao == 1 && (matrizPrincipal[yPeca+1][xPeca-1] ||
                                          matrizPrincipal[yPeca+1][xPeca] ||
                                          matrizPrincipal[yPeca+1][xPeca+1] || yPeca == 19)) ||

                peca == 1 && (posicao == 0 && (matrizPrincipal[yPeca+1][xPeca] ||///pronto
                                               matrizPrincipal[yPeca][xPeca-1] || yPeca == 19) ||
                              posicao == 1 && (matrizPrincipal[yPeca-1][xPeca] ||
                                               matrizPrincipal[yPeca][xPeca-1] ||
                                               matrizPrincipal[yPeca][xPeca-2] || yPeca == 20)) ||
                peca == 2 && (posicao == 0 && (matrizPrincipal[yPeca+1][xPeca] ||///pronto
                                               matrizPrincipal[yPeca+1][xPeca-1] || yPeca == 19)) ||
                peca == 3 && (posicao == 0 && (matrizPrincipal[yPeca][xPeca-2] ||///pronto
                                               matrizPrincipal[yPeca][xPeca-1] ||
                                               matrizPrincipal[yPeca][xPeca]) || yPeca == 20 ||
                              posicao == 1 && (matrizPrincipal[yPeca][xPeca-2] ||
                                               matrizPrincipal[yPeca+1][xPeca-1] || yPeca == 19) ||
                              posicao == 2 && (matrizPrincipal[yPeca][xPeca-2] ||
                                               matrizPrincipal[yPeca+1][xPeca-1] ||
                                               matrizPrincipal[yPeca][xPeca] || yPeca == 19) ||
                              posicao == 3 && (matrizPrincipal[yPeca+1][xPeca-1] ||
                                               matrizPrincipal[yPeca][xPeca] || yPeca == 19)) ||
                peca == 4 && (posicao == 0 && (matrizPrincipal[yPeca+1][xPeca-1] ||///pronto
                                               matrizPrincipal[yPeca][xPeca] || yPeca == 19) ||
                              posicao == 1 && (matrizPrincipal[yPeca-1][xPeca-1] ||
                                               matrizPrincipal[yPeca][xPeca+1] ||
                                               matrizPrincipal[yPeca][xPeca] || yPeca == 20)) ||
                peca == 5 && (posicao == 0 && (matrizPrincipal[yPeca][xPeca-1] ||///pronto
                                               matrizPrincipal[yPeca+2][xPeca] || yPeca == 18) ||
                              posicao == 1 && (matrizPrincipal[yPeca+1][xPeca-1] ||
                                               matrizPrincipal[yPeca+1][xPeca] ||
                                               matrizPrincipal[yPeca+1][xPeca+1] || yPeca == 19) ||
                              posicao == 2 && (matrizPrincipal[yPeca+1][xPeca-1] ||
                                               matrizPrincipal[yPeca+1][xPeca] || yPeca == 19) ||
                              posicao == 3 && (matrizPrincipal[yPeca+1][xPeca-1] ||
                                               matrizPrincipal[yPeca][xPeca] ||
                                               matrizPrincipal[yPeca][xPeca+1] || yPeca == 19)))
        {
            nova = 1;
            break;
        }
    }

    return;
}

bool linhaPreenchida(bool matriz[21][11], short i)
{
    for(short j = 0; j < 10; ++j)
    {
        if(!matriz[i][j]) return false;
    }

    return true;
}

void desceLinha(bool matriz[21][11], int& pontos, short j)
{
    while(j > 0)
    {
        for(short i = 0; i <= 9; ++i)
        {
            matriz[j][i] = matriz[j-1][i];
        }
        --j;
    }

    imprimeMatriz(matriz);

    return;
}

void imprimeMatriz(bool matriz[21][11])
{
    for(int i = 0; i < 20; ++ i)
    {
        for(int j = 0; j < 10; ++j)
        {
            gotoXY(j+2,i+2);
            if(matriz[i][j]) mudaCor(WHITE,WHITE);
            cout << " ";
            limpaEfeito();
        }
    }

    return;
}

void criaLayout()
{
    desligaCursor(true);
    noecho(true);
    mudaTamanhoTerminal(28,22);

    mudaCor(YELLOW,YELLOW);
    box(1,1,12,22,"   ");
    box(12,1,28,10);
    box(12,10,28,17);
    box(12,17,28,22);

    limpaEfeito();
    gotoXY(14,3);
    cout << "Próxima peça: ";

    gotoXY(13,11);
    cout << "Pontuação: ";
    gotoXY(13,13);
    cout << "Nível: ";
    gotoXY(13,15);
    cout << "Linhas: ";

    return;
}

void imprimeProximaPeca(short peca)
{
    limpaArea(18,5,25,8);

    ///muda cor da peça
    if(peca == 1) mudaCor(BLUE,BLUE);
    if(peca == 2) mudaCor(GREEN,GREEN);
    if(peca == 3) mudaCor(RED,RED);
    if(peca == 4) mudaCor(PURPLE,PURPLE);
    if(peca == 5) mudaCor(YELLOW,YELLOW);
    if(peca == 0) mudaCor(CYAN,CYAN);

    ///impressão da peça
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            if(PECAS[peca][0][i][j])
            {
                gotoXY(18+j,5+i);
                cout << " ";
            }
        }
    }
    limpaEfeito();

    return;
}

void perdeuJogo(bool matriz[21][11])
{
    imprimeMatriz(matriz);
    short cor = 0;

    gotoXY(14,20);
    cout << "Pressione algo";

    while(true)
    {
        mudaCor((COR)cor);

        gotoXY(15,19);
        cout << "Você Perdeu";

        if(kbhit())
        {
            limpaEfeito();
            return;
        }

        ++cor;
        if(cor == QTY_COR) cor = 0;
    }
}
