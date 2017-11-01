#pragma once
#if !defined(MYLIB_CONSTANTS_H)
#define MYLIB_CONSTANTS_H 1

//Écrire constantes ici
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGTH = 720;
const int LEVEL_WIDTH = 128;
const int LEVEL_HEIGTH = 18;
const int LEVEL_AMOUNT = 1;
const int TILE_SIZE = 70;
const int HERO_SPEED = 5;
const int HERO_JUMP_DURATION = 25;
const int HERO_JUMP_FLOATING_DURATION = 3;
const int ANIMATIONS_AMOUNT = 3;
const int FRAME_AMOUNT = 2;
const int RANDOM_SPAWN_LOCATION_AMOUNT = 24;
const int STATIC_SPAWN_LOCATION_AMOUNT = 7;
const int ENEMY_RANDOM_SPAWN_DELAY = 60 * 5;
const int ENEMY_STATIC_SPAWN_DELAY = 60 * 8;
const int HERO_WALK_ANIM_FRAME_QTY = 11;
const int HERO_WALK_ANIM_MAX_TICK = 33;
const int ENEMY_HORIZONTAL_OFFSET = 70 * 3;


const float DIAGONAL_MOVEMENT_RATIO = 1.41f;
const float ZOOM_RATIO = 1.5f;
const int ENEMY_SPEED = 1;

#endif