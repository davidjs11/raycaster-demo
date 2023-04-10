#include "gameUtils.h"

void moveEntity(struct entity *ent, uint8_t forw, uint8_t backw)
{
    ent->posX += cos(ent->angle)*ent->speed*forw +
	             cos(M_PI+ent->angle)*ent->speed*backw;
    ent->posY += sin(ent->angle)*ent->speed*forw +
		         sin(M_PI+ent->angle)*ent->speed*backw;
}

void rotateEntity(struct entity *ent, uint8_t left, uint8_t right)
{
    ent->angle += ent->angSpeed * (right - left);
}
