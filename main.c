#include <genesis.h>
#include <resources.h>
#include <timer.h>


// Esse código está aos poucos em construção - aprendendo com a 
// cópia de SONIC THE HEDGEHOG - Sega Genesis (Mega DRive) =).


#define ANIM_NOR 0
#define ANIM_STAND 1
#define ANIM_WALK 2
//#define ANIM_RUN 3
#define ANIM_STOP 4

#define SUBTICKPERSECOND    76800
#define TICKPERSECOND       300


//u16 numTimer = 0;

//void startTimer(u16, 0);

//u32  getTimer(u16 numTimer, u16 restart);
   




u16 ind = TILE_USER_INDEX;
Map* level_1_map;


Sprite* player; // Name do "Sprite" é "player".
int player_x = 4;
int player_y = -360;
int idle_timer = 0;
int idle_limit = 100;


//u32 subtick = 1;

// int anim = 1; -- teste da animação.

// ----  const_int ANIM_STAND = 1; ----- pode ser usado em lugar do "int anim".

//int y = 0;
int x = 0; //associado a linha "x += 1;" 
//int A = 0;
//int limit = 10;


static void idleTimer();
static void handleInput();
    
static void joyEvent(u16 joy, u16 changed, u16 state)
{
   if (state & BUTTON_LEFT) {
     idle_timer = 0;                 
   }
   else if (changed & BUTTON_LEFT) {

    idle_timer++;
   }
   if (state & BUTTON_RIGHT) {

    idle_timer = 0;
   }
   else if (changed & BUTTON_RIGHT)
   {
    idle_timer++;
   }

}






// ---------- PARTE PRINCIPAL "MAIN" ---------------- //

int main() 
{
    
    SPR_init();
    PAL_setPalette(PAL2, our_sprite.palette->data, DMA);
    player = SPR_addSprite(&our_sprite, player_x, player_y, TILE_ATTR(PAL2, FALSE, FALSE, FALSE)); 
    //A = y + 1;
    // Valor de localização "our_sprite, 2, -360" - testar esses valores antes listados!!!
    JOY_setEventHandler(joyEvent);



	VDP_loadTileSet(&our_tileset, ind, DMA);
    level_1_map = MAP_create(&our_level_map, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind));
    PAL_setPalette(PAL0, our_palette.data, DMA);
    MAP_scrollTo(level_1_map, x, 768);
    

// ------- FUNÇÃO LOOP DO JOGO ------- //
	
	while(TRUE) // Game Loop
    {

        handleInput();
        
        idleTimer(); 
        
        SPR_update();
        //SPR_setPosition();
        // else if (idle_timer == idle_duration) {
        
      // }               
        //MAP_scrollTo(level_1_map, x, 768); 
        // porque é necessário essa linha no "loop"? Porque é necessário manter o Scroll da tela do mapa, durante toda a exibição"
        
        //x += 1;
        
		SYS_doVBlankProcess();
	}
	return 0;
}

static void handleInput()
{   
   
    u16 value = JOY_readJoypad(JOY_1);
    if (value & BUTTON_RIGHT){
       player_x += 1; 
       SPR_setAnim(player, ANIM_WALK);
       SPR_setHFlip(player, FALSE);
       idle_timer = 0;
    }
    else if (value & BUTTON_LEFT) {
       player_x -= 1;
       SPR_setAnim(player, ANIM_WALK);
       SPR_setHFlip(player, TRUE); 
       idle_timer = 0;
    }
    
    if(!(value & BUTTON_RIGHT) && !(value & BUTTON_LEFT) && !(value & BUTTON_UP) && !(value & BUTTON_DOWN))
    {
       SPR_setAnim(player, ANIM_NOR);
       
       
    }
   
  
    
    
    //else if (!(value & BUTTON_RIGHT) && !(value & BUTTON_LEFT) && !(value & BUTTON_UP) && !(value & BUTTON_DOWN))
   
  
    
  //player_y +=  ;
    SPR_setPosition(player, player_x, player_y);

}

static void idleTimer()
{
    if (idle_timer < idle_limit) {
   idle_timer++;
   
  }
    else if (idle_timer == idle_limit) {
   
   SPR_setAnim(player, ANIM_STAND);
   //idle_timer = 0;

} 
}


 

//static void idle_function()
//{
     
//        if (idle_timer == 0) handleInput();
 //       else if (idle_timer > 0 && idle_timer < idle_duration) {
   //     
     //   idle_timer += 1; }
//
  //      else if (idle_timer == idle_duration) {
    //        SPR_setAnim(player, ANIM_STAND);
      //      handleInput();
        // }

//}

//static void joyEvent(u16 joy, u16 changed, u16 state)


  
//static void joyEvent(u16 joy, u16 changed, u16 state)

   //if (changed & state & BUTTON_RIGHT)          









