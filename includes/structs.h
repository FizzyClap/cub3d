#ifndef STRUCTS_H
# define STRUCTS_H

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
}	t_doors;

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
	int		x_max;
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
	double	speed;
	double	angle;
	t_ray	*cross_ray;
	t_image	cursor;
}	t_player;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	color;
}	t_color;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*select;
	char		*file;
	bool		launcher_is_running;
	int			nb_doors;
	t_image		minimap;
	t_image		raycast;
	t_image		ring;
	t_image		balrog;
	t_image		door_open;
	t_image		door;
	t_image		launcher;
	t_map		*map;
	t_texture	*texture;
	t_player	player;
	t_color		floor;
	t_color		ceiling;
	t_doors		*doors;
}	t_game;

#endif
