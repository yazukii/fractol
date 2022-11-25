/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:45:26 by yidouiss          #+#    #+#             */
/*   Updated: 2022/11/25 18:56:12 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

t_data	pixels(int x, int y, int i, t_data img)
{
	if (i < 40)
		my_mlx_pixel_put(&img, x, y, create_trgb(0, 255, i * 10, 255));
	else if (i < 80)
		my_mlx_pixel_put(&img, x, y, create_trgb(0, i * 10, 255, 255));
	else if (i < 101)
		my_mlx_pixel_put(&img, x, y, create_trgb(0, 255, 255, i * 10));
	return (img);
}

int	iter(t_complex z, t_complex c, int i)
{
	t_complex	z2;

	while (i < 100)
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

void	fractal(w_data mlx, t_res res, t_data p)
{
	t_complex	c;
	t_complex	z;
	t_res		pos;
	t_cplane	cp;
	int			i;

	cp.MinRe = -2.5;
	cp.MaxRe = 2.5;
	cp.MinIm = cp.MinRe * (res.y / res.x);
	p.img = mlx_new_image(mlx.mlx, 1920, 1080);
	p.addr = mlx_get_data_addr(p.img, &p.bpp, &p.line_length, &p.endian);
	while (pos.y < res.y)
	{
		c.im = -cp.MinIm - pos.y * ((-cp.MinIm - cp.MinIm) / (res.y - 1));
		while (pos.x < res.x)
		{
			c.re = cp.MinRe + pos.x * ((cp.MaxRe - cp.MinRe) / (res.x - 1));
			z = c;
			i = iter(z, c, i);
			p.img = pixels(pos.x, pos.y, i, p).img;
			pos.x++;
			i = 0;
		}
		pos.x = 0;
		pos.y++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, p.img, 0, 0);
}

int	main(int argc, char **argv)
{
	w_data		mlx;
	t_res		res;
	t_data		img;

	(void) argc;
	res.x = ft_atoi(argv[1]);
	res.y = ft_atoi(argv[2]);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, res.x, res.y, "fractol");
	fractal(mlx, res, img);
	mlx_loop(mlx.mlx);
	return (0);
}
