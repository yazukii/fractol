/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:26:19 by yidouiss          #+#    #+#             */
/*   Updated: 2022/12/20 13:33:08 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <time.h>

# define MAX_ITER 50
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
}	t_imgd;

typedef struct w_data {
	void		*mlx;
	void		*win;
	double		maxre;
	double		minre;
	double		minim;
	double		maxim;
	double		re;
	double		im;
	int			i;
	int			x;
	int			y;
	int			t;
	int			px;
	int			py;
	int			sw;
	void		*img;
	char		*addr;
	double			r;
	double			g;
	double			b;
	int			bpp;
	int			l_l;
	int			endian;
	t_imgd		p;
	t_cplane	def;
}	t_data;

// FUNCTIONS

void	pixels(int x, int y, t_data *mlx);
int		def(void *param);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
int		zoom(int button, int x, int y, void *param);
void	*mandelbrot(void *param);
void	julia(void *param, int x, int y);
int		call(t_data *mlx);
void	setdef(void *param);
int		hooks(int key, void *param);
int		killwin(void *param);
int		hook_mousemove(int button, int x, int y, void *param);

#endif