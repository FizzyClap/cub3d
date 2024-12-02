#include "../includes/cub3D_bonus.h"

static void	free_character(t_player player);

int	close_game(t_game *game)
{
	free_image(game);
	free_launcher_image(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_character(game->player);
	free_map(game->map);
	free_sound(game);
	free(game->door);
	free(game);
	exit(EXIT_SUCCESS);
}

int	close_launcher(t_game *game)
{
	free_launcher_image(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free(game->map);
	free_sound(game);
	free(game);
	exit(EXIT_SUCCESS);
}

static void	free_character(t_player player)
{
	free(player.action);
	free(player.cross_ray);
}
