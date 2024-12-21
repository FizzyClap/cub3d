/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:08:34 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:08:35 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	calcul_sprites(t_game *game, t_data *d, int i);
static int	render_sprites(t_game *game, t_data *d, t_image *current);

void	sort_enemies(t_game *game)
{
	int		i;
	int		j;
	t_enemy	temp;

	i = -1;
	while (++i < game->nb_enemy)
	{
		game->enemy[i].distance = pow(game->player.pos_x - game->enemy[i].x, 2) \
		+ pow(game->player.pos_y - game->enemy[i].y, 2);
	}
	i = -1;
	while (++i < game->nb_enemy)
	{
		j = -1;
		while (++j < game->nb_enemy - i - 1)
		{
			if (game->enemy[j].distance < game->enemy[j + 1].distance)
			{
				temp = game->enemy[j];
				game->enemy[j] = game->enemy[j + 1];
				game->enemy[j + 1] = temp;
			}
		}
	}
}

void	render_enemies(t_game *game)
{
	t_data		d;
	int			i;
	t_coord		pos;
	t_image		*current;

	i = -1;
	while (++i < game->nb_enemy)
	{
		if (!game->enemy[i].texture[0].img)
			continue ;
		pos.x = game->enemy[i].x;
		pos.y = game->enemy[i].y;
		current = enemy_animation(game, i, pos);
		if (!current || !current->img)
			return ;
		if (calcul_sprites(game, &d, i) == FAILURE)
			continue ;
		while (++d.stripe < d.draw_end_x)
			if (render_sprites(game, &d, current) == FAILURE)
				continue ;
	}
}

static int	calcul_sprites(t_game *game, t_data *d, int i)
{
	d->sprite_x = game->enemy[i].x - game->player.pos_x;
	d->sprite_y = game->enemy[i].y - game->player.pos_y;
	d->inv_det = 1.0 / (game->player.plane_x * game->player.dir_y - \
	game->player.dir_x * game->player.plane_y);
	d->transform_x = d->inv_det * (game->player.dir_y * d->sprite_x - \
	game->player.dir_x * d->sprite_y);
	d->transform_y = d->inv_det * (-game->player.plane_y * d->sprite_x + \
	game->player.plane_x * d->sprite_y);
	if (d->transform_y <= 0)
		return (FAILURE);
	d->sprite_screen_x = (int)((SCREEN_X / 2) * (1 + d->transform_x / \
	d->transform_y));
	d->sprite_height = abs((int)(SCREEN_Y / d->transform_y));
	d->sprite_width = d->sprite_height;
	d->draw_start_y = -d->sprite_height / 2 + SCREEN_Y / 2;
	d->draw_end_y = d->sprite_height / 2 + SCREEN_Y / 2;
	d->draw_start_x = -d->sprite_width / 2 + d->sprite_screen_x;
	d->draw_end_x = d->sprite_width / 2 + d->sprite_screen_x;
	d->stripe = d->draw_start_x - 1;
	return (SUCCESS);
}

static int	render_sprites(t_game *game, t_data *d, t_image *current)
{
	int	y;

	if (d->stripe >= 0 && d->stripe < SCREEN_X && \
		d->transform_y < game->z_buffer[d->stripe])
	{
		d->tex_x = (int)((d->stripe - (-d->sprite_width / 2 + \
		d->sprite_screen_x)) * current->width / d->sprite_width);
		y = d->draw_start_y - 1;
		while (++y < d->draw_end_y)
		{
			if (y < 0 || y >= SCREEN_Y)
				return (FAILURE);
			d->tex_y = (int)((y - (-d->sprite_height / 2 + SCREEN_Y / 2)) * \
			current->height / d->sprite_height);
			d->color = current->color[d->tex_y * current->width + d->tex_x];
			my_mlx_pixel_put(&game->raycast, d->stripe, y + game->player.z, \
			d->color);
		}
	}
	return (SUCCESS);
}
