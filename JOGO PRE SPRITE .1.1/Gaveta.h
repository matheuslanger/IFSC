#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"

#define WIDTH 1300
#define HEIGHT 750
#define ground 60

//Object IDS
enum IDS{FIRST_PLAYER, SECOND_PLAYER};
enum KEYS{LEFT, RIGHT, UP, DOWN, PUNCH, BLOCK, SPUNCH};
//Our Player
struct Personagem
{
	int ID;
	//centro
	int x;
	int y;
    //orientação
	int side;
	//tamanho imagem
	int spritew;
	int spriteh;
    //damegeable area
    int boundw;
	int boundh;
	//hit box
	int punchw;
	int punchh;
    //atributos
	float speed;
	int damage;
	//barra
	float live;
	int time_damage;
	int special;
	//timers
	int time_jump;
	int time_attack;
	int time_defence;
	//botões
	bool keys[5];
	bool hit;
	bool walking;

};

//prototypes
void InitPlayer(Personagem prof[]);
void DrawPlayer(Personagem prof[]);
void JUMP(Personagem prof[], int num);
void DownCase(Personagem &prof);
void LeftCase(Personagem prof[], int num);
void RightCase(Personagem prof[], int num);
void Colision(Personagem prof[], int num);
void Punch(Personagem prof[], int num);
void DrawLifeBar(Personagem prof[], ALLEGRO_BITMAP *image);
void Damage(Personagem prof[], int num);
void Menu(ALLEGRO_FONT *font_t, ALLEGRO_FONT *font_op, int largura, int altura, int id);
void Opcoes(ALLEGRO_FONT *font_op, int largura, int altura, int id);
