#include "../../includes/cub3D.h"

int	load_textures(t_game *game)
{
	int		width;
	int		height;
	int		i;
	char	*file;

	i = -1;
	while (++i < 4)
	{
		if (i == 0)
			file = ft_strdup(game->texture->north_path);
		else if (i == 1)
			file = ft_strdup(game->texture->south_path);
		else if (i == 2)
			file = ft_strdup(game->texture->west_path);
		else if (i == 3)
			file = ft_strdup(game->texture->east_path);
		printf("file = %s\n", file);
		game->texture[i].image.img = mlx_xpm_file_to_image(game->mlx, file, \
			&width, &height);
		if (!game->texture[i].image.img)
			return (FAILURE);
		game->texture[i].image.color = \
			(int *)mlx_get_data_addr(game->texture[i].image.img, \
			&game->texture[i].image.bpp, &game->texture[i].image.line_len, \
			&game->texture[i].image.endian);
		free(file);
	}
	return (SUCCESS);
}
