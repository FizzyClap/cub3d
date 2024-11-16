#include "../includes/cub3D.h"

// void ceil_raycast(t_game *game)
// {
// 	t_image *ceilingTexture = &game->texture->image[NORTH];  // Texture du sol

// 	for (int y = 0; y < ((SCREEN_HEIGHT / 2) + game->player.z); y++)
// 	{
// 		double rayDirX0 = cos(game->player.angle) + sin(game->player.angle);
// 		double rayDirY0 = -sin(game->player.angle) + cos(game->player.angle);
// 		double rayDirX1 = cos(game->player.angle) - sin(game->player.angle);
// 		double rayDirY1 = -sin(game->player.angle);

// 		int p = y - SCREEN_HEIGHT / 2 - game->player.z;

// 		double posZ = SCREEN_HEIGHT / 2;

// 		double rowDistance = posZ / p;

// 		double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
// 		double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

// 		double floorX = game->player.x + rowDistance * rayDirX0;
// 		double floorY = game->player.y + rowDistance * rayDirY0;

// 		for (int x = 0; x < SCREEN_WIDTH; ++x)
// 		{
// 			double tx = (int)(ceilingTexture->width * (floorX)) % (ceilingTexture->width - 1);  // Coordonnée X de la texture du sol
// 			double ty = (int)(ceilingTexture->height * (floorY)) % (ceilingTexture->height - 1);  // Coordonnée Y de la texture du sol

// 			floorX += floorStepX;
// 			floorY += floorStepY;

// 			int floorColor = get_texture_color(ceilingTexture, tx, ty);

// 			my_mlx_pixel_put(game->raycast, x, y, floorColor);
// 		}
// 	}
// }

// void floor_raycast(t_game *game)
// {
// 	t_image *floorTexture = &game->door;  // Texture du plafond

// 	for (int y = SCREEN_HEIGHT / 2 + game->player.z; y < SCREEN_HEIGHT; y++)
// 	{

// 		double rayDirX0 = cos(game->player.angle) + sin(game->player.angle);
// 		double rayDirY0 = -sin(game->player.angle) + cos(game->player.angle);
// 		double rayDirX1 = cos(game->player.angle) - sin(game->player.angle);
// 		double rayDirY1 = -sin(game->player.angle);

// 		int p = y - SCREEN_HEIGHT / 2 - game->player.z;

// 		double posZ = SCREEN_HEIGHT / 2;

// 		double rowDistance = posZ / p;

// 		double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
// 		double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_HEIGHT;

// 		double floorX = game->player.x + rowDistance * rayDirX0;
// 		double floorY = game->player.y + rowDistance * rayDirY0;

// 		for (int x = 0; x < SCREEN_WIDTH; ++x)
// 		{
// 			double tx = (int)(floorTexture->width * (floorX)) % (floorTexture->width - 1);  // Coordonnée X de la texture du sol
// 			double ty = (int)(floorTexture->height * (floorY)) % (floorTexture->height - 1);  // Coordonnée Y de la texture du sol

// 			floorX += floorStepX;
// 			floorY += floorStepY;

// 			int ceilingColor = get_texture_color(floorTexture, tx, ty);

// 			my_mlx_pixel_put(game->raycast, x, y, ceilingColor);
// 		}
// 	}
// 	ceil_raycast(game);
// }


int get_texture_color(t_image *texture, int tx, int ty)
{
    if (tx < 0 || tx >= texture->width || ty < 0 || ty >= texture->height)
        return (0);  // Retourne une couleur par défaut (noir)
    int index = ty * texture->width + tx;
    return texture->color[index];
}

void floor_raycast(t_game *game)
{
    t_image *ceilingTexture = &game->texture->image[NORTH];  // Texture du plafond
    t_image *floorTexture = &game->texture->image[SOUTH];    // Texture du sol

    for (int y = SCREEN_HEIGHT / 2 + game->player.z; y < SCREEN_HEIGHT; y++)
    {
        // Calcul des distances pour le sol et le plafond
        double dy = y - SCREEN_HEIGHT / 2.0;  // Différence entre la position actuelle et le centre de l'écran
        double rayDirX0 = cos(game->player.angle) - sin(game->player.angle);
        double rayDirY0 = -sin(game->player.angle) - cos(game->player.angle);
        double rayDirX1 = cos(game->player.angle) + sin(game->player.angle);
        double rayDirY1 = -sin(game->player.angle) + cos(game->player.angle);

        // Calcul de la distance du rayon pour le sol/plafond
        double rowDistance = (SCREEN_HEIGHT / (2.0 * dy));  // Distance en fonction de y
        double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
        double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

        // Position de départ des coordonnées du sol/plafond
        double floorX = game->player.x + rowDistance * rayDirX0;
        double floorY = game->player.y + rowDistance * rayDirY0;

        // Application des textures
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            // Coordonnées de la texture pour le sol
            int tx = (int)(floorX * floorTexture->width) % floorTexture->width;
            int ty = (int)(floorY * floorTexture->height) % floorTexture->height;

            // Calcul du pixel à afficher pour le sol
            int floorColor = get_texture_color(floorTexture, tx, ty);

            // Affichage du pixel du sol
            my_mlx_pixel_put(game->raycast, x, y + SCREEN_HEIGHT / 2, floorColor); // Plafond

            // Coordonnées de la texture pour le plafond
            tx = (int)(floorX * ceilingTexture->width) % ceilingTexture->width;
            ty = (int)(floorY * ceilingTexture->height) % ceilingTexture->height;

            // Calcul du pixel à afficher pour le plafond
            int ceilingColor = get_texture_color(ceilingTexture, tx, ty);

            // Affichage du pixel du plafond
            my_mlx_pixel_put(game->raycast, x, y, ceilingColor); // Sol

            // Mise à jour des coordonnées du sol/plafond pour la prochaine itération
            // Le mouvement latéral est pris en compte ici, mais l'orientation de la texture est fixe
            floorX += floorStepX;
            floorY += floorStepY;
        }

        // Mise à jour des coordonnées du sol/plafond pour la prochaine itération
        // A ce niveau, on ne fait plus de rotation des textures, seulement des déplacements latéraux
    }
	ceil_raycast(game);
}

void ceil_raycast(t_game *game)
{
    t_image *ceilingTexture = &game->texture->image[NORTH];  // Texture du plafond

    for (int y = 0; y < (SCREEN_HEIGHT / 2 + game->player.z); y++)
    {
        // Calcul des distances pour le sol et le plafond
        double dy = y - SCREEN_HEIGHT / 2.0;  // Différence entre la position actuelle et le centre de l'écran
        double rayDirX0 = cos(game->player.angle) - sin(game->player.angle);
        double rayDirY0 = -sin(game->player.angle) - cos(game->player.angle);
        double rayDirX1 = cos(game->player.angle) + sin(game->player.angle);
        double rayDirY1 = -sin(game->player.angle) + cos(game->player.angle);

        // Calcul de la distance du rayon pour le sol/plafond
        double rowDistance = SCREEN_HEIGHT / (2.0 * dy);  // Distance en fonction de y
        double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
        double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

        // Position de départ des coordonnées du sol/plafond
        double floorX = game->player.x + rowDistance * rayDirX0;
        double floorY = game->player.y + rowDistance * rayDirY0;

        // Application des textures
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            // Coordonnées de la texture pour le plafond
            int tx = (int)(floorX * ceilingTexture->width) % ceilingTexture->width;
            int ty = (int)(floorY * ceilingTexture->height) % ceilingTexture->height;

            // Calcul du pixel à afficher pour le plafond
            int ceilingColor = get_texture_color(ceilingTexture, tx, ty);

            // Affichage du pixel du plafond
            my_mlx_pixel_put(game->raycast, x, y, ceilingColor); // Sol

            // Mise à jour des coordonnées du sol/plafond pour la prochaine itération
            // Le mouvement latéral est pris en compte ici, mais l'orientation de la texture est fixe
            floorX += floorStepX;
            floorY += floorStepY;
        }

        // Mise à jour des coordonnées du sol/plafond pour la prochaine itération
        // A ce niveau, on ne fait plus de rotation des textures, seulement des déplacements latéraux
    }
}