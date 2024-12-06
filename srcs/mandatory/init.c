/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:13:26 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:13:28 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
}

void	init_game(t_game **game, t_texture *texture, t_map *map)
{
	int		i;

	*game = malloc(sizeof(t_game));
	(*game)->win = NULL;
	(*game)->texture = texture;
	(*game)->map = map;
	(*game)->raycast.img = NULL;
	(*game)->minimap.img = NULL;
	(*game)->player.cursor.img = NULL;
	i = -1;
	while (++i < 4)
		(*game)->texture->image[i].img = NULL;
	get_color(&(*game)->floor, (*game)->texture->floor_color);
	get_color(&(*game)->ceiling, (*game)->texture->ceiling_color);
	(*game)->ceiling.a = rgb_to_int((*game)->ceiling.r, \
	(*game)->ceiling.g, (*game)->ceiling.b);
	(*game)->floor.a = rgb_to_int((*game)->floor.r, \
	(*game)->floor.g, (*game)->floor.b);
}

void	init_ray(t_ray *ray, t_game *game, double angle)
{
	ray->pos_x = game->player.x;
	ray->pos_y = game->player.y;
	ray->dir_x = cos(deg_to_rad(angle));
	ray->dir_y = sin(deg_to_rad(angle));
	ray->plane_x = -ray->dir_y * FOV;
	ray->plane_y = ray->dir_x * FOV;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->angle = angle;
}

double	deg_to_rad(double degrees)
{
	return (degrees * PI / 180);
}
