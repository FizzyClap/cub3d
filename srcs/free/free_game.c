#include "../../includes/cub3D.h"

int	close_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->raycast.img);
	mlx_destroy_image(game->mlx, game->minimap.img);
	mlx_destroy_image(game->mlx, game->player.cursor.img);
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
