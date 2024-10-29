# include "../inc/game.h"

static bool	is_active(int points, int collectables)
{
	return (points == collectables);
}

static bool	collides(t_area a1, t_area a2)
{
	if (a1.v1.x > a2.v2.x || a2.v1.x > a1.v2.x)
		return (false);
	if (a1.v1.y > a2.v2.y || a2.v1.y > a1.v2.y)
		return (false);
	return (true);
}

static bool player_exit(t_player p, t_exit e)
{
	return (collides((t_area){(t_vector){e.pos.x + 16, e.pos.y + 16}, (t_vector){e.pos.x + 32, e.pos.y + 32}}, \
		(t_area){p.pos, (t_vector){p.pos.x + 16, p.pos.y + 27}}));
}

void	update_exit(t_game *g)
{
	g->e.is_open = is_active(g->p.score, g->map->c);
	if (g->e.is_open && player_exit(g->p, g->e))
		exit(0);
}
