/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:25:32 by dohelee           #+#    #+#             */
/*   Updated: 2021/01/04 07:44:35 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			**ft_malloc_err(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static unsigned int	ft_arrlen(char const *s, char c)
{
	unsigned int	i;
	unsigned int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			cnt++;
		}
	}
	return (cnt);
}

static char			*ft_getstr(char const *s, unsigned int i, unsigned int tmp)
{
	char *str;

	if ((str = (char *)malloc(sizeof(char) * (i - tmp + 1))) == NULL)
		return (NULL);
	ft_strlcpy(str, s + tmp, i - tmp + 1);
	return (str);
}

static unsigned int	ft_strlast_idx(char const *s, char c, unsigned int i)
{
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

char				**ft_split(char const *s, char c)
{
	char			**arr;
	unsigned int	i;
	unsigned int	cnt;
	unsigned int	tmp;

	i = 0;
	cnt = 0;
	if (s == NULL ||
		(arr = (char **)malloc(sizeof(char *) * (ft_arrlen(s, c) + 1))) == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			tmp = i;
			i = ft_strlast_idx(s, c, i);
			if ((arr[cnt] = ft_getstr(s, i, tmp)) == NULL)
				return (ft_malloc_err(arr));
			cnt++;
		}
	}
	arr[cnt] = NULL;
	return (arr);
}
