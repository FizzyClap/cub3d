# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
#include <stdlib.h>

int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    if (!mlx)
        return (EXIT_FAILURE);
    win = mlx_new_window(mlx, 800, 600, "Test Window");
    if (!win)
        return (EXIT_FAILURE);
    return (0);
}

