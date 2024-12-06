/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:05:25 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:05:27 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	free_map(t_map *map)
{
	int	y;

	free(map->file);
	free(map->first_line);
	if (map->lines)
	{
		y = -1;
		while (++y < map->y)
		{
			free(map->lines[y]->content);
			free(map->lines[y]);
		}
		free(map->lines);
	}
	free(map);
}
