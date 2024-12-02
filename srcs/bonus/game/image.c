#include "../includes/cub3D_bonus.h"

static int	load_walls(t_game *game);
static int	load_doors(t_game *game, char **map);

int	load_textures(t_game *game)
{
	static char	**map = NULL;

	if (!load_walls(game) || !init_weapon(game))
		return (FAILURE);
	if (ft_strcmp(game->map_type, "moria") == 0)
	{
		if (init_enemy(game, "textures/dwarf.xpm") == FAILURE)
			return (FAILURE);
		map = create_moria_tab(game);
		if (!map)
			return (FAILURE);
	}
	else if (ft_strcmp(game->map_type, "morgul") == 0)
	{
		if (init_enemy(game, "textures/nazgul.xpm") == FAILURE)
			return (FAILURE);
		map = create_morgul_tab(game);
		if (!map)
			return (FAILURE);
	}
	if (map && load_doors(game, map) == FAILURE)
		return (FAILURE);
	if (load_xpm(game, &game->ring, "textures/ring.xpm") == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	load_walls(t_game *game)
{
	int		i;
	char	*file[4];

	file[NORTH] = game->texture->north_path;
	file[SOUTH] = game->texture->south_path;
	file[WEST] = game->texture->west_path;
	file[EAST] = game->texture->east_path;
	i = -1;
	while (++i < 4)
		if (load_xpm(game, &game->texture->image[i], file[i]) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

static int	load_doors(t_game *game, char **map)
{
	int	i;

	game->door = ft_calloc(sizeof(t_image), (game->doors_frames + 2));
	if (!game->door)
		return (FAILURE);
	i = -1;
	while (++i < game->doors_frames + 2)
		if (load_xpm(game, &game->door[i], map[i]) == FAILURE)
			return (FAILURE);
	free(map);
	return (SUCCESS);
}
