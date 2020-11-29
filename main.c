#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define LARGURA_TELA 1200
#define ALTURA_TELA 900
#define FPS 60

ALLEGRO_DISPLAY *display = NULL;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;

ALLEGRO_FONT *fonte = NULL;
ALLEGRO_FONT *fonte_timer = NULL;

ALLEGRO_TIMER *timer = NULL;
ALLEGRO_TIMER *timer_relogio = NULL;

ALLEGRO_BITMAP *personagem[12];
ALLEGRO_BITMAP *forma = NULL;
ALLEGRO_BITMAP *imagem_fundo = NULL;
ALLEGRO_BITMAP *coracao = NULL;
ALLEGRO_BITMAP *virus = NULL;
ALLEGRO_BITMAP *pocao = NULL;
ALLEGRO_BITMAP *coracoes_vida1[5];
ALLEGRO_BITMAP *coracoes_vida2[5];
ALLEGRO_BITMAP *mascara = NULL;
ALLEGRO_BITMAP *botao_play = NULL;
ALLEGRO_BITMAP *botao_reset = NULL;
ALLEGRO_BITMAP *botao_verde = NULL;
ALLEGRO_BITMAP *botao_vermelho = NULL;
ALLEGRO_BITMAP *imagem_fundo2 = NULL;
ALLEGRO_BITMAP *imagem_fundo3 = NULL;
ALLEGRO_BITMAP *imagem_fundo4 = NULL;

ALLEGRO_AUDIO_STREAM *musica_fundo = NULL;

ALLEGRO_KEYBOARD_STATE keyState;

int initAllegro() {
    // Initialize allegro
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize allegro.\n");
        return 1;
    }
    // Create the display
    display = al_create_display(1200, 900);
    if (!display) {
        fprintf(stderr, "Failed to create display.\n");
        return 1;
    }

    al_set_window_title(display, "Taur");

	//Initialize font
	if (!al_init_font_addon()){
		fprintf(stderr,"Failed to initialize font addon.\n");
		return 1;
	}
    if(!al_init_image_addon()){
        fprintf(stderr,"Failed to initialize font addon.\n");
		return 1;
    }
    if(!al_install_audio()){
        fprintf(stderr,"Failed to initialize audio.\n");
		return 1;   
    }
    if(!al_init_acodec_addon()){
        fprintf(stderr,"Failed to initialize acodec.\n");
		return 1;   
    }
    if (!al_reserve_samples(5)){
        fprintf(stderr,"Failed to reserve sample.\n");
		return 1;   
    }
    /*musica_fundo = al_load_audio_stream("audio.ogg",4,1024);
    if(!musica_fundo){
        fprintf(stderr,"Failed to initialzie audio.\n");
		return 1;   
    }
    al_attach_audio_stream_to_mixer(musica_fundo, al_get_default_mixer());
    al_set_audio_stream_playmode(musica_fundo, ALLEGRO_PLAYMODE_LOOP);*/
	//Initialize ttf addon
	if (!al_init_ttf_addon()){
		fprintf(stderr,"Failed to initialize ttf addon.\n");
		return 1;
	}
    virus = al_load_bitmap("assets_personagem/virus.png");
    if(!virus){
		fprintf(stderr,"Failed to initialize ttf addon.\n");
		return 1;
    }
    personagem[0] = al_load_bitmap("assets_personagem/baixo_1.PNG");
    personagem[1] = al_load_bitmap("assets_personagem/baixo_2.PNG");
    personagem[2] = al_load_bitmap("assets_personagem/baixo_3.PNG");
    personagem[3] = al_load_bitmap("assets_personagem/cima_1.PNG");
    personagem[4] = al_load_bitmap("assets_personagem/cima_2.PNG");
    personagem[5] = al_load_bitmap("assets_personagem/cima_3.PNG");
    personagem[6] = al_load_bitmap("assets_personagem/direita_1.PNG");
    personagem[7] = al_load_bitmap("assets_personagem/direita_2.PNG");
    personagem[8] = al_load_bitmap("assets_personagem/direita_3.PNG");
    personagem[9] = al_load_bitmap("assets_personagem/esquerda_1.PNG");
    personagem[10] = al_load_bitmap("assets_personagem/esquerda_2.PNG");
    personagem[11] = al_load_bitmap("assets_personagem/esquerda_3.PNG");

	//Initialize mouse
	if(!al_install_mouse()){
		fprintf(stderr,"Failed to initialize mouse.\n");
		return 1;
    }
    if(!al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
		fprintf(stderr,"Failed to initialize mouse.\n");
        return 1;
    }
    //Initialize font
    fonte_timer = al_load_ttf_font("Electrolize-Regular.ttf",50,0);
    if(!fonte_timer){
		fprintf(stderr,"Failed to initialize font.\n");
        return 1;
    }
    fonte = al_load_ttf_font("Electrolize-Regular.ttf",50,0);
    if(!fonte){
		fprintf(stderr,"Failed to initialize font.\n");
        return 1;
    }
    //Initialize background
    imagem_fundo = al_load_bitmap("assets_personagem/fundo.png");
    if(!imagem_fundo){
		fprintf(stderr,"Failed to initialize background.\n");
        return 1;
    }

    imagem_fundo2 = al_load_bitmap("assets_personagem/fundo_2.png");

    if(!imagem_fundo2){
		fprintf(stderr,"Failed to initialize background.\n");
        return 1;
    }

    imagem_fundo3 = al_load_bitmap("assets_personagem/fundo_3.png");

    if(!imagem_fundo3){
		fprintf(stderr,"Failed to initialize background.\n");
        return 1;
    }

    imagem_fundo4 = al_load_bitmap("assets_personagem/fundo_4.png");

    if(!imagem_fundo4){
		fprintf(stderr,"Failed to initialize background.\n");
        return 1;
    }

    botao_verde = al_load_bitmap("assets_personagem/botao_verde.PNG");
    if(!botao_verde){
		fprintf(stderr,"Failed to initialize botao verde.\n");
        return 1;
    }

    botao_vermelho = al_load_bitmap("assets_personagem/botao_vermelho.PNG");
    if(!botao_vermelho){
		fprintf(stderr,"Failed to initialize botao verde.\n");
        return 1;
    }

    pocao = al_load_bitmap("assets_personagem/pocao.png");
    if(!pocao){
		fprintf(stderr,"Failed to initialize c.\n");
        return 1;
    }

    botao_play = al_load_bitmap("assets_personagem/botao_play.PNG");
    if(!botao_play){
		fprintf(stderr,"Failed to initialize botao play.\n");
        return 1;
    }

    botao_reset = al_load_bitmap("assets_personagem/reset.png");
    if(!botao_reset){
		fprintf(stderr,"Failed to initialize botao reset.\n");
        return 1;
    }

    coracoes_vida1[0] = al_load_bitmap("assets_personagem/0-4.png");
    coracoes_vida1[1] = al_load_bitmap("assets_personagem/1-4.png");
    coracoes_vida1[2] = al_load_bitmap("assets_personagem/2-4.png");
    coracoes_vida1[3] = al_load_bitmap("assets_personagem/3-4.png");
    coracoes_vida1[4] = al_load_bitmap("assets_personagem/4-4.png");

    coracoes_vida2[0] = al_load_bitmap("assets_personagem/0-4.png");
    coracoes_vida2[1] = al_load_bitmap("assets_personagem/1-4.png");
    coracoes_vida2[2] = al_load_bitmap("assets_personagem/2-4.png");
    coracoes_vida2[3] = al_load_bitmap("assets_personagem/3-4.png");
    coracoes_vida2[4] = al_load_bitmap("assets_personagem/4-4.png");

    mascara = al_load_bitmap("assets_personagem/mascara.png");
    if(!mascara){
		fprintf(stderr,"Failed to initialize mascara\n");
		return 1;
    }

	//Initialize keyboard
	if(!al_install_keyboard()){
		fprintf(stderr,"Failed to initialize keyboard.\n");
		return 1;
	}
	al_set_target_bitmap(al_get_backbuffer(display));
    // Initialize the timer
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "Failed to create timer.\n");
        return 1;
    }
    timer_relogio = al_create_timer(0.8);
    if(!timer_relogio){
        fprintf(stderr, "Failed to create timer relogio.\n");
        return 1;
    }
    // Create the event queue
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Failed to create event queue.");
        return 1;
    }
    // Register event sources
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(timer_relogio));
    return 0;
}

int pts = 0,pts1 = 0;

void desenhaMapa(int *coracao1, int *coracao2, int direcao_personagem,int muda_animacao, char pontuacao[],int *posX_virus, int *posY_virus,int *vel_virus
, int posX, int posY, bool *gerar_virus, bool *colidiu_virus, bool *running,int *pontuacao_personagem,int *posX_mascara,int *posY_mascara, bool *gerar_mascara,
bool *colidiu_mascara,int *regiao_atual,int *posX_pocao, int *posY_pocao,int *vel_personagem,bool *gerar_pocao, bool *colidiu_pocao){

    al_draw_bitmap(personagem[direcao_personagem+muda_animacao],posX,posY,0);
    al_draw_bitmap(coracoes_vida1[*coracao1],450,50,0);
    al_draw_bitmap(coracoes_vida2[*coracao2],540,50,0);

    if(*posX_virus < posX-10){
        *posX_virus += *vel_virus;
    }else if(*posX_virus > posX+10){
        *posX_virus -= *vel_virus;
    }
    if(*posY_virus < posY-10){
        *posY_virus += *vel_virus;
    }else if(*posY_virus > posY+10){
        *posY_virus -= *vel_virus;
    }

    if(!(*gerar_virus)){
        *posX_virus = -100 - (rand()%(200))+1;
        *posY_virus = -250 - (rand()%100)+1;
        *gerar_virus = true;
    }
    
    if(posX >= (*posX_virus)-30 && posX <= *posX_virus+90 && posY >= *posY_virus-20 && posY <= (*posY_virus)+40){
        *colidiu_virus = true;
        if(*vel_virus < *vel_personagem-1){
            *vel_virus+=1;
            *vel_personagem-=1;
        }
    }

    if(!(*colidiu_virus)){
        al_draw_bitmap(virus,*posX_virus,*posY_virus,0);
    }else{
        *gerar_virus = false;
        *colidiu_virus = false;
        if((*coracao2) == 0) (*coracao1)--;
        else (*coracao2)--;
        if(*coracao2 == 0 && *coracao1 == 0){
            *regiao_atual = 12;
        }
    }

    if(!*gerar_pocao){
        *posX_pocao = 20+(rand()%(1050))+1;
        *posY_pocao = 20+(rand()%(820))+1;
        *gerar_pocao = true;
    }

    if(posX >= *posX_pocao-40 && posX <= *posX_pocao+15 && posY >= *posY_pocao-60 && posY <= *posY_pocao+30){
        *colidiu_pocao=true;
    }

    if(!*colidiu_pocao){
        al_draw_bitmap(pocao,*posX_pocao,*posY_pocao,0);
    }else if(pts1 == 0){
        *gerar_pocao=false;
        if(*coracao1 < 4) (*coracao1)++;
        else if(*coracao2 < 4) (*coracao2)++;
        pts1 = 1;
    }

    if(posX >= (*posX_mascara)-30 && posX <= *posX_mascara+60 && posY >= *posY_mascara-35 && posY <= *posY_mascara+30){
        sprintf(pontuacao,"%d",*pontuacao_personagem);
        *colidiu_mascara=true;
    }

    if(!*gerar_mascara){
        *posX_mascara = 20+(rand()%(1050))+1;
        *posY_mascara = 20+(rand()%(820))+1;
        *gerar_mascara = true;
    }

    if(!(*colidiu_mascara)){
        al_draw_bitmap(mascara,*posX_mascara,*posY_mascara,0);
    }else if(pts == 0){
        *gerar_mascara=false;
        *pontuacao_personagem+=5;
        pts=1;
    }

    al_draw_text(fonte,al_map_rgb(255,255,255),950,50,0,pontuacao);
}

int main(){
    int err = initAllegro();
    if(err) {
        return err;
    }
	
	bool running = true;
    bool redraw = true;

    // Display a black screen
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
	
    // Start the timers
    al_start_timer(timer);
    al_start_timer(timer_relogio);
	
	//Variables
    int posX = 50, posY = 50;
    int velx = 0, vely = 0;
    enum regioes {REGIAO_1,REGIAO_2,REGIAO_3,REGIAO_4,REGIAO_5,REGIAO_6,REGIAO_7,REGIAO_8,REGIAO_9,REGIAO_10,REGIAO_11,REGIAO_12,FIM_DE_JOGO,MENU};
    int posX_virus = 50,posY_virus = 50;
    int regiao_atual = 13;
    int direcao_personagem = 0;
    int muda_animacao = 0;
    int coracao1 = 4, coracao2 = 4;
    int posX_mascara = 250 ,posY_mascara=250;
    int vel_personagem = 7, vel_virus = 4;
    int posX_pocao = 50,posY_pocao = 50;
    char pontuacao[20]={"0"};
    int pontuacao_personagem = 0;
    bool colidiu_mascara = false;
    bool gerar_mascara = false;
    bool colidiu_virus = false;
    bool gerar_virus = false;
    bool colidiu_pocao = false;
    bool gerar_pocao = false;
    bool inicia_jogo = false;
    bool reinicia_jogo = false;
    int regiao_vermelha = 50, regiao_verde = 20;

    // Game loop
    while (running) {
        ALLEGRO_EVENT event;
        ALLEGRO_TIMEOUT timeout;
        // Initialize timeout
        al_init_timeout(&timeout, 0.06);
        // Fetch the event (if one exists)
        bool get_event = al_wait_for_event_until(event_queue, &event, &timeout);
        al_get_keyboard_state(&keyState);
        // Handle the event
        if (get_event) {
            if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                running = 0;
            }else if(event.type == ALLEGRO_EVENT_TIMER){
                if(event.timer.source == timer){
                    if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT)){
                        direcao_personagem = 6;
                        velx = vel_personagem;
                    }else if(al_key_down(&keyState,ALLEGRO_KEY_LEFT)){
                        direcao_personagem = 9;
                        velx = -vel_personagem;
                    }else{
                        velx = 0;
                    }
                    if(al_key_down(&keyState,ALLEGRO_KEY_UP)){
                        direcao_personagem = 3;
                        vely = -vel_personagem;
                    }else if(al_key_down(&keyState,ALLEGRO_KEY_DOWN)){
                        direcao_personagem = 0;
                        vely = vel_personagem;
                    }else{
                        vely = 0;
                    }
                    if(al_key_down(&keyState,ALLEGRO_KEY_SPACE)){
                    }
                }else if(event.timer.source == timer_relogio){
                    muda_animacao+=1;
                }
            }else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if(regiao_atual == MENU){
                    if(event.mouse.x >= 460 && event.mouse.x <= 660 && event.mouse.y >= 350 && event.mouse.y <= 400) inicia_jogo = true;
                }
                if(regiao_atual == FIM_DE_JOGO){
                    if(event.mouse.x>=550 && event.mouse.x <= 620 && event.mouse.y >= 520 && event.mouse.y <= 590) reinicia_jogo = true;
                }
            }
        }
        posX += velx;
        posY += vely;
        muda_animacao%=3;
        //Baixo
        if(posY > 800){
            bool passou = true;
            if(regiao_atual == 0) regiao_atual = 3; 
            else if(regiao_atual == 1)regiao_atual = 4;
            else if(regiao_atual == 2) regiao_atual = 5;
            else if(regiao_atual == 3) regiao_atual = 6;
            else if(regiao_atual == 4) regiao_atual = 7;
            else if(regiao_atual == 5) regiao_atual = 8;
            else if(regiao_atual == 6) regiao_atual = 9;
            else if(regiao_atual == 7) regiao_atual = 10;
            else if(regiao_atual == 8) regiao_atual = 11;
            else{
                posY = 800;
                passou = false;
            }
            if(passou){
                posY=0;
                colidiu_mascara = false;
                colidiu_virus = false;
                colidiu_pocao = false;
                pts = 0; pts1 = 0;
            }
        }
        //Direita
        if(posX > 1120){
            bool passou = true;
            if(regiao_atual == 0) regiao_atual = 1; 
            else if(regiao_atual == 1)regiao_atual = 2;
            else if(regiao_atual == 3) regiao_atual = 4;
            else if(regiao_atual == 4) regiao_atual = 5;
            else if(regiao_atual == 6) regiao_atual = 7;
            else if(regiao_atual == 7) regiao_atual = 8;
            else if(regiao_atual == 9) regiao_atual = 10;
            else if(regiao_atual == 10) regiao_atual = 11;
            else{
                posX = 1120;
                passou = false;
            }
            if(passou){
                posX = 0;
                colidiu_mascara = false;
                colidiu_virus = false;
                colidiu_pocao = false;
                pts = 0;  pts1 = 0;
            }
        }
        //Esquerda
        if(posX < 0){
            bool passou = true;
            if(regiao_atual == 2) regiao_atual = 1; 
            else if(regiao_atual == 1) regiao_atual = 0;
            else if(regiao_atual == 5) regiao_atual = 4;
            else if(regiao_atual == 4) regiao_atual = 3;
            else if(regiao_atual == 8) regiao_atual = 7;
            else if(regiao_atual == 7) regiao_atual = 6;
            else if(regiao_atual == 11) regiao_atual = 10;
            else if(regiao_atual == 10) regiao_atual = 9;
            else{
                passou = false;
                posX = 0;
            }
            if(passou){
                posX = 1119;
                colidiu_mascara = false;
                colidiu_virus = false;
                colidiu_pocao = false;
                pts = 0; pts1 = 0;
            }
        }
        //Cima
        if(posY < 0){
            bool passou = true;
            if(regiao_atual == 11) regiao_atual = 8; 
            else if(regiao_atual == 10) regiao_atual = 7;
            else if(regiao_atual == 9) regiao_atual = 6;
            else if(regiao_atual == 8) regiao_atual = 5;
            else if(regiao_atual == 7) regiao_atual = 4;
            else if(regiao_atual == 6) regiao_atual = 3;
            else if(regiao_atual == 5) regiao_atual = 2;
            else if(regiao_atual == 4) regiao_atual = 1;
            else if(regiao_atual == 3) regiao_atual = 0;
            else{
                passou = false;
                posY = 0;
            }
            if(passou){
                posY = 800;
                colidiu_virus = false;
                colidiu_mascara = false;
                colidiu_pocao = false;
                pts = 0; pts1 = 0;
            }
        }

        // Check if we need to redraw
        if (redraw && al_is_event_queue_empty(event_queue)) {
            al_draw_bitmap_region(imagem_fundo,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
            if(regiao_atual == REGIAO_1){
                al_draw_bitmap_region(imagem_fundo,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);
            }else if(regiao_atual == REGIAO_2){
                al_draw_bitmap_region(imagem_fundo,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);
            }else if(regiao_atual == REGIAO_3){
                al_draw_bitmap_region(imagem_fundo,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);
            }else if(regiao_atual == REGIAO_4){
                al_draw_bitmap_region(imagem_fundo2,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);
            }else if(regiao_atual == REGIAO_5){
                al_draw_bitmap_region(imagem_fundo2,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);
            }else if(regiao_atual == REGIAO_6){
                al_draw_bitmap_region(imagem_fundo2,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);            
            }else if(regiao_atual == REGIAO_7){
                al_draw_bitmap_region(imagem_fundo3,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);
            }else if(regiao_atual == REGIAO_8){
                al_draw_bitmap_region(imagem_fundo3,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);
            }else if(regiao_atual == REGIAO_9){
                al_draw_bitmap_region(imagem_fundo3,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);
            }else if(regiao_atual == REGIAO_10){
                al_draw_bitmap_region(imagem_fundo4,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);
            }else if(regiao_atual == REGIAO_11){
                al_draw_bitmap_region(imagem_fundo4,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);
            }else if(regiao_atual == REGIAO_12){
                al_draw_bitmap_region(imagem_fundo4,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
                desenhaMapa(&coracao1,&coracao2,direcao_personagem,muda_animacao,pontuacao,&posX_virus,&posY_virus,&vel_virus,posX,posY,&gerar_virus
                ,&colidiu_virus,&running,&pontuacao_personagem,&posX_mascara,&posY_mascara, &gerar_mascara,&colidiu_mascara,&regiao_atual
                ,&posX_pocao,&posY_pocao,&vel_personagem,&gerar_pocao,&colidiu_pocao);
            }else if(regiao_atual == FIM_DE_JOGO){
                al_draw_text(fonte,al_map_rgb(0,0,0),230,250,0,"A pontuação total do jogador foi: ");
                al_draw_text(fonte,al_map_rgb(0,0,0),560,380,0,pontuacao);
                al_draw_bitmap(botao_reset,550,520,0);
                if(reinicia_jogo){
                    regiao_atual = 0;
                    coracao1 = 4; coracao2 = 4;
                    reinicia_jogo=false;
                    pontuacao_personagem = 0;
                    strcpy(pontuacao,"0");
                }
            }else if(regiao_atual == MENU){
                al_draw_bitmap(botao_play,460,350,0);
                if(inicia_jogo){
                    regiao_atual = 0;
                }
            }
            int i;
            for(i = 0;i < 3;i++){
                if(i == regiao_atual) al_draw_bitmap(botao_vermelho,1050+20*i,50,0);
                else al_draw_bitmap(botao_verde,1050+20*i,50,0);
            }
            for(i = 4; i < 7;i++){
                if(i-1 == regiao_atual) al_draw_bitmap(botao_vermelho,1050+20*(i-4),70,0);
                else al_draw_bitmap(botao_verde,1050+20*(i-4),70,0);
            }
            for(i = 7; i < 10;i++){
                if(i-1 == regiao_atual) al_draw_bitmap(botao_vermelho,1050+20*(i-7),90,0);
                else al_draw_bitmap(botao_verde,1050+20*(i-7),90,0);
            }
            for(i = 10; i < 13;i++){
                if(i-1 == regiao_atual) al_draw_bitmap(botao_vermelho,1050+20*(i-10),110,0);
                else al_draw_bitmap(botao_verde,1050+20*(i-10),110,0);
            }
            al_flip_display();
        }
    }
	//al_destroy_audio_stream(musica_fundo);
    al_destroy_timer(timer_relogio);
	al_destroy_bitmap(forma);
    al_destroy_bitmap(personagem[direcao_personagem+muda_animacao]);
    al_destroy_bitmap(imagem_fundo);
	al_destroy_timer(timer);
  	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
    return 0;
}