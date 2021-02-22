/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 00:41:55 by dohelee           #+#    #+#             */
/*   Updated: 2020/12/26 02:24:49 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*cpy1;
	unsigned char	*cpy2;

	cpy1 = (unsigned char *)s1;
	cpy2 = (unsigned char *)s2;
	i = 0;
	if ((int)n == 0)
		return (0);
	while (++i < n)
	{
		if (*cpy1 == *cpy2)
		{
			cpy1++;
			cpy2++;
		}
	}
	return ((int)(*cpy1 - *cpy2));
}
