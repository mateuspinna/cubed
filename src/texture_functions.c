/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:17:21 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/08/12 18:17:23 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_color(t_texture texture, int x, int y)
{
	int	color;

	color = *(int *)(texture.texture_img.addr + y
			* texture.texture_img.line_len + x * texture.texture_img.bpp / 8);
	return (color);
}

void	texture_images(t_setup *set, t_texture *texture, char *path)
{
	texture->height = 0;
	texture->width = 0;
	texture->texture_img.img = mlx_xpm_file_to_image(set->mlx, path,
			&texture->width, &texture->height);
	texture->texture_img.addr = mlx_get_data_addr(texture->texture_img.img,
			&texture->texture_img.bpp, &texture->texture_img.line_len,
			&texture->texture_img.endian);
}

void	init_texture(t_setup *set)
{
	texture_images(set, &set->texture[NORTH], set->map_data.n_path);
	texture_images(set, &set->texture[SOUTH], set->map_data.s_path);
	texture_images(set, &set->texture[EAST], set->map_data.e_path);
	texture_images(set, &set->texture[WEST], set->map_data.w_path);
}

void	set_texture_details(t_rays *ray)
{
	ray->tex_x = floor(ray->wall_hit_x * 64);
	if (ray->side == 0 && ray->ray_dirx > 0)
		ray->tex_x = ray->tex_x;
	if (ray->side == 0 && ray->ray_dirx <= 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_diry > 0)
		ray->tex_x = ray->tex_x;
	if (ray->side == 1 && ray->ray_diry <= 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if (ray->side == 0)
	{
		if (ray->ray_dirx > 0)
			ray->texture_index = EAST;
		else
			ray->texture_index = WEST;
	}
	else
	{
		if (ray->ray_diry > 0)
			ray->texture_index = SOUTH;
		else
			ray->texture_index = NORTH;
	}
}

void	clean_textures(t_setup *set)
{
	mlx_destroy_image(set->mlx, set->texture[NORTH].texture_img.img);
	mlx_destroy_image(set->mlx, set->texture[SOUTH].texture_img.img);
	mlx_destroy_image(set->mlx, set->texture[EAST].texture_img.img);
	mlx_destroy_image(set->mlx, set->texture[WEST].texture_img.img);
}
