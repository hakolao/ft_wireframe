/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:07:11 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/11 14:40:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define FPS 30

# define ERR_INVALID_INPUT "Lines must "\
						"consist of spaces & numbers."
# define ERR_SERIALIZATION "Input serialization failed."
# define ERRNO_INVALID_INPUT 5

# define KEY_ESC 53

# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"

# define MAP_COLOR ft_rgbtoi(0, 255, 0)

typedef struct		s_vertex
{
	double			x;
	double			y;
	double			z;
}					t_vertex;

typedef t_vertex	t_point;

typedef struct		s_map
{
	t_list			*vertices;
	int				vertex_count;
	double			x_max;
	double			y_max;
	double			z_max;
}					t_map;

typedef struct		s_canvas
{
	double			width;
	double			height;
}					t_canvas;

typedef struct 		s_camera
{
	t_point			*position;
	t_canvas		*canvas;
	t_rgb			*color;
}					t_camera;

typedef struct		s_scene
{
	t_camera		*camera;
	t_map			*map;
}					t_scene;

/*
** Input functions & serialization
*/
t_map				*serialize(char *filename);

/*
** Logging functions
*/
void				log_map(t_map *map);
void				log_error(char *str, char *strerror);

/*
** Event handling
*/
int					handle_key_events(int key, void *param);

/*
** Draw graphics
*/
void				draw(void *mlx, void *mlx_wdw, t_scene *scene);

#endif