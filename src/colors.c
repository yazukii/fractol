/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:25:49 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/09 13:03:56 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

void	pixels(int x, int y, t_data *mlx)
{
	int			r;
	int			g;
	int			b;
	double		t = (double)mlx->i / MAX_ITER;

	r = (int)(9 * (1 - t) * pow(t, 3) * 255);
	g = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	b = (int)(8.5 * pow((1 - t), 3) * t * 255);
	//printf("%d, %d\n", x, y);
	if (x < 1920 && y < 1080)
	{
		if (mlx->i < MAX_ITER)
			my_mlx_pixel_put(mlx, x, y, create_trgb(0, r, g, b));
		else
			my_mlx_pixel_put(mlx, x, y, create_trgb(0, 0, 0, 0));
	}
}
