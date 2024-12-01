#include "../includes/cub3D.h"

int	load_textures(t_game *game)
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
