#include "../includes/cub3D.h"

static void	my_mlx_pixel_put(t_image img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(unsigned int*)dst = color;
}
static void	draw_tile(t_image img, int tile_x, int tile_y, char c)
{
	int	x;
	int	y;

	x = -1;
	while (++x < tile_x)
	{
		y = -1;
		while (++y < tile_y)
		{
			if (c == 'c')
				my_mlx_pixel_put(img, x, y, RED);
			if (c == 'w')
				my_mlx_pixel_put(img, x, y, BLUE);
			if (c == 'f')
				my_mlx_pixel_put(img, x, y, WHITE);
		}
	}
}

static void	put_minimap(t_game *game, t_image wall, t_image floor, t_coord tile)
{
	t_coord	coord;
	int		x;
	int		y;

	coord.y = 0;
	y = -1;
	while (++y < game->map->y)
	{
		coord.x = 0;
		x = -1;
		while (++x < game->map->lines[y]->x)
		{
			if (game->map->lines[y]->content[x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, wall.img, coord.x + x, coord.y + y);
			else if (game->map->lines[y]->content[x] != ' ')
				mlx_put_image_to_window(game->mlx, game->win, floor.img, coord.x + x, coord.y + y);
			coord.x += tile.x;
		}
		coord.y += tile.y;
	}
}

void	minimap(t_game *game)
{
	t_image	wall;
	t_image	floor;
	t_image charac;
	t_coord	tile;

	tile.x = MML / game->map->x_max;
	tile.y = MMH / game->map->y;
	wall.img = mlx_new_image(game->mlx, tile.x, tile.y);
	charac.img = mlx_new_image(game->mlx, tile.x / 10, tile.y / 10);
	wall.addr = mlx_get_data_addr(wall.img, &wall.bpp, &wall.line_len, &wall.endian);
	charac.addr = mlx_get_data_addr(charac.img, &charac.bpp, &charac.line_len, &charac.endian);
	floor.img = mlx_new_image(game->mlx, tile.x, tile.y);
	floor.addr = mlx_get_data_addr(floor.img, &floor.bpp, &floor.line_len, &floor.endian);
	draw_tile(wall, tile.x, tile.y, 'w');
	draw_tile(charac, tile.x / 10, tile.y / 10, 'c');
	draw_tile(floor, tile.x, tile.y, 'f');
	put_minimap(game, wall, floor, tile);
	get_char_pos(game, tile, charac);
	mlx_destroy_image(game->mlx, wall.img);
	mlx_destroy_image(game->mlx, floor.img);
	mlx_destroy_image(game->mlx, charac.img);
	//faire les mouvements
	//les associer au personnage
	//les faire bouger de tile/10 ou 20 selo la vitesse
	//faire boucler la map puis mettre a jour la position du perso
}