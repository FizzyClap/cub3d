/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:05:30 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:05:32 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (game->game_over.img)
		mlx_destroy_image(game->mlx, game->game_over.img);
	if (game->floor_txt.img)
		mlx_destroy_image(game->mlx, game->floor_txt.img);
	if (game->ceil_txt.img)
		mlx_destroy_image(game->mlx, game->ceil_txt.img);
	free_images_in_tab(game);
}

static void	free_images_in_tab(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
		if (game->texture->image[i].img)
			mlx_destroy_image(game->mlx, game->texture->image[i].img);
	i = -1;
	while (++i < game->weapons_frames)
		if (game->weapon[i].img)
			mlx_destroy_image(game->mlx, game->weapon[i].img);
	i = -1;
	while (++i < game->doors_frames)
		if (game->door[i].img)
			mlx_destroy_image(game->mlx, game->door[i].img);
	i = -1;
	while (++i < game->nb_enemy)
	{
		j = -1;
		while (++j < game->enemy_frames)
			if (game->enemy[i].texture[j].img)
				mlx_destroy_image(game->mlx, game->enemy[i].texture[j].img);
		free(game->enemy[i].texture);
	}
}

void	free_launcher_image(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->launcher_frames)
		if (game->launcher[i].img)
			mlx_destroy_image(game->mlx, game->launcher[i].img);
	if (game->launcher)
		free(game->launcher);
}
