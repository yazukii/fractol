/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:22:25 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/20 13:08:10 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

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
		if (z2.re + z2.im > 4)
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
	double	rgre;
	double	rgim;

	mlx = param;
	mlx->px = 0;
	mlx->py = 0;
	while (mlx->py < mlx->y)
	{
		rgim = mlx->maxim - mlx->minim;
		mlx->im = (mlx->maxim - (mlx->py) * ((rgim) / (mlx->y - 1)));
		while (mlx->px < mlx->x)
		{
			rgre = mlx->maxre - mlx->minre;
			mlx->re = (mlx->minre + (mlx->px) * ((rgre) / (mlx->x - 1)));
			mandelbrot_calc(mlx);
			mlx->px += 1;
		}
		mlx->px = 0;
		mlx->py += 1;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (param);
}
