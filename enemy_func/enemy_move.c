#include "../inc/game.h"

void	enemy_move(t_enemy *e, t_map *m, double dt)
{
	int direction = rand() % 4;
    int new_x = e->pos.x;
    int new_y = e->pos.y;

    if (direction == 0 && m->map[(e->pos.y - 1) / 32][e->pos.x / 32] != '1') {
        new_y -= (3 * dt) + 1;
    } else if (direction == 1 && m->map[(e->pos.y + 24) / 32][e->pos.x / 32] != '1') {
        new_y += (3 * dt) + 1;
    } else if (direction == 2 && m->map[e->pos.y / 32][(e->pos.x - 1) / 32] != '1') {
        new_x -= (3 * dt) + 1;
    } else if (direction == 3 && m->map[e->pos.y / 32][(e->pos.x + 24) / 32] != '1') {
        new_x += (3 * dt) + 1;
    }

    e->pos.x = new_x;
    e->pos.y = new_y;
}
