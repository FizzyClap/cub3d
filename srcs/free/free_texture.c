/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:27:00 by roespici          #+#    #+#             */
/*   Updated: 2024/10/07 11:59:33 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_texture(t_texture *texture)
{
	if (texture->id)
		free(texture->id);
	if (texture->no_path)
		free(texture->no_path);
	if (texture->so_path)
		free(texture->so_path);
	if (texture->we_path)
		free(texture->we_path);
	if (texture->ea_path)
		free(texture->ea_path);
	if (texture->floor_color)
		free(texture->floor_color);
	if (texture->ceiling_color)
		free(texture->ceiling_color);
	free(texture);
}
