#include "../includes/cub3D.h"

void	move_up(t_game *game)
{
	if (check_backroom(game, MOVEUP) < 0.2)
	{
		check_move(game, MOVEUP);
		return ;
	}
	refresh_position(game, MOVE, game->player.speed / game->player.move_div);
	if (game->player.speed < 0.01)
		game->player.speed += 0.0005;
}

void	move_down(t_game *game)
{
	game->player.angle -= PI;
	correct_angle(game);
	if (check_backroom(game, MOVEUP) < 0.2)
	{
		check_move(game, MOVEUP);
		game->player.angle += PI;
		correct_angle(game);
		return ;
	}
	refresh_position(game, DELTA, 0);
	refresh_position(game, MOVE, game->player.speed / game->player.move_div);
	game->player.angle += PI;
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	if (game->player.speed < 0.01)
		game->player.speed += 0.0005;
}

void	move_left(t_game *game)
{
	game->player.angle -= (D_PI);
	correct_angle(game);
	if (check_backroom(game, MOVEUP) < 0.2)
	{
		check_move(game, MOVEUP);
		game->player.angle += (D_PI);
		correct_angle(game);
		return ;
	}
	refresh_position(game, DELTA, 0);
	refresh_position(game, MOVE, game->player.speed / game->player.move_div);
	game->player.angle += (D_PI);
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	if (game->player.speed < 0.01)
		game->player.speed += 0.0005;
}

void	move_right(t_game *game)
{
	game->player.angle += (D_PI);
	correct_angle(game);
	if (check_backroom(game, MOVEUP) < 0.2)
	{
		check_move(game, MOVEUP);
		game->player.angle -= (D_PI);
		correct_angle(game);
		return ;
	}
	refresh_position(game, DELTA, 0);
	refresh_position(game, MOVE, game->player.speed / game->player.move_div);
	game->player.angle -= (D_PI);
	correct_angle(game);
	refresh_position(game, DELTA, 0);
	if (game->player.speed < 0.01)
		game->player.speed += 0.0005;
}
