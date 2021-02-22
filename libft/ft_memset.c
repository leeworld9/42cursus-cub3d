/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:39:58 by dohelee           #+#    #+#             */
/*   Updated: 2020/12/31 02:17:10 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cpy;

	cpy = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		cpy[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
