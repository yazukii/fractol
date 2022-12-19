/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:01:17 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/19 16:57:02 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	julia_calc(t_data *mlx, t_complex j)
{
	t_complex	c;
	t_complex	z;
	t_complex	z2;

	z.re = mlx->re;
	z.im = mlx->im;
	mlx->i = 0;
	
	while (mlx->i < MAX_ITER)
	{
		z2.re = z.re * z.re;
		z2.im = z.im * z.im;
		if(z2.re + z2.im > 4)
			break ;
		z.im = 2 * z.re * z.im + j.im;
		z.re = z2.re - z2.im + j.re;
		mlx->i += 1;
	}
	pixels(mlx->px, mlx->py, mlx);
}

void	julia(t_data mlx)
{
	t_complex	j;
	
	mlx.px = 0;
	mlx.py = 0;
	while (mlx.py < mlx.y)
	{
		mlx.im = (mlx.maxim - (mlx.py) * ((mlx.maxim - mlx.minim) / (mlx.y - 1)));
		j.im = mlx.minim - y * ((mlx.minim - mlx.maxim) / (mlx.y - 1));
		while (mlx.px < mlx.x)
		{
			mlx.re = (mlx.minre + (mlx.px) * ((mlx.maxre - mlx.minre) / (mlx.x - 1)));
			j.re = mlx.minre + x * ((mlx.maxre - mlx.minre) / (mlx.x - 1));
			julia_calc(&mlx, j);
			mlx.px += 1;
		}
		mlx.px = 0;
		mlx.py += 1;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
}

int	hook_mousemove(int button, int x, int y, void *param)
{
	t_data	*mlx;

	mlx = param;
	julia(*mlx, x, y);
	return (0);
}
