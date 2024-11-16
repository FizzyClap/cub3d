#include "../includes/cub3D.h"

static void	fill_struct_doors(t_game *game);

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

void	select_door_texture(t_game *game, t_ray *ray, t_image **tex)
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
			*tex = doors_animation(game, i, start);
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