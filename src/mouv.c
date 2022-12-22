/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:10:39 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/22 18:17:40 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

int	zoomout(int x, int y, void *param)
{	
	t_cplane	cp;
	t_complex	rg;
	t_complex	eps;
	t_data		*mlx;

	mlx = param;
	rg.re = mlx->maxre - mlx->minre;
	rg.im = mlx->maxim - mlx->minim;
	if (rg.re < 0)
		rg.re *= -1;
	if (rg.im < 0)
		rg.im *= -1;
	eps.re = rg.re / (mlx->x);
	eps.im = rg.im / (mlx->y);
	mlx->minre = mlx->minre - (rg.re / STEP);
	mlx->maxre = mlx->maxre + (rg.re / STEP);
	mlx->minim = mlx->minim - (rg.im / STEP);
	mlx->maxim = mlx->maxim + (rg.im / STEP);
	call(mlx);
	return (0);
}

int	zoom(int x, int y, void *param)
{
	t_cplane	cp;
	t_data		*mlx;
	t_complex	rg;
	t_complex	eps;

	mlx = param;
	rg.re = mlx->maxre - mlx->minre;
	rg.im = mlx->maxim - mlx->minim;
	if (rg.re < 0)
		rg.re *= -1;
	if (rg.im < 0)
		rg.im *= -1;
	eps.re = rg.re / (mlx->x);
	eps.im = rg.im / (mlx->y);
	mlx->minre = mlx->minre + (rg.re / STEP);
	mlx->maxre = mlx->maxre - (rg.re / STEP);
	mlx->minim = mlx->minim + (rg.im / STEP);
	mlx->maxim = mlx->maxim - (rg.im / STEP);
	call(mlx);
	return (0);
}

void	pan(int dir, void *param)
{
	t_data	*mlx;

	mlx = param;
	if (dir == 2)
	{
		mlx->minre += (mlx->maxre / STEP);
		mlx->maxre += (mlx->maxre / STEP);
	}
	if (dir == 1)
	{
		mlx->minre -= (mlx->maxre / STEP);
		mlx->maxre -= (mlx->maxre / STEP);
	}
	if (dir == 4)
	{
		mlx->minim += (mlx->maxim / STEP);
		mlx->maxim += (mlx->maxim / STEP);
	}
	if (dir == 3)
	{
		mlx->minim -= (mlx->maxim / STEP);
		mlx->maxim -= (mlx->maxim / STEP);
	}
	call(mlx);
}

void	shift_julia(int dir, void *param)
{
	t_data	*mlx;

	mlx = param;
	if (dir == 2)
	{
		mlx->cx += 0.05;
	}
	if (dir == 1)
	{
		mlx->cx -= 0.05;
	}
	if (dir == 4)
	{
		mlx->cy += 0.05;
	}
	if (dir == 3)
	{
		mlx->cy -= 0.05;
	}
	call(mlx);
}
