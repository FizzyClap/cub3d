/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:11:17 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:11:20 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_map(t_map *map, int fd)
{
	int	i;

	i = -1;
	ft_fprintf(fd, "MAP :\n");
	while (++i < map->y)
		ft_fprintf(fd, "%s", map->lines[i]->content);
	ft_fprintf(fd, "\n");
}

void	print_texture(t_texture *texture, int fd)
{
	ft_fprintf(fd, "texture->north_path = %s\n", texture->north_path);
	ft_fprintf(fd, "texture->south_path = %s\n", texture->south_path);
	ft_fprintf(fd, "texture->west_path = %s\n", texture->west_path);
	ft_fprintf(fd, "texture->east_path = %s\n", texture->east_path);
	ft_fprintf(fd, "texture->floor_color = %s\n", texture->floor_color);
	ft_fprintf(fd, "texture->ceiling_color = %s\n", texture->ceiling_color);
}
