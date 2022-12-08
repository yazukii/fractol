/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:45:26 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/08 17:51:51 by yidouiss         ###   ########.fr       */
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

int	die(char *reason)
{
	ft_putendl_fd(reason, 1);
	return (1);
}

int	def(void *param)
{
	t_data *mlx;

	mlx = param;
	mlx->minre = mlx->def.minre;
	mlx->maxre = mlx->def.maxre;
	mlx->minim = mlx->def.minim;
	mlx->maxim = mlx->def.maxim;
	callman(*mlx);
	return (0);
}

int	callman(t_data mlx)
{
	t_pixel	f;
	t_res	pos;
	t_imgd	p;

	pos.x = 0;
	pos.y = 0;
	p.img = mlx_new_image(mlx.mlx, mlx.x, mlx.y);
	p.addr = mlx_get_data_addr(p.img, &p.bpp, &p.line_length, &p.endian);
	while (pos.y < mlx.y)
	{
		while (pos.x < mlx.x)
		{
			f = mandelbrot(pos.x, pos.y, mlx);
			p.img = pixels(pos, f.i, p).img;
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, p.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		mlx;

	setdef(&mlx);
	if (argc <= 3)
		return (die("error: Not enough arguments"));
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
		callman(mlx);
		mlx_mouse_hook(mlx.win, &zoom, &mlx);
	}
	mlx_key_hook(mlx.win, &hooks, &mlx);
	//mlx_hook(mlx.win, 17, 0L, &killwin, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
