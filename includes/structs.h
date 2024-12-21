/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:18:57 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:18:59 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/include/libft.h"
# include "../sound/SDL2/include/SDL.h"
# include "../sound/SDL2_mixer/include/SDL_mixer.h"
# include "../sound/SDL2_mixer/src/codecs/music_wav.h"
# include "define.h"

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_line
{
	char	*content;
	int		x;
}	t_line;

typedef struct s_doors
{
	int		x;
	int		y;
	bool	is_open;
	bool	is_animating;
	double	start_animation;
}	t_doors;

typedef struct s_weapon
{
	bool	is_animating;
	int		current_frames;
	bool	hit;
	double	start_animation;
}	t_weapon;

typedef struct s_map
{
	bool	start_read;
	bool	end_read;
	char	*first_line;
	char	*file;
	t_line	**lines;
	int		start_x;
	int		start_y;
	int		y;
	int		count_start_pos;
	char	orientation;
}	t_map;

typedef enum e_order
{
	NO_ORDER,
	SO_ORDER,
	WE_ORDER,
	EA_ORDER,
	F_ORDER,
	C_ORDER,
	DONE
}	t_order;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		*color;
	int		width;
	int		height;
	int		x;
	int		y;
	int		bpp;
	int		endian;
	int		line_len;
	double	wall_x;
	double	step;
	double	pos;
}	t_image;

typedef struct s_texture
{
	char	*id;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	char	*floor_color;
	char	*ceiling_color;
	bool	f_textured;
	bool	c_textured;
	t_order	order;
	t_image	image[4];
}	t_texture;

typedef struct s_ray
{
	double	projected_dist;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	dir_x;
	double	dir_y;
	int		step_x;
	int		step_y;
	double	delta_x;
	double	delta_y;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	double	wall_dist;
	double	angle;
	bool	is_door;
	int		door_idx;
	char	pos_door;
	int		door_y;
	int		door_x;
	t_coord	map;
	t_list	*doors;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	bool	jump;
	bool	crouch;
	int		*action;
	int		move_div;
	int		z;
	int		h;
	t_ray	*cross_ray;
	t_image	cursor;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	pos_x;
	double	pos_y;
	double	rot_speed;
	double	move_speed;
}	t_player;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

typedef struct s_music
{
	Mix_Music	*launcher;
	Mix_Music	*moria;
	Mix_Music	*morgul;
	Mix_Music	*game_over;
	Mix_Music	*gollum_song;
	Mix_Chunk	*door;
	Mix_Chunk	*step;
	Mix_Chunk	*weapon;
	Mix_Chunk	*hit;
	Mix_Chunk	*gollum;
}	t_music;

typedef struct s_enemy
{
	double	x;
	double	y;
	double	distance;
	t_image	*texture;
	bool	is_animating;
	double	start_animation;
}	t_enemy;

typedef struct s_data
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_start_x;
	int		draw_end_y;
	int		draw_end_x;
	int		stripe;
	int		tex_x;
	int		tex_y;
	int		color;
	int		draw_start;
	int		draw_end;
	double	raydir_x0;
	double	raydir_y0;
	double	raydir_x1;
	double	raydir_y1;
	int		p;
	double	pos_z;
	double	row_distance;
	double	floor_step_x;
	double	floor_step_y;
	double	floor_x;
	double	floor_y;
	int		cell_x;
	int		cell_y;
}	t_data;

typedef struct s_game
{
	int			old_time;
	void		*mlx;
	void		*win;
	char		*file;
	char		*map_type;
	bool		show_gollum;
	int			nb_gollum;
	double		gollum_time;
	bool		restart_music;
	int			nb_doors;
	int			door_idx;
	char		**morgul;
	int			enemy_frames;
	int			doors_frames;
	int			weapons_frames;
	int			launcher_frames;
	bool		launcher_animation;
	bool		launcher_is_running;
	double		launcher_start_animation;
	int			nb_enemy;
	int			target;
	double		time;
	double		z_buffer[SCREEN_X];
	t_image		minimap;
	t_image		raycast;
	t_image		ring;
	t_weapon	anim_weapons;
	t_image		*weapon;
	t_enemy		*enemy;
	t_image		*door;
	t_image		game_over;
	t_image		ceil_txt;
	t_image		floor_txt;
	t_image		*launcher;
	t_map		*map;
	t_texture	*texture;
	t_player	player;
	t_color		minimap_wall;
	t_color		minimap_floor;
	t_color		floor;
	t_color		ceiling;
	t_doors		*doors;
	t_music		*music;
}	t_game;

#endif
