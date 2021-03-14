/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 07:21:18 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 12:34:36 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		remove_space(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n' ||
			line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f')
		(*i)++;
	return (1);
}

bool	check_num(char *str)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

int		get_xpmfile(t_game *g, t_img *img, char *file)
{
	int		fd;
	char	*color;

	if (ext_check(file, "xpm") == 0)
		return (-1);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	img->i = mlx_xpm_file_to_image(g->mlx, file, &img->w, &img->h);
	if (img == NULL)
		return (-1);
	color = mlx_get_data_addr(img->i, &img->b, &img->l, &img->e);
	img->d = (unsigned int*)color;
	return (0);
}

char	*get_line(t_game *g, char *line, int *i)
{
	char	*tmp;
	int		j;

	if (line_length(g, line) == -1)
		return (NULL);
	else if ((tmp = malloc(sizeof(char) * (line_length(g, line) + 1))) == NULL)
		return (NULL);
	j = 0;
	while (line[*i] != '\0')
	{
		if ((line[*i] == '0' || line[*i] == '1' || line[*i] == 'N')
			|| (line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W'))
			tmp[j++] = line[*i];
		else if (line[*i] == '2')
			tmp[j++] = line[*i];
		else if (line[*i] != ' ')
		{
			free(tmp);
			return (NULL);
		}
		(*i)++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int		line_length(t_game *g, char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')
			count++;
		else if (line[i] == 'N' || line[i] == 'S' ||
				line[i] == 'W' || line[i] == 'E')
			count++;
		i++;
	}
	if (g->map.my != 0 && g->map.my != count)
		return (-1);
	return (count);
}
