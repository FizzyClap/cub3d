/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:11:30 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:11:31 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
