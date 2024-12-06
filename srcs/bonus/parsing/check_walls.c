/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:10:36 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:10:37 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	check_map_boundaries(t_map *map, int y, int x);
static int	check_neighbors(t_map *map, int y, int x);
static int	is_wall(t_map *map, int y, int x);

int	check_walls(t_map *map, int y, int x)
{
	if (!check_map_boundaries(map, y, x) || !check_neighbors(map, y, x))
	{
		ft_fprintf(STDERR_FILENO, "Error: missing wall at (%d, %d)\n", y, x);
		return (FAILURE);
	}
	return (SUCCESS);
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

static int	check_neighbors(t_map *map, int y, int x)
{
	if (!is_wall(map, y, x) && !ft_char_iswhitespace(map->lines[y]->content[x])
		&& (x > map->lines[y - 1]->x || \
		ft_char_iswhitespace(map->lines[y]->content[x + 1]) || \
		ft_char_iswhitespace(map->lines[y]->content[x - 1]) || \
		ft_char_iswhitespace(map->lines[y + 1]->content[x]) || \
		ft_char_iswhitespace(map->lines[y - 1]->content[x]) || \
		ft_char_iswhitespace(map->lines[y + 1]->content[x + 1]) || \
		ft_char_iswhitespace(map->lines[y - 1]->content[x + 1]) || \
		ft_char_iswhitespace(map->lines[y + 1]->content[x - 1]) || \
		ft_char_iswhitespace(map->lines[y - 1]->content[x - 1])))
		return (FAILURE);
	return (SUCCESS);
}

static int	is_wall(t_map *map, int y, int x)
{
	if (map->lines[y]->content[x] == '1')
		return (SUCCESS);
	return (FAILURE);
}
