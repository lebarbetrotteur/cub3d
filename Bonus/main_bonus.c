/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 16:15:46 by cbertola          #+#    #+#             */
/*   Updated: 2020/04/21 08:17:30 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		destroy(t_data *d)
{
	ft_error("Exit\n", d, 3);
	return (0);
}

int		refresh_img(t_data *d)
{
	while (d->p.alpha >= (M_PI * 2))
		d->p.alpha -= M_PI * 2;
	if (d->p.alpha <= 0)
		d->p.alpha += M_PI * 2;
	radar(d);
	if (d->mini.display == 0)
		display_mini(d);
	return (0);
}

int		key_press(int key, t_data *d)
{
	if (key == K_W)
		move_fb(d, 1);
	if (key == K_A)
		move_lr(d, 1);
	if (key == K_S)
		move_fb(d, -1);
	if (key == K_D)
		move_lr(d, -1);
	if (key == K_UP)
		d->p.angle_visu += d->p.angle_visu < d->r[1] / 3 ? 10 : 0;
	if (key == K_DOWN)
		d->p.angle_visu -= d->p.angle_visu > -d->r[1] / 3 ? 10 : 0;
	if (key == K_RIGHT)
		d->p.alpha += d->p.vitesse_rot;
	if (key == K_LEFT)
		d->p.alpha -= d->p.vitesse_rot;
	if (key == K_M)
		d->mini.display = !d->mini.display;
	if (key == K_ESC)
		destroy(d);
	refresh_img(d);
	return (0);
}

int		main(int argc, char **argv)
{
	t_data			d;

	ft_bzero(&d, sizeof(t_data));
	if (argc < 2)
		return (write(2, "Error \nMissing Map\n", 20));
	d.ptr = mlx_init();
	parsing(argv[1], &d);
	if ((d.win = mlx_new_window(d.ptr, d.r[0], d.r[1], "Cub3d")) == NULL)
		ft_error("Error\n Window creation failed", &d, 2);
	d.img = new_image(&d, d.r[0], d.r[1]);
	d.mini.img = new_image(&d, d.map.x_max * d.mini.size,
			d.map.y_max * d.mini.size);
	refresh_img(&d);
	if (argv[2] && !ft_strcmp(argv[2], "--save"))
		get_image(&d);
	mlx_hook(d.win, 17, 1L << 17, destroy, &d);
	mlx_hook(d.win, 2, 1L << 0, key_press, &d);
	mlx_loop(d.ptr);
}
