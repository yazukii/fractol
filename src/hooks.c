/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:48:42 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/22 18:11:40 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

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
		mlx->cx = mlx->minre + x * ((mlx->maxre - mlx->minre) / (mlx->x - 1));
		mlx->cy = mlx->minim - y * ((mlx->minim - mlx->maxim) / (mlx->y - 1));
		call(mlx);
	}
	return (0);
}

void	switch_set(t_data *mlx, int x)
{
	if (x == 1)
		mlx->sw = 1;
	else
		mlx->sw = 0;
	setdef(mlx);
	call(mlx);
}

int	switch_arr(t_data *mlx, int x)
{
	if (x == 7)
		x = 1;
	else
		x = 0;
	return (x);
}

int	hooks(int keycode, void *param)
{
	t_data		*mlx;
	t_complex	rg;
	static int	sw;

	mlx = param;
	if (keycode == 7 || keycode == 8)
		sw = switch_arr(mlx, keycode);
	if (keycode == 15)
	{
		setdef(mlx);
		call(mlx);
	}
	if (keycode == 53)
		killwin(mlx);
	if (keycode == 6)
		zoom(1, 1, mlx);
	if (keycode < 127 && keycode > 122 && sw == 0)
		pan(keycode - 122, mlx);
	if (keycode < 127 && keycode > 122 && sw == 1)
		shift_julia(keycode - 122, mlx);
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
