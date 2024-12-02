#include "../includes/cub3D_bonus.h"

static void	kill_enemy(t_game *game);

double	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec + time.tv_usec / 1000000.0);
}

t_image	*doors_animation(t_game *game, int idx, int start)
{
	int		current_frame;
	double	elapsed_time;

	elapsed_time = game->time - game->doors[idx].start_animation;
	if (elapsed_time < 0)
		elapsed_time = 0;
	if (game->doors[idx].is_animating == false)
	{
		if (game->doors[idx].is_open == true)
			return (&game->door[game->doors_frames - 1]);
		else
			return (&game->door[0]);
	}
	current_frame = (int)(elapsed_time / 0.1);
	if (current_frame >= game->doors_frames)
	{
		current_frame = game->doors_frames - 1;
		game->doors[idx].is_animating = false;
	}
	if (start == 0)
		current_frame = game->doors_frames - 1 - current_frame;
	return (&game->door[current_frame]);
}

t_image	*weapon_animation(t_game *game)
{
	int		current_frame;
	double	elapsed_time;

	elapsed_time = game->time - game->anim_weapons.start_animation;
	if (elapsed_time < 0)
		elapsed_time = 0;
	if (game->anim_weapons.is_animating == false)
		return (&game->weapon[0]);
	current_frame = (int)(elapsed_time / 0.1);
	if (current_frame >= game->weapons_frames)
	{
		current_frame = game->weapons_frames - 1;
		game->anim_weapons.is_animating = false;
	}
	if (current_frame == game->weapons_frames - 1)
	{
		shoot_ray_to_center(game, false);
		kill_enemy(game);
	}
	return (&game->weapon[current_frame]);
}

static void	kill_enemy(t_game *game)
{
	t_coord	pos;
	int		target;

	target = game->target;
	if (target != -1)
	{
		pos.y = (int)game->enemy[target].y;
		pos.x = (int)game->enemy[target].x;
		Mix_PlayChannel(-1, game->music->hit, 0);
		if (game->enemy[target].texture.img)
			mlx_destroy_image(game->mlx, game->enemy[target].texture.img);
		game->enemy[target].texture.img = NULL;
		game->map->lines[pos.y]->content[pos.x] = '0';
	}
}

void	*gollum(t_game *game)
{
	int		current_frame;
	double	elapsed_time;
	double	adjusted_time;

	elapsed_time = game->time - game->launcher_start_animation;
	if (elapsed_time < 0)
		elapsed_time = 0;
	if (elapsed_time >= 4 * 0.1 && elapsed_time < (4 * 0.1 + 3.5))
		adjusted_time = 4 * 0.1;
	else if (elapsed_time >= (4 * 0.1 + 3.5))
		adjusted_time = elapsed_time - 3.5;
	else
		adjusted_time = elapsed_time;
	if (game->launcher_animation == false)
		return (game->launcher[0].img);
	current_frame = (int)(adjusted_time / 0.1);
	if (current_frame >= game->launcher_frames)
	{
		current_frame = game->launcher_frames - 1;
		game->launcher_animation = false;
	}
	return (game->launcher[current_frame].img);
}

