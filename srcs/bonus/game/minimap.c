#include "../includes/cub3D.h"

static void		draw_tile(t_coord coord, t_image image, t_coord max, int color);
static t_coord	get_max(t_game *game, t_coord coord);

void	minimap(t_game *game)
{
	int	t;

	game->minimap.img = mlx_new_image(game->mlx, MMW, MMH);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, &t, &t, &t);
	game->ring.img = mlx_new_image(game->mlx, MMW, MMH);
	game->ring.addr = mlx_get_data_addr(game->ring.img, &t, &t, &t);
	draw_minimap(game, game->minimap);
}

void	draw_minimap(t_game *game, t_image minimap)
{
	t_coord	coord;
	t_coord	pos;

	pos.x = (int)(game->player.x) - 6;
	coord.x = 0;
	while (++pos.x < (int)(game->player.x) + 5)
	{
		pos.y = (int)(game->player.y) - 6;
		coord.y = 0;
		while (++pos.y < (int)(game->player.y) + 5)
		{
			draw_tile(coord, minimap, get_max(game, coord), \
			minimap_color(game, pos));
			if (coord.y == 0)
				coord.y += TILE - (int)((game->player.y - \
				(int)(game->player.y)) * TILE);
			else
				coord.y += TILE;
		}
		if (coord.x == 0)
			coord.x += TILE - (int)((game->player.x - \
			(int)(game->player.x)) * TILE);
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
				my_mlx_pixel_put(image, x + 20 + coord.x, y + 20 + coord.y, color);
		}
	}
}

void	my_mlx_pixel_put(t_image img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > SCREEN_WIDTH || y > SCREEN_HEIGHT)
		return ;
	dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(unsigned int *) dst = color;
}

static t_coord	get_max(t_game *game, t_coord coord)
{
	t_coord	result;

	if (coord.x == 0)
		result.x = TILE - (int)(game->player.x - (int)(game->player.x)) * TILE;
	else
		result.x = TILE;
	if (coord.y == 0)
		result.y = TILE - (int)(game->player.y - (int)(game->player.y)) * TILE;
	else
		result.y = TILE;
	return (result);
}

void	draw_ring(t_game *game)
{
	t_ring	ring;

	ring.offset.x = 20;
	ring.offset.y = 20;
	ring.center.x = ring.offset.x + MMW / 2;
	ring.center.y = ring.offset.y + MMH / 2;
	ring.radius_inner = MINIMAP_RADIUS - 5;
	ring.radius_outer = MINIMAP_RADIUS + 7;
	ring.pos.y = -1;
	while (++ring.pos.y < SCREEN_HEIGHT)
	{
		ring.pos.x = -1;
		while (++ring.pos.x < SCREEN_WIDTH)
		{
			ring.dist.x = ring.pos.x - ring.center.x;
			ring.dist.y = ring.pos.y - ring.center.y;
			ring.distance_squared = pow(ring.dist.x, 2) + pow(ring.dist.y, 2);
			if (ring.distance_squared >= pow(ring.radius_inner, 2) && \
				ring.distance_squared <= pow(ring.radius_outer, 2))
				my_mlx_pixel_put(game->raycast, ring.pos.x, ring.pos.y, 0xFFFF00);
		}
	}
}

