#include "../includes/cub3D.h"

void	make_actions(t_game *game)
{
	if (game->player.action[MOVEUP] == 1)
		move_up(game);
	if (game->player.action[MOVEBACK] == 1)
		move_down(game);
	if (game->player.action[MOVELEFT] == 1)
		move_left(game);
	if (game->player.action[MOVERIGHT] == 1)
		move_right(game);
}

int	keyrelease(int keycode, t_game *game)
{
	if (keycode == W || keycode == UP)
		game->player.action[MOVEUP] = 0;
	if (keycode == A)
		game->player.action[MOVELEFT] = 0;
	if (keycode == S || keycode == DOWN)
		game->player.action[MOVEBACK] = 0;
	if (keycode == D)
		game->player.action[MOVERIGHT] = 0;
	if (keycode == RIGHT)
		right_cam(game, 970);
	if (keycode == LEFT)
		left_cam(game, 950);
	return (SUCCESS);
}

int	keycode(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	if (keycode == W || keycode == UP)
		game->player.action[0] = 1;
	if (keycode == A)
		game->player.action[2] = 1;
	if (keycode == S || keycode == DOWN)
		game->player.action[1] = 1;
	if (keycode == D)
		game->player.action[3] = 1;
	if (keycode == RIGHT)
		right_cam(game, 970);
	if (keycode == LEFT)
		left_cam(game, 950);
	if (keycode == SPACE && game->player.h <= 0)
	{
		game->player.crouch = false;
		game->player.jump = ft_change_bool(game->player.jump);
	}
	if (keycode == SHIFT)
	{
		game->player.jump = false;
		game->player.crouch = ft_change_bool(game->player.crouch);
	}
	return (SUCCESS);
}

void	move_up(t_game *game)
{
	double	x;
	double	y;

	x = (game->player.x + game->player.d_x * (game->player.speed * 2));
	y = (game->player.y + game->player.d_y * (game->player.speed * 2));
	if (check_backroom(game, x, y) < 0.25)
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
	double	x;
	double	y;

	game->player.angle -= PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = (game->player.x - game->player.d_x * game->player.speed);
	y = (game->player.y - game->player.d_y * game->player.speed);
	if (check_backroom(game, x, y) < 0.25)
		check_move(game);
	refresh_position(game, MOVE, game->player.speed / 2);
	game->player.angle += PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
}

void	move_left(t_game *game)
{
	double	x;
	double	y;

	game->player.angle -= (PI / 2);
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = (game->player.x - game->player.d_x * game->player.speed);
	y = (game->player.y - game->player.d_y * game->player.speed);
	if (check_backroom(game, x, y) < 0.25)
		check_move(game);
	refresh_position(game, MOVE, game->player.speed / 2);
	game->player.angle += (PI / 2);
	correct_angle(game);
	refresh_position(game, DELTA, 0);
}

void	move_right(t_game *game)
{
	double	x;
	double	y;

	game->player.angle += (PI / 2);
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	x = (game->player.x - game->player.d_x * game->player.speed);
	y = (game->player.y - game->player.d_y * game->player.speed);
	if (check_backroom(game, x, y) < 0.25)
		check_move(game);
	refresh_position(game, MOVE, game->player.speed / 2);
	game->player.angle -= (PI / 2);
	correct_angle(game);
	refresh_position(game, DELTA, 0);
}
