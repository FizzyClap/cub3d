/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:34:36 by roespici          #+#    #+#             */
/*   Updated: 2024/10/07 11:31:01 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	is_wall(t_map *map, int y, int x);
static int	check_map_boundaries(t_map *map, int y, int x);
static int	check_spaces(t_map *map, int y, int x);

int	check_walls(t_map *map, int y, int x)
{
	if (!check_map_boundaries(map, y, x) || !check_spaces(map, y, x))
	{
		ft_fprintf(2, "Error: missing wall at (%d, %d)\n", y, x);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	is_wall(t_map *map, int y, int x)
{
	return (!ft_char_iswhitespace(map->lines[y]->content[x]) && \
			map->lines[y]->content[x] == '1');
}

static int	check_map_boundaries(t_map *map, int y, int x)
{
	if (!is_wall(map, y, 0) && !ft_char_iswhitespace(map->lines[y]->content[0]))
		return (FAILURE);
	if ((y == 0 || y == map->y - 1) && !is_wall(map, y, x) && \
		!ft_char_iswhitespace(map->lines[y]->content[x]))
		return (FAILURE);
	return (SUCCESS);
}

static int	check_spaces(t_map *map, int y, int x)
{
	while (ft_char_iswhitespace(map->lines[y]->content[x]))
		x++;
	if ((x > 0 && ft_char_iswhitespace(map->lines[y]->content[x - 1]) && \
		map->lines[y]->content[x] != '1'))
		return (FAILURE);
	if ((ft_char_iswhitespace(map->lines[y]->content[x + 1]) && \
		map->lines[y]->content[x] != '1'))
		return (FAILURE);
	return (SUCCESS);
}
