/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 16:54:31 by dohelee           #+#    #+#             */
/*   Updated: 2021/01/02 21:53:50 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1len;
	size_t	s2len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL || s2 == NULL)
		return (s1 == NULL ? ft_strdup(s2) : ft_strdup(s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if ((str = (char *)malloc((s1len + s2len + 1) * sizeof(char))) == NULL)
		return (NULL);
	ft_strlcpy(str, s1, s1len + 1);
	ft_strlcat(str + s1len, s2, s2len + 1);
	return (str);
}
