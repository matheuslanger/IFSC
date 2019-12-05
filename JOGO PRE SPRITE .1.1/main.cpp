#include <allegro5\allegro.h>
#include <stdio.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <math.h>
#include <windows.h>

#include "Prototipos.h"
#include "Gaveta.h"

//GLOBALS==============================

bool debug = false;
bool done = false;
bool menu = true;
bool opcoes = false;
bool init = false;

int main(void)
{
	//primitive variable
	bool redraw = true;
	const int FPS = 60;
	int escolha = 0;
	int i;

	//object variables
	Personagem prof[2];

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *fonte_titulo = NULL, *fonte_opcoes = NULL;
    ALLEGRO_BITMAP  *image   = NULL;

	//Initialization Functions
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

    fonte_titulo = al_load_font("sft.ttf", 90, 0);
    fonte_opcoes = al_load_font("arial.ttf", 50, 0);

    if (!fonte_titulo || !fonte_opcoes)
    {
        return 2;
    }

    image = al_load_bitmap("image.png");

    if (!image)
    {
        return 3;
    }

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	srand(time(NULL));
	InitPlayer(prof);
	DrawLifeBar(prof, image);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);
	while(!done)
	{
	    ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER){
        while(!init){
		if(menu){
            Menu(fonte_titulo, fonte_opcoes, WIDTH, HEIGHT, escolha);
            for(i = 0; i < 7; i++){
                prof[0].keys[i]= false;
                prof[1].keys[i]= false;
            }
        }


        if(opcoes){
            Opcoes(fonte_opcoes, WIDTH, HEIGHT, escolha);
            for(i = 0; i < 7; i++){
                prof[0].keys[i]= false;
                prof[1].keys[i]= false;
            }
        }
	}
}
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if(prof[FIRST_PLAYER].keys[UP])
				JUMP(prof, FIRST_PLAYER);
			if(prof[FIRST_PLAYER].keys[LEFT])
				LeftCase(prof, FIRST_PLAYER);
			if(prof[FIRST_PLAYER].keys[RIGHT])
				RightCase(prof, FIRST_PLAYER);
            if(prof[FIRST_PLAYER].keys[PUNCH]){
                Punch(prof, FIRST_PLAYER);
            }

            if(prof[SECOND_PLAYER].keys[UP])
				JUMP(prof,SECOND_PLAYER);
			if(prof[SECOND_PLAYER].keys[LEFT])
				LeftCase(prof, SECOND_PLAYER);
			if(prof[SECOND_PLAYER].keys[RIGHT])
				RightCase(prof, SECOND_PLAYER);
            if(prof[SECOND_PLAYER].keys[PUNCH])
                Punch(prof, SECOND_PLAYER);
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				if(opcoes){
                 opcoes = false;
                 menu = true;
				}
				else{
                 done = true;
				}
				break;
			case ALLEGRO_KEY_UP:
				prof[FIRST_PLAYER].keys[UP] = true;
				if(menu){
                    escolha--;
				if(escolha < 0)
                    escolha = 2;
				}
				if(opcoes){
                    escolha--;
                    if(escolha < 0)
                        escolha = 3;
				}
				break;
			case ALLEGRO_KEY_DOWN:
				DownCase(prof[FIRST_PLAYER]);
				if(menu){
                    escolha++;
				if(escolha > 2)
                    escolha = 0;
				}
				if(opcoes){
                    escolha++;
                    if(escolha > 3)
                        escolha = 0;
				}
				break;
			case ALLEGRO_KEY_LEFT:
			    if(!prof[FIRST_PLAYER].keys[DOWN])
					prof[FIRST_PLAYER].keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
			    if(!prof[FIRST_PLAYER].keys[DOWN])
					prof[FIRST_PLAYER].keys[RIGHT] = true;
				break;
            case ALLEGRO_KEY_ENTER:
                    if(menu){
                    switch (escolha){
                    case 0:
                        menu = false;
                        break;
                    case 1:
                        menu = false;
                        opcoes = true;
                        break;
                    case 2:
                        return 5;
                    }
                    }
                    else if(opcoes){
                        switch(escolha){
                        case 0:
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        opcoes = false;
                        menu = true;
                        escolha = 0;
                        break;
                        }
                    }
                break;
            case ALLEGRO_KEY_P:
                prof[FIRST_PLAYER].keys[PUNCH] = true;
                break;

			case ALLEGRO_KEY_W:
				prof[SECOND_PLAYER].keys[UP] = true;
				if(menu){
                    escolha--;
				if(escolha < 0)
                    escolha = 2;
				}
				if(opcoes){
                    escolha--;
                    if(escolha < 0)
                        escolha = 3;
				}
				break;
			case ALLEGRO_KEY_S:
                DownCase(prof[SECOND_PLAYER]);
                if(menu){
                    escolha++;
				if(escolha > 2)
                    escolha = 0;
				}
				if(opcoes){
                    escolha++;
                    if(escolha > 3)
                        escolha = 0;
				}
				break;
			case ALLEGRO_KEY_A:
			    if(!prof[SECOND_PLAYER].keys[DOWN])
					prof[SECOND_PLAYER].keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_D:
			    if(!prof[SECOND_PLAYER].keys[DOWN])
					prof[SECOND_PLAYER].keys[RIGHT] = true;
				break;
            case ALLEGRO_KEY_T:
                prof[SECOND_PLAYER].keys[PUNCH] = true;
                break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;

			case ALLEGRO_KEY_DOWN:
			    if(prof[FIRST_PLAYER].keys[DOWN])
                    DownCase(prof[FIRST_PLAYER]);
				break;
			case ALLEGRO_KEY_LEFT:
				prof[FIRST_PLAYER].keys[LEFT] = false;
				prof[FIRST_PLAYER].walking=false;
				break;
			case ALLEGRO_KEY_RIGHT:
				prof[FIRST_PLAYER].keys[RIGHT] = false;
				prof[FIRST_PLAYER].walking=false;
				break;

            case ALLEGRO_KEY_S:
                if(prof[SECOND_PLAYER].keys[DOWN])
                    DownCase(prof[SECOND_PLAYER]);
				break;
			case ALLEGRO_KEY_A:
				prof[SECOND_PLAYER].keys[LEFT] = false;
				prof[SECOND_PLAYER].walking=false;
				break;
			case ALLEGRO_KEY_D:
				prof[SECOND_PLAYER].keys[RIGHT] = false;
				prof[SECOND_PLAYER].walking=false;
				break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
            DrawPlayer(prof);
			DrawLifeBar(prof, image);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object

	return 0;
}



