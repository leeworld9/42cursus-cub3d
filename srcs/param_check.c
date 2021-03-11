/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 02:37:46 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/12 01:33:53 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		param_chk(t_game *game, int argc, char **argv)
{
	int ret;

	if ((argc == 2 || argc == 3))
	{
		if (ext_check(argv[1], "cub") < 0)
			return (ft_strerror(-5));
		if ((ret = cub_check(game, argv[1], 1)) > 0)
		{
			if (argc == 2)
				return (2);
			else
			{
				if (argc == 3 && (ft_strncmp(argv[2],"--save", ft_strlen(argv[2])) == 0))
					return (3);
				else
					return (ft_strerror(-3));
			}
		}
		else 
			return (ret);	
	}
	else
		return (ft_strerror(-99));
}

int		ext_check(char *argv, char *ext)
{
	int	len;

	len = ft_strlen(argv);
	if (len > 4 && argv[len - 1] == ext[2] && argv[len - 2] == ext[1] && 
				argv[len - 3] == ext[0] && argv[len - 4] == '.')
		return (1);
	return (-1);
}

int		wall_check(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < game->map.mx)
	{
		y = 0;
		while (y < game->map.my)
		{
			if (game->map.map[x][y] != '1' && x == 0)
				return (-1);
			else if (game->map.map[x][y] != '1' && x == game->map.mx - 1)
				return (-1);
			else if (game->map.map[x][y] != '1' && y == 0)
				return (-1);
			else if (game->map.map[x][y] != '1' && y == game->map.my - 1)
				return (-1);
			y++;
		}
		x++;
	}
	return (1);
}

int		cub_check(t_game *game, char *argv, int fd)
{
	char *line;
	int ret;
	int cub;
	
	if ((fd = open(argv, O_RDONLY)) == -1)
		return (ft_strerror(-1));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		cub = map_parsing(game, line);
		free(line);
		if(cub < 0)
			return (-1);
	}
	if (user_location(game) < 0)
		return (-1);
	//// 사방이 벽으로 둘러 쌓여있는지 확인하는 메소드 필요
	if (wall_check(game) < 0)
		return (ft_strerror(-18));
	////
	if (ret < 0)
		return (ft_strerror(-2));
	else
	{
		close(fd);
		return (1);
	}
}




int		ft_strerror(int err)
{
	(err == -1) ? write(2, "Error : Couldn't open file (FD)\n", ft_strlen("Error : Couldn't open file (FD)\n")) : 0;
	(err == -2) ? write(2, "Error : Couldn't parse file (GNL)\n", ft_strlen("Error : Couldn't parse file (GNL)\n")) : 0;
	(err == -3) ? write(2, "Error : Invalid param\n", ft_strlen("Error : invalid param\n")) : 0;
	(err == -4) ? write(2, "Error : Couldn't parse '*.cub' file\n", ft_strlen("Error : Couldn't parse .cub file\n")) : 0;
	(err == -5) ? write(2, "Error : Invalid filename extension \n", ft_strlen("Error : Invalid filename extension \n")) : 0;
	(err == -6) ? write(2, "Error : Invalid resolution\n", ft_strlen("Error : Invalid resolution\n")) : 0;
	(err == -7) ? write(2, "Error : Floor/ceiling specified twice\n", 38) : 0;
	(err == -8) ? write(2, "Error : Invaild Floor/ceiling color\n", 38) : 0;
	(err == -9) ? write(2, "Error : Texture path specified twice\n", 37) : 0;
	(err == -10) ? write(2, "Error : Invalid line in file\n", 29) : 0;
	(err == -11) ? write(2, "Error : Malloc fail (texture path)\n", 35) : 0;
	(err == -12) ? write(2, "Error : Invalid texture image\n", 30) : 0;
	(err == -13) ? write(2, "Error : Resolution specified twice\n", 35) : 0;
	(err == -14) ? write(2, "Error : Map isn't a rectangle\n", 30) : 0;
	(err == -15) ? write(2, "Error : Invalid map\n", 20) : 0;
	(err == -16) ? write(2, "Error : duplicated user direction\n", ft_strlen("Error : duplicated user direction\n")) : 0;
	(err == -17) ? write(2, "Error : Not Use user direction\n", ft_strlen("Error : Not Use user direction\n")) : 0;
	(err == -18) ? write(2, "Error : Map isn't surrounded by walls\n", 38) : 0;
	(err == -99) ? write(2, "Usage : ./cub3d *.map <--save>\n", ft_strlen("Usage : ./cub3d *.map <--save>\n")) : 0;
	return (-1);
}
