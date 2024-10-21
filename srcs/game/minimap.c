#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_image img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(unsigned int*)dst = color;
}

static void	draw_tile(t_game *game, t_coord pos, t_image minimap, char c)
{
	t_coord pixel;

	pixel.x = -1;
	while (++pixel.x < game->map->tile_x - 1)
	{
		pixel.y = -1;
		while (++pixel.y < game->map->tile_y - 1)
		{
			if (c == '1')
				my_mlx_pixel_put(minimap, pixel.x + (game->map->tile_x * pos.x), pixel.y + (game->map->tile_y * pos.y), BLUE);
			else if (ft_strchr("0NSEW", c))
				my_mlx_pixel_put(minimap, pixel.x + (game->map->tile_x * pos.x), pixel.y + (game->map->tile_y * pos.y), WHITE);
		}
	}
}

static void	draw_minimap(t_game *game, t_image minimap)
{
	t_coord	pos;

	pos.y = -1;
	while (++pos.y < game->map->y)
	{
		pos.x = -1;
		while (++pos.x < game->map->lines[pos.y]->x)
			draw_tile(game, pos, minimap, game->map->lines[pos.y]->content[pos.x]);
	}
}

void	minimap(t_game *game)
{
	game->map->tile_x = MML / game->map->x_max;
	game->map->tile_y = MMH / game->map->y;
	game->minimap.img = mlx_new_image(game->mlx, MML, MMH);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, &game->minimap.bpp, &game->minimap.line_len, &game->minimap.endian);
	draw_minimap(game, game->minimap);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 0, 0);
	//faire les mouvements
	//les associer au personnage
	//les faire bouger de tile/10 ou 20 selo la vitesse
	//faire boucler la map puis mettre a jour la position du perso
}
