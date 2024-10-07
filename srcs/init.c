/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:08:15 by roespici          #+#    #+#             */
/*   Updated: 2024/10/07 11:58:36 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_map(t_map *map, char *file)
{
	map->file = ft_strdup(file);
	map->lines = NULL;
	map->first_line = NULL;
	map->start_read = false;
	map->y = 0;
	map->start_x = 0;
	map->start_y = 0;
	map->count_start_pos = 0;
}

void	init_texture(t_texture *texture)
{
	texture->id = NULL;
	texture->no_path = NULL;
	texture->so_path = NULL;
	texture->we_path = NULL;
	texture->ea_path = NULL;
	texture->floor_color = NULL;
	texture->ceiling_color = NULL;
}
