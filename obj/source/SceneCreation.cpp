#include "../../src/header/Game.h"

/*
    This file is responsible for creating all of the displays for the game.
    Rather than clumping functionality and display creation all in 1 file,
    separate it in two.
*/

// Create scene 1
void Game::create_scene_1(int width, int height){
    // Everything to display
    this->display.push_back(new Display(width, height, 2, 5, "lofi_background.wav"));

    // Add player to the scene
    this->display.at(1)->add_to_scene(this->player->get_sprite());

    // Add other assets to the current display
    for(size_t i = 0; i < width / 16; i++){
        for(size_t j = 0; j < height / 16; j++){
            // Adding a small patch of grass near the bottom center.
            if(j >= 21 && j <= 31 && i <= 15){
                this->display.at(1)->add_to_scene(new TileSprite(3, j * 16, height - (i*16) - 16));
                if(j == 21 || j == 31){
                    this->display.at(1)->add_to_scene(new TileSprite(4, j * 16, height - (i*16) - 16));
                }
            }
            // Add 5 rows of water right beside the fenced area
            else if(((j >= 14 && j <= 21) || (j >= 31 && j <= 38)) && i <= 15){
                if((j >= 15 && j <= 20) || (j >= 32 && j <= 37)){
                    this->display.at(1)->add_to_scene(new TileSprite(6, j * 16, height - (i*16) - 16));
                }
                else{
                    this->display.at(1)->add_to_scene(new TileSprite(3, j * 16, height - (i*16) - 16));
                    this->display.at(1)->add_to_scene(new TileSprite(4, j * 16, height - (i*16) - 16));
                }
            }
            // Add grass and fence around the water
            else if(i == 16 && j >= 14 && j <= 38){
                this->display.at(1)->add_to_scene(new TileSprite(3, j * 16, height - (i*16) - 16));
                if((j >= 14 && j <= 21) || (j >= 31 && j <= 38)){
                    this->display.at(1)->add_to_scene(new TileSprite(4, j * 16, height - (i*16) - 16));
                }
            }

            else{
                this->display.at(1)->add_to_scene(new TileSprite(1, j * 16, height - (i*16) - 16));
            }
        }
    }

    // Adding a fenced area around the house
    // TL: (288,192); TR: (672,192); BL: (288,432); BR: (672,432)
    // No fences between (432,400) and (480,400)
    for(size_t i = 320; i <= 672; i += 32){
        this->display.at(1)->add_to_scene(new TileSprite(8, i, 256));
        if(!(i >= 464 && i <= 512))
            this->display.at(1)->add_to_scene(new TileSprite(8, i, 416));
    }
    for(size_t j = 256; j < 432; j += 32){
        this->display.at(1)->add_to_scene(new TileSprite(7, 288, j));
        this->display.at(1)->add_to_scene(new TileSprite(7, 704, j));
    }

    // Adding trees
    this->display.at(1)->add_to_scene(new TileSprite(5, 352, 320));
    this->display.at(1)->add_to_scene(new TileSprite(5, 624, 320));

    // Adding the house.
    this->display.at(1)->add_to_scene(new TileSprite(2, width / 2 + 16, (height - 312) / 2));
}

// Create scene 2
void Game::create_scene_2(int width, int height){
    // Everything to display
    this->display.push_back(new Display(width, height, 4, 8, "lofi_background.wav"));

    // Add all of terrain set 2 onto this scene
    // Add other assets to the current display
    for(size_t i = 0; i < width / 16; i++){
        for(size_t j = 0; j < height / 16; j++){
            this->display.at(2)->add_to_scene(new TileSprite(9, j * 16, height - (i*16) - 16));
        }
    }

    // Add more stuff to overlap with the terrain that is already set.

}

// Create battle scene
void Game::create_scene_battle(int width, int height){
    if(this->battle_scene_created)
        return;

    // Add new display (no min/max levels needed)
    this->display[0] = new Display(width, height, -1, -1, "lofi_background.wav", true);

    // Add the lead party pokemon to the screen, but scale it down to 128x128
    //this->player.add_pokemon(*this->pokemon.find(252)->second);
    //if(this->player.get_num_pokemon() > 0)
    //    this->display.at(0)->add_to_scene(new TileSprite(-1, 144, 448, QString("./PokemonHomeImages/%1.png").arg(this->player.get_pokemon(0)->get_dex_id()), 144, 144));

    // And then mark as true
    this->battle_scene_created = true;


    // Add event filter on this display
    //this->display.at(0)->installEventFilter(this);
}

