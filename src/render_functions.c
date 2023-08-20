/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:08:52 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/07/07 16:08:59 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_floor_celling(t_setup *set)
{
	int	x;
	int	y;

	set->frame.img = mlx_new_image(set->mlx,
			set->map_data.win_width, set->map_data.win_height);
	set->frame.addr = mlx_get_data_addr(set->frame.img, &set->frame.bpp,
			&set->frame.line_len, &set->frame.endian);
	x = -1;
	while (++x < set->map_data.win_width)
	{
		y = -1;
		while (++y < set->map_data.win_height / 2)
		{
			my_mlx_pixel_put(&set->frame, x, y, set->map_data.c_color);
			my_mlx_pixel_put(&set->frame, x,
				y + (set->map_data.win_height / 2), set->map_data.f_color);
		}
	}
}

void	render_strip(int x, t_rays *ray, t_setup *set, int *tex)
{	
	float	rate;
	float	tex_pos;
	int		tex_y;

	rate = (float) 64 / ray->line_height;
	tex_pos = (ray->draw_start - set->map_data.win_height / 2
			+ ray->line_height / 2) * rate;
	while (ray->draw_start <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (T_HEIGHT - 1);
		tex_pos += rate;
		my_mlx_pixel_put(&set->frame, x, ray->draw_start++, tex[tex_y]);
	}
}
