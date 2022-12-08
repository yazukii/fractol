/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:26:19 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/08 17:59:51 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# define MAX_ITER 100
# define STEP 20

// STRUCTS

typedef struct s_complex
{
	double		re;
	double		im;
}	t_complex;

typedef struct s_pixel
{
	t_complex	c;
	int			i;
}	t_pixel;

typedef struct s_res
{
	int		x;
	int		y;
}	t_res;

typedef struct s_plane
{
	double	maxre;
	double	minre;
	double	minim;
	double	maxim;
}	t_cplane;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_imgd;

typedef struct w_data {
	void	*mlx;
	void	*win;
	double	maxre;
	double	minre;
	double	minim;
	double	maxim;
	int	x;
	int	y;
	t_imgd	p;
	t_cplane	def;
}	t_data;

// FUNCTIONS

t_imgd	pixels(t_res pos, int i, t_imgd img);
int		def(void *param);
void	my_mlx_pixel_put(t_imgd *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
int		zoom(int button, int x, int y, void *param);
t_pixel	mandelbrot(int x, int y, t_data mlx);
int		callman(t_data mlx);
int		hooks(int keycode, void *param);
int		killwin(void *param);
int		hook_mousemove(int button, int x, int y, void *param);
void	julia(t_data mlx, int x, int y);

#endif