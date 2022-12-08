/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:01:17 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/07 14:42:42 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

t_imgd	iterj(t_complex c, t_res pos, t_imgd p, t_complex j)
{
	t_complex	z2;
	int			i;

	i = 0;
	while (i < MAX_ITER)
	{
		z2.re = c.re * c.re;
		z2.im = c.im * c.im;
		if (z2.re + z2.im > 4)
			break ;
		c.im = 2 * c.re * c.im + j.im;
		c.re = z2.re - z2.im + j.re;
		i++;
	}
	p.img = pixels(pos, i, p).img;
	return (p);
}

void	julia(t_data mlx, int x, int y)
{
	t_complex	c;
	t_complex	j;
	t_res		pos;
	t_imgd		p;

	p.img = mlx_new_image(mlx.mlx, mlx.x, mlx.y);
	p.addr = mlx_get_data_addr(p.img, &p.bpp, &p.line_length, &p.endian);
	while (pos.y < mlx.y)
	{
		c.im = mlx.minim - pos.y * ((mlx.minim - mlx.maxim) / (mlx.y - 1));
		j.im = mlx.minim - y * ((mlx.minim - mlx.maxim) / (mlx.y - 1));
		while (pos.x < mlx.x)
		{
			c.re = mlx.minre + pos.x * ((mlx.maxre - mlx.minre) / (mlx.x - 1));
			j.re = mlx.minre + x * ((mlx.maxre - mlx.minre) / (mlx.x - 1));
			p.img = iterj(c, pos, p, j).img;
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, p.img, 0, 0);
}

int	hook_mousemove(int button, int x, int y, void *param)
{
	t_data	*mlx;

	mlx = param;
	julia(*mlx, x, y);
	return (0);
}
