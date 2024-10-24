#include "../../includes/cub3D.h"

static void	free_image(t_game *game);

int	close_game(t_game *game)
{
	free_image(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_texture(game->texture);
	free_map(game->map);
	free(game);
	exit(EXIT_SUCCESS);
}

static void	free_image(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(game->mlx, game->texture->image[i].img);
	mlx_destroy_image(game->mlx, game->raycast.img);
	mlx_destroy_image(game->mlx, game->minimap.img);
	mlx_destroy_image(game->mlx, game->player.cursor.img);
}
