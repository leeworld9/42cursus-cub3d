/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 02:37:18 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 10:28:46 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_parsing(t_game *g, char *line)
{
	int	i;

	i = 0;
	remove_space(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		g->err_chk = check_resolution(g, line);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		g->err_chk = check_texture(g, &g->wall_n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		g->err_chk = check_texture(g, &g->wall_s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		g->err_chk = check_texture(g, &g->wall_w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		g->err_chk = check_texture(g, &g->wall_e, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		g->err_chk = check_texture(g, &g->sprite, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		g->err_chk = check_colors(&g->floor.color, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		g->err_chk = check_colors(&g->ceiling.color, line, &i);
	else if ((line[i] == '1' || g->map.chk == 1) && line[i] != '\0')
		g->err_chk = check_map(g, line, &i);
	else if (g->err_chk == 0 && line[i] != '\0')
		return (ft_strerror(-10));
	return (g->err_chk < 0 ? ft_strerror(g->err_chk) : 0);
}

int	check_resolution(t_game *g, char *line)
{
	int		k;
	char	**str;

	k = 0;
	if ((str = ft_split(line + 2, ' ')) == NULL)
		return (-6);
	while (str[k] != NULL)
		k++;
	if (k != 2)
		return (free_2d_c(str, k, -6));
	if (g->win.x != 0 || g->win.y != 0)
		return (free_2d_c(str, k, -13));
	if (!check_num(str[0]) || !check_num(str[1]))
		return (free_2d_c(str, k, -6));
	if ((g->win.x = ft_atoi(str[0])) > g->win.max_x)
		g->win.x = g->win.max_x;
	if ((g->win.y = ft_atoi(str[1])) > g->win.max_y)
		g->win.y = g->win.max_y;
	if (g->win.x <= 0 || g->win.y <= 0 || line[0] == '\0')
		return (free_2d_c(str, k, -4));
	return (free_2d_c(str, k, 0));
}

int	check_texture(t_game *g, t_img *img, char *line, int *i)
{
	char	*file;
	int		j;

	if (img->d != NULL)
		return (-9);
	(*i) += 2;
	remove_space(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(file = malloc(sizeof(char) * (*i - j + 1))))
		return (-11);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = get_xpmfile(g, img, file);
	free(file);
	return (j == -1 ? -12 : 0);
}

int	check_colors(unsigned int *color, char *line, int *i)
{
	char	**str;
	int		k;

	k = 0;
	if (*color != 0x000000)
		return (-7);
	if ((str = ft_split(&line[*i + 2], ',')) == NULL)
		return (-10);
	while (str[k] != NULL)
		k++;
	if (k != 3)
		return (free_2d_c(str, k, -10));
	if (!check_num(str[0]) || !check_num(str[1]) || !check_num(str[2]))
		return (free_2d_c(str, k, -8));
	if (ft_atoi(str[0]) > 255 || ft_atoi(str[1]) > 255 || ft_atoi(str[2]) > 255)
		return (free_2d_c(str, k, -8));
	*color = encode_color(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
	return (free_2d_c(str, k, 0));
}

int	check_map(t_game *g, char *line, int *i)
{
	char	**tmp;
	int		j;

	g->map.chk = 1;
	if (!(tmp = (char **)malloc(sizeof(char *) * (g->map.mx + 2))))
		return (-11);
	j = -1;
	while (++j < g->map.mx)
		tmp[j] = g->map.map[j];
	if ((tmp[g->map.mx] = get_line(g, line, i)) == NULL)
	{
		free(tmp);
		return (free_2d_c(g->map.map, g->map.mx, -15));
	}
	tmp[g->map.mx + 1] = NULL;
	if (g->map.mx > 0)
		free(g->map.map);
	g->map.map = tmp;
	g->map.mx++;
	if ((g->map.my = line_length(g, line)) == -1)
		return (-14);
	return (0);
}
