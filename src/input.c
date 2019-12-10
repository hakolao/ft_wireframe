/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:14:35 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/10 17:51:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static t_vertex		*new_vertex(int x, int y, int z)
{
	t_vertex	*vertex;

	if ((vertex = (t_vertex*)malloc(sizeof(*vertex))) == NULL)
		return (NULL);
	vertex->x = x;
	vertex->y = y;
	vertex->z = z;
	return (vertex);
}

static t_list		*add_to_list(t_list *vertices, int x, int y, int z)
{
	t_list	*node;

	if (vertices == NULL)
	{
		if ((vertices = ft_lstnew(new_vertex(x, y, z), sizeof(t_vertex))) == NULL)
			return (NULL);
	}
	else
	{
		if ((node = ft_lstnew(new_vertex(x, y, z), sizeof(t_vertex))) == NULL)
			return (NULL);
		ft_lstappend(&vertices, node);
	}
	return (vertices);
}

static t_list		*add_vertices(t_list *vertices, char *line, int y, t_map *map)
{
	int		x;
	int		z;

	x = 0;
	while (*line)
	{
		if (ft_isdigit(*line))
		{
			z = ft_atoi(line);
			while (*line && ft_isdigit(*line))
				line++;
			while (*line && !ft_isdigit(*line))
				line++;
			if ((vertices = add_to_list(vertices, x, y, z)) == NULL)
					return (NULL);
			map->z_max = map->z_max >= z ? map->z_max : z;
			map->x_max = map->x_max >= x ? map->x_max : x;
			(map->vertex_count)++;
			x++;
		}
		else
			line++;
	}
	return (vertices);
}

static t_map		*file_to_map(int fd)
{
	char	*line;
	int		ret;
	int		y;
	t_list	*vertices;
	t_map	*map;

	if ((map = (t_map*)malloc(sizeof(*map))) == NULL)
		return (NULL);
	line = NULL;
	vertices = NULL;
	y = 0;
	map->vertex_count = 0;
	map->x_max = 0;
	map->z_max = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if ((vertices = add_vertices(vertices, line, y, map)) == NULL)
			return (NULL);
		ft_strdel(&line);
		y++;
	}
	map->vertices = vertices;
	if (ret == 0)
		map->y_max = y - 1;
	if (ret == -1)
		return (NULL);
	return (map);
}

t_map				*serialize(char *filename)
{
	t_map	*map;
	int		fd;

	map = NULL;
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (NULL);
	if ((map = file_to_map(fd)) == NULL)
		return (NULL);
	close(fd);
	return (map);
}