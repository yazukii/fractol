/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:26:19 by yidouiss          #+#    #+#             */
/*   Updated: 2022/11/25 18:59:59 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <unistd.h>

// STRUCTS

typedef struct	s_complex
{
	double		re;
	double		im;
}	t_complex;

typedef struct	s_res
{
	double		x;
	double		y;
}	t_res;

typedef struct	s_plane
{
	double	MaxRe;
	double	MinRe;
	double	MinIm;
	double	MaxIm;
}	t_cplane;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	w_data {
	void	*mlx;
	void	*win;
}	w_data;

// FUNCTIONS

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);