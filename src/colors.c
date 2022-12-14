/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:25:49 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/22 18:09:44 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	pixels(int x, int y, t_data *mlx)
{
	int			r;
	int			g;
	int			b;
	double		t;

	t = (double)mlx->i / MAX_ITER;
	r = (int)(mlx->r * (1 - t) * pow(t, 3) * 220);
	g = (int)(mlx->g * pow((1 - t), 2) * pow(t, 2) * 255);
	b = (int)(mlx->b * pow((1 - t), 3) * t * 255);
	if (x < mlx->x && y < mlx->y)
	{
		if (mlx->i < MAX_ITER)
			my_mlx_pixel_put(mlx, x, y, create_trgb(0, r, g, b));
		else
			my_mlx_pixel_put(mlx, x, y, create_trgb(0, 0, 0, 0));
	}
}
