#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_image img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(unsigned int *) dst = color;
}

static void	draw_tile(t_coord coord, t_image image, t_coord max, int color)
{
	int	x;
	int	y;

	if (color == 0)
		return ;
	x = -1;
	while (++x < max.x - 1 && (x + coord.x) < MML)
	{
		y = -1;
		while (++y < max.y - 1 && (y + coord.y) < MMH)
			my_mlx_pixel_put(image, x + coord.x, y + coord.y, color);
	}
}

static int	get_color(t_game *game, t_coord pos)
{
	if (pos.y > -1 && pos.x > -1 && pos.y < game->map->y && pos.x < game->map->lines[pos.y]->x)
	{
		if (game->map->lines[pos.y]->content[pos.x] == '1')
			return (BLUE);
		else
			return (WHITE);
	}
	else
		return (0);
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

static void draw_minimap(t_game *game, t_image minimap)
{
	t_coord	coord;
	t_coord	pos;

	pos.x = (int)(game->player.x) - 5;
	coord.x = 0;
	while (pos.x < (int)(game->player.x) + 5)
	{
		pos.y = (int)(game->player.y) - 5;
		coord.y = 0;
		while (pos.y < (int)(game->player.y) + 5)
		{
			draw_tile(coord, minimap, get_max(game, coord), get_color(game, pos));
			if (coord.y == 0)
				coord.y += TILE - (int)((game->player.y - (int)(game->player.y)) * TILE);
			else
				coord.y += TILE;
			pos.y++;
		}
		if (coord.x == 0)
			coord.x += TILE - (int)((game->player.x - (int)(game->player.x)) * TILE);
		else
			coord.x += TILE;
		pos.x++;
	}
}

void	minimap(t_game *game)
{
	game->minimap.img = mlx_new_image(game->mlx, MML, MMH);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, &game->\
	minimap.bpp, &game->minimap.line_len, &game->minimap.endian);
	draw_minimap(game, game->minimap);
}
