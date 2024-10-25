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
# include <sys/time.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

//INIT
void	init_map(t_map *map, char *file);
void	init_texture(t_texture *texture);
void	init_game(t_game **game, t_texture *texture, t_map *map);
void	init_ray(t_ray *ray, t_game *game, double angle);
//DEBUG/PRINT
void	print_map(t_map *map, int fd);
void	print_texture(t_texture *texture, int fd);
//FREE/FREE_GAME
int		close_game(t_game *game);
//FREE/FREE_MAP
void	free_map(t_map *map);
//FREE/FREE_TEXTURE
void	free_texture(t_texture *texture);
//GAME/CHARACTER
void	player_init(t_game *game);
//GAME/COLORS
void	get_colors(t_texture *texture, t_color *floor, t_color *ceiling);
int		rgb_to_int(int r, int g, int b);
void	draw_floor_ceiling(t_game *game, int floor_color, int ceiling_color);
int		minimap_color(t_game *game, t_coord pos);
//GAME/CONTROLS_UTILS
void	correct_angle(t_game *game);
void	refresh_position(t_game *game, int action, double speed);
void	check_move(t_game *game);
//GAME/CONTROLS
int		keycode(int keycode, t_game *game);
void	move_up(t_game *game);
void	move_down(t_game *game);
void	jump_and_crouch(t_game *game);
//GAME/IMAGE
int		load_textures(t_game *game);
//GAME/MINIMAP
void	draw_minimap(t_game *game, t_image minimap);
void	minimap(t_game *game);
void	my_mlx_pixel_put(t_image img, int x, int y, int color);
//GAME/MOUSE
int		check_backroom(t_game *game, int x, int y);
void	mouse_move(t_game *game);
void	left_cam(t_game *game, int x);
void	right_cam(t_game *game, int x);
//GAME/RAYCASTING_UTILS
void	draw_vertical_line(t_game *game, int x, int start, int color);
void	camera_angle_distortion(t_game *game, t_ray *ray);
void	select_wall_texture(t_game *game, t_ray *ray, t_texture_data **tex);
//GAME/RAYCASTING
void	raycasting(t_ray *ray, t_game *game);
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
void	clear_image(char *address, int height, int width);

#endif
