#include "../includes/cub3D.h"

double	deg_to_rad(double degrees)
{
	return (degrees * PI / 180);
}

void	init_ray(t_ray *ray, t_game *game, double angle)
{
	ray->pos_x = game->player.x;
	ray->pos_y = game->player.y;
	ray->dir_x = cos(deg_to_rad(angle)); //direction du rayon x
	ray->dir_y = sin(deg_to_rad(angle)); //direction du rayon y
	ray->plane_x = -ray->dir_y * FOV; //plan de la camera x
	ray->plane_y = ray->dir_x * FOV; //plan de la camera y
	ray->delta_x = fabs(1 / ray->dir_x); //distance entre chaque pas x
	ray->delta_y = fabs(1 / ray->dir_y); //distance entre chaque pas y
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->angle = angle;
}

void	calculate_steps(t_ray *ray)
{
	//step = direction du rayon
	//side dist = distance du rayon jusqu'a la premiere ligne dans la grille
	if (ray->dir_x < 0) //rayon vers la gauche
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - floor(ray->pos_x)) * ray->delta_x;
		//distance jusqu'a la premiere ligne verticale a gauche
	}
	else
	{
		ray->step_x = 1; //rayon vers la droite
		ray->side_dist_x = (floor(ray->pos_x + 1) - ray->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0) //rayon vers le haut
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - floor(ray->pos_y)) * ray->delta_y;
		//distance jusqu'a la premiere ligne horizontale vers le haut
	}
	else //rayon vers le bas
	{
		ray->step_y = 1;
		ray->side_dist_y = (floor(ray->pos_y + 1) - ray->pos_y) * ray->delta_y;
	}
}

void	perform_dda(t_ray *ray, t_game *game)
{
	int	hit;

	//deplacement le long d'un rayon jusqu'a renconter un mur
	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y) //rayon traverse une ligne verticale d'abord
		{
			ray->side_dist_x += ray->delta_x;
			ray->pos_x += ray->step_x; //on se deplace verticalement jusqu'a la prochaine cellule
			ray->side = 0;
		}
		else //rayon traverse une ligne horizontale d'abord
		{
			ray->side_dist_y += ray->delta_y;
			ray->pos_y += ray->step_y; //on se deplace horizontalement jusqu'a la prochaine cellule
			ray->side = 1;
		}
		if (game->map->lines[(int)ray->pos_y]->content[(int)ray->pos_x] == '1')
			hit = 1; //si le rayon a touche un mur = stop
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0) //ligne verticale
		ray->wall_dist = ray->side_dist_x - ray->delta_x;
	else //ligne horizontale
		ray->wall_dist = ray->side_dist_y - ray->delta_y;
}

void	draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
	int	y;

	//dessine une ligne verticale entre start et end de la colour indiquee
	if (start < 0)
		start = 0;
	if (end >= SCREEN_HEIGHT)
		end = SCREEN_HEIGHT - 1;
	y = start - 1;
	while (++y <= end)
		my_mlx_pixel_put(game->raycast, x, y, color);
}

//void	draw_wall(int x, t_ray *ray, t_game *game)
//{
//	int		line_height;
//	int		draw_start;
//	int		draw_end;
//	int		color;

//	line_height = (int)(SCREEN_HEIGHT / ray->wall_dist); //hauteur du mur
//	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
//	if (draw_start < 0)
//		draw_start = 0;
//	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
//	if (draw_end >= SCREEN_HEIGHT)
//		draw_end = SCREEN_HEIGHT - 1;
//	if (ray->side == 0)
//		color = 0xFF0000;
//	else
//		color = 0x00FF00;
//	draw_vertical_line(game, x, draw_start, draw_end, color);
//}

void	draw_wall(int x, t_ray *ray, t_game *game)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	t_image	texture;
	double	wall_x;

	line_height = (int)(SCREEN_HEIGHT / ray->wall_dist); //hauteur du mur
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	if (ray->side == 1 && ray->step_y < 0) //Mur nord
		texture = game->texture->image[0];
	else if (ray->side == 1 && ray->step_y > 0) //Mur sud
		texture = game->texture->image[1];
	else if (ray->side == 0 && ray->step_x < 0) //Mur ouest
		texture = game->texture->image[2];
	else if (ray->side == 0 && ray->step_x > 0) //Mur est
		texture = game->texture->image[3];
	if (ray->side == 0)
		wall_x = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		wall_x = ray->pos_x + ray->wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	color = *texture.color;
	draw_vertical_line(game, x, draw_start, draw_end, color);
}

void	raycasting(t_ray *ray, t_game *game)
{
	int		x;
	double	camera_angle;
	double	ray_angle;

	x = -1;
	ray = malloc(sizeof(t_ray));
	while (++x < SCREEN_WIDTH)
	{
		ray_angle = (game->player.angle * 180 / PI) - FOV / 2 + FOV * (x / (double)SCREEN_WIDTH);
		init_ray(ray, game, ray_angle);
		calculate_steps(ray);
		perform_dda(ray, game);
		calculate_wall_distance(ray);
		//correction de la distorsion
		camera_angle = game->player.angle - (ray->angle * PI / 180);
		if (camera_angle < 0)
			camera_angle += 2 * PI;
		if (camera_angle > 2 * PI)
			camera_angle -= 2 * PI;
		ray->wall_dist = ray->wall_dist * cos(camera_angle);
		draw_wall(x, ray, game);
	}
	free(ray);
}
