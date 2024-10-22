#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_image img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(unsigned int *) dst = color;
}

// static void	draw_tile(t_game *game, t_coord loc, t_image minimap, char c)
// {
// 	t_coord	pixel;

// 	pixel.x = -1;
// 	while (++pixel.x < game->map->tile_x - 1)
// 	{
// 		pixel.y = -1;
// 		while (++pixel.y < game->map->tile_y - 1)
// 		{
// 			if (c == '1')
// 				my_mlx_pixel_put(minimap, pixel.x + (game->map->tile_x * \
// 				loc.x), pixel.y + (game->map->tile_y * loc.y), BLUE);
// 			else if (ft_strchr("0NSEW", c))
// 				my_mlx_pixel_put(minimap, pixel.x + (game->map->tile_x * \
// 				loc.x), pixel.y + (game->map->tile_y * loc.y), WHITE);
// 		}
// 	}
// }
static void	draw_minimap(t_game *game, t_image minimap)
{
	t_coord	pixel;
	double	x;
	double	y;

	pixel.x = -1;
	x = game->player.x - 5;
	while (++pixel.x < MML)
	{
		x += 1;
		y = game->player.y - 5;
		pixel.y = -1;
		while (++pixel.y < MMH)
		{
			y += 1;
			if (y > -1 && x > -1 && y < game->map->y && x < game->map->lines[(int)y]->x)
			{
				printf("pix x = %i, pix y = %i\n", pixel.x, pixel.y);
				if (game->map->lines[(int)y]->content[(int)x] == '1')
					my_mlx_pixel_put(minimap, pixel.x, pixel.y, BLUE);
				else if (ft_strchr("0NSEW", game->map->lines[(int)y]->content[(int)x]))
					my_mlx_pixel_put(minimap, pixel.x, pixel.y, WHITE);
			}
		}
	}
}
// static void	draw_minimap(t_game *game, t_image minimap)
// {
// 	t_coord	pos;
// 	t_coord	check;
// 	t_coord	loc;

// 	loc.y = -1;
// 	pos.y = (game->player.y) - 5;
// 	// if (pos.y < 0)
// 		// pos.y = 0;
// 	check.y = pos.y + 10; 
// 	while (++pos.y < check.y)
// 	{
// 		++loc.y;
// 		loc.x = -1;
// 		pos.x = (game->player.x) - 5;
// 		// if (pos.x < 0)
// 			// pos.x = 0;
// 		check.x = pos.x + 10;
// 		while (++pos.x < check.x)
// 		{
// 			++loc.x;
// 			if (pos.y > -1 && pos.x > -1 && pos.y < game->map->y && pos.x < game->map->lines[pos.y]->x)
// 			{
// 				draw_tile(game, loc, minimap, game->map->lines[pos.y]->\
// 				content[pos.x]);
// 			}
// 		}
// 	}
// }

void	minimap(t_game *game)
{
	game->map->tile_x = 20;
	game->map->tile_y = 20;
	game->minimap.img = mlx_new_image(game->mlx, MML, MMH);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, &game->\
	minimap.bpp, &game->minimap.line_len, &game->minimap.endian);
	draw_minimap(game, game->minimap);
}
