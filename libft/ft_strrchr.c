/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 09:43:58 by dohelee           #+#    #+#             */
/*   Updated: 2020/12/31 08:33:14 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;
	char	*chr;

	s_len = ft_strlen(s);
	chr = (char *)s;
	while (chr[s_len] != c)
	{
		if (s_len == 0)
			return (NULL);
		s_len--;
	}
	return (&chr[s_len]);
}
