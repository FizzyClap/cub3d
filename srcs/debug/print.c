/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:13:53 by roespici          #+#    #+#             */
/*   Updated: 2024/10/07 15:20:14 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	print_map(t_map *map)
{
	int	i;

	i = -1;
	printf("MAP :\n");
	while (++i < map->y)
		printf("%s", map->lines[i]->content);
	printf("\n");
}

void	print_texture(t_texture *texture)
{
	printf("texture->north_path = %s\n", texture->north_path);
	printf("texture->south_path = %s\n", texture->south_path);
	printf("texture->west_path = %s\n", texture->west_path);
	printf("texture->east_path = %s\n", texture->east_path);
	printf("texture->floor_color = %s\n", texture->floor_color);
	printf("texture->ceiling_color = %s\n", texture->ceiling_color);
}
