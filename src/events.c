/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:56:37 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/20 15:48:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int				handle_key_events_home(int key, void *param)
{
	t_scene	*scene;
	int 	ret;

	scene = (t_scene *)param;
	if (key == HOME_KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
		exit(0);
	}
	ret = ((key == HOME_KEY_W && rotate_map(scene->map, 3, 0, 0)) ||
			(key == HOME_KEY_S && rotate_map(scene->map, -3, 0, 0)) ||
			(key == HOME_KEY_A && rotate_map(scene->map, 0, 3, 0)) ||
			(key == HOME_KEY_D && rotate_map(scene->map, 0, -3, 0)) ||
			(key == HOME_KEY_Q && rotate_map(scene->map, 0, 0, -3)) ||
			(key == HOME_KEY_E && rotate_map(scene->map, 0, 0, 3)) ||
			(key == HOME_KEY_UP && move_camera_z(scene, 1)) ||
			(key == HOME_KEY_DOWN && move_camera_z(scene, -1)) ||
			(key == HOME_KEY_RIGHT && move_camera_x(scene, 1)) ||
			(key == HOME_KEY_LEFT && move_camera_x(scene, -1)) ||
			(key == HOME_KEY_J && turn_camera(scene, 0, -2)) ||
			(key == HOME_KEY_K && turn_camera(scene, 0, 2)) ||
			(key == HOME_KEY_I && turn_camera(scene, 2, 0)) ||
			(key == HOME_KEY_M && turn_camera(scene, -2, 0)) ||
			(key == HOME_KEY_P && loop_perspective(scene)) ||
			(key == HOME_KEY_1 && zoom(scene, 1)) ||
			(key == HOME_KEY_2 && zoom(scene, -1)) ||
			(key == HOME_PLUS && scale_map_z(scene->map, 1.1)) ||
			(key == HOME_MINUS && scale_map_z(scene->map, 0.9)));
	draw(scene);
	ft_putnbr(key);
	ft_putstr("\n");
	return (ret);
}

int				handle_key_events(int key, void *param)
{
	t_scene	*scene;
	int 	ret;

	scene = (t_scene *)param;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
		exit(0);
	}
	ret = ((key == KEY_W && rotate_map(scene->map, 3, 0, 0)) ||
			(key == KEY_S && rotate_map(scene->map, -3, 0, 0)) ||
			(key == KEY_A && rotate_map(scene->map, 0, 3, 0)) ||
			(key == KEY_D && rotate_map(scene->map, 0, -3, 0)) ||
			(key == KEY_Q && rotate_map(scene->map, 0, 0, -3)) ||
			(key == KEY_E && rotate_map(scene->map, 0, 0, 3)) ||
			(key == KEY_UP && move_camera_z(scene, 1)) ||
			(key == KEY_DOWN && move_camera_z(scene, -1)) ||
			(key == KEY_RIGHT && move_camera_x(scene, 1)) ||
			(key == KEY_LEFT && move_camera_x(scene, -1)) ||
			(key == KEY_NUM_4 && turn_camera(scene, 0, -2)) ||
			(key == KEY_NUM_6 && turn_camera(scene, 0, 2)) ||
			(key == KEY_NUM_8 && turn_camera(scene, 2, 0)) ||
			(key == KEY_NUM_2 && turn_camera(scene, -2, 0)) ||
			(key == KEY_P && loop_perspective(scene)) ||
			(key == KEY_R && reset_fdf(scene)) ||
			(key == KEY_1 && zoom(scene, 1)) ||
			(key == KEY_2 && zoom(scene, -1)));
	draw(scene);
	ft_putnbr(key);
	return (ret);
}

int				handle_mouse_button_events(int key, int x, int y, void *param)
{
	t_scene	*scene;
	int 	ret;

	(void)x;
	(void)y;
	scene = (t_scene *)param;
	ret = ((key == SCROLL_UP && scale_map_z(scene->map, 1.1)) ||
			(key == SCROLL_DOWN && scale_map_z(scene->map, 0.9)));
	draw(scene);
	return (ret);
}
