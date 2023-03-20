#ifndef GAME_UTILS
#define GAME_UTILS

#include <math.h>
#include <stdint.h>

// struct that contains the necessary info for a entity
// like the player, an enemy, an object...
struct entity
{
    float posX;
    float posY;
    float angle;
    float speed;
    float angSpeed;
};

// move an entity
void moveEntity(struct entity *ent, uint8_t forw, uint8_t backw);
void rotateEntity(struct entity *ent, uint8_t left, uint8_t right);

#endif
