/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:43:15 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/07/15 19:17:59 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_delta_dist(t_setup *set, t_rays *ray, int x)
{
	ray->camera_x = 2 * x / (float)set->map_data.win_width - 1;
	ray->ray_dirx = set->player.dir_x + set->player.plane_x * ray->camera_x;
	ray->ray_diry = set->player.dir_y + set->player.plane_y * ray->camera_x;
	ray->map_x = (int)set->player.posx;
	ray->map_y = (int)set->player.posy;
	if (ray->ray_dirx == 0)
		ray->delta_distx = 1e30;
	else
		ray->delta_distx = fabs(1 / ray->ray_dirx);
	if (ray->ray_diry == 0)
		ray->delta_disty = 1e30;
	else
		ray->delta_disty = fabs(1 / ray->ray_diry);
}

void	calculate_side_dist(t_setup *set, t_rays *ray)
{
	if (ray->ray_dirx < 0)
	{
		ray->step_x = -1;
		ray->side_distx = (set->player.posx - ray->map_x) * ray->delta_distx;
	}
	else
	{
		ray->step_x = 1;
		ray->side_distx = (ray->map_x + 1.0 - set->player.posx)
			* ray->delta_distx;
	}
	if (ray->ray_diry < 0)
	{
		ray->step_y = -1;
		ray->side_disty = (set->player.posy - ray->map_y)
			* ray->delta_disty;
	}
	else
	{
		ray->step_y = 1;
		ray->side_disty = (ray->map_y + 1.0 - set->player.posy)
			* ray->delta_disty;
	}
}

void	calculate_wall_distance(t_setup *set, t_rays *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (set->map_data.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->distance = (ray->side_distx - ray->delta_distx);
	else
		ray->distance = (ray->side_disty - ray->delta_disty);
}

void	projection(t_setup *set, t_rays *ray, int x)
{
	int	texture_strip[64];
	int	i;

	ray->line_height = (int)((set->map_data.win_height) / ray->distance);
	ray->draw_start = -ray->line_height / 2 + set->map_data.win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + set->map_data.win_height / 2;
	if (ray->draw_end >= set->map_data.win_height)
		ray->draw_end = set->map_data.win_height - 1;
	if (ray->side == 0)
		ray->wall_hit_x = set->player.posy + ray->distance * ray->ray_diry;
	else
		ray->wall_hit_x = set->player.posx + ray->distance * ray->ray_dirx;
	ray->wall_hit_x -= floor(ray->wall_hit_x);
	set_texture_details(ray);
	i = -1;
	while (++i < 64)
		texture_strip[i] = get_pixel_color(set->texture[ray->texture_index],
				ray->tex_x, i);
	render_strip(x, ray, set, texture_strip);
}

void	cast_all_rays(t_setup *set)
{
	int		x;
	t_rays	ray;

	x = -1;
	while (++x < set->map_data.win_width)
	{
		ft_memset(&ray, 0, sizeof(t_rays));
		calculate_delta_dist(set, &ray, x);
		calculate_side_dist(set, &ray);
		calculate_wall_distance(set, &ray);
		projection(set, &ray, x);
	}
}
