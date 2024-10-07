/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:50:03 by roespici          #+#    #+#             */
/*   Updated: 2024/10/07 11:58:56 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_texture	*texture;
	t_map		*map;
	int			fd;

	if (check_arg(argc, argv) == FAILURE)
		return (FAILURE);
	texture = malloc(sizeof(t_texture));
	init_texture(texture);
	fd = read_textures(texture, argv[1]);
	if (fd == FAILURE)
		return (free_texture(texture), FAILURE);
	map = malloc(sizeof(t_map));
	init_map(map, argv[1]);
	if (read_map(map, fd) == FAILURE)
		return (free_texture(texture), free_map(map), FAILURE);
	free_texture(texture);
	free_map(map);
}
