#include "../includes/cub3D.h"

static int	fill_struct_ennemy(t_game *game);

int	init_ennemy(t_game *game)
{
	int	y;
	int	x;
	int	i;

	game->nb_ennemy = 0;
	y = -1;
	while (++y < game->map->y)
	{
		x = -1;
		while (++x < game->map->lines[y]->x)
			if (game->map->lines[y]->content[x] == 'A')
				game->nb_ennemy++;
	}
	if (game->nb_ennemy == 0)
		return (SUCCESS);
	game->ennemy = malloc(sizeof(t_ennemy) * game->nb_ennemy);
	if (!game->ennemy)
		return (FAILURE);
	i = -1;
	while (++i < game->nb_ennemy)
		game->ennemy[i].texture.img = NULL;
	if (fill_struct_ennemy(game) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	fill_struct_ennemy(t_game *game)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = -1;
	while (++y < game->map->y)
	{
		x = -1;
		while (++x < game->map->lines[y]->x)
		{
			if (game->map->lines[y]->content[x] == 'A')
			{
				game->ennemy[i].x = x;
				game->ennemy[i].y = y;
				if (load_xpm(game, &game->ennemy[i].texture,
				"textures/gimli.xpm") == FAILURE)
					return (FAILURE);
				i++;
			}
		}
	}
	return (SUCCESS);
}
