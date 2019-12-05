#include "Gaveta.h"
#include <math.h>

void InitPlayer(Personagem prof[])
{
    int i;
    prof[FIRST_PLAYER].side=LEFT;
    prof[SECOND_PLAYER].side=RIGHT;
    for(i=0;i<2;i++){
		//bordas
        prof[i].boundh=50*5;
        prof[i].boundw=26*5;
        if(i==0){
            prof[i].x = (WIDTH*4)/5;
            prof[i].y = HEIGHT-(prof[i].boundh/2)-ground;
            prof[i].ID = FIRST_PLAYER;
        }
        else{
            prof[i].x = WIDTH/5;
            prof[i].y = HEIGHT-(prof[i].boundh/2)-ground;
            prof[i].ID = SECOND_PLAYER;
        }
        prof[i].punchh = 0;
        prof[i].punchw = 0;
		//propriedades
        prof[i].live = 400;
        prof[i].speed = 7;
		//contador
        prof[i].time_jump = 0;
		prof[i].time_attack = 0;
		prof[i].time_defence =0;
		prof[i].time_damage = 0;
		//estados
        prof[i].keys[UP]=false;
        prof[i].keys[DOWN]=false;
        prof[i].keys[LEFT]=false;
        prof[i].keys[RIGHT]=false;
        prof[i].keys[PUNCH]=false;
        prof[i].hit=false;
        prof[i].walking=false;
    }
}
void DrawPlayer(Personagem prof[])
{
    int i;
    al_draw_filled_rectangle(0,0,WIDTH,HEIGHT,al_map_rgb(200,200,255));
    al_draw_filled_rectangle(0, HEIGHT-ground, WIDTH, HEIGHT, al_map_rgb(139, 69, 19));

    for(i=0;i<2;i++){
        if(prof[i].keys[DOWN] && !prof[i].keys[UP])
            al_draw_filled_rectangle(prof[i].x + prof[i].boundw/2,
                                     prof[i].y - prof[i].boundh/2,
                                     prof[i].x - prof[i].boundw/2,
                                     prof[i].y + prof[i].boundh/6,
                                     al_map_rgb(255, 255, 255*i));
        else
            al_draw_filled_rectangle(prof[i].x + prof[i].boundw/2,
                                     prof[i].y - prof[i].boundh/2,
                                     prof[i].x - prof[i].boundw/2,
                                     prof[i].y + prof[i].boundh/2,
                                     al_map_rgb(255, 255, 255*i));
    }

    for(i=0;i<2;i++){
        if(prof[i].keys[PUNCH]){
            if(!prof[i].side){
                al_draw_filled_rectangle(prof[i].x - prof[i].boundw/2 - prof[i].punchw,
                                         prof[i].y - prof[i].boundh/10- prof[i].punchh,
                                         prof[i].x - prof[i].boundw/2,
                                         prof[i].y - prof[i].boundh/10,
                                         al_map_rgb(255, 255, 255*i));
            }
            else{
                al_draw_filled_rectangle(prof[i].x + prof[i].boundw/2 + prof[i].punchw,
                                         prof[i].y - prof[i].boundh/10- prof[i].punchh,
                                         prof[i].x + prof[i].boundw/2,
                                         prof[i].y - prof[i].boundh/10,
                                         al_map_rgb(255, 255, 255*i));
            }
        }
    }
}

void Colision(Personagem prof[], int num)
{
    int i;

    if(prof[num].y+prof[num].boundh/2 > prof[!num].y - prof[num].boundh/2 &&
        prof[num].y-prof[num].boundh/2<prof[!num].y + prof[num].boundh/2){

        if (prof[num].x+prof[num].boundw/2>prof[!num].x-prof[!num].boundw/2 &&
            prof[num].x<prof[!num].x)
            prof[num].x = prof[!num].x-prof[!num].boundw;

        if(prof[num].x-prof[num].boundw/2<prof[!num].x+prof[!num].boundw/2 &&
           prof[num].x>prof[!num].x)
            prof[num].x = prof[!num].x+prof[!num].boundw;

        if(prof[!num].x+prof[!num].boundw >= WIDTH &&
           prof[!num].x==prof[num].x)
            prof[num].x = prof[!num].x-prof[!num].boundw;

        if(prof[!num].x-prof[!num].boundw <= 0 &&
           prof[!num].x==prof[num].x)
            prof[num].x = prof[!num].x+prof[!num].boundw;
    }
    if(prof[num].hit){
        if(prof[num].walking){
                if(prof[num].x>prof[!num].x)
                prof[!num].x-=prof[num].punchw/20;
            else
                prof[!num].x+=prof[num].punchw/20;
        }
        else if(!prof[num].keys[LEFT] && !prof[num].keys[RIGHT]){
            if(prof[num].x>prof[!num].x)
                prof[!num].x-=prof[num].punchw/25;
            else
                prof[!num].x+=prof[num].punchw/25;
        }
    }
    for(i=0;i<2;i++){
        if(prof[i].x < 0)
            prof[i].x = 0;
        else if(prof[i].x >WIDTH)
            prof[i].x = WIDTH;
    }
}

void JUMP(Personagem prof[], int num)
{
    prof[num].time_jump++;
    if(prof[num].time_jump<30){
		prof[num].y-=25-(1.75*prof[num].time_jump)/2;
    }
    else if(prof[num].time_jump<48){
        prof[num].y+=(1.06*prof[num].time_jump)/2;

        if(prof[num].y+prof[num].boundh/2>HEIGHT-ground && !prof[num].keys[DOWN])
            prof[num].y=HEIGHT-(prof[num].boundh/2)-ground;
    }
    else{
        prof[num].time_jump=0;
        prof[num].keys[UP]=false;
    }

    if(prof[num].keys[UP] && prof[num].keys[DOWN]){
        prof[num].y-=(prof[num].boundh/3);
        prof[num].keys[DOWN]=false;
    }

    Colision(prof, num);
}
void DownCase(Personagem &prof)
{
    if(!prof.keys[UP]){
        if(prof.keys[DOWN])
            prof.keys[DOWN]=false;
        else
            prof.keys[DOWN]=true;

        if(prof.keys[DOWN]){
            prof.y+=(prof.boundh/3);
        }
        else{
            prof.y-=(prof.boundh/3);
        }
    }
}
void LeftCase(Personagem prof[], int num)
{

    if(!prof[num].keys[PUNCH] &&
       !prof[num].keys[DOWN]){
        prof[num].side=LEFT;
        prof[num].x -= prof[num].speed;
        prof[num].walking=true;
    }
    else if(prof[num].walking && !prof[num].keys[DOWN])
        prof[num].x -= prof[num].speed;

    Colision(prof, num);
}

void RightCase(Personagem prof[], int num)
{
    if(!prof[num].keys[PUNCH] &&
       !prof[num].keys[DOWN]){
        prof[num].side=RIGHT;
        prof[num].x += prof[num].speed;
        prof[num].walking=true;
    }
    else if(prof[num].walking && !prof[num].keys[DOWN])
        prof[num].x += prof[num].speed;

    Colision(prof, num);

}

void Damage(Personagem prof[], int num){
    if(prof[num].y - prof[num].boundh/3 > prof[!num].y-prof[!num].boundh/2 &&
       prof[num].y - prof[num].boundh/3 < prof[!num].y+prof[!num].boundh/2 &&
	   prof[num].time_attack>=12 && prof[num].time_attack<=18 && !prof[num].hit){

        if(prof[num].x>prof[!num].x && !prof[num].side){
            if(prof[num].x-prof[num].boundw/2-prof[num].punchw<=prof[!num].x+prof[!num].boundw/2)
                prof[num].hit=true;
        }
        else if(prof[num].x<prof[!num].x && prof[num].side){
            if(prof[num].x+prof[num].boundw/2+prof[num].punchw>=prof[!num].x-prof[!num].boundw/2)
                prof[num].hit=true;
        }
    }
	if(prof[num].time_damage<=10 && prof[num].hit){
        prof[num].time_damage++;
        prof[!num].live -= prof[num].damage;
		Colision(prof, num);
    }
    if(prof[!num].live <= 0)
        prof[!num].live = 0;
}

void Punch(Personagem prof[], int num){
    prof[num].time_attack++;
	prof[num].damage = 2;
    if(prof[num].time_attack<=36 && prof[num].time_attack>0 && !prof[!num].hit){
        if(prof[num].time_attack>2){
            if(prof[num].time_attack<7){
                prof[num].punchw=2*5;
                prof[num].punchh=9*5;
            }
            else if(prof[num].time_attack<11){
                prof[num].punchw=17*5;
                prof[num].punchh=9*5;
            }
            else if(prof[num].time_attack<15){
                prof[num].punchw=15*5;
                prof[num].punchh=9*5;
            }
        }
    }
    else if(prof[num].time_attack>15 || prof[!num].hit){
        prof[num].time_attack=0;
        if(prof[num].hit)
            prof[num].time_attack=-4;

        prof[num].punchw=0;
        prof[num].punchh=0;

        prof[num].time_damage=0;
		prof[num].hit=false;
		prof[num].damage = 0;

        prof[num].keys[PUNCH]=false;
        prof[num].speed*=3;
    }
    if(prof[num].keys[PUNCH] && prof[num].time_attack==1)
        prof[num].speed/=3;
    Damage(prof, num);
}

void DrawLifeBar(Personagem prof[], ALLEGRO_BITMAP *image){
    int k, i;
    for(i = 0; i < 2 ; i++){
        k = pow((-1*!i),(!i));
        al_draw_filled_rectangle(!i*WIDTH + k*70,24, !i*WIDTH + k*prof[i].live + k*70, 45, al_map_rgb(255-(prof[i].live+110)/2, ((prof[i].live+110)/2)-50, 0));
            al_draw_bitmap(image, !i*WIDTH-!i*426 +k*67,20,ALLEGRO_FLIP_HORIZONTAL*!i);

    }
    al_convert_mask_to_alpha(image, al_map_rgb(55, 234, 0));
}

void Menu(ALLEGRO_FONT *font_t, ALLEGRO_FONT *font_op, int largura, int altura, int id){

    al_draw_text(font_t, al_map_rgb(255, 51, 51), largura / 2, 30, ALLEGRO_ALIGN_CENTRE, "Teacher");
    al_draw_text(font_t, al_map_rgb(255, 51, 51), largura / 2, 120, ALLEGRO_ALIGN_CENTRE, "Smackdown");
    al_draw_text(font_op, al_map_rgb(200, 200, 200), largura / 2, 400, ALLEGRO_ALIGN_CENTRE, "Start");
    al_draw_text(font_op, al_map_rgb(200, 200, 200), largura / 2, 500, ALLEGRO_ALIGN_CENTRE, "Options");
    al_draw_text(font_op, al_map_rgb(200, 200, 200), largura / 2, 600, ALLEGRO_ALIGN_CENTRE, "Quit");

    while(!al_is_event_queue_empty(event_queue)){
            ALLEGRO_EVENT evento;
            //espera ate que algum evento esteja na fila
            al_wait_for_event(event_queue, &evento);

            //se o evento for pressionar uma tecla
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
                //verifica qual tecla foi pressionada
                switch(evento.keyboard.keycode){
                //seta para cima
                case ALLEGRO_KEY_UP:
                    tecla = 1;
                    break;
                //seta para baixo
                case ALLEGRO_KEY_DOWN:
                    tecla = 2;
                    break;
                //seta para esquerda
                case ALLEGRO_KEY_LEFT:
                    tecla = 3;
                    break;
                //seta para direita.
                case ALLEGRO_KEY_RIGHT:
                    tecla = 4;
                    break;
                //esc. sair=1 faz com que o programa saia do loop principal
                case ALLEGRO_KEY_ESCAPE:
                    sair = 1;
                }
            }


    switch(id){
    case 0:
        al_draw_text(font_op, al_map_rgb(255, 51, 51), largura / 2, 400, ALLEGRO_ALIGN_CENTRE, "Start");
        break;
    case 1:
        al_draw_text(font_op, al_map_rgb(255, 51, 51), largura / 2, 500, ALLEGRO_ALIGN_CENTRE, "Options");
        break;
    case 2:
        al_draw_text(font_op, al_map_rgb(255, 51, 51), largura / 2, 600, ALLEGRO_ALIGN_CENTRE, "Quit");
        break;
    }
    al_flip_display();
    al_clear_to_color(al_map_rgb(0,0,0));
}

void Opcoes(ALLEGRO_FONT *font_op, int largura, int altura, int id){

    al_draw_text(font_op, al_map_rgb(200, 200, 200), largura / 2, 70, ALLEGRO_ALIGN_CENTRE, "Option 1");
    al_draw_text(font_op, al_map_rgb(200, 200, 200), largura / 2, 220, ALLEGRO_ALIGN_CENTRE, "Option 2");
    al_draw_text(font_op, al_map_rgb(200, 200, 200), largura / 2, 370, ALLEGRO_ALIGN_CENTRE, "Option 3");
    al_draw_text(font_op, al_map_rgb(200, 200, 200), largura / 2, 650, ALLEGRO_ALIGN_CENTRE, "Back");

    switch(id){
    case 0:
        al_draw_text(font_op, al_map_rgb(255, 51, 51), largura / 2, 70, ALLEGRO_ALIGN_CENTRE, "Option 1");
        break;
    case 1:
        al_draw_text(font_op, al_map_rgb(255, 51, 51), largura / 2, 220, ALLEGRO_ALIGN_CENTRE, "Option 2");
        break;
    case 2:
        al_draw_text(font_op, al_map_rgb(255, 51, 51), largura / 2, 370, ALLEGRO_ALIGN_CENTRE, "Option 3");
        break;
    case 3:
        al_draw_text(font_op, al_map_rgb(225, 51, 51), largura / 2, 650, ALLEGRO_ALIGN_CENTRE, "Back");
    }
    al_flip_display();
    al_clear_to_color(al_map_rgb(0,0,0));
}
