/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:50:03 by roespici          #+#    #+#             */
/*   Updated: 2024/10/10 08:57:05 by roespici         ###   ########.fr       */
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
	print_map(map, STDOUT_FILENO);
	print_texture(texture, STDOUT_FILENO);
	free_texture(texture);
	free_map(map);
}
