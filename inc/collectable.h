#ifndef COLLECTABLE_H
# define COLLECTABLE_H

# include "structs.h"

void		collectable_to_w(t_img *w, t_img *c, t_vector pos);
void		collectable_update(t_colectable *c, double dt);
bool		is_colliding(t_colectable c, t_player p);
void		draw_c(t_game *g, int src_x, int src_y, int n);
void		update_col(t_game *g, double dt);
void		render_coll(t_game *g);
void		collect_img(t_game *g, t_col *c);
void		collected_img(t_game *g, t_col *c);
void		start_collect(t_game *g, int n);
void		save_collect(t_game *g, t_map *map);
#endif
