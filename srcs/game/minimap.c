#include "../includes/cub3D.h"

static void		draw_tile(t_coord coord, t_image image, t_coord max, int color);
static t_coord	get_max(t_game *game, t_coord coord);

void	minimap(t_game *game)
{
	game->minimap.img = mlx_new_image(game->mlx, MMW, MMH);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, &game->\
	minimap.bpp, &game->minimap.line_len, &game->minimap.endian);
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
	int	x;
	int	y;

	if (color == 0)
		return ;
	x = -1;
	while (++x < max.x && (x + coord.x) < MMW)
	{
		y = -1;
		while (++y < max.y && (y + coord.y) < MMH)
			my_mlx_pixel_put(image, x + coord.x, y + coord.y, color);
	}
}

void	my_mlx_pixel_put(t_image img, int x, int y, int color)
{
	char	*dst;

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
