#include "../includes/cub3D.h"

static double	check_ray(t_game *game, t_ray ray);
static double	ray_distance(t_game *game, t_ray ray);

double	check_backroom(t_game *game, int move)
{
	double	result;

	result = check_ray(game, game->player.cross_ray[move]);
	if (result == FAILURE)
		return (FAILURE);
	return (result);
}

static double	check_ray(t_game *game, t_ray ray)
{
	double	tmp;
	double	result;

	tmp = game->player.angle;
	result = ray_distance(game, ray);
	if (result < 0.2)
		return (FAILURE);
	game->player.angle += Q_PI;
	correct_angle(game);
	if (ray_distance(game, ray) < 0.15)
	{
		game->player.angle = tmp;
		return (FAILURE);
	}
	game->player.angle = tmp;
	game->player.angle -= Q_PI;
	correct_angle(game);
	if (ray_distance(game, ray) < 0.15)
	{
		game->player.angle = tmp;
		return (FAILURE);
	}
	game->player.angle = tmp;
	correct_angle(game);
	return (result);
}

static double	ray_distance(t_game *game, t_ray ray)
{
	double	angle;

	angle = game->player.angle;
	angle = ((angle * CENT_PI) - 30 + \
	FOV * (870 / (double)SCREEN_WIDTH));
	ray.pos_x = game->player.x;
	ray.pos_y = game->player.y;
	ray.dir_x = cos(deg_to_rad(angle));
	ray.dir_y = sin(deg_to_rad(angle));
	ray.plane_x = -ray.dir_y * FOV;
	ray.plane_y = ray.dir_x * FOV;
	ray.delta_x = fabs(1 / ray.dir_x);
	ray.delta_y = fabs(1 / ray.dir_y);
	ray.side_dist_x = 0;
	ray.side_dist_y = 0;
	ray.angle = angle;
	calculate_steps(&ray);
	perform_dda(&ray, game, false);
	calculate_wall_distance(&ray);
	return (ray.wall_dist);
}

void	jump(t_game *game)
{
	if (game->player.crouch == true)
		game->player.speed = 0.005;
	if (game->player.crouch == false && game->player.speed < 0.01)
		game->player.speed += 0.01;
	if (game->player.jump == false && game->player.h > 0)
		game->player.h -= 100;
	if (game->player.jump == true && game->player.h < 400)
		game->player.h += 100;
	if (game->player.h >= 400)
		game->player.jump = false;
	if (game->player.crouch == true && game->player.h > -250)
		game->player.h -= 50;
	if (game->player.crouch == false && game->player.h < 0)
		game->player.h += 50;
}
