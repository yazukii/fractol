/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:45:26 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/20 14:00:42 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	setdef(void *param)
{
	t_data	*mlx;
	double	rg;

	rg = (4 + 3) / (double)1920;
	mlx = param;
	mlx->def.minre = -4;
	mlx->def.maxre = 3;
	mlx->def.minim = -((rg / 2) * 1080);
	mlx->def.maxim = (rg / 2) * 1080;
	mlx->minre = mlx->def.minre;
	mlx->maxre = mlx->def.maxre;
	mlx->minim = mlx->def.minim;
	mlx->maxim = mlx->def.maxim;
	mlx->r = 9;
	mlx->g = 15;
	mlx->b = 8.5;
}

int	die(char *reason)
{
	ft_putendl_fd(reason, 1);
	return (1);
}

int	def(void *param)
{
	t_data	*mlx;

	mlx = param;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->x, mlx->y, "fractol");
	mlx->img = mlx_new_image(mlx->mlx, mlx->x, mlx->y);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->l_l, &mlx->endian);
	mlx->minre = mlx->def.minre;
	mlx->maxre = mlx->def.maxre;
	mlx->minim = mlx->def.minim;
	mlx->maxim = mlx->def.maxim;
	call(mlx);
	return (0);
}

int	call(t_data *mlx)
{
	if (mlx->sw == 0)
		mandelbrot(mlx);
	else if (mlx->sw == 1)
		julia(mlx, 661, 613 );
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	printf("minre: %f, maxre: %f, minim: %f, maxim: %f\n", mlx->minre, mlx->maxre, mlx->minim, mlx->maxim);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		mlx;

	if (argc <= 2)
		return (die("error: Not enough arguments"));
	mlx.x = ft_atoi(argv[1]);
	mlx.y = ft_atoi(argv[2]);
	if (argv[3][0] == 'm')
		mlx.sw = 0;
	if (argv[3][0] == 'j')
		mlx.sw = 1;
	setdef(&mlx);
	def(&mlx);
	mlx_mouse_hook(mlx.win, &zoom, &mlx);
	mlx_hook(mlx.win, 2, 1L << 2, &hooks, &mlx);
	mlx_key_hook(mlx.win, &hooks, &mlx);
	mlx_hook(mlx.win, 17, 0L, &killwin, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
