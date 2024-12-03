#include "../includes/cub3D.h"

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
	// free_character(game->player);
	free(game->player.action);
	free_texture(game->texture);
	free_map(game->map);
	// free(game->doors);
	free_sound(game);
	free(game);
	exit(EXIT_SUCCESS);
}

static void	free_image(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (game->texture->image[i].img)
			mlx_destroy_image(game->mlx, game->texture->image[i].img);
	if (game->raycast.img)
		mlx_destroy_image(game->mlx, game->raycast.img);
	if (game->minimap.img)
		mlx_destroy_image(game->mlx, game->minimap.img);
	if (game->player.cursor.img)
		mlx_destroy_image(game->mlx, game->player.cursor.img);
	if (game->balrog.img)
		mlx_destroy_image(game->mlx, game->balrog.img);
	if (game->launcher.img)
		mlx_destroy_image(game->mlx, game->launcher.img);
	i = -1;
	while (++i < game->total_frames + 2)
		if (game->door[i].img)
			mlx_destroy_image(game->mlx, game->door[i].img);
}
