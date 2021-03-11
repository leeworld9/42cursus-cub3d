/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 02:37:18 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/12 01:47:10 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		remove_space(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n' || 
			line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f')
		(*i)++;
	return (1);
}

int		check_colors(unsigned int *color, char *line, int *i)
{
	char **str;
	int	r;
	int	g;
	int	b;
	int k;

	k = 0;
	if (*color != 0x000000)
		return (-7);	
	if ((str = ft_split(&line[*i + 2], ',')) == NULL)
		return (-10);
	while (str[k] != NULL)
		k++;
	if (k != 3)
		return (-10);
	r = ft_atoi(str[0]); // 숫자이외에 문자가 들어갔을때 exceoption 처리 필요(함수만들기)
	g = ft_atoi(str[1]);
	b = ft_atoi(str[2]);
	if (r > 255 || g > 255 || b > 255)
		return (-8);
	*color = encode_color(r, g, b);
	//printf("color : %d\n", *color);
	k = 0;
	while (k < 3)
		free(str[k++]);
	free(str);
	return (0);
}

int		check_texture(t_game *game, t_img *img, char *line, int *i)
{
	char	*file;
	int		j;

	if (img->data != NULL)
		return (-9);
	(*i) += 2;
	remove_space(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(file = malloc(sizeof(char) * (*i - j + 1))))
		return (-11);
	ft_memset(file, '\0', *i - j + 1);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0') //strlcpy 변환 가능
 		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = get_xpmfile(game, img, file);
	free(file);
	return (j == -1 ? -12 : 0);
}

int		get_xpmfile(t_game *game, t_img *img, char *file)
{
	int		fd;

	if (ext_check(file, "xpm") == 0)
		return (-1);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	close(fd); // 중요!!
	img->img = mlx_xpm_file_to_image(game->mlx, file, &img->width, &img->height);
	if (img == NULL || img->width != 64 || img->height != 64)
		return (-1);
	img->data = (unsigned int*)mlx_get_data_addr(img->img, &img->bpp, &img->line_size, &img->endian);
	//printf("file : %s\n", file);
	free(img->img);
	return (0);
}

int		ft_slablen(t_game *game, char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')
			count++;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
			count++;
		i++;
	}
	if (game->map.my != 0 && game->map.my != count)
		return (-1);
	return (count);
}

char	*ft_slab(t_game *game, char *line, int *i)
{
	char	*slab;
	int		j;

	if (!(slab = malloc(sizeof(char) * (ft_slablen(game, line) + 1))))
		return (NULL);
	ft_memset(slab, '\0', ft_slablen(game, line) + 1);
	j = 0;
	while (line[*i] != '\0')
	{
		if ((line[*i] == '0' || line[*i] == '1' || line[*i] == 'N')
			|| (line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W'))
			slab[j++] = line[*i];
		else if (line[*i] == '2')
		{
			slab[j++] = line[*i];
			//s->map.spr++;
		}
		else if (line[*i] != ' ')
		{
			free(slab);
			return (NULL);
		}
		(*i)++;
	}
	slab[j] = '\0';
	return (slab);
}

int		ft_map(t_game *game, char *line, int *i)
{
	char	**tmp;
	int		j;

	game->map.chk = 1;
	if (!(tmp = (char **)malloc(sizeof(char *) * (game->map.mx + 2))))
		return (-11);
	ft_memset(tmp, 0, game->map.mx + 2);
	j = -1;
	while (++j < game->map.mx)
		tmp[j] = game->map.map[j];
	if ((tmp[game->map.mx] = ft_slab(game, line, i)) == NULL)
	{
		free(tmp);
		return (-15);
	}
	tmp[game->map.mx + 1] = NULL;
	if (game->map.mx > 0)
		free(game->map.map);
	game->map.map = tmp;
	game->map.mx++;
	if ((game->map.my = ft_slablen(game, line)) == -1)
		return (-14);
	return (0);
}

int 	map_parsing(t_game *game, char *line)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	remove_space(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		err = check_resolution(game, line);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		err = check_texture(game, &game->wall_n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		err = check_texture(game, &game->wall_s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		err = check_texture(game, &game->wall_w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		err = check_texture(game, &game->wall_e, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		err = check_texture(game, &game->sprite, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		err = check_colors(&game->bottom.color, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		err = check_colors(&game->top.color, line, &i);
	else if ((line[i] == '1' || game->map.chk == 1) && line[i] != '\0')
		err = ft_map(game, line, &i);
	else if (err == 0 && line[i] != '\0')
	{
		//printf("err : %d, line[i] : %c\n", err, line[i]);
		return (ft_strerror(-10));
	}
	return (err < 0 ? ft_strerror(err) : 0);
	
}


int		check_resolution(t_game *game, char *line)
{
	int max_x;
	int max_y;
	int	k;
	char **str;

	k = 0;
	if ((str = ft_split(line + 2 , ' ')) == NULL)
		return (-6);
	while (str[k] != NULL)
		k++;
	if (k != 2)
		return (-6);
	mlx_get_screen_size(game->mlx, &max_x, &max_y);
	if (game->win.winx != 0 || game->win.winy != 0)
		return (-13);
	game->win.winx = ft_atoi(str[0]); // 80s 같이 문자 들어갔을때 예외처리 필요
	game->win.winy = ft_atoi(str[1]); 
	if (game->win.winx > max_x)
		game->win.winx = max_x;
	if (game->win.winy > max_y)
		game->win.winy = max_y;
	if (game->win.winx <= 0 || game->win.winy <= 0 || line[0] == '\0')
		return (-4);
	k = 0;
	while (k < 2) // 함수로 만들어서 빼면 좋을듯, 에러도?
		free(str[k++]);
	free(str);
	return (0);
}


bool	user_dir(int c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (true);
	else
		return (false);
}

int		user_deg(int c)
{
	if (c == 'N')
		return (180);
	else if (c == 'E')
		return (90);
	else if (c == 'W')
		return (270);
	else
		return (0);
}

int	user_location(t_game *game)
{
	int x;
	int y;
	int c;
	int chk;

	chk = 0;
	x = 0;
	while (x < game->map.mx)
	{
		y = 0;
		while (y < game->map.my)
		{
			c = map_get_cell(game, x, y);
			if (user_dir(c)) 
			{ 
				game->px = x + 0.5;
				game->py = y + 0.5;
				game->th = deg2rad(user_deg(c));
				chk++;
			}
			y++;
		}
		x++;
	}
	if (chk == 1)
		return (0);
	else if (chk > 1)
		return (ft_strerror(-16));
	else
		return (ft_strerror(-17));
}
