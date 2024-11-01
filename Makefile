# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 18:06:05 by hladeiro          #+#    #+#              #
#    Updated: 2024/10/17 18:06:10 by hladeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -g
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
LIBFT = inc/libft/libft.a
MLX = mlx/libmlx.a
INC = -I. -Iinc/libft -Iinc/mlx
OBJ_DIR = obj

SRC_CAM = init_cam.c update_cam.c
SRC_COL = collect_img.c collectable_to_w.c collectable_update.c collected_img.c draw_c.c is_colliding.c render_coll.c save_collet.c start_collect.c update_col.c
SRC_DELTA = get_delta.c
SRC_EVENT = event_handler.c key_pressed.c key_released.c
SRC_EXIT = draw_exit.c update_exit.c
SRC_GAME = ft_free_g.c mlx_put_str.c update_game.c init_game.c
SRC_MAP = error_message.c fload_fill.c fload_helper.c free_map.c init_map.c valid_name.c
SRC_PLA = draw_p.c player_start.c player_to_world.c player_update.c wall_collide.c
SRC_WRD = init_world.c render_map.c write_world.c

SRC := $(addprefix cam_func/, $(SRC_CAM))
SRC += $(addprefix collect/, $(SRC_COL))
SRC += $(addprefix delta/, $(SRC_DELTA))
SRC += $(addprefix event/, $(SRC_EVENT))
SRC += $(addprefix exit_func/, $(SRC_EXIT))
SRC += $(addprefix game/, $(SRC_GAME))
SRC += $(addprefix map_func/, $(SRC_MAP))
SRC += $(addprefix player/, $(SRC_PLA))
SRC += $(addprefix world_func/, $(SRC_WRD))
SRC += game_start.c so_long.c

OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C inc/libft

$(MLX):
	@$(MAKE) -C mlx

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "Executable created: $(NAME)"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C inc/libft clean
	@$(MAKE) -C mlx clean
	@echo "Cleaned up object files and libraries"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C inc/libft fclean
	@echo "Removed executable: $(NAME)"

re: fclean all

.PHONY: all clean fclean re
