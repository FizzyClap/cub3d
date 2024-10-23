#include "../../includes/cub3D.h"

int	load_textures(t_game *game)
{
	int	height;
	int	width;

	game->img_wall[0] = mlx_xpm_file_to_image(game->mlx, "wall1.xpm", &width, &height);
	game->img_wall[1] = mlx_xpm_file_to_image(game->mlx, "wall2.xpm", &width, &height);
	if (!game->img_wall[0] || !game->img_wall[1])
		return (FAILURE);
	return (SUCCESS);
}
