#ifndef COLLECTABLE_H
# define COLLECTABLE_H

# include "structs.h"

void		collectable_to_w(t_img *w, t_img *c, t_vector pos);
void		collectable_update(t_colectable *c, double dt);
bool		is_colliding(t_colectable c, t_player p);

#endif
