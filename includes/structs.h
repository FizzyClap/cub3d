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
	t_order	order;
	t_image	image[4];
}	t_texture;

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	dir_x;
	double	dir_y;
	double	projected_dist;
	int		step_x;
	int		step_y;
	double	delta_x;
	double	delta_y;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	double	wall_dist;
	double	angle;
	int		end;
	bool	is_door;
	int		door_idx;
	t_list	*doors;
}	t_ray;

typedef struct s_player
{
	bool	jump;
	bool	crouch;
	int		*action;
	int		move_div;
	int		z;
	int		h;
	double	x;
	double	y;
	double	d_x;
	double	d_y;
	double	plane_x;
	double	plane_y;
	double	speed;
	double	angle;
	t_ray	*cross_ray;
	t_image	cursor;
	// new wave
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	posX;
	double	posY;
	double	rotSpeed;
	double	moveSpeed;
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
	Mix_Chunk	*door;
	Mix_Chunk	*step;
	Mix_Chunk	*weapon;
	Mix_Chunk	*hit;
	Mix_Chunk	*fire;
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

typedef struct s_render
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
}	t_render;

typedef struct s_draw
{
	int	color;
	int	draw_start;
	int	draw_end;
	int	h_line;
	int	h_correct;
}	t_draw;

typedef struct s_game
{
	int			oldTime;
	void		*mlx;
	void		*win;
	char		*file;
	char		*map_type;
	bool		show_gollum;
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
	double		z_buffer[SCREEN_WIDTH];
	t_image		minimap;
	t_image		raycast;
	t_image		ring;
	t_weapon	anim_weapons;
	t_image		*weapon;
	t_enemy		*enemy;
	t_image		*door;
	t_image		game_over;
	t_image		ceil;
	t_image		floor_txt;
	t_image		*launcher;
	t_map		*map;
	t_texture	*texture;
	t_player	player;
	t_color		floor;
	t_color		ceiling;
	t_doors		*doors;
	t_music		*music;
}	t_game;

#endif
