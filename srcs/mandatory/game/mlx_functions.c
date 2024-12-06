/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:12:42 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:12:43 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > SCREEN_X || y > SCREEN_Y)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

int	load_xpm(t_game *game, t_image *texture, char *xpm_file)
{
	int	width;
	int	height;

	texture->img = mlx_xpm_file_to_image(game->mlx, xpm_file, &width, &height);
	if (!texture->img)
		return (FAILURE);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, \
		&texture->line_len, &texture->endian);
	texture->color = (int *)texture->addr;
	texture->width = width;
	texture->height = height;
	return (SUCCESS);
}
