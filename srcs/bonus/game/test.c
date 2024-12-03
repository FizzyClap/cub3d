#include "../includes/cub3D_bonus.h"

void raycast(t_game *game)
{
	t_image *floorTexture = &game->door[game->doors_frames + 1];
	t_image *ceilTexture = &game->door[game->doors_frames];

	for(int y = 0; y < SCREEN_HEIGHT; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		double rayDirX0 = game->player.dirX - game->player.planeX;
		double rayDirY0 = game->player.dirY - game->player.planeY;
		double rayDirX1 = game->player.dirX + game->player.planeX;
		double rayDirY1 = game->player.dirY + game->player.planeY;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - SCREEN_HEIGHT / 2;

		// Vertical position of the camera.
		double posZ = 0.5 * SCREEN_HEIGHT;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		double rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
		double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		double floorX = game->player.posX + rowDistance * rayDirX0;
		double floorY = game->player.posY + rowDistance * rayDirY0;

		for(int x = 0; x < SCREEN_WIDTH; ++x)
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
		my_mlx_pixel_put(&game->raycast, x, y, color);

		//ceiling (symmetrical, at SCREEN_HEIGHT - y - 1 instead of y)
		color = ceilTexture->color[ceilTexture->width * ty + tx];
		color = (color >> 1) & 8355711; // make a bit darker
		my_mlx_pixel_put(&game->raycast, x, SCREEN_HEIGHT - y - 1, color);
		}
	}
	// printf("ici\n");
	for(int x = 0; x < SCREEN_WIDTH; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
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

		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		t_image *tex;

		tex = &game->texture->image[NORTH];

		double  wallX;

		if (side == 0)
			wallX = game->player.posY + perpWallDist * rayDirY;
		else
			wallX = game->player.posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)(tex->width));
		if(side == 0 && rayDirX > 0)
			texX = tex->width - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = tex->width - texX - 1;

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
			my_mlx_pixel_put(&game->raycast, x, y, color);
		}
	}
}
