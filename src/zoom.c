/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:48:42 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/21 17:28:58 by yidouiss         ###   ########.fr       */
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

int	mouse_hooks(int button, int x, int y, void *param)
{
	t_data	*mlx;

	mlx = param;
	if (button == 4)
		zoom(x, y, mlx);
	if (button == 5)
		zoomout(x, y, mlx);
	if (button == 1 && mlx->sw == 1)
	{
		mlx->cx = (double)x;
		mlx->cx = (double)y;
		call(mlx);
	}
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

void	switch_set(t_data *mlx, int x)
{
	if (x == 1)
		mlx->sw = 1;
	else
		mlx->sw = 0;
	printf("X");
	setdef(mlx);
	call(mlx);
}

int	hooks(int keycode, void *param)
{
	t_data		*mlx;
	t_complex	rg;

	mlx = param;
	if (keycode == 15)
	{
		setdef(mlx);
		call(mlx);
	}
	if (keycode == 53)
		killwin(mlx);
	if (keycode == 6)
		zoom(1, 1, mlx);
	if (keycode < 127 && keycode > 122)
		pan(keycode - 122, mlx);
	if (keycode == 38)
		switch_set(mlx, 1);
	if (keycode == 46)
		switch_set(mlx, 0);
	return (0);
}

int	killwin(void *param)
{
	t_data	*mlx;

	mlx = param;
	mlx_destroy_image(mlx->mlx, mlx->win);
	mlx_clear_window(mlx->mlx, mlx->win);
	exit (0);
}
/*
mlx->minre = (mlx->minre + (((double)x - 960) * eps.re)) + (rg.re / STEP);
mlx->maxre = (mlx->maxre + (((double)x - 960) * eps.re)) - (rg.re / STEP);
mlx->minim = (mlx->minim + (((double)y - 540) * eps.im)) + (rg.im / STEP);
mlx->maxim = (mlx->maxim + (((double)y - 540) * eps.im)) - (rg.im / STEP);
*/