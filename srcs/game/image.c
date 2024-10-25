#include "../../includes/cub3D.h"

int	load_textures(t_game *game)
{
	int		width;
	int		height;
	int		i;
	char	*file[4];

	file[NORTH] = game->texture->north_path;
	file[SOUTH] = game->texture->south_path;
	file[WEST] = game->texture->west_path;
	file[EAST] = game->texture->east_path;
	i = -1;
	while (++i < 4)
	{
		game->texture->image[i].img = mlx_xpm_file_to_image(game->mlx, file[i],
				&width, &height);
		if (!game->texture->image[i].img)
			return (FAILURE);
		game->texture->image[i].color = \
			(int *)mlx_get_data_addr(game->texture->image[i].img, \
			&game->texture->image[i].bpp, &game->texture->image[i].line_len, \
			&game->texture->image[i].endian);
		game->texture->image[i].width = width;
		game->texture->image[i].height = height;
	}
	return (SUCCESS);
}
