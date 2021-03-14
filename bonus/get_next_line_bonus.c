/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:06:22 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 11:38:46 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	chk_nl(char *backup)
{
	int i;

	i = 0;
	while (backup[i] != '\0')
	{
		if (backup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*join_backup(char *backup, char *buff, ssize_t rd_size)
{
	char *tmp;

	buff[rd_size] = '\0';
	tmp = ft_strjoin(backup, buff);
	if (chk_nl(tmp) >= 0)
		free(buff);
	free(backup);
	return (tmp);
}

static char	*ret_line(char *backup, int nl_idx, char **line)
{
	char *tmp;

	*line = ft_substr(backup, 0, nl_idx);
	tmp = ft_substr(backup, nl_idx + 1, ft_strlen(backup) - nl_idx);
	free(backup);
	return (tmp);
}

static char	*ret_remain(char *backup, char **line)
{
	if (backup == NULL)
		*line = ft_strdup("");
	else
		*line = ft_strdup(backup);
	free(backup);
	return (NULL);
}

int			get_next_line(int fd, char **line)
{
	char		*buff;
	ssize_t		rd_size;
	static char	*backup[OPEN_MAX];

	if ((fd < 0 && fd > OPEN_MAX) || BUFFER_SIZE <= 0 || line == NULL
		|| (buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		return (-1);
	while ((rd_size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		backup[fd] = join_backup(backup[fd], buff, rd_size);
		if (backup[fd] != NULL && chk_nl(backup[fd]) >= 0)
		{
			backup[fd] = ret_line(backup[fd], chk_nl(backup[fd]), line);
			return (1);
		}
	}
	free(buff);
	if (rd_size < 0)
		return (-1);
	if (backup[fd] != NULL && chk_nl(backup[fd]) >= 0)
	{
		backup[fd] = ret_line(backup[fd], chk_nl(backup[fd]), line);
		return (1);
	}
	return (((backup[fd] = ret_remain(backup[fd], line)) == NULL) ? 0 : -1);
}
