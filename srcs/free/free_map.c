/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:20:38 by roespici          #+#    #+#             */
/*   Updated: 2024/10/07 11:51:00 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
