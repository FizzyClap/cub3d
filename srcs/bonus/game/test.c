#include "../includes/cub3D.h"

//place the example code below here:


// void	make_actions(t_game *game)
// {
// 	if (game->player.action[MOVEUP] == 1)
// 		move_up(game);
// 	if (game->player.action[MOVEBACK] == 1)
// 		move_down(game);
// 	if (game->player.action[MOVELEFT] == 1)
// 		move_left(game);
// 	if (game->player.action[MOVERIGHT] == 1)
// 		move_right(game);
// }

double	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec + time.tv_usec / 1000000.0);
}

int	keyrelease(int keycode, t_game *game)
{
	if (keycode == W || keycode == UP)
		game->player.action[MOVEUP] = 0;
	if (keycode == A)
		game->player.action[MOVELEFT] = 0;
	if (keycode == S || keycode == DOWN)
		game->player.action[MOVEBACK] = 0;
	if (keycode == D)
		game->player.action[MOVERIGHT] = 0;
	// if (keycode == RIGHT)
	// 	right_cam(game, 970);
	// if (keycode == LEFT)
	// 	left_cam(game, 950);
	return (SUCCESS);
}

int	keycode(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_game(game);
	// if (keycode == O)
	// 	shoot_ray_to_door(game);
	if (keycode == W || keycode == UP)
		game->player.action[MOVEUP] = 1;
	if (keycode == S || keycode == DOWN)
		game->player.action[1] = 1;
	if (keycode == A)
		game->player.action[2] = 1;
	if (keycode == D)
		game->player.action[3] = 1;
	// if (keycode == RIGHT)
	// 	right_cam(game, 970);
	// if (keycode == LEFT)
	// 	left_cam(game, 950);
	// if (keycode == SPACE && game->player.h <= 0)
	// {
	// 	game->player.crouch = false;
	// 	game->player.jump = ft_change_bool(game->player.jump);
	// }
	// if (keycode == SHIFT)
	// {
	// 	game->player.jump = false;
	// 	game->player.crouch = ft_change_bool(game->player.crouch);
	// }
	return (SUCCESS);
}

void raycast(t_game *game)
{
	{
	draw_floor_ceiling(game, BLACK, BLUE);
	t_image *floorTexture = &game->door[game->total_frames + 1];
	// t_image *ceilTexture = &game->door[game->total_frames];

	for(int y = 0; y < SCREEN_HEIGHT; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		double rayDirX0 = game->player.dirX - game->player.planeX;
		double rayDirY0 = game->player.dirY - game->player.planeY;
		double rayDirX1 = game->player.dirX + game->player.planeX;
		double rayDirY1 = game->player.dirY + game->player.planeY;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - screenHeight / 2;

		// Vertical position of the camera.
		double posZ = 0.5 * screenHeight;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		double rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
		double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		double floorX = game->player.posX + rowDistance * rayDirX0;
		double floorY = game->player.posY + rowDistance * rayDirY0;

		for(int x = 0; x < screenWidth; ++x)
		{
		// the cell coord is simply got from the integer parts of floorX and floorY
		int cellX = (int)(floorX);
		int cellY = (int)(floorY);

		// get the texture coordinate from the fractional part
		int tx = (int)(floorTexture->width * (floorX - cellX)) % (floorTexture->width - 1);
		int ty = (int)(floorTexture->height * (floorY - cellY)) % (floorTexture->height - 1);

		floorX += floorStepX;
		floorY += floorStepY;

		// choose texture and draw the pixel
		int color;

		// floor
		color = floorTexture->color[floorTexture->width * ty + tx];
		color = (color >> 1) & 8355711; // make a bit darker
		my_mlx_pixel_put(game->raycast, x, y, color);

		//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
		color = floorTexture->color[floorTexture->width * ty + tx];
		color = (color >> 1) & 8355711; // make a bit darker
		my_mlx_pixel_put(game->raycast, x, SCREEN_HEIGHT - y - 1, color);
		}
	}
	// printf("ici\n");
	for(int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		double rayDirX = game->player.dirX + game->player.planeX * cameraX;
		double rayDirY = game->player.dirY + game->player.planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)game->player.posX;
		int mapY = (int)game->player.posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		double deltaDistX;

		if (rayDirX == 0)
		deltaDistX = INT_MAX;
		else
		deltaDistX = fabs(1 / rayDirX);
		double deltaDistY;
		if (rayDirY == 0)
		deltaDistY = INT_MAX;
		else
		deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
		stepX = -1;
		sideDistX = (game->player.posX - mapX) * deltaDistX;
		}
		else
		{
		stepX = 1;
		sideDistX = (mapX + 1.0 - game->player.posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
		stepY = -1;
		sideDistY = (game->player.posY - mapY) * deltaDistY;
		}
		else
		{
		stepY = 1;
		sideDistY = (mapY + 1.0 - game->player.posY) * deltaDistY;
		}
		//perform DDA
		while(hit == 0)
		{
		//jump to next map square, either in x-direction, or in y-direction
		if(sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if(game->map->lines[mapY]->content[mapX] == '1')
			hit = 1;
		}

		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

		t_image *tex;

		tex = &game->texture->image[NORTH];

		double  wallX;

		if (side == 0)
		wallX = game->player.posY + perpWallDist * rayDirY;
		else
		wallX = game->player.posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)(tex->width));
		if(side == 0 && rayDirX > 0) texX = tex->width - texX - 1;
		if(side == 1 && rayDirY < 0) texX = tex->width - texX - 1;

		double step = 1.0 * tex->height / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos % (tex->height - 1);
		texPos += step;
		int color = tex->color[tex->height * texY + texX];
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(side == 1) color = (color >> 1) & 8355711;
		my_mlx_pixel_put(game->raycast, x, y, color);
		}

		//choose wall color
		// int color = RED;

		// //give x and y sides different brightness
		// if(side == 1) {color = color / 2;}

		// //draw the pixels of the stripe as a vertical line
		// for (int t = drawStart; t < drawEnd; t++)
		//   my_mlx_pixel_put(game->raycast, x, t, color);
	}
	//timing for input and FPS counter
	game->oldTime = game->time;
	game->time = get_current_time();
	double frameTime = (game->time - game->oldTime); //frameTime is the time this frame has taken, in seconds
	game->player.rotSpeed = frameTime * 3.0; //the constant value is in radians/second
	game->player.moveSpeed = frameTime * 5.0; //the constant value is in squares/second

	}
}

void	draw_floor_ceiling(t_game *game, int floor_color, int ceiling_color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < (540))
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(game->raycast, x, y, ceiling_color);
	}
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(game->raycast, x, y, floor_color);
	}
}

void	move_div(t_game *game)
{
	int	result;

	result = 0;
	if (game->player.action[MOVEUP] == 1)
		result++;
	if (game->player.action[MOVELEFT] == 1)
		result++;
	if (game->player.action[MOVERIGHT] == 1)
		result++;
	if (game->player.action[MOVEBACK] == 1)
		result++;
	game->player.move_div = result;
}

void	my_mlx_pixel_put(t_image img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > screenWidth || y > screenHeight)
		return ;
	dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(unsigned int *) dst = color;
}

static int	loop(t_game *game)
{
	game->time = get_current_time();
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->raycast.img, 0, 0);
	if(game->player.action[MOVEUP] == 1)
	{
		if(ft_strchr("0NSEWD", game->map->lines[(int)(game->player.posY + game->player.dirY * game->player.moveSpeed)]->content[(int)(game->player.posX)]))game->player. posY += game->player.dirY * game->player.moveSpeed;
		if(ft_strchr("0NSEWD", game->map->lines[(int)(game->player.posY)]->content[(int)(game->player.posX + game->player.dirX * game->player.moveSpeed)])) game->player.posX += game->player.dirX * game->player.moveSpeed;
	}
	if(game->player.action[MOVEBACK] == 1)
	{
		if(ft_strchr("0NSEWD", game->map->lines[(int)(game->player.posY - game->player.dirY * game->player.moveSpeed)]->content[(int)(game->player.posX)])) game->player.posY -= game->player.dirY * game->player.moveSpeed;
		if(ft_strchr("0NSEWD", game->map->lines[(int)(game->player.posY)]->content[(int)(game->player.posX - game->player.dirX * game->player.moveSpeed)])) game->player.posX -= game->player.dirX * game->player.moveSpeed;
	}
	if(game->player.action[MOVELEFT] == 1)
	{
		double oldDirX = game->player.dirX;
		game->player.dirX = game->player.dirX * cos(-game->player.rotSpeed) - game->player.dirY * sin(-game->player.rotSpeed);
		game->player.dirY = oldDirX * sin(-game->player.rotSpeed) + game->player.dirY * cos(-game->player.rotSpeed);
		double oldPlaneX = game->player.planeX;
		game->player.planeX = game->player.planeX * cos(-game->player.rotSpeed) - game->player.planeY * sin(-game->player.rotSpeed);
		game->player.planeY = oldPlaneX * sin(-game->player.rotSpeed) + game->player.planeY * cos(-game->player.rotSpeed);
	}
	if(game->player.action[MOVERIGHT] == 1)
	{
		double oldDirX = game->player.dirX;
		game->player.dirX = game->player.dirX * cos(game->player.rotSpeed) - game->player.dirY * sin(game->player.rotSpeed);
		game->player.dirY = oldDirX * sin(game->player.rotSpeed) + game->player.dirY * cos(game->player.rotSpeed);
		double oldPlaneX = game->player.planeX;
		game->player.planeX = game->player.planeX * cos(game->player.rotSpeed) - game->player.planeY * sin(game->player.rotSpeed);
		game->player.planeY = oldPlaneX * sin(game->player.rotSpeed) + game->player.planeY * cos(game->player.rotSpeed);
	}
	return (SUCCESS);
}

void new(t_game *game)
{
	game->oldTime = 0; //time of previous frame
	game->player.posX = (double)game->map->start_x;
	game->player.posY = (double)game->map->start_y;  //x and y start position
	game->player.dirX = 1;
	game->player.dirY = 0; //initial direction vector
	game->player.planeX = 0;
	game->player.planeY = 0.66; //the 2d raycaster version of camera plane
	int a = -1;
	game->player.action = malloc(sizeof(int) * 4);
	while (++a < 4)
		game->player.action[a] = 0;
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, keyrelease, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, keycode, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, close_game, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_hook(game->win, DestroyNotify, NoEventMask, close_game, game);
	mlx_loop_hook(game->mlx, loop, game);
	mlx_loop(game->mlx);
}
