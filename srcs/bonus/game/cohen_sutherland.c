#include "../includes/cub3D.h"

int	computeOutCode(double x, double y)
{
	int	code;

	code = INSIDE_SCREEN;
	if (x < 0)
		code |= LEFT_SCREEN;
	else if (x >= SCREEN_WIDTH)
		code |= RIGHT_SCREEN;
	if (y < 0)
		code |= TOP_SCREEN;
	else if (y >= SCREEN_HEIGHT)
		code |= BOTTOM_SCREEN;
	return (code);
}

bool	cohenSutherland(double x0, double y0, double x1, double y1)
{
	int		outcode0;
	int		outcode1;
	int		outcode_out;
	bool	accept;
	double	y;
	double	x;

	outcode0 = computeOutCode(x0, y0);
	outcode1 = computeOutCode(x1, y1);
	accept = false;
	while (true)
	{
		if (!(outcode0 | outcode1))
		{
			accept = true;
			break ;
		}
		else if (outcode0 & outcode1)
			break ;
		else
		{
			outcode_out = outcode0;
			if (outcode1 > outcode0)
				outcode_out = outcode1;
			if (outcode_out & TOP_SCREEN)
			{
				x = x0 + (x1 - x0) * (SCREEN_HEIGHT - y0) / (y1 - y0);
				y = SCREEN_HEIGHT;
			}
			else if (outcode_out & BOTTOM_SCREEN)
			{
				x = x0 + (x1 - x0) * (0 - y0) / (y1 - y0);
				y = 0;
			}
			else if (outcode_out & RIGHT_SCREEN)
			{
				y = y0 + (y1 - y0) * (SCREEN_WIDTH - x0) / (x1 - x0);
				x = SCREEN_WIDTH;
			}
			else if (outcode_out & LEFT_SCREEN)
			{
				y = y0 + (y1 - y0) * (0 - x0) / (x1 - x0);
				x = 0;
			}
			if (outcode_out == outcode0)
			{
				x0 = x;
				y0 = y;
				outcode0 = computeOutCode(x0, y0);
			}
			else
			{
				x1 = x;
				y1 = y;
				outcode1 = computeOutCode(x1, y1);
			}
		}
	}
	return (accept);
}
