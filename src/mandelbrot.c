/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:22:25 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/19 16:38:02 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

t_complex	screen_to_complex(int x, int y, t_data mlx)
{
	t_complex	p;

	p.re = (((double)x / mlx.x) * (mlx.maxre - mlx.minre)) * 1.0 + mlx.minre + -0.5;
	p.im = (((double)y / mlx.y) * (mlx.maxim - mlx.minim)) * 1.0 + mlx.minim;
	return (p);
}

void	mandelbrot_calc(t_data *mlx)
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
		z.im = 2 * z.re * z.im + mlx->im;
		z.re = z2.re - z2.im + mlx->re;
		mlx->i += 1;
	}
	pixels(mlx->px, mlx->py, mlx);
}

void	*mandelbrot(void *param)
{
	t_data	*mlx;

	mlx = param;
	mlx->px = 0;
	mlx->py = 0;
	while (mlx->py < mlx->y)
	{
		mlx->im = (mlx->maxim - (mlx->py) * ((mlx->maxim - mlx->minim) / (mlx->y - 1)));
		while (mlx->px < mlx->x)
		{
			mlx->re = (mlx->minre + (mlx->px) * ((mlx->maxre - mlx->minre) / (mlx->x - 1)));
			mandelbrot_calc(mlx);
			mlx->px += 1;
		}
		mlx->px = 0;
		mlx->py += 1;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (param);
}