#include "../includes/cub3D.h"

// double	get_current_time(void)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);
// 	return (time.tv_sec + time.tv_usec / 1000000.0);
// }

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
			return (&game->door[game->total_frames - 1]);
		else
			return (&game->door[0]);
	}
	current_frame = (int)(elapsed_time / 0.1);
	if (current_frame >= game->total_frames)
	{
		current_frame = game->total_frames - 1;
		game->doors[idx].is_animating = false;
	}
	if (start == 0)
		current_frame = game->total_frames - 1 - current_frame;
	return (&game->door[current_frame]);
}
