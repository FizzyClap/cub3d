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
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <limits.h>

void    new(t_game *game);

void    ceil_raycast(t_game *game);
int     get_texture_color(t_image *texture, int tx, int ty);
void	floor_raycast(t_game *game);

// void	draw_floor(t_game *game, t_ray *ray, t_coord loop);
int		parse_texture_and_map(t_texture **texture, t_map **map, char *file, bool launcher);
void	start_game(t_game *game, bool launcher);
int		open_launcher(t_game *game);
//INIT
void	init_map(t_map *map, char *file);
void	init_texture(t_texture *texture);
void	init_game(t_game *game, t_texture *texture, t_map *map, bool launcher);
void	init_ray(t_ray *ray, t_game *game, double angle);
double	deg_to_rad(double degrees);
//DEBUG/PRINT
void	print_map(t_map *map, int fd);
void	print_texture(t_texture *texture, int fd);
//FREE/FREE_GAME
int		close_game(t_game *game);
//FREE/FREE_MAP
void	free_map(t_map *map);
//FREE/FREE_TEXTURE
void	free_texture(t_texture *texture);
//GAME/ANIMATION
t_image	*doors_animation(t_game *game, int idx, int start);
//GAME/CHARACTER
void	player_init(t_game *game);
//GAME/COLORS
void	get_color(t_color *type, char *path);
int		rgb_to_int(int r, int g, int b);
void	draw_floor_ceiling(t_game *game, int floor_color, int ceiling_color);
int		minimap_color(t_game *game, t_coord pos);
t_color	get_alpha_blended_color(t_color prev, t_color new);
//GAME/CONTROLS_UTILS
// void	check_move(t_game *game, int move);
void	correct_angle(t_game *game);
void	refresh_position(t_game *game, int action, double speed);
//GAME/CONTROLS
void	make_actions(t_game *game);
int		keyrelease(int keycode, t_game *game);
int		keycode(int keycode, t_game *game);
void	move_div(t_game *game);
//GAME/DOORS
void	init_doors(t_game *game);
void	toggle_door(t_game *game, int y, int x);
void	select_door_texture(t_game *game, t_ray *ray, t_image **tex);
bool	is_door_open(t_game *game, double x, double y);
//GAME/FLOORS_RAYCAST
int		get_texture_color(t_image *texture, int tx, int ty);
void	floor_raycast(t_game *game);
void	ceil_raycast(t_game *game);
//GAME/IMAGE
int		load_textures(t_game *game);
//GAME/MINIMAP
void	minimap(t_game *game);
void	draw_minimap(t_game *game, t_image minimap);
void	my_mlx_pixel_put(t_image img, int x, int y, int color);
//GAME/MOUSE
void	mouse_move(t_game *game);
void	left_cam(t_game *game, int x);
void	right_cam(t_game *game, int x);
//GAME/MOVEMENT_SECURITY
double	check_backroom(t_game *game, int move);
void	jump(t_game *game);
//GAME/MOVES
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
//GAME/RAYCASTING_UTILS
void	camera_angle_distortion(t_game *game, t_ray *ray);
void	select_wall_texture(t_game *game, t_ray *ray, t_image **tex);
void	shoot_ray_to_door(t_game *game);
//GAME/RAYCASTING
void	raycasting(t_ray *ray, t_game *game);
void	perform_dda(t_ray *ray, t_game *game);
void	calculate_steps(t_ray *ray);
void	calculate_wall_distance(t_ray *ray);
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
double	get_current_time(void);
void	sound(t_game *game);
void	init_sound(void);
void	free_sound(t_game *game);
void	struct_game_sound(t_game *game);
void	init_sound_effects(t_game *game);

#endif
