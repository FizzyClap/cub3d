#include "../includes/cub3D_bonus.h"

static void	paint_cursor(t_game *game);

void	player_init(t_game *game)
{
	int	i;

	game->oldTime = 0;
	paint_cursor(game);
	game->player.posX = (double)game->map->start_x + 0.5;
	game->player.posY = (double)game->map->start_y + 0.5;  //x and y start position
	game->player.dirX = 1;
	game->player.dirY = 0; //initial direction vector
	game->player.planeX = 0;
	game->player.planeY = 0.66; //the 2d raycaster version of camera plane
	i = -1;
	game->player.action = malloc(sizeof(int) * 4);
	while (++i < 4)
		game->player.action[i] = 0;
	game->player.rotSpeed = 0.1;
	game->player.moveSpeed = 0.1;
	game->player.z = 0;
	game->player.h = 0;
	game->player.jump = false;
	game->player.crouch = false;
	game->player.move_div = 0;
}

static void	paint_cursor(t_game *game)
{
	t_coord	paint;

	game->player.cursor.img = mlx_new_image(game->mlx, 5, 5);
	game->player.cursor.addr = mlx_get_data_addr(game->player.cursor.img, \
	&game->player.cursor.bpp, &game->player.cursor.line_len, &game->\
	player.cursor.endian);
	paint.x = -1;
	while (++paint.x < 5)
	{
		paint.y = -1;
		while (++paint.y < 5)
			my_mlx_pixel_put(&game->player.cursor, paint.x, paint.y, RED);
	}
}
