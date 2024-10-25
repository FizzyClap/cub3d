#include "../../includes/cub3D.h"

static void	move_left(t_game *game);
static void	move_right(t_game *game);

int	keycode(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	if (keycode == W || keycode == UP)
		move_up(game);
	if (keycode == A)
		move_left(game);
	if (keycode == S || keycode == DOWN)
		move_down(game);
	if (keycode == D)
		move_right(game);
	if (keycode == RIGHT)
		right_cam(game, 970);
	if (keycode == LEFT)
		left_cam(game, 950);
	return (SUCCESS);
}

void	move_up(t_game *game)
{
	int	x;
	int	y;

	x = (game->player.x + game->player.d_x * (game->player.speed * 2));
	y = (game->player.y + game->player.d_y * (game->player.speed * 2));
	if (check_backroom(game, x, y) == FAILURE)
	{
		check_move(game);
		return ;
	}
	refresh_position(game, MOVE, game->player.speed);
	if (game->player.speed < 0.01)
		game->player.speed += 0.0005;
}

void	move_down(t_game *game)
{
	int	x;
	int	y;

	game->player.angle -= PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = (game->player.x - game->player.d_x * game->player.speed);
	y = (game->player.y - game->player.d_y * game->player.speed);
	if (check_backroom(game, x, y) == FAILURE)
		check_move(game);
	move_up(game);
	game->player.angle += PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
}

static void	move_left(t_game *game)
{
	int	x;
	int	y;

	game->player.angle -= (PI / 2);
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = (game->player.x - game->player.d_x * game->player.speed);
	y = (game->player.y - game->player.d_y * game->player.speed);
	if (check_backroom(game, x, y) == FAILURE)
		check_move(game);
	move_up(game);
	game->player.angle += (PI / 2);
	correct_angle(game);
	refresh_position(game, DELTA, 0);
}

static void	move_right(t_game *game)
{
	int	x;
	int	y;

	game->player.angle += (PI / 2);
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = (game->player.x - game->player.d_x * game->player.speed);
	y = (game->player.y - game->player.d_y * game->player.speed);
	if (check_backroom(game, x, y) == FAILURE)
		check_move(game);
	move_up(game);
	game->player.angle -= (PI / 2);
	correct_angle(game);
	refresh_position(game, DELTA, 0);
}
