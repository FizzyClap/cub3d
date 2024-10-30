#include "../includes/cub3D.h"

static double	check_ray(t_game *game, t_ray *ray, int pos, double x, double y)
{
	double	angle;

	angle = (game->player.angle * 180 / PI) - FOV / 2 + \
	FOV * ((pos) / (double)SCREEN_WIDTH);
	ray->pos_x = x;
	ray->pos_y = y;
	ray->dir_x = cos(deg_to_rad(angle));
	ray->dir_y = sin(deg_to_rad(angle));
	ray->plane_x = -ray->dir_y * FOV;
	ray->plane_y = ray->dir_x * FOV;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->angle = angle;
	calculate_steps(ray);
	perform_dda(ray, game);
	calculate_wall_distance(ray);
	return (ray->wall_dist);
}

double	check_backroom(t_game *game, double x, double y)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (check_ray(game, ray, 0, x, y) < 0.25 || check_ray(game, ray, SCREEN_WIDTH, x, y) < 0.25)
	{
		free(ray);
		return (0);
	}
	free(ray);
	return (check_ray(game, ray, SCREEN_WIDTH / 2, x, y));
}

void	jump(t_game *game)
{
	if (game->player.crouch == true)
		game->player.speed = 0.003;
	if (game->player.jump == false && game->player.h > 0)
		game->player.h -= 40;
	if (game->player.jump == true && game->player.h < 400)
		game->player.h += 40;
	if (game->player.h >= 400)
		game->player.jump = false;
	if (game->player.crouch == true && game->player.h > -250)
		game->player.h -= 50;
	if (game->player.crouch == false && game->player.h < 0)
		game->player.h += 50;
	
}