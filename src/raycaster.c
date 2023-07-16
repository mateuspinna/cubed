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

/* void	cast_all_rays(t_setup *set)
{
    float   FOV;
    float	rayAngle;
    int     strip_id;
    int     ray_number;

    ray_number = set->map_data.win_width;
    FOV = 60 * PI / 180;
    rayAngle = set->player.rotation_angle - (FOV / 2);
    strip_id = -1;
    while (++strip_id < ray_number)
    {
        cast_ray(rayAngle, strip_id, set);
        rayAngle += FOV / ray_number;
    }
}

float normalize_angle(float angle, t_setup *set)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0)
        angle = TWO_PI + angle;
    return angle;
}

void cast_ray(float rayAngle, int strip_id, t_setup *set)
{
    rayAngle = normalize_angle(rayAngle, set);

    int     isRayFacingDown = rayAngle > 0 && rayAngle < 180;
    int     isRayFacingUp = !isRayFacingDown;
    int     isRayFacingRight= rayAngle > 0.5 || rayAngle > 1.5 * PI;
    int     isRayFacingLeft = !isRayFacingRight;

    float   xintercept;
    float   yintercept;
    float   xstep;
    float   ystep;

    int     foundHorizontalWallHit = 0;
    float   horizontalWallHitX = 0;
    float   horizontalWallHitY = 0;
    int     horizontalWallContent = 0;

} */

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
