/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:17:18 by dohelee           #+#    #+#             */
/*   Updated: 2021/01/04 07:41:50 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_getstart(char const *s1, char const *set)
{
	int		n;
	size_t	len;

	n = 0;
	len = ft_strlen(s1);
	while (n < (int)len)
	{
		if (ft_strchr(set, s1[n]))
			n++;
		else
			break ;
	}
	return (n);
}

static int		ft_getend(char const *s1, char const *set)
{
	int		n;
	size_t	len;

	n = 0;
	len = ft_strlen(s1);
	while (n < (int)len)
	{
		if (ft_strchr(set, s1[len - n - 1]))
			n++;
		else
			break ;
	}
	return (len - n);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;

	if (s1 == NULL)
		return (ft_strdup(""));
	if (set == NULL)
		return (ft_strdup(s1));
	start = ft_getstart(s1, set);
	end = ft_getend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	if ((str = (char *)malloc((end - start + 1) * sizeof(char))) == NULL)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}
