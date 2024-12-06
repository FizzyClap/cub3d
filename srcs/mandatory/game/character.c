/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:11:51 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:12:06 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	paint_cursor(t_game *game);
static void	init_moves(t_game *game);

void	player_init(t_game *game)
{
	paint_cursor(game);
	game->player.x = game->map->start_x + 0.5;
	game->player.y = game->map->start_y + 0.5;
	if (game->map->orientation == 'N')
		game->player.angle = 3 * D_PI;
	else if (game->map->orientation == 'S')
		game->player.angle = D_PI;
	else if (game->map->orientation == 'E')
		game->player.angle = PI;
	else if (game->map->orientation == 'W')
		game->player.angle = 0;
	game->player.plane_x = -0.66 * sin(game->player.angle);
	game->player.plane_y = 0.66 * cos(game->player.angle);
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
	game->player.move_speed = 0.05;
	game->player.z = 0;
	game->player.h = 0;
	game->player.jump = false;
	game->player.crouch = false;
	game->player.move_div = 0;
	init_moves(game);
}

static void	init_moves(t_game *game)
{
	int	i;

	i = -1;
	game->player.action = malloc(sizeof(int) * 4);
	while (++i < 4)
		game->player.action[i] = 0;
	game->player.cross_ray = malloc(sizeof(t_ray));
}

static void	paint_cursor(t_game *game)
{
	t_coord	paint;

	game->player.cursor.img = mlx_new_image(game->mlx, 5, 5);
	game->player.cursor.addr = mlx_get_data_addr(game->player.cursor.img, \
	&game->player.cursor.bpp, &game->player.cursor.line_len, &game->\
	player.cursor.endian);
	paint.x = -1;
	while (++paint.x < 5)
	{
		paint.y = -1;
		while (++paint.y < 5)
			my_mlx_pixel_put(&game->player.cursor, paint.x, paint.y, RED);
	}
}
