/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:45:26 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/21 17:24:34 by yidouiss         ###   ########.fr       */
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
	//printf("minre: %f, maxre: %f, minim: %f, maxim: %f\n", mlx->minre, mlx->maxre, mlx->minim, mlx->maxim);
	return (0);
}

double str_to_float(char *arr)
{
	int		i,j,flag;
	double	val;
	char	c;

	i = 0;
	j = 0;
	val = 0;
	flag = 0;
	while ((c = *(arr + i)) != '\0')
	{
		if (c != '.')
		{
			val = (val * 10) + (c - '0');
			if (flag == 1)
				j--;
		}
		if (c == '.')
		{ 
			if (flag == 1) 
				return 0; 
			flag = 1;
		}
		i++;
	}
	val = val * pow(10, j);
	return val;
}

int	main(int argc, char **argv)
{
	t_data		mlx;

	if (argc <= 2)
		return (die("error: Not enough arguments"));
	if (argv[3][0] == 'm')
		mlx.sw = 0;
	if (argv[3][0] == 'j')
		mlx.sw = 1;
	mlx.cx = str_to_float(argv[1]);
	mlx.cy = str_to_float(argv[2]);
	printf("a: %f, b: %f\n", mlx.cx, mlx.cy);
	setdef(&mlx);
	def(&mlx);
	mlx_mouse_hook(mlx.win, &mouse_hooks, &mlx);
	mlx_hook(mlx.win, 2, 1L << 2, &hooks, &mlx);
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