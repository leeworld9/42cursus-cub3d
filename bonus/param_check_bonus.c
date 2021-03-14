/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 02:37:46 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 11:38:58 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	param_check(t_game *g, int argc, char **argv)
{
	int s1;
	int s2;
	int ret;

	ret = -1;
	if (argc == 2 || argc == 3)
	{
		if (ext_check(argv[1], "cub") < 0)
			return (ft_strerror(-5));
		if (argc == 3)
		{
			s1 = ft_strncmp(argv[2], "--save", ft_strlen(argv[2]));
			s2 = ft_strncmp("--save", argv[2], ft_strlen("--save"));
			if (s1 != 0 || s2 != 0)
				return (ft_strerror(-3));
		}
		if (cub_check(g, argv[1], 1) > 0)
			ret = (argc == 2) ? 2 : 3;
		return (ret);
	}
	else
		return (ft_strerror(-99));
}

int	cub_check(t_game *g, char *argv, int fd)
{
	char	*line;
	int		ret;
	int		cub;

	if ((fd = open(argv, O_RDONLY)) == -1)
		return (ft_strerror(-1));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		cub = cub_parsing(g, line);
		free(line);
		if (cub < 0)
			return (-1);
	}
	free(line);
	if (user_location(g) < 0)
		return (-1);
	if (wall_check(g) < 0)
		return (ft_strerror(-18));
	if (ret < 0)
		return (ft_strerror(-2));
	else
	{
		close(fd);
		return (1);
	}
}

int	ext_check(char *argv, char *ext)
{
	int	len;

	len = ft_strlen(argv);
	if (len > 4 && argv[len - 1] == ext[2] && argv[len - 2] == ext[1] &&
				argv[len - 3] == ext[0] && argv[len - 4] == '.')
		return (1);
	return (-1);
}

int	wall_check(t_game *g)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < g->map.mx)
	{
		y = 0;
		while (y < g->map.my)
		{
			if (g->map.map[x][y] != '1' && x == 0)
				return (-1);
			else if (g->map.map[x][y] != '1' && x == g->map.mx - 1)
				return (-1);
			else if (g->map.map[x][y] != '1' && y == 0)
				return (-1);
			else if (g->map.map[x][y] != '1' && y == g->map.my - 1)
				return (-1);
			y++;
		}
		x++;
	}
	return (1);
}

int	ft_strerror(int err)
{
	(err == -1) ? write(2, "Error : Can't open file (fd)\n", 32) : 0;
	(err == -2) ? write(2, "Error : Can't parse file (gnl)\n", 34) : 0;
	(err == -3) ? write(2, "Error : Invalid param\n", 22) : 0;
	(err == -4) ? write(2, "Error : Can't parse '*.cub' file\n", 36) : 0;
	(err == -5) ? write(2, "Error : Invalid filename extension\n", 35) : 0;
	(err == -6) ? write(2, "Error : Invalid resolution\n", 27) : 0;
	(err == -7) ? write(2, "Error : Floor/ceiling specified twice\n", 38) : 0;
	(err == -8) ? write(2, "Error : Invaild Floor/ceiling color\n", 36) : 0;
	(err == -9) ? write(2, "Error : Texture path specified twice\n", 37) : 0;
	(err == -10) ? write(2, "Error : Invalid line in file\n", 29) : 0;
	(err == -11) ? write(2, "Error : Malloc fail\n", 20) : 0;
	(err == -12) ? write(2, "Error : Invalid texture image\n", 30) : 0;
	(err == -13) ? write(2, "Error : Resolution specified twice\n", 35) : 0;
	(err == -14) ? write(2, "Error : Map isn't a rectangle\n", 30) : 0;
	(err == -15) ? write(2, "Error : Invalid map\n", 20) : 0;
	(err == -16) ? write(2, "Error : duplicated user direction\n", 34) : 0;
	(err == -17) ? write(2, "Error : Not Use user direction\n", 31) : 0;
	(err == -18) ? write(2, "Error : Map isn't surrounded by walls\n", 38) : 0;
	(err == -19) ? write(2, "Error : invalid key\n", 20) : 0;
	(err == -99) ? write(2, "Usage : ./cub3d *.map <--save>\n", 31) : 0;
	return (-1);
}
