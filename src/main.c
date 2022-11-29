/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:45:26 by yidouiss          #+#    #+#             */
/*   Updated: 2022/11/29 13:33:19 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

t_data	pixels(int x, int y, int i, t_data img)
{
	if (i >= MAX_ITER)
		my_mlx_pixel_put(&img, x, y, create_trgb(0, 0, 0, 0));
	else if (i < MAX_ITER / 3)
		my_mlx_pixel_put(&img, x, y, create_trgb(0, i * (255 / (MAX_ITER / 3)), 50, 50));
	else if (i < (MAX_ITER / 3) * 2)
		my_mlx_pixel_put(&img, x, y, create_trgb(0, 255, i * (255 / (MAX_ITER / 3)), 50));
	else
		my_mlx_pixel_put(&img, x, y, create_trgb(0, 255, 255, i * (255 / (MAX_ITER / 3))));
	return (img);
}

int	iter(t_complex z, t_complex c, int i)
{
	t_complex	z2;

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
	return (i);
}

void	fractal(w_data mlx)
{
	t_complex	c;
	t_complex	z;
	t_res		pos;
	t_data		p;
	int			i;

	p.img = mlx_new_image(mlx.mlx, mlx.x, mlx.y);
	p.addr = mlx_get_data_addr(p.img, &p.bpp, &p.line_length, &p.endian);
	while (pos.y < mlx.y)
	{
		c.im = -mlx.MinIm - pos.y * ((-mlx.MinIm - mlx.MinIm) / (mlx.y - 1));
		while (pos.x < mlx.x)
		{
			c.re = mlx.MinRe + pos.x * ((mlx.MaxRe - mlx.MinRe) / (mlx.x - 1));
			z = c;
			i = iter(z, c, i);
			p.img = pixels(pos.x, pos.y, i, p).img;
			pos.x++;
			i = 0;
		}
		pos.x = 0;
		pos.y++;
	}
	my_mlx_pixel_put(&p, 1920 / 2, 1080 / 2, create_trgb(0, 255, 0, 0));
	mlx_put_image_to_window(mlx.mlx, mlx.win, p.img, 0, 0);
}

int	main(int argc, char **argv)
{
	w_data		mlx;	

	(void) argc;
	mlx.MinRe = -2.5;
	mlx.MaxRe = 2.5;
	mlx.x = ft_atoi(argv[1]);
	mlx.y = ft_atoi(argv[2]);
	mlx.MinIm = -1.3;
	mlx.MaxIm = 1.3;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, mlx.x, mlx.y, "fractol");
	fractal(mlx);
	mlx_mouse_hook(mlx.win, &zoom, &mlx);
	mlx_key_hook(mlx.win, &hooks, &mlx);
	mlx_hook(mlx.win, 17, 0L, &killwin, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
