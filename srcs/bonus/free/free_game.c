#include "../includes/cub3D_bonus.h"

static void	free_character(t_player player);
static void	free_image(t_game *game);
static void	free_images_in_tab(t_game *game);

int	close_game(t_game *game)
{
	free_image(game);
	free_gollum(game);
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

static void	free_character(t_player player)
{
	free(player.action);
	free(player.cross_ray);
}

static void	free_image(t_game *game)
{
	if (game->raycast.img)
		mlx_destroy_image(game->mlx, game->raycast.img);
	if (game->minimap.img)
		mlx_destroy_image(game->mlx, game->minimap.img);
	if (game->player.cursor.img)
		mlx_destroy_image(game->mlx, game->player.cursor.img);
	if (game->ring.img)
		mlx_destroy_image(game->mlx, game->ring.img);
	free_images_in_tab(game);
}

static void	free_images_in_tab(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (game->texture->image[i].img)
			mlx_destroy_image(game->mlx, game->texture->image[i].img);
	free_texture(game->texture);
	i = -1;
	while (++i < game->weapons_frames)
		if (game->weapon[i].img)
			mlx_destroy_image(game->mlx, game->weapon[i].img);
	free(game->weapon);
	i = -1;
	while (++i < game->doors_frames + 2)
		if (game->door[i].img)
			mlx_destroy_image(game->mlx, game->door[i].img);
	free(game->doors);
	i = -1;
	while (++i < game->nb_enemy)
		if (game->enemy[i].texture.img)
			mlx_destroy_image(game->mlx, game->enemy[i].texture.img);
	free(game->enemy);
}

void	free_gollum(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->launcher_frames)
		if (game->launcher[i].img)
			mlx_destroy_image(game->mlx, game->launcher[i].img);
	free(game->launcher);
}
