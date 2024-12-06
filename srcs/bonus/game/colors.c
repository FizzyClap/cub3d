/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:05:55 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:05:56 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	draw_floor(t_game *game, int floor_color)
{
	int	x;
	int	y;

	y = SCREEN_Y / 2 + game->player.z - 1;
	while (++y < SCREEN_Y)
	{
		x = -1;
		while (++x < SCREEN_X)
			my_mlx_pixel_put(&game->raycast, x, y, floor_color);
	}
}

void	draw_ceiling(t_game *game, int ceiling_color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_Y / 2 + game->player.z)
	{
		x = -1;
		while (++x < SCREEN_X)
			my_mlx_pixel_put(&game->raycast, x, y, ceiling_color);
	}
}

void	get_color(t_color *type, char *path)
{
	char	**rgb;

	rgb = ft_split(path, ',');
	type->r = ft_atoi(rgb[0]);
	type->g = ft_atoi(rgb[1]);
	type->b = ft_atoi(rgb[2]);
	ft_free_tab(rgb);
}

int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
