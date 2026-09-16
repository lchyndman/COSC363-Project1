#ifndef CONVEYOR_H
#define CONVEYOR_H
#include "legoman.h"
void loadConveyorTexture();
void updateConveyor(float t);
void drawConveyorTile();
float tileX(float t);

// CONVEYOR CONSTANTS
const int N_TILES = 10;
const int N_HEADS = 10;

const float X_SPEED = 10;
const float Y_SPEED = 2;
const float Z_SPEED = X_SPEED;

const float STRAIGHT_LENGTH = 200;
const float DROP_HEIGHT = 20;
const float SPIRAL_WIDTH = 50;

const float SPIRAL_START = STRAIGHT_LENGTH / X_SPEED;
const float BOTTOM_START = SPIRAL_START + DROP_HEIGHT / Y_SPEED;
const float TOP_START = 0;
const float TOTAL_TIME = BOTTOM_START + STRAIGHT_LENGTH / X_SPEED;

//  TILE CONSTANTS
const float TILE_LENGTH = 20;
const float TILE_HEIGHT = 3;
const float TILE_WIDTH = 40;

const float SPAWN_HOLE_HEIGHT = INGOT_HEIGHT + TILE_HEIGHT * 2;
// Spawn box constants
const float SPAWN_BOX_LENGTH = 3 * TILE_LENGTH;
const float SPAWN_BOX_HEIGHT =  DROP_HEIGHT + HEAD_HEIGHT + TILE_HEIGHT+2*HEAD_HEIGHT;
const float SPAWN_BOX_WIDTH = 1.5 * TILE_WIDTH + SPIRAL_WIDTH;

// Torch constants
const float TORCH_X_POSITION = STRAIGHT_LENGTH/3;
const float TORCH_NOZZLE_LENGTH = 6;
const float TORCH_NOZZLE_RADIUS = 4;

const float TORCH_PIPE_RADIUS = 2;
const float TORCH_PIPE_LENGTH = 10;

const float TORCH_TANK_LENGTH =  8;
const float TORCH_TANK_RADIUS = 6;

const float TORCH_START = TORCH_X_POSITION / X_SPEED;

// Paint Constants
const float PAINT_X_POSITION = 0.7*STRAIGHT_LENGTH;
const float PAINT_CAN_RADIUS = TILE_LENGTH/8;
const float PAINT_CAN_LENGTH = 12;

const float PAINT_NOZZLE_RADIUS = 2;
const float PAINT_NOZZLE_LENGTH = 2;

const float PAINT_BRACKET_HEIGHT = TILE_HEIGHT+HEAD_HEIGHT+2+PAINT_NOZZLE_LENGTH;
const float PAINT_BRACKET_LENGTH = TILE_WIDTH+2*5;

const float PAINT_START = BOTTOM_START + (STRAIGHT_LENGTH - PAINT_X_POSITION) / X_SPEED - 0.2;

// Press constants
const float PRESS_SHAFT_WIDTH = 5;
const float PRESS_SHAFT_MAX_LENGTH = 20;
const float PRESS_SHAFT_MIN_LENGTH = 5;
const float PRESS_SHAFT_RANGE = PRESS_SHAFT_MAX_LENGTH - PRESS_SHAFT_MIN_LENGTH;
const float PRESS_CYLINDER_RADIUS = TILE_LENGTH/2-1;
const float PRESS_CYLINDER_HEIGHT = HEAD_HEIGHT + 2;
const float PRESS_X_POSITION = 2*STRAIGHT_LENGTH/3;
const float PRESS_Y_POSITION = PRESS_CYLINDER_HEIGHT+PRESS_SHAFT_MAX_LENGTH+0.5*TILE_HEIGHT;
const float PRESS_Z_POSITION = 0;
const float PRESS_START = PRESS_X_POSITION / X_SPEED;
const float PRESS_PERIOD = TOTAL_TIME / N_HEADS; 
// const float PRESS_OFFSET = (PRESS_PERIOD*N_HEADS - PRESS_START);
const float PRESS_OFFSET = 0;
const float PRESS_DOWN_TIME = PRESS_PERIOD / 2 - 0.4;
const float PRESS_UP_TIME = PRESS_PERIOD / 2 + 0.4;
// Rail Constants
const float RAIL_LENGTH = STRAIGHT_LENGTH;
const float RAIL_HEIGHT = 5;
const float RAIL_WIDTH = 10; 

// Pole Constants
const float POLE_WIDTH = 0.5*(SPIRAL_WIDTH - TILE_WIDTH);
const float POLE_HEIGHT = 80;
const float POLE_PERIOD = BOTTOM_START - SPIRAL_START;




#endif