#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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

void	raycasting(t_game *game);
void raycast(t_game *game);
//MAIN
int		parse_texture_and_map(t_texture **texture, t_map **map, char *file, bool launcher);
int		start_game(t_game *game, bool launcher);
//INIT
void	init_map(t_map *map, char *file);
void	init_texture(t_texture *texture);
void	init_game(t_game *game, t_texture *texture, t_map *map, bool launcher);
void	init_ray(t_game *game, t_ray *ray, int x);
double	deg_to_rad(double degrees);
//DEBUG/PRINT
void	print_map(t_map *map, int fd);
void	print_texture(t_texture *texture, int fd);
//FREE/FREE_GAME
int		close_game(t_game *game);
int		close_launcher(t_game *game);
//FREE/FREE_MAP
void	free_map(t_map *map);
//FREE/FREE_TEXTURE
void	free_texture(t_texture *texture);
void	free_image(t_game *game);
void	free_launcher_image(t_game *game);
//GAME/ANIMATION
double	get_current_time(void);
t_image	*doors_animation(t_game *game, int idx, int start);
t_image	*weapon_animation(t_game *game);
t_image	*enemy_animation(t_game *game, int target, t_coord pos);
void	*gollum(t_game *game);
//GAME/CHARACTER
void	player_init(t_game *game);
//GAME/COLORS
void	get_color(t_color *type, char *path);
int		rgb_to_int(int r, int g, int b);
void	draw_floor_ceiling(t_game *game, int floor_color, int ceiling_color);
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
//GAME/ENEMY
int		init_enemy(t_game *game, char *prefix);
void	sort_enemies(t_game *game);
void	render_enemies(t_game *game);
int		hit_enemy(t_ray *ray, t_game *game);
void	move_ray(t_game *game, t_ray *ray);
//GAME/FLOORS_RAYCAST
void	floor_ceil_raycast(t_game *game);
//GAME/IMAGE
int		load_textures(t_game *game);
//GAME/LAUNCHER
int		open_launcher(t_game *game);
void	get_map_type(t_game *game);
void	game_over(t_game *game);
//GAME/MINIMAP
void	minimap(t_game *game);
void	draw_minimap(t_game *game, t_image minimap);
//GAME/MLX_FUNCTIONS
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	my_put_image(t_game *game, t_image *img, int x_offset, int y_offset);
int		load_xpm(t_game *game, t_image *texture, char *xpm_file);
int		mouse_click(int button, int x, int y, t_game *game);
//GAME/MOUSE
void	mouse_move(t_game *game);
void	left_cam(t_game *game);
void	right_cam(t_game *game);
//GAME/MOVEMENT_SECURITY
double	check_backroom(t_game *game, int move);
void	jump(t_game *game);
int		enemy_collision(t_game *game, double x, double y);
//GAME/MOVES
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
//GAME/RAYCASTING_UTILS
void	camera_angle_distortion(t_game *game, t_ray *ray);
void	select_wall_texture(t_game *game, t_ray *ray, t_image **tex);
void	shoot_ray_to_center(t_game *game, bool door);
//GAME/RAYCASTING
void	perform_dda(t_game *game, t_ray *ray, bool hitDoor);
void	calculate_steps(t_game *game, t_ray *ray);
void	calculate_wall_distance(t_ray *ray);
//GAME/SOUND
void	init_sound(void);
int		sound(t_game *game);
int		init_sound_effects(t_game *game);
void	init_struct_game_sound(t_game *game);
void	free_sound(t_game *game);
//GAME/TAB_IMAGES
char	**create_moria_tab(t_game *game);
char	**create_morgul_tab(t_game *game);
char	**create_balrog_tab(t_game *game);
char	**create_staff_tab(t_game *game);
int		create_launcher_images(t_game *game, char *prefix);
//GAME/TRANSPARENCY
void	draw_doors(t_game *game, t_ray *ray, t_coord loop);
void	doors_transparency(t_game *game, t_list **tmp, t_ray *ray, t_coord loop);
void	add_doors(t_game *game, t_ray *ray, bool *isLastDoor, bool *isFirst);
//GAME/WEAPON
int		init_weapon(t_game *game);
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
