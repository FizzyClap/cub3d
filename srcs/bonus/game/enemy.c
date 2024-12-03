#include "../includes/cub3D_bonus.h"

static int	fill_struct_enemy(t_game *game, char *prefix);

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
		game->enemy[i].distance = pow(game->player.x - game->enemy[i].x, 2) \
		+ pow(game->player.y - game->enemy[i].y, 2);
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
	t_render	r;
	int			i;
	int			y;
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
		r.sprite_x = game->enemy[i].x - game->player.x;
		r.sprite_y = game->enemy[i].y - game->player.y;
		r.inv_det = 1.0 / (game->player.plane_x * game->player.d_y - game->player.d_x * game->player.plane_y);
		r.transform_x = r.inv_det * (game->player.d_y * r.sprite_x - game->player.d_x * r.sprite_y);
		r.transform_y = r.inv_det * (-game->player.plane_y * r.sprite_x + game->player.plane_x * r.sprite_y);
		if (r.transform_y <= 0)
			continue;
		r.sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + r.transform_x / r.transform_y));
		r.sprite_height = abs((int)(SCREEN_HEIGHT / r.transform_y));
		r.sprite_width = r.sprite_height;
		r.draw_start_y = -r.sprite_height / 2 + SCREEN_HEIGHT / 2;
		r.draw_end_y = r.sprite_height / 2 + SCREEN_HEIGHT / 2;
		r.draw_start_x = -r.sprite_width / 2 + r.sprite_screen_x;
		r.draw_end_x = r.sprite_width / 2 + r.sprite_screen_x;
		r.stripe = r.draw_start_x - 1;
		while (++r.stripe < r.draw_end_x)
		{
			if (r.stripe >= 0 && r.stripe < SCREEN_WIDTH && r.transform_y < game->z_buffer[r.stripe])
			{
				r.tex_x = (int)((r.stripe - (-r.sprite_width / 2 + r.sprite_screen_x)) * current->width / r.sprite_width);
				y = r.draw_start_y - 1;
				while (++y < r.draw_end_y)
				{
					if (y < 0 || y >= SCREEN_HEIGHT)
						continue;
					r.tex_y = (int)((y - (-r.sprite_height / 2 + SCREEN_HEIGHT / 2)) * current->height / r.sprite_height);
					r.color = current->color[r.tex_y * current->width + r.tex_x];
					my_mlx_pixel_put(&game->raycast, r.stripe, y + game->player.z, r.color);
				}
			}
		}
	}
}

int	hit_enemy(t_ray *ray, t_game *game)
{
	int		hit;
	t_coord	ray_pos;
	int		i;
	char	pos;

	hit = 0;
	while (!hit)
	{
		move_ray(ray);
		ray_pos.y = (int)floor(ray->pos_y);
		ray_pos.x = (int)floor(ray->pos_x);
		if (ray_pos.y < 0 || ray_pos.y >= game->map->y - 1 ||
		ray_pos.x < 0 || ray_pos.x >= game->map->lines[ray_pos.y]->x)
			return (-1);
		pos = game->map->lines[ray_pos.y]->content[ray_pos.x];
		if (pos == 'A' || pos == '1' || pos == 'D')
			hit = 1;
		i = -1;
		while (++i < game->nb_enemy)
			if ((int)game->enemy[i].x == ray_pos.x && \
				(int)game->enemy[i].y == ray_pos.y)
			return (i);
	}
	return (-1);
}
