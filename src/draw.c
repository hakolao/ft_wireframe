/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/24 12:10:35 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void			draw_map(t_scene *scene)
{
	t_line_connect	*line_connect;
	size_t			i;

	if ((line_connect = malloc(sizeof(t_line_connect))) == NULL)
		return ;
	line_connect->scene = scene;
	i = -1;
	while (++i < scene->map->vertex_count - 1)
	{
		if ((i + 1) % (scene->map->x + 1) != 0)
			connect_map_pts_with_gradient(line_connect,
				scene->map->vertices[i],
					scene->map->vertices[i + 1]);
		if (i < scene->map->vertex_count - scene->map->x - 1)
			connect_map_pts_with_gradient(line_connect,
				scene->map->vertices[i],
					scene->map->vertices[i + 1 + scene->map->x]);
	}
	free(line_connect);
}

int					draw(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	draw_map(scene);
	draw_axes(scene);
	draw_ui(scene);
	return (1);
}
