/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:05:48 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:05:49 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	paint_cursor(t_game *game);
static void	set_player_orientation(t_game *game);

void	player_init(t_game *game)
{
	int	i;

	game->old_time = 0;
	paint_cursor(game);
	game->player.pos_x = (double)game->map->start_x + 0.5;
	game->player.pos_y = (double)game->map->start_y + 0.5;
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
	i = -1;
	game->player.action = malloc(sizeof(int) * 4);
	while (++i < 4)
		game->player.action[i] = 0;
	game->player.rot_speed = 0.025;
	game->player.move_speed = 0.05;
	game->player.z = 0;
	game->player.h = 0;
	game->player.jump = false;
	game->player.crouch = false;
	game->player.move_div = 0;
	set_player_orientation(game);
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

static void	set_player_orientation(t_game *game)
{
	if (game->map->orientation == 'N')
	{
		while (game->player.dir_x > 0 && game->player.dir_y > -1)
			left_cam(game, 959);
	}
	else if (game->map->orientation == 'W')
	{
		while (game->player.dir_x > -1)
			left_cam(game, 959);
	}
	else if (game->map->orientation == 'S')
	{
		while (game->player.dir_x > 0 && game->player.dir_y < 1)
			right_cam(game, 961);
	}
}
