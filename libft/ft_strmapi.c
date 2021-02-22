/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:08:55 by dohelee           #+#    #+#             */
/*   Updated: 2021/01/02 21:51:36 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[len] = '\0';
	return (str);
}
