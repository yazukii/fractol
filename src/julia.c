/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:01:17 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/22 18:07:49 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	julia_calc(t_data *mlx)
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
		z.im = 2 * z.re * z.im + mlx->j.im;
		z.re = z2.re - z2.im + mlx->j.re;
		mlx->i += 1;
	}
	pixels(mlx->px, mlx->py, mlx);
}

void	julia(void *param, double x, double y)
{
	t_data		*mlx;
	double		rgim;
	double		rgre;

	mlx = param;
	mlx->px = 0;
	mlx->py = 0;
	while (mlx->py < mlx->y)
	{
		rgim = mlx->maxim - mlx->minim;
		mlx->im = (mlx->maxim - (mlx->py) * ((rgim) / (mlx->y - 1)));
		mlx->j.im = y;
		while (mlx->px < mlx->x)
		{
			rgre = mlx->maxre - mlx->minre;
			mlx->re = (mlx->minre + (mlx->px) * ((rgre) / (mlx->x - 1)));
			mlx->j.re = x;
			julia_calc(mlx);
			mlx->px += 1;
		}
		mlx->px = 0;
		mlx->py += 1;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
//TODO pan with j.im and j.re