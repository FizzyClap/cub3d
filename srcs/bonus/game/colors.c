#include "../includes/cub3D_bonus.h"

void	get_color(t_color *type, char *path)
{
	char	**rgb;

	rgb = ft_split(path, ',');
	type->r = ft_atoi(rgb[0]);
	type->g = ft_atoi(rgb[1]);
	type->b = ft_atoi(rgb[2]);
	ft_free_tab(rgb);
}

int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
