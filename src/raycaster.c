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

float hypotenuse(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return (sqrt(dx * dx + dy * dy));
}

void cast_ray(float rayAngle, int id, t_setup *set)
{
	set->rays[id].isRayFacingDown = rayAngle > 0 && rayAngle < PI;
	set->rays[id].isRayFacingUp = !set->rays[id].isRayFacingDown;
	set->rays[id].isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
	set->rays[id].isRayFacingLeft = !set->rays[id].isRayFacingRight;

	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;

	printf("R %i\n", set->rays[id].isRayFacingRight);
	// HORIZONTAL 
	yintercept = floor(set->player.posy / TILE_SIZE) * TILE_SIZE;
	if (set->rays[id].isRayFacingDown)
		yintercept += TILE_SIZE;
	
	xintercept = set->player.posx + (yintercept - set->player.posy) / tan(rayAngle);
	printf(" x %f y %f\n", xintercept, yintercept);
	ystep = TILE_SIZE;
	if (set->rays[id].isRayFacingUp)
		ystep *= -1;

	xstep = TILE_SIZE / tan(rayAngle);
	if (set->rays[id].isRayFacingLeft && xstep > 0)
		xstep *= -1;
	if (set->rays[id].isRayFacingRight && xstep < 0)
		xstep *= -1;

	int		foundHorizontalWallHit = 0;
	float	horizontalWallHitX = 0;
	float	horizontalWallHitY = 0;
	int		horizontalWallContent = 0;

	float	next_hor_toach_x;
	float	next_hor_toach_y;

	next_hor_toach_x = xintercept;
	next_hor_toach_y = yintercept;

	while (next_hor_toach_x >= 0 && next_hor_toach_x <= set->map_data.win_width && next_hor_toach_y >= 0 &&  next_hor_toach_y <= set->map_data.win_height)
	{
		int	xToCheck = (int)floor(next_hor_toach_x / TILE_SIZE);
		int	yToCheck = (int)floor(next_hor_toach_y / TILE_SIZE);
		if (set->rays[id].isRayFacingUp)
			yToCheck -= 1;
		if (set->map_data.map[yToCheck][xToCheck] == '1')
		{
			horizontalWallHitX = next_hor_toach_x;
			horizontalWallHitY = next_hor_toach_y;
			//horizontalWallContent = '1';
			foundHorizontalWallHit = 1;
			break;
		}
		else 
		{
			next_hor_toach_x += xstep;
			next_hor_toach_y += ystep;
		}
	}
	//dda_points(set, horizontalWallHitX, horizontalWallHitY, hypotenuse(set->player.posx, set->player.posy, horizontalWallHitX, horizontalWallHitY), rayAngle);

	(void)horizontalWallContent;
	(void)foundHorizontalWallHit;

// Vertical

	int		foundVerticalWallHit = 0;
	float	verticalWallHitX = 0;
	float	verticalWallHitY = 0;
	int		verticalWallContent = 0;

	float	next_ver_toach_x;
	float	next_ver_toach_y;

	xintercept = floor(set->player.posx / TILE_SIZE) * TILE_SIZE;
	if (set->rays[id].isRayFacingRight)
		xintercept += TILE_SIZE;
	
	yintercept = set->player.posy + (xintercept - set->player.posx) * tan(rayAngle);

	xstep = TILE_SIZE;
	if (set->rays[id].isRayFacingLeft)
		xstep *= -1;

	ystep = TILE_SIZE * tan(rayAngle);
	if (set->rays[id].isRayFacingUp && ystep > 0)
		ystep *= -1;
	if (set->rays[id].isRayFacingDown && ystep < 0)
		ystep *= -1;

	next_ver_toach_x = xintercept;
	next_ver_toach_y = yintercept;

	while (next_ver_toach_x >= 0 && next_ver_toach_x <= set->map_data.win_width && next_ver_toach_y >= 0 &&  next_ver_toach_y <= set->map_data.win_height)
	{
		int	xToCheck = (int)floor(next_ver_toach_x / TILE_SIZE);
		int	yToCheck = (int)floor(next_ver_toach_y / TILE_SIZE);
		if (set->rays[id].isRayFacingLeft)
			xToCheck -= 1;
		if (set->map_data.map[yToCheck][xToCheck] == '1')
		{
			verticalWallHitX = next_ver_toach_x;
			verticalWallHitY = next_ver_toach_y;
			//verticalWallContent = '1';
			foundVerticalWallHit = 1;
			break;
		}
		else 
		{
			next_ver_toach_x += xstep;
			next_ver_toach_y += ystep;
		}
	}
	//dda_points(set, verticalWallHitX, verticalWallHitY, hypotenuse(set->player.posx, set->player.posy, verticalWallHitX, verticalWallHitY), rayAngle);
	(void)verticalWallContent;
	(void)foundVerticalWallHit;


	float distance1 = hypotenuse(set->player.posx, set->player.posy, horizontalWallHitX, horizontalWallHitY);
	float distance2 = hypotenuse(set->player.posx, set->player.posy, verticalWallHitX, verticalWallHitY);
	
	if (distance1 > distance2)
		distance1 = distance2;
	dda_points(set, 0, 0, distance1, rayAngle);

	}	

void	cast_all_rays(t_setup *set)
{
	float	fov;
	float	rayAngle;
	int		strip_id;
	int		ray_number;

	ray_number = set->map_data.win_width;
	fov = 60 * PI / 180;
	rayAngle = set->player.rotation_angle - (fov / 2);
	set->rays = malloc(sizeof(t_rays) * ray_number);
	rayAngle = normalize_angle(rayAngle);
	strip_id = -1;
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
		my_mlx_pixel_put(&set->frame, x * MINIMAP_SCALE,
			y * MINIMAP_SCALE, RED);
		x += deltas[0] / (float)steps;
		y += deltas[1] / (float)steps;
	}
}

void	dda_points(t_setup *set, float x, float y, float distance, float rayAngle)
{
	int		deltas[2];
	int		steps;
	int		i;

	x = set->player.posx;
	y = set->player.posy;
	deltas[0] = (x - (x + cos(rayAngle) * distance)) * -1;
	deltas[1] = (y - (y + sin(rayAngle) * distance)) * -1;
	if (abs(deltas[0]) > abs(deltas[1]))
		steps = abs(deltas[0]);
	else
		steps = abs(deltas[1]);
	i = -1;
	while (++i <= steps)
	{
		my_mlx_pixel_put(&set->frame, x * MINIMAP_SCALE,
			y * MINIMAP_SCALE, RED);
		x += deltas[0] / (float)steps;
		y += deltas[1] / (float)steps;
	}
}
