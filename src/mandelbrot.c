/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:22:25 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/08 18:00:42 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

int ib;
ib = 0;

t_complex	screen_to_complex(int x, int y, t_data mlx)
{
	t_complex	p;

	p.re = (((double)x / mlx.x) * (mlx.maxre - mlx.minre)) * 1.0 + mlx.minre + -0.5;
	p.im = (((double)y / mlx.y) * (mlx.maxim - mlx.minim)) * 1.0 + mlx.minim;
	return (p);
}

t_pixel	mandelbrot(int x, int y, t_data mlx)
{
	t_complex	c;
	t_complex	z;
	t_complex tmp;
	int			i;

	z = screen_to_complex(x, y, mlx);
	c = screen_to_complex(x, y, mlx);
	i = 0;
	while (pow(z.re, 2) + pow(z.im, 2) < 4 && i < MAX_ITER)
	{
		tmp.re = pow(z.re, 2) - pow(z.im, 2) + c.re;
		tmp.im = z.re * z.im * 2 + c.im;
		if (z.re == tmp.re && z.im == tmp.im)
		{
			i = MAX_ITER;
			break;
		}
		z.re = tmp.re;
		z.im = tmp.im;
		i++;
	}
	//printf("%d\n", ib++);
	return((t_pixel){.c = z, .i = i});
}
