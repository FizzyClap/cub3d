#include "../includes/cub3D_bonus.h"

static void	free_images_in_tab(t_game *game);

void	free_texture(t_texture *texture)
{
	if (texture->id)
		free(texture->id);
	if (texture->north_path)
		free(texture->north_path);
	if (texture->south_path)
		free(texture->south_path);
	if (texture->west_path)
		free(texture->west_path);
	if (texture->east_path)
		free(texture->east_path);
	if (texture->floor_color)
		free(texture->floor_color);
	if (texture->ceiling_color)
		free(texture->ceiling_color);
	free(texture);
}

void	free_image(t_game *game)
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

void	free_launcher_image(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->launcher_frames)
		if (game->launcher[i].img)
			mlx_destroy_image(game->mlx, game->launcher[i].img);
	free(game->launcher);
}
