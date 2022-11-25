/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:45:26 by yidouiss          #+#    #+#             */
/*   Updated: 2022/11/25 16:43:15 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

int	main(int argc, char **argv)
{
	(void)argc;
	w_data mlx;
	unsigned long int		i = 0;
	unsigned long int		x;
	unsigned long int		y = 0;
	double						resx = ft_atoi(argv[1]);
	double						resy = ft_atoi(argv[2]);
	t_complex				c;
	t_complex				Z;
	t_data	img;
	double MinRe = -3.0;
	double MaxRe = 3.0;
	double MinIm = MinRe * (resy/resx);
	double MaxIm = MinIm * -1;
	double Re_fact;
	double Im_fact;
	double c_im;
	double c_re;
	double Z_re;
	double Z_im;
	double Z_re2;
	double Z_im2;
	
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, resx, resy, "fractol");
	img.img = mlx_new_image(mlx.mlx, resx, resy);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	Re_fact = (MaxRe - MinRe) / (resx - 1);
	Im_fact = (MaxIm - MinIm) / (resy - 1);
	while (y < resy)
	{
		c_im = MaxIm - y * Im_fact;
		while (x < resx)
		{
			c_re = MinRe + x * Re_fact;
			Z_re = c_re; 
			Z_im = c_im; // Set Z = c
			while (i < 100)
			{
				Z_re2 = Z_re * Z_re;
				Z_im2 = Z_im * Z_im;
				if(Z_re2 + Z_im2 > 4)
					break;
				Z_im = 2 * Z_re * Z_im + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
				i++;
			}
			if (i < 40)
				my_mlx_pixel_put(&img, x, y, create_trgb(0, 255, i * 10, 255));
			else if (i < 80)
				my_mlx_pixel_put(&img, x, y, create_trgb(0, i * 10, 255, 255));
			else if (i < 101)
				my_mlx_pixel_put(&img, x, y, create_trgb(0, 255, 255, i * 10));
			x++;
			i = 0;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}