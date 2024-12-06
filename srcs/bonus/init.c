/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:10:57 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:10:59 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	init_colors(t_game *game, t_texture *texture);

void	init_map(t_map *map, char *file)
{
	map->file = ft_strdup(file);
	map->lines = NULL;
	map->first_line = NULL;
	map->start_read = false;
	map->end_read = false;
	map->y = 0;
	map->start_x = 0;
	map->start_y = 0;
	map->count_start_pos = 0;
}

void	init_texture(t_texture *texture)
{
	texture->id = NULL;
	texture->north_path = NULL;
	texture->south_path = NULL;
	texture->west_path = NULL;
	texture->east_path = NULL;
	texture->floor_color = NULL;
	texture->ceiling_color = NULL;
	texture->f_textured = false;
	texture->c_textured = false;
}

void	init_game(t_game *game, t_texture *texture, t_map *map, bool launcher)
{
	int		i;

	if (launcher == false)
	{
		game->launcher_is_running = false;
		game->launcher_frames = 0;
		game->launcher = NULL;
		game->texture = texture;
		game->map = map;
		init_struct_game_sound(game);
	}
	init_doors(game);
	game->target = -1;
	game->door_idx = -1;
	game->enemy = NULL;
	game->raycast.img = NULL;
	game->minimap.img = NULL;
	game->player.cursor.img = NULL;
	game->game_over.img = NULL;
	i = -1;
	while (++i < 4)
		game->texture->image[i].img = NULL;
	game->floor_txt.img = NULL;
	game->ceil_txt.img = NULL;
	init_colors(game, texture);
}

static void	init_colors(t_game *game, t_texture *texture)
{
	if (!texture->f_textured)
	{
		get_color(&game->floor, game->texture->floor_color);
		game->floor.a = rgb_to_int(game->floor.r, game->floor.g, game->floor.b);
	}
	if (!texture->c_textured)
	{
		get_color(&game->ceiling, game->texture->ceiling_color);
		game->ceiling.a = rgb_to_int(game->ceiling.r, game->ceiling.g, \
		game->ceiling.b);
	}
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->pos_x = 2 * x / (double)SCREEN_X - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->pos_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->pos_x;
	if (ray->dir_x == 0)
		ray->delta_x = INT_MAX;
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = INT_MAX;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}
