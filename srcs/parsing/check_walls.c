/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:34:36 by roespici          #+#    #+#             */
/*   Updated: 2024/10/09 08:36:33 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	flood_fill(t_map *map, int y, int x);
static int	check_last_line(t_map *map, int y);
static int	check_neighbors(t_map *map, int y, int x);

int	check_walls(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->lines[y]->x)
		{
			if (flood_fill(map, map->start_y, map->start_x) == FAILURE)
			{
				print_map(map, true);
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

static int	flood_fill(t_map *map, int y, int x)
{
	if (x < 0 || y < 0 || !map->lines || map->lines[y]->copy[x] == '1' || \
		map->lines[y]->copy[x] == 'F')
		return (SUCCESS);
	map->lines[y]->copy[x] = 'F';
	if (!check_last_line(map, y) || !check_neighbors(map, y, x))
	{
		ft_fprintf(2, "Error: a wall is missing at (%d, %d)\n", y, x);
		return (FAILURE);
	}
	flood_fill(map, y, x + 1);
	flood_fill(map, y, x - 1);
	flood_fill(map, y + 1, x);
	flood_fill(map, y - 1, x);
	return (SUCCESS);
}

static int	check_last_line(t_map *map, int y)
{
	if (y == map->y - 1)
		return (FAILURE);
	return (SUCCESS);
}

static int	check_neighbors(t_map *map, int y, int x)
{
	if (ft_char_iswhitespace(map->lines[y]->copy[x + 1]) || \
		ft_char_iswhitespace(map->lines[y]->copy[x - 1]) || \
		ft_char_iswhitespace(map->lines[y + 1]->copy[x]) || \
		ft_char_iswhitespace(map->lines[y - 1]->copy[x]))
		return (FAILURE);
	return (SUCCESS);
}
