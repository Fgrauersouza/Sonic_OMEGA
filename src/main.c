#include <genesis.h>
#include <resources.h>


// Esse código está aos poucos em construção - aprendendo com a 
// cópia de SONIC THE HEDGEHOG - Sega Genesis (Mega DRive) =).


#define ANIM_STAND 1


#define ANIM_WALK 2
//#define ANIM_RUN 3
#define ANIM_STOP 4




u16 ind = TILE_USER_INDEX;
Map* level_1_map;


Sprite* player; // Name do "Sprite" é "player".
int player_x = 4;
int player_y = -360;




// int anim = 1; -- teste da animação.

// ----  const_int ANIM_STAND = 1; ----- pode ser usado em lugar do "int anim".


int x = 0; //associado a linha "x += 1;" 

static void handleInput();

// ---------- PARTE PRINCIPAL "MAIN" ---------------- //

int main() 
{
    
    SPR_init();
    PAL_setPalette(PAL2, our_sprite.palette->data, DMA);
    player = SPR_addSprite(&our_sprite, player_x, player_y, TILE_ATTR(PAL2, FALSE, FALSE, FALSE)); 

    // Valor de localização "our_sprite, 2, -360" - testar esses valores antes listados!!!
    



	VDP_loadTileSet(&our_tileset, ind, DMA);
    level_1_map = MAP_create(&our_level_map, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind));
    PAL_setPalette(PAL0, our_palette.data, DMA);
    MAP_scrollTo(level_1_map, x, 768);


// ------- FUNÇÃO LOOP DO JOGO ------- //
	
	while(TRUE) // Game Looping
    {
        handleInput();
        SPR_setPosition();
        SPR_update();  
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
       SPR_setHFlip(player, TRUE);
    }
    else if (value & BUTTON_LEFT) {
       player_x -= 1;
       SPR_setAnim(player, ANIM_WALK);
       SPR_setHFlip(player, FALSE);
       
    }
    
    if (!(value & BUTTON_RIGHT) && !(value & BUTTON_LEFT) && !(value & BUTTON_UP) && !(value & BUTTON_DOWN))
    {
       SPR_setAnim(player, ANIM_STAND);
    }
    
    
  //player_y +=  ;
    SPR_setPosition(player, player_x, player_y);

}
