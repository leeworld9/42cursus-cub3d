/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 06:47:53 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 10:26:24 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		**malloc_2d(int i, int j)
{
	int **arr;
	int x;

	if ((arr = (int **)malloc(sizeof(int *) * i)) == NULL)
		return (NULL);
	x = 0;
	while (x < i)
	{
		if ((arr[x] = (int *)malloc(sizeof(int) * j)) == NULL)
		{
			free_2d_i(arr, x, -1);
			return (NULL);
		}
		x++;
	}
	return (arr);
}

int		free_2d_i(int **arr, int j, int errnum)
{
	int i;

	i = 0;
	while (i < j)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (errnum);
}

int		free_2d_c(char **arr, int j, int errnum)
{
	int i;

	i = 0;
	while (i < j)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (errnum);
}

void	memset_2d(int **arr, int x, int y, int c)
{
	int i;

	i = 0;
	while (i < x)
	{
		ft_memset(arr[i], c, sizeof(int) * y);
		i++;
	}
}
