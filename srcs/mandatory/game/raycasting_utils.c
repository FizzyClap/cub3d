/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:12:54 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:12:55 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_vertical_line(t_game *game, int x, int start, int color)
{
	int	y;
	int	end;

	if (start < 0)
		start = 0;
	end = start + 1;
	if (end >= SCREEN_Y)
		end = SCREEN_Y - 1;
	y = start - 1;
	while (++y <= end)
		my_mlx_pixel_put(&game->raycast, x, y, color);
}

void	camera_angle_distortion(t_game *game, t_ray *ray)
{
	double	camera_angle;

	camera_angle = game->player.angle - (ray->angle * PI / 180);
	if (camera_angle < 0)
		camera_angle += 2 * PI;
	if (camera_angle > 2 * PI)
		camera_angle -= 2 * PI;
	ray->projected_dist = ray->wall_dist * cos(camera_angle);
}

void	select_wall_texture(t_game *game, t_ray *ray, t_image **tex)
{
	if (ray->side == 1 && ray->step_y < 0)
		*tex = &game->texture->image[NORTH];
	else if (ray->side == 1 && ray->step_y > 0)
		*tex = &game->texture->image[SOUTH];
	else if (ray->side == 0 && ray->step_x < 0)
		*tex = &game->texture->image[WEST];
	else if (ray->side == 0 && ray->step_x > 0)
		*tex = &game->texture->image[EAST];
	if (ray->side == 0)
		(*tex)->wall_x = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		(*tex)->wall_x = ray->pos_x + ray->wall_dist * ray->dir_x;
	(*tex)->wall_x -= floor((*tex)->wall_x);
	(*tex)->x = (int)((*tex)->wall_x * (double)(*tex)->width);
	if ((!ray->side && ray->dir_x > 0) || (ray->side && ray->dir_y < 0))
		(*tex)->x = (*tex)->width - (*tex)->x - 1;
}
