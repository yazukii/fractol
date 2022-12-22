/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:45:26 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/22 20:01:30 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	setdef(void *param)
{
	t_data	*mlx;
	double	rg;

	rg = (3.5 + 3.5) / (double)1920;
	mlx = param;
	mlx->def.minre = -3.5;
	mlx->def.maxre = 3.5;
	mlx->def.minim = -((rg / 2) * 1080);
	mlx->def.maxim = (rg / 2) * 1080;
	mlx->x = 1920;
	mlx->y = 1080;
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
		julia(mlx, mlx->cx, mlx->cy);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		mlx;

	if (argc <= 3)
	{
		ft_putstr("usage: ./fractol [julia: x] [julia: y] [fractal]");
		return (0);
	}
	if (argv[3][0] == 'm')
		mlx.sw = 0;
	if (argv[3][0] == 'j')
		mlx.sw = 1;
	mlx.cx = ft_stod(argv[1]);
	mlx.cy = ft_stod(argv[2]);
	printf("a: %f, b: %f\n", mlx.cx, mlx.cy);
	setdef(&mlx);
	def(&mlx);
	mlx_mouse_hook(mlx.win, &mouse_hooks, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, &hooks, &mlx);
	mlx_key_hook(mlx.win, &hooks, &mlx);
	mlx_hook(mlx.win, 17, 0L, &killwin, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}

/*
	///!350
	mlx->def.minre = -0.753;
	mlx->def.maxre = -0.727;
	mlx->def.minim = 0.1441;
	mlx->def.maxim = 0.1588;

	///!1000
	mlx->def.minre = -0.7475087485;
	mlx->def.maxre = -0.7475087322;
	mlx->def.minim = 0.0830715266;
	mlx->def.maxim = 0.0830715359;

	///!475
	mlx->def.minre = -0.439165;
	mlx->def.maxre = -0.43909;
	mlx->def.minim = 0.574507;
	mlx->def.maxim = 0.574549

	///!2500
	mlx->def.minre = -1.74858614;
	mlx->def.maxre = -1.74858479;
	mlx->def.minim = 0.01262719;
	mlx->def.maxim = 0.01262795;

	///!2250
	mlx->def.minre = -0.74766;
	mlx->def.maxre = -0.74728;
	mlx->def.minim = 0.08290;
	mlx->def.maxim = 0.08312;

*/