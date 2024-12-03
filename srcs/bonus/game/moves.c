#include "../includes/cub3D_bonus.h"

static void	check_collision(t_game *game, double x, double y);

void	move_up(t_game *game)
{
	double	x;
	double	y;

	x = game->player.posX + game->player.dirX * game->player.moveSpeed;
	y = game->player. posY + game->player.dirY * game->player.moveSpeed;
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	//if (enemy_collision(game, x, y))
		//game_over(game);
}

void	move_down(t_game *game)
{
	double	x;
	double	y;

	x = game->player.posX - game->player.dirX * game->player.moveSpeed;
	y = game->player.posY - game->player.dirY * game->player.moveSpeed;
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	//if (enemy_collision(game, x, y))
	//	game_over(game);
}

void	move_left(t_game *game)
{
	double	x;
	double	y;

	x = game->player.posX + game->player.dirX * game->player.moveSpeed;
	y = game->player. posY - game->player.dirY * game->player.moveSpeed;
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	//if (enemy_collision(game, x, y))
		//game_over(game);
}

void	move_right(t_game *game)
{
	double	x;
	double	y;

	x = game->player.posX - game->player.dirX * game->player.moveSpeed;
	y = game->player. posY + game->player.dirY * game->player.moveSpeed;
	check_collision(game, x, y);
	if (!Mix_Playing(-1))
		Mix_PlayChannel(-1, game->music->step, 0);
	//if (enemy_collision(game, x, y))
		//game_over(game);
}

static void	check_collision(t_game *game, double x, double y)
{
	int	py;
	int	px;

	py = (int)(game->player.posY);
	px = (int)(game->player.posX);
	if (x > game->player.posX && \
	ft_strchr("NSWE0", game->map->lines[py]->content[(int)(x)]))
		game->player.posX = x;
	else if (x < game->player.posX && \
	ft_strchr("NSWE0", game->map->lines[py]->content[(int)(x)]))
		game->player.posX = x;
	if (y > game->player.posY && \
	ft_strchr("NSWE0", game->map->lines[(int)(y)]->content[px]))
		game->player.posY = y;
	else if (y < game->player.posY && \
	ft_strchr("NSWE0", game->map->lines[(int)(y)]->content[px]))
		game->player.posY = y;
}
