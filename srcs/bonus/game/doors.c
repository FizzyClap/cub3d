#include "../includes/cub3D.h"

static void	fill_struct_doors(t_game *game);
t_image	*doors_animation(t_game *game, double time, int idx, int start);

void	init_doors(t_game *game)
{
	int	y;
	int	x;

	game->nb_doors = 0;
	y = -1;
	while (++y < game->map->y)
	{
		x = -1;
		while (++x < game->map->lines[y]->x)
			if (game->map->lines[y]->content[x] == 'D')
				game->nb_doors++;
	}
	game->doors = malloc(sizeof(t_doors) * (game->nb_doors));
	if (!game->doors)
		return ;
	fill_struct_doors(game);
}

static void	fill_struct_doors(t_game *game)
{
	int	y;
	int	x;
	int	door_index;

	door_index = 0;
	y = -1;
	while (++y < game->map->y)
	{
		x = -1;
		while (++x < game->map->lines[y]->x)
		{
			if (game->map->lines[y]->content[x] == 'D')
			{
				game->doors[door_index].y = y;
				game->doors[door_index].x = x;
				game->doors[door_index].is_open = false;
				game->doors[door_index].is_animating = false;
				door_index++;
			}
		}
	}
}

void	toggle_door(t_game *game, int y, int x)
{
	int	i;

	i = -1;
	while (++i < game->nb_doors)
	{
		if (game->doors[i].y == y && game->doors[i].x == x)
		{
			if (game->doors[i].is_animating == false)
			{
				game->doors[i].is_open = ft_change_bool(game->doors[i].is_open);
				game->doors[i].is_animating = true;
				game->doors[i].current_frames = 0;
				game->doors[i].start_animation = get_current_time();
			}
			return ;
		}
	}
}

void	select_door_texture(t_game *game, t_ray *ray, t_image **tex, double time)
{
	int	i;
	int	start;

	i = -1;
	while (++i < game->nb_doors)
	{
		if (game->doors[i].y == (int)ray->pos_y && \
		game->doors[i].x == (int)ray->pos_x)
		{
			if (game->doors[i].is_open == false)
				start = 0;
			else
				start = game->total_frames;
			*tex = doors_animation(game, time, i, start);
			break ;
		}
	}
}

bool	is_door_open(t_game *game, double x, double y)
{
	int	i;

	i = -1;
	while (++i < game->nb_doors)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (game->doors[i].is_open);
	}
	return (false);
}

t_image	*doors_animation(t_game *game, double time, int idx, int start)
{
	int		current_frame;
	double	elapsed_time;

	elapsed_time = time - game->doors[idx].start_animation;
	if (elapsed_time < 0)
		elapsed_time = 0;
	if (game->doors[idx].is_animating == false)
	{
		if (game->doors[idx].is_open == true)
			return (&game->door[game->total_frames - 1]);
		else
			return (&game->door[0]);
	}
	current_frame = (int)(elapsed_time / 0.1);
	if (current_frame >= game->total_frames)
	{
		current_frame = game->total_frames - 1;
		game->doors[idx].is_animating = false;
	}
	if (start == 0)
		current_frame = game->total_frames - 1 - current_frame;
	return (&game->door[current_frame]);
}
