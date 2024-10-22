#include "../../includes/cub3D.h"

static void	move_up(t_game *game);
static void	move_left(t_game *game);
static void	move_down(t_game *game);
static void	move_right(t_game *game);

int	keycode(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	if (keycode == W || keycode == UP)
		move_up(game);
	if (keycode == A || keycode == LEFT)
		move_left(game);
	if (keycode == S || keycode == DOWN)
		move_down(game);
	if (keycode == D || keycode == RIGHT)
		move_right(game);
	return (SUCCESS);
}

static void	move_up(t_game *game)
{
	int	x;
	int	y;

	x = (game->player.x + game->player.d_x * game->player.speed);
	y = (game->player.y + game->player.d_y * game->player.speed);
	if (game->map->lines[y]->content[x] == '1')
		return ;
	game->player.x += game->player.d_x * game->player.speed;
	game->player.y += game->player.d_y * game->player.speed;
}

static void	move_left(t_game *game)
{
	game->player.angle -= 0.05;
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	game->player.d_x = cos(game->player.angle) * 5;
	game->player.d_y = sin(game->player.angle) * 5;
}

static void	move_down(t_game *game)
{
	int	x;
	int	y;

	x = (game->player.x - game->player.d_x * game->player.speed);
	y = (game->player.y - game->player.d_y * game->player.speed);
	if (game->map->lines[y]->content[x] == '1')
		return ;
	game->player.x -= game->player.d_x * game->player.speed;
	game->player.y -= game->player.d_y * game->player.speed;
}

static void	move_right(t_game *game)
{
	game->player.angle += 0.05;
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
	game->player.d_x = cos(game->player.angle) * 5;
	game->player.d_y = sin(game->player.angle) * 5;
}
