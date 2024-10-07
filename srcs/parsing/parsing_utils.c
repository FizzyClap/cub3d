/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:50:54 by roespici          #+#    #+#             */
/*   Updated: 2024/10/07 14:51:58 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "Error: %s : ", file);
		perror("");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	fill_path(t_texture *texture, char *line)
{
	if (ft_strcmp(texture->id, "NO") == 0)
		texture->no_path = ft_strdup(line);
	else if (ft_strcmp(texture->id, "SO") == 0)
		texture->so_path = ft_strdup(line);
	else if (ft_strcmp(texture->id, "WE") == 0)
		texture->we_path = ft_strdup(line);
	else if (ft_strcmp(texture->id, "EA") == 0)
		texture->ea_path = ft_strdup(line);
	else if (ft_strcmp(texture->id, "F") == 0)
	{
		if (color_format(texture->id, line) == FAILURE)
			return (FAILURE);
		texture->floor_color = ft_strdup(line);
	}
	else if (ft_strcmp(texture->id, "C") == 0)
	{
		if (color_format(texture->id, line) == FAILURE)
			return (FAILURE);
		texture->ceiling_color = ft_strdup(line);
	}
	return (SUCCESS);
}
