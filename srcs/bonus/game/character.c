#include "../includes/cub3D.h"

static void	paint_cursor(t_game *game);
static void	init_moves(t_game *game);

void	player_init(t_game *game)
{
	game->player.cursor.img = mlx_new_image(game->mlx, 5, 5);
	game->player.cursor.addr = mlx_get_data_addr(game->player.cursor.img, \
	&game->player.cursor.bpp, &game->player.cursor.line_len, &game->\
	player.cursor.endian);
	paint_cursor(game);
	game->player.x = game->map->start_x + 0.5;
	game->player.y = game->map->start_y + 0.5;
	if (game->map->orientation == 'N')
		game->player.angle = PI / 2;
	else if (game->map->orientation == 'S')
		game->player.angle = 3 * PI / 2;
	else if (game->map->orientation == 'E')
		game->player.angle = PI;
	else if (game->map->orientation == 'W')
		game->player.angle = 0;
	game->player.d_x = cos(game->player.angle) * 5;
	game->player.d_y = sin(game->player.angle) * 5;
	game->player.speed = 0.005;
	game->player.z = 0;
	game->player.h = 0;
	game->player.jump = false;
	game->player.crouch = false;
	game->player.move_div = 0;
	init_moves(game);
}

static void	init_moves(t_game *game)
{
	game->player.action = malloc(sizeof(int) * 4);
	game->player.action[MOVEUP] = 0;
	game->player.action[MOVEBACK] = 0;
	game->player.action[MOVELEFT] = 0;
	game->player.action[MOVERIGHT] = 0;
}

static void	paint_cursor(t_game *game)
{
	t_coord	paint;

	paint.x = -1;
	while (++paint.x < 5)
	{
		paint.y = -1;
		while (++paint.y < 5)
			my_mlx_pixel_put(game->player.cursor, paint.x, paint.y, RED);
	}
}
