/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:48:42 by yidouiss          #+#    #+#             */
/*   Updated: 2022/11/28 20:12:05 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

int	zoom(int button, int x, int y, void *param)
{
	t_cplane	cp;
	w_data		*mlx;
	double		range;
	double		eps;

	mlx = param;
	range = mlx->MinRe - mlx->MaxRe;
	if (range < 0)
		range *= -1;
	eps = range / (mlx->x);
	printf("%f\n", mlx->MinRe);
	printf("%f\n", mlx->MaxRe);
	mlx->MinRe = (mlx->MinRe + (((double)x - 960) * eps)) * 0.2;
	mlx->MaxRe = (mlx->MaxRe + (((double)x - 960) * eps)) * 0.2;
	mlx->MinIm *= 0.2;
	mlx->MaxIm *= 0.2;
	fractal(*mlx);
	return (0);
}

int	hooks(int keycode, void *param)
{
	w_data	*mlx;

	mlx = param;
	if (keycode == 53)
	{
		mlx_destroy_image(mlx->mlx, mlx->win);
		mlx_clear_window(mlx->mlx, mlx->win);
		exit (0);
	}
	return (0);
}

int	killwin(void *param)
{
	w_data	*mlx;

	mlx = param;
	mlx_destroy_image(mlx->mlx, mlx->win);
	mlx_clear_window(mlx->mlx, mlx->win);
	exit (0);
	return (0);
}

//TODO REGLER LE ZOOM PARCE QUE CA RETOURN TJRS AU CENTRE