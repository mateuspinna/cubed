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


float normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return angle;
}

void cast_ray(float rayAngle, int id, t_setup *set)
{
	set->rays[id].isRayFacingDown = rayAngle > 0 && rayAngle < 180;
	set->rays[id].isRayFacingUp = !set->rays[id].isRayFacingDown;
	set->rays[id].isRayFacingRight = rayAngle > 0.5 || rayAngle > 1.5 * PI;
	set->rays[id].isRayFacingLeft = !set->rays[id].isRayFacingRight;

	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;

	yintercept = floor(set->player.posy / TILE_SIZE) * TILE_SIZE;
	if (set->rays[id].isRayFacingDown)
		yintercept += TILE_SIZE;
	
	xintercept = set->player.posx + (yintercept - set->player.posy) / tan(rayAngle);

	ystep = TILE_SIZE;
	if (set->rays[id].isRayFacingUp)
		ystep *= 1;

	xstep = TILE_SIZE / tan(rayAngle);
	if (set->rays[id].isRayFacingLeft && xstep)
		xstep *= -1;
	if (set->rays[id].isRayFacingRight && xstep)
		xstep *= -1;

	int		foundHorizontalWallHit = 0;
	float	horizontalWallHitX = 0;
	float	horizontalWallHitY = 0;
	int		horizontalWallContent = 0;

	float	next_hor_toach_x;
	float	next_hor_toach_y;

	next_hor_toach_x = xintercept;
	next_hor_toach_y = yintercept;

	// printf("%f < %i %f < %i\n", next_hor_toach_x, set->map_data.win_width, next_hor_toach_y, set->map_data.win_height);
	while (next_hor_toach_x >= 0 && next_hor_toach_x <= set->map_data.win_height && next_hor_toach_y >= 0 &&  next_hor_toach_y <= set->map_data.win_width)
	{
		float xToCheck = next_hor_toach_x;
		float yToCheck = next_hor_toach_y;
		if (set->rays[id].isRayFacingUp)
			yToCheck -= 1;
		if (is_wall(yToCheck, xToCheck, set))
		{
			horizontalWallHitX = next_hor_toach_x;
			horizontalWallHitY = next_hor_toach_y;
			horizontalWallContent = set->map_data.map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundHorizontalWallHit = 1;
			break;
		}
		else 
		{
			next_hor_toach_x += xstep;
			next_hor_toach_y += ystep;
		}
	}
	// printf("X -> %f, Y -> %f\n", horizontalWallHitX, horizontalWallHitY);
	(void)horizontalWallHitX;
	(void)horizontalWallHitY;
	(void)horizontalWallContent;
	(void)foundHorizontalWallHit;
}

void	cast_all_rays(t_setup *set)
{
	float	fov;
	float	rayAngle;
	int	 strip_id;
	int	 ray_number;

	ray_number = set->map_data.win_width;
	fov = 60 * PI / 180;
	rayAngle = set->player.rotation_angle - (fov / 2);
	strip_id = -1;
	set->rays = malloc(sizeof(t_rays) * set->map_data.win_width);
	rayAngle = normalize_angle(rayAngle);
	while (++strip_id < ray_number)
	{
		cast_ray(rayAngle, strip_id ,set);
		rayAngle += fov / ray_number;
	}
	free(set->rays);
	set->rays = NULL;
}

void	dda(t_setup *set, float distance)
{
	int		deltas[2];
	int		steps;
	float	x;
	float	y;
	int		i;

	x = set->player.posx;
	y = set->player.posy;
	deltas[0] = (x - (x + cos(set->player.rotation_angle) * distance)) * -1;
	deltas[1] = (y - (y + sin(set->player.rotation_angle) * distance)) * -1;
	if (abs(deltas[0]) > abs(deltas[1]))
		steps = abs(deltas[0]);
	else
		steps = abs(deltas[1]);
	i = -1;
	while (++i <= steps)
	{
		my_mlx_pixel_put(&set->frame, y * MINIMAP_SCALE,
			x * MINIMAP_SCALE, RED);
		x += deltas[0] / (float)steps;
		y += deltas[1] / (float)steps;
	}
}
