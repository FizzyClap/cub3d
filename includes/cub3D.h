#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include "structs.h"
# include "define.h"
# include "../libft/include/libft.h"
# include "../libft/printf/printf.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

void	init_map(t_map *map, char *file);
void	init_texture(t_texture *texture);
void	init_game(t_game **game, t_texture *texture, t_map *map);
//DEBUG/PRINT
void	print_map(t_map *map, int fd);
void	print_texture(t_texture *texture, int fd);
//FREE/FREE_GAME
int		close_game(t_game *game);
//FREE/FREE_MAP
void	free_map(t_map *map);
//MINIMAP/MINIMAP
void	my_mlx_pixel_put(t_image img, int x, int y, int color);
void	minimap(t_game *game);
//MINIMAP/CHARACTER
void	player_init(t_game *game);
//FREE/FREE_TEXTURE
void	free_texture(t_texture *texture);
//GAME/CONTROLS
int		keycode(int keycode, t_game *game);
//PARSING/CHECK_ARG
int		check_arg(int argc, char **argv);
int		open_map(char *file);
//PARSING/CHECK_MAP
int		read_map(t_map *map, int fd);
//PARSING/CHECK_TEXTURE
int		read_textures(t_texture *texture, char *file);
//PARSING/CHECK_WALLS
int		check_walls(t_map *map, int y, int x);
//PARSING/PARSING_UTILS
int		path_exist(char *file);
int		color_format(char *id, char *line);
int		nb_start_pos(t_map *map, int y, int x);
int		char_is_valid(char c);
int		check_len(int len, int min, char *line);

#endif
