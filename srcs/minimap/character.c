#include "../includes/cub3D.h"

void	player_init(t_game *game)
{
	t_coord	paint;

	game->player.cursor.img = mlx_new_image(game->mlx, 5, 5);
	game->player.cursor.addr = mlx_get_data_addr(game->player.cursor.img, \
	&game->player.cursor.bpp, &game->player.cursor.line_len, &game->player.cursor.endian);
	paint.x = -1;
	while (++paint.x < 5)
	{
		paint.y = -1;
		while (++paint.y < 5)
			my_mlx_pixel_put(game->player.cursor, paint.x, paint.y, RED);
	}
	game->player.x = game->map->start_x * game->map->tile_x;
	game->player.y = game->map->start_y * game->map->tile_y;
}
