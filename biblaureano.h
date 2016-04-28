/**
    \section LICENÇA
    Copyright (C) 2011-2013 Marcos Laureano, Gabriel Candido e Thiago Romano

    Este arquivo é parte do programa Biblaureano.

    Biblaureano é um software livre; você pode redistribui-lo e/ou
    modifica-lo dentro dos termos da Licença Pública Geral GNU como
    publicada pela Fundação do Software Livre (FSF); na versão 2 da
    Licença, ou (na sua opnião) qualquer versão.

    Este programa é distribuido na esperança que possa ser  util,
    mas SEM NENHUMA GARANTIA; sem uma garantia implicita de ADEQUAÇÂO a qualquer
    MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a
    Licença Pública Geral GNU para maiores detalhes.

    Você deve ter recebido uma cópia da Licença Pública Geral GNU
    junto com este programa, se não, escreva para a Fundação do Software
    Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/**
* @file biblaureano.h
* @author Marcos Laureano <marcos.laureano@ifpr.edu.br>
* @author Gabriel Candido <gabiru.vinicius@gmail.com>
* @author Thiago Romano
* \brief Protótipos da Biblaureano.
*/

#include <string>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>

using namespace std;

/** \enum COR
* \brief Enumerador com as possíveis cores para alterar o texto e seu fundo.
* @remarks Varia de acordo com o SO.
* @remarks QTY_COR é a quantidade de cores possíveis. Usado para randomização de cores.
* @see mudaCor()
*/
enum COR {
#if defined(_WIN32)
BLACK = 0, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW, WHITE, QTY_COR
#elif defined (unix)
BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE, QTY_COR
#endif
};

#if defined (_WIN32)
#define K_UP    72 /**<Valor ASCII referente a seta para cima do teclado */
#define K_DOWN  80 /**<Valor ASCII referente a seta para baixo do teclado */
#define K_LEFT  75 /**<Valor ASCII referente a seta para a esquerda do teclado */
#define K_RIGHT 77 /**<Valor ASCII referente a seta para a direita do teclado */
#elif defined (unix)
#define K_UP    65 /**<Valor ASCII referente a seta para cima do teclado */
#define K_DOWN  66 /**<Valor ASCII referente a seta para baixo do teclado */
#define K_LEFT  68 /**<Valor ASCII referente a seta para a esquerda do teclado */
#define K_RIGHT 67 /**<Valor ASCII referente a seta para a direita do teclado */
#endif
#define END_FILE_CHARACTER 0x04 /**<Valor hexadecimal referente ao caractere de fim de arquivo */
#define TEMPO clock_t /**<Definição para uso do termo TEMPO no lugar de clock_t, para melhor entendimento do código */

/** \brief Classe para manipulação de pontos na tela.
* Contém métodos básicos para manipulação de caracteres como pontos na tela.
* @see Imagem
*/
class Ponto
{
   private:
      int x, y;
      string caractere;
      COR corFrente, corFundo;
   public:
      Ponto(int _x, int _y, string _caracter);
      Ponto(int _x, int _y, string _caracter, COR _corFrente);
      Ponto(int _x, int _y, string _caracter, COR _corFrente, COR _corFundo);
      int getX();
      int getY();
      COR getCor();
      COR getCorFundo();
      void colore();
      string getChar();
      void setCor(COR _corFrente);
      void setCor(COR _corFrente, COR _corFundo);
      void imprime(int _x = 0, int _y = 0);
      void limpa(int _x = 0, int _y = 0);
};

/** \brief Classe para manipulação de imagens em modo texto, como sprites.
* Contém métodos para manipulação de imagens como pontos na tela.
* @see Ponto
*/
class Imagem
{
   private:
      vector<Ponto> pontos;
      int x, y;
      int xMin, yMin, xMax, yMax;
      int altura, largura;
   public:
      Imagem();
      Imagem(string _sprite);
      Imagem(string _sprite, int _x, int _y);
      void imprime(int _x, int _y);
      void imprime();
      void limpa(int _x, int _y);
      void limpa();
      void mudaCor(COR _corFrente);
      void mudaCor(COR _corFrente, COR _corFundo);
      void mudaCor255(int _codigoLetra);
      void mudaCor255(int _codigoLetra, int _codigoFundo);
      bool colisao(Imagem _i);
      bool colisao(Imagem _i, int _x1, int _y1, int _x2, int _y2);
      int getX();
      int getY();
      vector<Ponto> getPontos();
      void setX(int _x);
      void setY(int _y);
      int incrementaX();
      int incrementaY();
      int decrementaX();
      int decrementaY();
      void setPontos(vector<Ponto> _pontos);
      void setLimites(int _xMin, int _yMin, int _xMax, int _yMax);
      int getColisaoX(Imagem _i);
      int getColisaoY(Imagem _i);
      int getAltura();
      int getLargura();
};

void mudaCor(COR _corLetra);
void mudaCor(COR _corLetra, COR _corFundo);
void mudaCor255(int _codigo);
void mudaCor255(int _codigoLetra, int _codigoFundo);
void limpaEfeito();

extern "C"
{
    extern int kbhit();
    extern int getch();
}
int verificaKB(char& _tecla);

void limparTela();
void gotoXY(int _x, int _y);
void desligaCursor(bool _liga);
void desligaBufferTela(bool _liga);
void apagaLinha(int _yInicial, int _yFinal);
void mudaTamanhoTerminal(int _x, int _y);
void noecho(bool _liga);

long randomico(int _inicial = 0, int _final = 0);
time_t tempoDecorrido(time_t _entrada = 0);
void espera(long int _tempo);
clock_t tempoInicio();
int tempoPassado(clock_t _inicio);

int readInt(string _mensagem = "");
float readFloat(string _mensagem = "");
double readDouble(string _mensagem = "");
bool readBool(string _mensagem = "");
string readString(string _mensagem = "");
char readChar(string _mensagem = "");

string numeroToString(int _valor);
string numeroToString(double _valor);
string numeroToString(float _valor);

void box(int _xInicial, int _yInicial, int _xFinal, int _yFinal, string _sequencia = "+-|");
void circulo(int _x, int _y, int _raio);

string retornaConteudoArquivo(string _nomeArquivo);
vector<string> retornaArquivoSprites(string _nomeArquivo, string _separador = "*????????*");
vector<Imagem> retornaImagens(string _nomeArquivo, string _separador = "*????????*");
/*Varias imagens**/
void animaSprites(vector<string> _sprites, int _x, int _y, int _tempo = 100);
/*Uma imagem**/
void imprimeSprite(string _sprite, int _x = 1, int _y = 1);
vector<Imagem> criaImagens(const string _imagens[], int _x = 1, int _y = 1, int _tamanho = 1);
vector<Imagem> criaImagens(const vector<string> _imagens, int _x = 1, int _y = 1);
vector<Imagem> criaImagens(const string _imagem, int _x = 1, int _y = 1);

#if defined (_WIN32)
void limpaArea(int _xInicial = 1, int _yInicial = 1, int _xFinal = 80, int _yFinal = 25);
#elif defined (unix)
void limpaArea(int _xInicial = 0, int _yInicial = 0, int _xFinal = 79, int _yFinal = 24);
#endif

string palavraAleatoria(string _palavras);

int mostraMenuV(int _x, int _y, string _opcoes[], int _qtd, COR _ativo = BLUE, COR _inativo = WHITE);
int mostraMenuH(int _x, int _y, string _opcoes[], int _qtd, COR _ativo = BLUE, COR _inativo = WHITE);

string geraLetraRandomico(int _qtd);
string geraLetraRandomicoMaiscula(int _qtd);
string geraLetraRandomicoMinuscula(int _qtd);

Imagem modificaCorPontos(Imagem _colorir, Imagem _referencia);

//void tocaMusica(char* caminhoMusica);
