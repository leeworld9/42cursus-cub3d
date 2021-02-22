/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:06:34 by dohelee           #+#    #+#             */
/*   Updated: 2021/01/03 22:56:27 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		tmp;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		tmp = i;
		while (big[tmp] == little[j] && little[j] != '\0' && tmp < len)
		{
			tmp++;
			j++;
		}
		if (ft_strlen(little) == j)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
