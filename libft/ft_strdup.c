/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:18:29 by dohelee           #+#    #+#             */
/*   Updated: 2021/01/25 23:23:31 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dst, char const *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char		*ft_strdup(const char *s)
{
	char	*dst;
	size_t	len;

	len = sizeof(char) * (unsigned long)ft_strlen(s) + 1;
	dst = (char *)malloc(len);
	if (dst != NULL)
		ft_strcpy(dst, s);
	else
		return (NULL);
	return (dst);
}
