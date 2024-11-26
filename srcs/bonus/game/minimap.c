#include "../includes/cub3D.h"

static void		draw_tile(t_coord coord, t_image image, t_coord max, int color);
static t_coord	get_max(t_game *game, t_coord coord);

void	minimap(t_game *game)
{
	int	t;

	game->minimap.img = mlx_new_image(game->mlx, MMW, MMH);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, &t, &t, &t);
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
				my_mlx_pixel_put(&image, x + 20 + coord.x, y + 20 + coord.y, color);
		}
	}
}

int is_color_close_to_magenta(int color, int tolerance)
{
	t_color	magenta;
	t_color	col;
	col.r = (color >> 16) & 0xFF;
	col.g = (color >> 8) & 0xFF;
	col.b = color & 0xFF;

	magenta.r = 0xFC;
	magenta.g = 0x00;
	magenta.b = 0xFF;

	if (abs(col.r - magenta.r) <= tolerance && \
		abs(col.g - magenta.g) <= tolerance && \
		abs(col.b - magenta.b) <= tolerance)
		return (1);
	return (0);
}


void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > SCREEN_WIDTH || y > SCREEN_HEIGHT)
		return ;
	if (is_color_close_to_magenta(color, 100))
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
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
