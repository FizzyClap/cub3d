#include "../includes/cub3D_bonus.h"

static int	fill_struct_enemy(t_game *game, char *prefix);
static int	calcul(t_game *game, t_data *d, int i);
static int	render(t_game *game, t_data *d, t_image *current);

int	init_enemy(t_game *game, char *prefix)
{
	int	y;
	int	x;

	game->nb_enemy = 0;
	y = -1;
	while (++y < game->map->y)
	{
		x = -1;
		while (++x < game->map->lines[y]->x)
			if (game->map->lines[y]->content[x] == 'A')
				game->nb_enemy++;
	}
	if (game->nb_enemy == 0)
		return (SUCCESS);
	game->enemy = malloc(sizeof(t_enemy) * game->nb_enemy);
	if (!game->enemy)
		return (FAILURE);
	if (fill_struct_enemy(game, prefix) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	create_enemy_tab(t_game *game, char *prefix, int i)
{
	char	**enemy_tab;
	int		idx;

	enemy_tab = malloc(sizeof(char *) * 6);
	if (!enemy_tab)
		return (FAILURE);
	enemy_tab[0] = ft_strjoin(prefix, ".xpm");
	enemy_tab[1] = ft_strjoin(prefix, "(1).xpm");
	enemy_tab[2] = ft_strjoin(prefix, "(2).xpm");
	enemy_tab[3] = ft_strjoin(prefix, "(3).xpm");
	enemy_tab[4] = ft_strjoin(prefix, "(4).xpm");
	enemy_tab[5] = NULL;
	game->enemy_frames = 5;
	game->enemy[i].texture = ft_calloc(sizeof(t_image), (game->enemy_frames + 1));
	idx = -1;
	while (++idx < game->enemy_frames)
		if (!load_xpm(game, &game->enemy[i].texture[idx], enemy_tab[idx]))
			return (FAILURE);
	ft_free_tab(enemy_tab);
	return (SUCCESS);
}

static int	fill_struct_enemy(t_game *game, char *prefix)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = -1;
	while (++y < game->map->y)
	{
		x = -1;
		while (++x < game->map->lines[y]->x)
		{
			if (game->map->lines[y]->content[x] == 'A')
			{
				game->enemy[i].x = x + 0.5;
				game->enemy[i].y = y + 0.5;
				game->enemy[i].is_animating = false;
				if (create_enemy_tab(game, prefix, i) == FAILURE)
					return (FAILURE);
				i++;
			}
		}
	}
	return (SUCCESS);
}

void	sort_enemies(t_game *game)
{
	int			i;
	int			j;
	t_enemy	temp;

	i = -1;
	while (++i < game->nb_enemy)
	{
		game->enemy[i].distance = pow(game->player.posX - game->enemy[i].x, 2) \
		+ pow(game->player.posY - game->enemy[i].y, 2);
	}
	i = -1;
	while (++i < game->nb_enemy)
	{
		j = -1;
		while (++j < game->nb_enemy - i - 1)
		{
			if (game->enemy[j].distance < game->enemy[j + 1].distance)
			{
				temp = game->enemy[j];
				game->enemy[j] = game->enemy[j + 1];
				game->enemy[j + 1] = temp;
			}
		}
	}
}

void render_enemies(t_game *game)
{
	t_data		d;
	int			i;
	t_coord		pos;
	t_image		*current;

	i = -1;
	while (++i < game->nb_enemy)
	{
		if (!game->enemy[i].texture[0].img)
			continue ;
		pos.x = game->enemy[i].x;
		pos.y = game->enemy[i].y;
		current = enemy_animation(game, i, pos);
		if (!current || !current->img)
			return ;
		if (calcul(game, &d, i) == FAILURE)
			continue ;
		while (++d.stripe < d.draw_end_x)
			if (render(game, &d, current) == FAILURE)
				continue ;
	}
}

static int	calcul(t_game *game, t_data *d, int i)
{
	d->sprite_x = game->enemy[i].x - game->player.posX;
	d->sprite_y = game->enemy[i].y - game->player.posY;
	d->inv_det = 1.0 / (game->player.planeX * game->player.dirY - game->player.dirX * game->player.planeY);
	d->transform_x = d->inv_det * (game->player.dirY * d->sprite_x - game->player.dirX * d->sprite_y);
	d->transform_y = d->inv_det * (-game->player.planeY * d->sprite_x + game->player.planeX * d->sprite_y);
	if (d->transform_y <= 0)
		return (FAILURE);
	d->sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + d->transform_x / d->transform_y));
	d->sprite_height = abs((int)(SCREEN_HEIGHT / d->transform_y));
	d->sprite_width = d->sprite_height;
	d->draw_start_y = -d->sprite_height / 2 + SCREEN_HEIGHT / 2;
	d->draw_end_y = d->sprite_height / 2 + SCREEN_HEIGHT / 2;
	d->draw_start_x = -d->sprite_width / 2 + d->sprite_screen_x;
	d->draw_end_x = d->sprite_width / 2 + d->sprite_screen_x;
	d->stripe = d->draw_start_x - 1;
	return (SUCCESS);
}

static int	render(t_game *game, t_data *d, t_image *current)
{
	int	y;

	if (d->stripe >= 0 && d->stripe < SCREEN_WIDTH && \
		d->transform_y < game->z_buffer[d->stripe])
	{
		d->tex_x = (int)((d->stripe - (-d->sprite_width / 2 + \
		d->sprite_screen_x)) * current->width / d->sprite_width);
		y = d->draw_start_y - 1;
		while (++y < d->draw_end_y)
		{
			if (y < 0 || y >= SCREEN_HEIGHT)
				return (FAILURE);
			d->tex_y = (int)((y - (-d->sprite_height / 2 + SCREEN_HEIGHT / 2)) * current->height / d->sprite_height);
			d->color = current->color[d->tex_y * current->width + d->tex_x];
			my_mlx_pixel_put(&game->raycast, d->stripe, y + game->player.z, d->color);
		}
	}
	return (SUCCESS);
}

int	hit_enemy(t_ray *ray, t_game *game)
{
	int		hit;
	int		i;
	char	pos;

	hit = 0;
	ray->map.x = (int)game->player.posX;
	ray->map.y = (int)game->player.posY;
	while (!hit)
	{
		move_ray(game, ray);
		if (ray->map.y < 0 || ray->map.y >= game->map->y - 1 ||
		ray->map.x < 0 || ray->map.x >= game->map->lines[ray->map.y]->x)
			return (-1);
		pos = game->map->lines[ray->map.y]->content[ray->map.x];
		if (pos == 'A' || pos == '1' || pos == 'D')
			hit = 1;
		i = -1;
		while (++i < game->nb_enemy)
			if ((int)game->enemy[i].x == ray->map.x && \
				(int)game->enemy[i].y == ray->map.y)
			return (i);
	}
	return (-1);
}

void	move_ray(t_game *game, t_ray *ray)
{
	char	pos;

	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_x;
		ray->map.x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_y;
		ray->map.y += ray->step_y;
		ray->side = 1;
	}
	pos = game->map->lines[ray->map.y]->content[ray->map.x];
	ray->pos_door = pos;
	ray->door_x = ray->map.x;
	ray->door_y = ray->map.y;
}
