/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil_raycast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:07:26 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:14:25 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	floor_calcul(t_game *game, t_data *d, t_coord loop);
static void	render(t_game *game, t_data *d, t_coord loop, t_image texture);
static void	ceil_calcul(t_game *game, t_data *d, t_coord loop);

void	floor_raycast(t_game *game)
{
	t_data	d;
	t_coord	loop;
	t_image	floor_texture;

	floor_texture = game->floor_txt;
	loop.y = SCREEN_Y / 2 + game->player.z - 1;
	while (++loop.y < SCREEN_Y)
	{
		floor_calcul(game, &d, loop);
		loop.x = -1;
		while (++loop.x < SCREEN_X)
			render(game, &d, loop, floor_texture);
	}
}

void	ceil_raycast(t_game *game)
{
	t_data	d;
	t_coord	loop;
	t_image	ceil_texture;

	ceil_texture = game->ceil_txt;
	loop.y = -1;
	while (++loop.y < SCREEN_Y / 2 + game->player.z)
	{
		ceil_calcul(game, &d, loop);
		loop.x = -1;
		while (++loop.x < SCREEN_X)
			render(game, &d, loop, ceil_texture);
	}
}

static void	floor_calcul(t_game *game, t_data *d, t_coord loop)
{
	d->raydir_x0 = game->player.dir_x - game->player.plane_x;
	d->raydir_y0 = game->player.dir_y - game->player.plane_y;
	d->raydir_x1 = game->player.dir_x + game->player.plane_x;
	d->raydir_y1 = game->player.dir_y + game->player.plane_y;
	d->p = loop.y - SCREEN_Y / 2 - game->player.z;
	d->pos_z = 0.5 * SCREEN_Y;
	d->row_distance = d->pos_z / d->p;
	d->floor_step_x = d->row_distance * \
		(d->raydir_x1 - d->raydir_x0) / SCREEN_X;
	d->floor_step_y = d->row_distance * \
		(d->raydir_y1 - d->raydir_y0) / SCREEN_X;
	d->floor_x = game->player.pos_x + d->row_distance * d->raydir_x0;
	d->floor_y = game->player.pos_y + d->row_distance * d->raydir_y0;
}

static void	ceil_calcul(t_game *game, t_data *d, t_coord loop)
{
	d->raydir_x0 = game->player.dir_x - game->player.plane_x;
	d->raydir_y0 = game->player.dir_y - game->player.plane_y;
	d->raydir_x1 = game->player.dir_x + game->player.plane_x;
	d->raydir_y1 = game->player.dir_y + game->player.plane_y;
	d->p = SCREEN_Y / 2 + game->player.z - loop.y;
	d->pos_z = 0.5 * SCREEN_Y;
	d->row_distance = d->pos_z / d->p;
	d->floor_step_x = d->row_distance * \
		(d->raydir_x1 - d->raydir_x0) / SCREEN_X;
	d->floor_step_y = d->row_distance * \
		(d->raydir_y1 - d->raydir_y0) / SCREEN_X;
	d->floor_x = game->player.pos_x + d->row_distance * d->raydir_x0;
	d->floor_y = game->player.pos_y + d->row_distance * d->raydir_y0;
}

static void	render(t_game *game, t_data *d, t_coord loop, t_image texture)
{
	d->cell_x = (int)d->floor_x;
	d->cell_y = (int)d->floor_y;
	d->tex_x = (int)(texture.width * (d->floor_x - d->cell_x)) % \
		(texture.width - 1);
	d->tex_y = (int)(texture.height * (d->floor_y - d->cell_y)) % \
		(texture.height - 1);
	d->floor_x += d->floor_step_x;
	d->floor_y += d->floor_step_y;
	if (d->tex_x < 0 || d->tex_x >= texture.width || \
		d->tex_y < 0 || d->tex_y >= texture.height)
		return ;
	d->color = texture.color[texture.width * d->tex_y + d->tex_x];
	my_mlx_pixel_put(&game->raycast, loop.x, loop.y, d->color);
}
