/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:45:26 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/01 19:23:43 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

t_imgd	pixels(t_res pos, int i, t_imgd img, t_complex z)
{
	static double prev;
	double 	v;
	double s;
	double	L;
	double C;
	double H;
	double	smooth;

	s = (double)i / MAX_ITER;
	v = 1.0 - powf(cos(M_PI * s), 2.0);
	smooth = (i + 2 - log(log(z.re * z.re + z.im * z.im) / M_LN2) / M_LN2) / 42;\
	if (i < MAX_ITER)
		my_mlx_pixel_put(&img, pos.x, pos.y, create_trgb(0, 55, smooth * 255, 55));
	else
		my_mlx_pixel_put(&img, pos.x, pos.y, create_trgb(0, 0, 0, 0));
	return (img);
}

t_imgd	iter(t_complex z, t_complex c, t_res pos, t_imgd p)
{
	t_complex	z2;
	int i;

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

void	fractal(t_data mlx)
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

int	main(int argc, char **argv)
{
	t_data		mlx;	

	(void) argc;
	mlx.minre = -2.5;
	mlx.maxre = 2.5;
	mlx.x = ft_atoi(argv[1]);
	mlx.y = ft_atoi(argv[2]);
	mlx.minim = -1.3;
	mlx.maxim = 1.3;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, mlx.x, mlx.y, "fractol");
	fractal(mlx);
	mlx_mouse_hook(mlx.win, &zoom, &mlx);
	mlx_key_hook(mlx.win, &hooks, &mlx);
	mlx_hook(mlx.win, 17, 0L, &killwin, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
