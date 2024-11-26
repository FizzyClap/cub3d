#include "../includes/cub3D.h"

static void	free_image(t_game *game);
static void	free_character(t_player player);

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
	free_character(game->player);
	free_texture(game->texture);
	free_map(game->map);
	free(game->doors);
	free(game->door);
	free(game->enemy);
	free(game->weapon);
	free_sound(game);
	free(game);
	exit(EXIT_SUCCESS);
}

static void	free_character(t_player player)
{
	free(player.action);
	free(player.cross_ray);
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
	i = -1;
	while (++i < game->weapons_frames)
		if (game->weapon[i].img)
			mlx_destroy_image(game->mlx, game->weapon[i].img);
	if (game->launcher.img)
		mlx_destroy_image(game->mlx, game->launcher.img);
	i = -1;
	while (++i < game->doors_frames + 2)
		if (game->door[i].img)
			mlx_destroy_image(game->mlx, game->door[i].img);
	i = -1;
	while (++i < game->nb_enemy)
		if (game->enemy[i].texture.img)
			mlx_destroy_image(game->mlx, game->enemy[i].texture.img);
	if (game->ring.img)
		mlx_destroy_image(game->mlx, game->ring.img);
}
