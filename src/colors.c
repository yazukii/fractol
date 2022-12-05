/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:25:49 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/05 15:38:13 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

t_imgd	pixels(t_res pos, int i, t_imgd img, t_complex z)
{
	static double	prev;
	int			r;
	int			g;
	int			b;
	double		t = (double)i / MAX_ITER;

	r = 9 * (1 - t) * pow(t, 3) * 255;
	g = 15 * pow((1 - t), 2) * pow(t, 2) * 255;
	b = 8.5 * pow((1 - t), 3) * t * 255;
	//printf("%d, %d, %d\n", r, g, b);
	if (i < MAX_ITER)
		my_mlx_pixel_put(&img, pos.x, pos.y, create_trgb(0, r, g, b));
	else
		my_mlx_pixel_put(&img, pos.x, pos.y, create_trgb(0, 0, 0, 0));
	return (img);
}

t_imgd	jpixels(t_res pos, int i, t_imgd img)
{
	if (i < MAX_ITER)
		my_mlx_pixel_put(&img, pos.x, pos.y, create_trgb(0, 55, ((double)i / 100) * 255, 55));
	else
		my_mlx_pixel_put(&img, pos.x, pos.y, create_trgb(0, 0, 0, 0));
	return (img);
}
