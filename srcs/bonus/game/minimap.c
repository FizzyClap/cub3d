/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:07:43 by roespici          #+#    #+#             */
/*   Updated: 2024/12/06 12:15:23 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void		draw_tile(t_coord coord, t_image image, t_coord max, int color);
static int		minimap_color(t_game *game, t_coord pos);
static t_coord	get_max(t_game *game, t_coord coord);

void	minimap(t_game *game)
{
	game->minimap.img = mlx_new_image(game->mlx, MMW, MMH);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, \
	&game->minimap.bpp, &game->minimap.line_len, &game->minimap.endian);
	draw_minimap(game, game->minimap);
}

void	draw_minimap(t_game *game, t_image minimap)
{
	t_coord	coord;
	t_coord	pos;

	pos.x = (int)(game->player.pos_x) - 6;
	coord.x = 0;
	while (++pos.x < (int)(game->player.pos_x) + 5)
	{
		pos.y = (int)(game->player.pos_y) - 6;
		coord.y = 0;
		while (++pos.y < (int)(game->player.pos_y) + 5)
		{
			draw_tile(coord, minimap, get_max(game, coord), \
			minimap_color(game, pos));
			if (coord.y == 0)
				coord.y += TILE - (int)((game->player.pos_y - \
				(int)(game->player.pos_y)) * TILE);
			else
				coord.y += TILE;
		}
		if (coord.x == 0)
			coord.x += TILE - (int)((game->player.pos_x - \
			(int)(game->player.pos_x)) * TILE);
		else
			coord.x += TILE;
	}
}

static void	draw_tile(t_coord coord, t_image image, t_coord max, int color)
{
	int		y;
	int		x;
	t_coord	center;
	t_coord	dist;

	if (color == 0)
		return ;
	center.x = MMW / 2;
	center.y = MMH / 2;
	y = -1;
	while (++y < max.y && (y + coord.y) < MMH)
	{
		x = -1;
		while (++x < max.x && (x + coord.x) < MMW)
		{
			dist.x = (x + coord.x) - center.x;
			dist.y = (y + coord.y) - center.y;
			if (pow(dist.x, 2) + pow(dist.y, 2) <= pow(MINIMAP_RADIUS, 2) && \
			color != rgb_to_int(135, 206, 235))
				my_mlx_pixel_put(&image, x + 20 + coord.x, y + 20 + coord.y, \
				color);
		}
	}
}

static int	minimap_color(t_game *game, t_coord pos)
{
	int	i;

	i = -1;
	if (pos.y > -1 && pos.x > -1 && pos.y < game->map->y && \
	pos.x < game->map->lines[pos.y]->x)
	{
		if (game->map->lines[pos.y]->content[pos.x] == '1')
			return (game->minimap_wall.a);
		else if (game->map->lines[pos.y]->content[pos.x] == 'D')
		{
			while (++i < game->nb_doors)
				if (game->doors[i].y == pos.y && game->doors[i].x == pos.x && \
				game->doors[i].is_open == false)
					return (game->minimap_wall.a);
			return (game->minimap_floor.a);
		}
		else
			return (game->minimap_floor.a);
	}
	else
		return (0);
}

static t_coord	get_max(t_game *game, t_coord coord)
{
	t_coord	result;

	if (coord.x == 0)
		result.x = TILE - (int)(game->player.pos_x - \
		(int)(game->player.pos_x)) * TILE;
	else
		result.x = TILE;
	if (coord.y == 0)
		result.y = TILE - (int)(game->player.pos_y - \
		(int)(game->player.pos_y)) * TILE;
	else
		result.y = TILE;
	return (result);
}
