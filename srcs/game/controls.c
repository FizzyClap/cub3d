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

	x = (game->player.x + game->player.d_x * (SPEED * 2));
	y = (game->player.y + game->player.d_y * (SPEED * 2));
	if (game->map->lines[y]->content[x] == '1')
	{
		check_move(game);
		return ;
	}
		refresh_position(game, MOVE, SPEED);
}

void	move_down(t_game *game)
{
	int	x;
	int	y;

	game->player.angle -= PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = (game->player.x - game->player.d_x * SPEED);
	y = (game->player.y - game->player.d_y * SPEED);
	if (game->map->lines[y]->content[x] == '1')
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
	x = (game->player.x - game->player.d_x * SPEED);
	y = (game->player.y - game->player.d_y * SPEED);
	if (game->map->lines[y]->content[x] == '1')
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
	x = (game->player.x - game->player.d_x * SPEED);
	y = (game->player.y - game->player.d_y * SPEED);
	if (game->map->lines[y]->content[x] == '1')
		check_move(game);
	move_up(game);
	game->player.angle -= (PI / 2);
	correct_angle(game);
	refresh_position(game, DELTA, 0);
}
