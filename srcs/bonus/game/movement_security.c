#include "../includes/cub3D.h"

static double	ray_distance(t_game *game, t_ray ray)
{
	double	angle;

	angle = game->player.angle;
	angle = ((angle * 180 / PI) - FOV / 2 + \
	FOV * (870 / (double)SCREEN_WIDTH));
	ray.pos_x = game->player.x;
	ray.pos_y =	game->player.y;
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
	perform_dda(&ray, game);
	calculate_wall_distance(&ray);
	return (ray.wall_dist);
}

static double	check_ray(t_game *game, t_ray ray)
{
	double	tmp;

	tmp = game->player.angle;
	if (ray_distance(game, ray) < 0.2)
		return (0);
	game->player.angle += PI / 4;
	if (ray_distance(game, ray) < 0.15)
	{
		game->player.angle = tmp;
		return (0);
	}
	game->player.angle = tmp;
	game->player.angle -= PI / 4;
	if (ray_distance(game, ray) < 0.15)
	{
		game->player.angle = tmp;
		return (0);
	}
	game->player.angle = tmp;
	return (ray_distance(game, ray));
}

double	check_backroom(t_game *game, int move)
{
	if (check_ray(game, game->player.cross_ray[move]) < 0.2)
		return (0);
	return (check_ray(game, game->player.cross_ray[move]));
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