#include "../includes/cub3D.h"

static int	ft_charinstr(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (SUCCESS);
	}
	return (FAILURE);
}

void	get_char_pos(t_game *game, t_coord tile, t_image charac)
{
	t_coord	coord;
	float	x;
	float	y;

	coord.y = -1;
	y = 0;
	while (++coord.y < game->map->y)
	{
		coord.x = -1;
		x = 0;
		while (++coord.x < game->map->lines[coord.y]->x)
		{
			if (ft_charinstr("NSEW", game->map->lines[coord.y]->content[coord.x]) == SUCCESS)
			{
				mlx_put_image_to_window(game->mlx, game->win, charac.img, \
				x + ((float)tile.x + coord.x) / 2, y + ((float)tile.y + coord.y) / 2);
			}
			x += tile.x;
		}
		y += tile.y;
	}
}
