/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:48:42 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/08 17:06:51 by yidouiss         ###   ########.fr       */
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
	mlx->minre = (mlx->minre + (((double)x - 960) * eps.re)) - (rg.re / STEP);
	mlx->maxre = (mlx->maxre + (((double)x - 960) * eps.re)) + (rg.re / STEP);
	mlx->minim = (mlx->minim - (((double)y - 540) * eps.im)) - (rg.im / STEP);
	mlx->maxim = (mlx->maxim - (((double)y - 540) * eps.im)) + (rg.im / STEP);
	callman(*mlx);
	return (0);
}

int	zoom(int button, int x, int y, void *param)
{
	t_cplane	cp;
	t_data		*mlx;
	t_complex	rg;
	t_complex	eps;

	mlx = param;
	if (button == 4 && y >= 0)
	{
		rg.re = mlx->maxre - mlx->minre;
		rg.im = mlx->maxim - mlx->minim;
		if (rg.re < 0)
			rg.re *= -1;
		if (rg.im < 0)
			rg.im *= -1;
		eps.re = rg.re / (mlx->x);
		eps.im = rg.im / (mlx->y);
		mlx->minre = (mlx->minre + (((double)x - 960) * eps.re)) + (rg.re / STEP);
		mlx->maxre = (mlx->maxre + (((double)x - 960) * eps.re)) - (rg.re / STEP);
		mlx->minim = (mlx->minim - (((double)y - 540) * eps.im)) + (rg.im / STEP);
		mlx->maxim = (mlx->maxim - (((double)y - 540) * eps.im)) - (rg.im / STEP);
		callman(*mlx);
	}
	else if (button == 5 && y >= 0)
		zoomout(x, y, mlx);
	//mlx_mouse_move(mlx->win, mlx->x / 2, mlx->y / 2);
	//TODO this lol
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
	if (dir == 3)
	{
		mlx->minim += (mlx->maxim / STEP);
		mlx->maxim += (mlx->maxim / STEP);
	}
	if (dir == 4)
	{
		mlx->minim -= (mlx->maxim / STEP);
		mlx->maxim -= (mlx->maxim / STEP);
	}
	callman(*mlx);
}

int	hooks(int keycode, void *param)
{
	t_data		*mlx;
	t_complex	rg;

	mlx = param;
	if (keycode == 15)
		def(mlx);
	if (keycode == 53)
	{
		mlx_destroy_image(mlx->mlx, mlx->win);
		mlx_clear_window(mlx->mlx, mlx->win);
		exit (0);
	}
	if (keycode == 6)
	{
		rg.re = mlx->maxre - mlx->minre;
		rg.im = mlx->maxim - mlx->minim;
		mlx->minre += rg.re / STEP;
		mlx->maxre -= rg.re / STEP;
		mlx->minim += rg.im / STEP;
		mlx->maxim -= rg.im / STEP;
		callman(*mlx);
	}
	if (keycode == 15)
	{
		mlx->minre = -2.5;
		mlx->maxre = 2.5;
	}
	if (keycode < 127 && keycode > 122)
		pan(keycode - 122, mlx);
	return (0);
}

int	killwin(void *param)
{
	t_data	*mlx;

	mlx = param;
	mlx_destroy_image(mlx->mlx, mlx->win);
	mlx_clear_window(mlx->mlx, mlx->win);
	exit (0);
	return (0);
}
