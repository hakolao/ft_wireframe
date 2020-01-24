/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_pt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:26:52 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/24 12:49:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector			*screen_pt(t_vector *point, t_scene *scene)
{
	t_vector	*on_screen;

	if ((on_screen = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(
			scene->camera->transform, point, on_screen) == FALSE)
		return (NULL);
	on_screen->v[0] /= on_screen->v[3];
	on_screen->v[1] /= on_screen->v[3];
	on_screen->v[2] /= on_screen->v[3];
	on_screen->v[3] /= on_screen->v[3];
	return (on_screen);
}

static int			in_front_of_camera(t_vector *p1, t_vector *p2,
					t_camera *camera)
{
	t_vector	*c1;
	t_vector	*c2;
	int			ret;

	if ((c1 = ft_vector_new(4)) == NULL ||
		(c2 = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(camera->view, p1, c1) == FALSE ||
		ft_matrix_mul_vector(camera->view, p2, c2) == FALSE)
		return (0);
	ret = c1->v[2] > 0.5 && c2->v[2] > 0.5;
	ft_vector_free(c1);
	ft_vector_free(c2);
	return (ret);
}

void				connect_points(t_line_connect *line_connect)
{
	t_vector	*s1;
	t_vector	*s2;

	if (!in_front_of_camera(line_connect->point1,
		line_connect->point2,
		line_connect->scene->camera))
		return ;
	if (((s1 = screen_pt(line_connect->point1, line_connect->scene)) == NULL ||
		(s2 = screen_pt(line_connect->point2, line_connect->scene)) == NULL) &&
		log_error("Something failed in point_to_screen.", ""))
		exit(1);
	s1->v[0] = (s1->v[0] * ASPECT_RATIO);
	s2->v[0] = (s2->v[0] * ASPECT_RATIO);
	line_connect->point1 = s1;
	line_connect->point2 = s2;
	draw_line(line_connect);
	ft_vector_free(s1);
	ft_vector_free(s2);
}

void				connect_map_pts_with_gradient(t_line_connect *line_connect,
					t_vector *point1, t_vector *point2)
{
	t_map		*map;
	t_vector	*reset_p1;
	t_vector	*reset_p2;
	double		mul;
	
	map = line_connect->scene->map;
	line_connect->point1 = point1;
	line_connect->point2 = point2;
	if ((reset_p1 = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(
		line_connect->scene->map->reset_rotation,
		point1, reset_p1) == FALSE)
		return ;
	mul = 1 * (1 + sin(reset_p1->v[2] / map->z_max));
	line_connect->color_start = COLOR(
		(int)(mul * MAP_R), 
		(int)(mul * MAP_G), 
		(int)(mul * MAP_B)
	);
	printf("point1: tmp->z: %f, p->z: %f, z_min: %f, map-z_max: %d, mul: %f, start: %d\n", reset_p1->v[2], point1->v[2], map->z_min, (int)map->z, mul, line_connect->color_start);
	if ((reset_p2 = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(
		line_connect->scene->map->reset_rotation,
		line_connect->point2, reset_p2) == FALSE)
		return ;
	mul = 1 * (1 + sin(reset_p2->v[2] / map->z_max));
	line_connect->color_end = COLOR(
		(int)(mul * MAP_R), 
		(int)(mul * MAP_G), 
		(int)(mul * MAP_B)
	);
	printf("point1: tmp->z: %f, p->z: %f, z_min: %f, map-z_max: %d, mul: %f, end: %d\n", reset_p2->v[2], point2->v[2], map->z_min, (int)map->z, mul, line_connect->color_end);
	connect_points(line_connect);
}
