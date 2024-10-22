#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_image img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(unsigned int *) dst = color;
}

static void	y_mlx_pixel_put(t_image img, int x, int y, int color)
{
	char	*dst;

	printf("x = %d, y = %d\n", x, y);
	dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(unsigned int *) dst = color;
}

// static void	draw_tile(t_game *game, t_coord loc, t_image minimap, char c, int offset_x, int offset_y)
// {
// 	t_coord	pixel;

// 	pixel.x = -1;
// 	while (++pixel.x < offset_x - 1)
// 	{
// 		pixel.y = -1;
// 		while (++pixel.y < offset_y - 1)
// 		{
// 			if (c == '1')
// 				y_mlx_pixel_put(minimap, (pixel.x) + (offset_x * loc.x), (pixel.y) + (offset_y * loc.y), BLUE);
// 			else if (ft_strchr("0NSEW", c))
// 				y_mlx_pixel_put(minimap, (pixel.x) + (offset_x * loc.x), (pixel.y) + (offset_y * loc.y), WHITE);
// 		}
// 	}
// }

// static void	draw_minimap(t_game *game, t_image minimap)
// {
// 	t_coord	pos;
// 	t_coord	check;
// 	t_coord	loc;
// 	int		offset_x;
// 	int		offset_y;

// 	offset_x = (game->player.x - floor(game->player.x)) * game->map->tile_x;
// 	offset_y = (game->player.y - floor(game->player.y)) * game->map->tile_y;

// 	loc.y = -1;
// 	pos.y = (game->player.y) - 5;
// 	check.y = pos.y + 10;
// 	while (++pos.y < check.y)
// 	{
// 		++loc.y;
// 		loc.x = -1;
// 		pos.x = (game->player.x) - 5;
// 		check.x = pos.x + 10;
// 		while (++pos.x < check.x)
// 		{
// 			if (pos.x > 0)
// 				offset_x = 20;
// 			if (pos.y > 0)
// 				offset_y = 20;
// 			if (pos.x == 9)
// 				offset_x = 20 - ((game->player.x - floor(game->player.x)) * game->map->tile_x);
// 			if (pos.y == 9)
// 				offset_y = 20 - ((game->player.y - floor(game->player.y)) * game->map->tile_y);
// 			++loc.x;
// 			if (pos.y > -1 && pos.x > -1 && pos.y < game->map->y && pos.x < game->map->lines[pos.y]->x)
// 			{
// 				draw_tile(game, loc, minimap, game->map->lines[pos.y]->\
// 				content[pos.x], offset_x, offset_y);
// 			}
// 		}
// 	}
// }

static void	draw_tile(t_coord check, t_image image, t_coord max, int color)
{
	int	x;
	int	y;

	if (color == 0)
		return ;
	x = -1;
	while (++x < max.x && x < MML)
	{
		y = -1;
		while (++y < max.y && y < MMH)
			y_mlx_pixel_put(image, x + (TILE * check.x), y + (TILE * check.y), color);
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
		result.x = (game->player.x - floor(game->player.x)) * TILE;
	else
		result.x = TILE;	
	if (coord.y == 0)
		result.y = (game->player.y - floor(game->player.y)) * TILE;
	else
		result.y = TILE;
	return (result);
		
}

static void draw_minimap(t_game *game, t_image minimap)
{
	t_coord	coord;
	t_coord	pos;
	t_coord	check;

	pos.x = floor(game->player.x) - 4;
	check.x = 0;
	coord.x = 0;
	while (check.x < 10)
	{
		pos.y = floor(game->player.y) - 4;
		check.y = 0;
		coord.y = 0;
		while (check.y < 10)
		{
			// printf("x = %d, y = %d\n", coord.x, coord.y);
			draw_tile(check, minimap, get_max(game, coord), get_color(game, pos));
			if (coord.y == 0)
				coord.y += (int)((game->player.y - floor(game->player.y)) * TILE);
			else
				coord.y += TILE;
			pos.y++;
			check.y++;
		}
		if (coord.x == 0)
			coord.x += (int)((game->player.x - floor(game->player.x)) * TILE);
		else
			coord.x += TILE;
		pos.x++;
		check.x++;
	}
}

void	minimap(t_game *game)
{
	game->minimap.img = mlx_new_image(game->mlx, MML, MMH);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, &game->\
	minimap.bpp, &game->minimap.line_len, &game->minimap.endian);
	draw_minimap(game, game->minimap);
}
