#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_line
{
	char	*content;
	int		x;
}	t_line;

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
}	t_texture;

//typedef struct s_img
//{
//}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	//t_img		*img;
	t_map		*map;
	t_texture	*texture;
}	t_game;

#endif
