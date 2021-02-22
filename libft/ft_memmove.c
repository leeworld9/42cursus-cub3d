/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 02:49:53 by dohelee           #+#    #+#             */
/*   Updated: 2020/12/31 08:31:05 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char*)dest;
	s = (unsigned char*)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		if (dest < src)
		{
			d[i] = s[i];
			i++;
		}
		else
		{
			d[n - 1 - i] = s[n - 1 - i];
			i++;
		}
	}
	return (d);
}
