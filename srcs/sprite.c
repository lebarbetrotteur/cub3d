/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cyrille.bertola@student.42.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 14:39:32 by cyrillebert       #+#    #+#             */
/*   Updated: 2020/04/14 19:37:58 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		init_sprite(t_data *d, char type, t_vector hit, t_radar *r)
{
	d->sprite.vec.x = hit.x;
	d->sprite.vec.y = hit.y;
	d->sprite.vec_mid.x = (int)hit.x + 0.5;
	d->sprite.vec_mid.y = (int)hit.y + 0.5;
	d->sprite.dist = sqrt(calc_dst_vector(d->sprite.vec_mid, d->p.vector));
	d->sprite.type = type;
	d->sprite.next = 0;
	d->sprite.alpha = r->alpha;
	if (d->sprite.alpha > (M_PI * 2))
				d->sprite.alpha -= M_PI * 2;	
	if (d->sprite.alpha < 0)
				d->sprite.alpha += M_PI * 2;	
	d->sprite.touch = r->touch;
}
void		display_sprite(t_data *d, int i)
{
	double	sprite;
	int		y;
	double	j;
	int		color;

	j = 0;
	
	sprite = d->r[1] / d->sprite.dist; //hauteur
	y = ((d->r[1] - sprite) / 2) + d->p.angle_visu; // placement du sprite
	while (sprite-- > 0)
	{
		color = color_sprite(d, j++, d->r[1] / d->sprite.dist);
		if (color)
			image_set_pixel(&d->img, i, y, color);
		y++;
	}
}
// int			color_sprite(t_data *d, double pixel, int size)
// {
// 	int color;
// 	double beta;
// 	double diffx;
// 	double diffy;

// 	diffx = (d->sprite.vec.x - (int)d->sprite.vec.x);
// 	diffy = (d->sprite.vec.y - (int)d->sprite.vec.y);

// 	beta = M_PI_2 - d->sprite.alpha;
	
// 	if (d->sprite.touch == 0 && sin(d->sprite.alpha) > 0)
// 	{
// 	//	printf("%f\n", cos(beta));
// 		color = image_get_pixel(&d->texture.sp, (sin(beta) + cos(beta) * diffx) *
// 				d->texture.sp.width, pixel / size * d->texture.sp.height);
// 			//color = 0x55ff55;

// 	}
// 	else if (d->sprite.touch == 0)
// 	{
// 		color = 0xff00ff;
// 		//color = image_get_pixel(&d->texture.sp, diffx * 0 *
// 		//		d->texture.sp.width, pixel / size * d->texture.sp.height);

// 	}
// 	else if (d->sprite.touch == 1 && cos(d->sprite.alpha) > 0)
// 		color = image_get_pixel(&d->texture.sp, diffy * sin(beta) *
// 				d->texture.sp.width, pixel / size * d->texture.sp.height);
// 	else
// 		color = 0x000000;
// 	//	color = image_get_pixel(&d->texture.sp, diffy * 0 *
// 	//			d->texture.sp.width, pixel / size * d->texture.sp.height);
// 	return (color);
// }

int			color_sprite(t_data *d, double pixel, int size)
{
	int color;
	double diffx;
	double diffy;
	diffx = (d->sprite.vec.x - (int)d->sprite.vec.x);
	diffy = (d->sprite.vec.y - (int)d->sprite.vec.y);
	float inter;
	if (d->sprite.alpha <= M_PI_2)
		inter = (d->sprite.touch == 0 ? cos(d->sprite.alpha) + diffx * sin(d->sprite.alpha) : diffy * cos(d->sprite.alpha));
	else if (d->sprite.alpha > M_PI_2 && d->sprite.alpha <= M_PI)
		inter =  (d->sprite.touch == 0 ? sin(d->sprite.alpha) * diffx : sin(d->sprite.alpha) - (1 - diffy) * cos(d->sprite.alpha));
	else if (d->sprite.alpha > M_PI && d->sprite.alpha <= 3 * M_PI_2)
		inter = (d->sprite.touch == 0 ? 1 + sin(d->sprite.alpha) * diffx : 1 + (sin(d->sprite.alpha) + diffy * cos(d->sprite.alpha)));
	else
		inter = (d->sprite.touch == 0 ? sin(d->sprite.alpha) * (diffx - 1) : -sin(d->sprite.alpha) + diffy * cos(d->sprite.alpha));
	color = image_get_pixel(&d->texture.sp, inter * d->texture.sp.width, pixel / size * d->texture.sp.height);
	return (color);
}