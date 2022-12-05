/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:22:25 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/05 19:02:27 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

t_imgd	iter(t_complex z, t_complex c, t_res pos, t_imgd p)
{
	t_complex	z2;
	int			i;

	i = 0;
	while (i < MAX_ITER)
	{
		z2.re = z.re * z.re;
		z2.im = z.im * z.im;
		if (z2.re + z2.im > 4)
			break ;
		z.im = 2 * z.re * z.im + c.im;
		z.re = z2.re - z2.im + c.re;
		i++;
	}
	p.img = pixels(pos, i, p, z).img;
	return (p);
}

void	mandelbrot(t_data mlx)
{
	t_complex	c;
	t_complex	z;
	t_res		pos;
	t_imgd		p;
	int			i;

	p.img = mlx_new_image(mlx.mlx, mlx.x, mlx.y);
	p.addr = mlx_get_data_addr(p.img, &p.bpp, &p.line_length, &p.endian);
	while (pos.y < mlx.y)
	{
		c.im = mlx.minim - pos.y * ((mlx.minim - mlx.maxim) / (mlx.y - 1));
		while (pos.x < mlx.x)
		{
			c.re = mlx.minre + pos.x * ((mlx.maxre - mlx.minre) / (mlx.x - 1));
			z = c;
			p.img = iter(z, c, pos, p).img;
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, p.img, 0, 0);
}
