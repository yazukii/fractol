/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:45:26 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/05 18:56:42 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

int	setdef(void *param)
{
	t_data	*mlx;

	mlx = param;
	mlx->def.minre = -2.5;
	mlx->def.maxre = 2.5;
	mlx->def.minim = -1.3;
	mlx->def.maxim = 1.3;
	mlx->minre = mlx->def.minre;
	mlx->maxre = mlx->def.maxre;
	mlx->minim = mlx->def.minim;
	mlx->maxim = mlx->def.maxim;
	return (0);
}

int	def(void *param)
{
	t_data *mlx;

	mlx = param;
	mlx->minre = mlx->def.minre;
	mlx->maxre = mlx->def.maxre;
	mlx->minim = mlx->def.minim;
	mlx->maxim = mlx->def.maxim;
	mandelbrot(*mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		mlx;

	(void)argc;
	setdef(&mlx);
	mlx.x = ft_atoi(argv[1]);
	mlx.y = ft_atoi(argv[2]);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, mlx.x, mlx.y, "fractol");
	if (argv[3][0] == 'j')
	{
		julia(mlx, 661, 613);
		mlx_mouse_hook(mlx.win, hook_mousemove, &mlx);
	}
	else
	{
		mandelbrot(mlx);
		mlx_mouse_hook(mlx.win, &zoom, &mlx);
	}
	mlx_key_hook(mlx.win, &hooks, &mlx);
	//mlx_hook(mlx.win, 17, 0L, &killwin, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
