#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>

int *isometric(int x, int y, int z)
{
  int *points;

  points = malloc(sizeof(int) * 2);
  points[0] = x * cos(-M_PI / 6) - y * sin(-M_PI / 3);
  points[1] = y * cos(-M_PI / 3) + x * sin(-M_PI / 6) - z;
  return (points);
}

void plot_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
  int dx;
  int sx;
  int dy;
  int sy;
  int err;
  int e2;

  dx = abs(x1 - x0);
  sx = x0 < x1 ? 1 : -1;
  dy = -abs(y1 - y0);
  sy = y0 < y1 ? 1 : -1;
  err = dx + dy;

  while (1)
  {
    mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0xFFFFFF);
    if (x0 == x1 && y0 == y1)
      break;
    e2 = 2 * err;
    if (e2 >= dy)
    {
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx)
    {
      err += dx;
      y0 += sy;
    }
  }
}

int main(void)
{
  void *mlx_ptr;
  void *win_ptr;

  mlx_ptr = mlx_init();
  win_ptr = mlx_new_window(mlx_ptr, 400, 400, "mlxer");
  for (int x = 1; x < 10; x++)
  {
    for (int y = 1; y < 10; y++)
    {
      // mlx_pixel_put(mlx_ptr, win_ptr, 200 + (x - y) * 10, 100 + (x + y) * 10, 0xFFFFFF);
      // mlx_pixel_put(mlx_ptr, win_ptr, 200 + (x * 200 / 10 + y * 200 / 10) / 2, 100 + (y * 200 / 10 - x * 200 / 10) / 2, 0xFFFFFF);
      // // plot_line(mlx_ptr, win_ptr, x * 30, y * 30, (x + 1) * 30, y * 30);
      if (x == 3 && y == 3)
        plot_line(mlx_ptr, win_ptr, 200 + (x - y * 2) * 20, 100 + (x + y - 5) * 20, 200 + (x + 1 - y * 2) * 20, 100 + (x + y + 1) * 20);
      else if (x + 1 == 3 && y == 3)
        plot_line(mlx_ptr, win_ptr, 200 + (x - y * 2) * 20, 100 + (x + y) * 20, 200 + (x + 1 - y * 2) * 20, 100 + (x + 1 + y - 5) * 20);
      else
        plot_line(mlx_ptr, win_ptr, 200 + (x - y * 2) * 20, 100 + (x + y) * 20, 200 + (x + 1 - y * 2) * 20, 100 + (x + y + 1) * 20);
      // if (x + 1 == 10)
      //   plot_line(mlx_ptr, win_ptr, (x + 1) * 30, y * 30, (x + 1) * 30, (y + 1) * 30);
      // // plot_line(mlx_ptr, win_ptr, x * 30, y * 30, x * 30, (y + 1) * 30);
      if (x == 3 && y == 3)
        plot_line(mlx_ptr, win_ptr, 200 + (x - y * 2) * 20, 100 + (x + y - 5) * 20, 200 + (x + 2 - y * 2) * 20, 100 + (x + y - 1) * 20);
      else if (x == 3 && y - 1 == 3)
        plot_line(mlx_ptr, win_ptr, 200 + (x - y * 2) * 20, 100 + (x + y) * 20, 200 + (x + 2 - y * 2) * 20, 100 + (x + y - 1 - 5) * 20);
      else
        plot_line(mlx_ptr, win_ptr, 200 + (x - y * 2) * 20, 100 + (x + y) * 20, 200 + (x + 2 - y * 2) * 20, 100 + (x + y - 1) * 20);
      // // if (y + 1 == 10)
      // //   plot_line(mlx_ptr, win_ptr, x * 30, (y + 1) * 30, (x + 1) * 30, (y + 1) * 30);
    }
  }
  mlx_loop(mlx_ptr);
}