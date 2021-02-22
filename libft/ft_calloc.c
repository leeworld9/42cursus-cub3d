/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:38:22 by dohelee           #+#    #+#             */
/*   Updated: 2020/12/31 08:28:50 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *s;

	if ((s = malloc(nmemb * size)) == NULL)
		return (NULL);
	else
	{
		ft_bzero(s, nmemb * size);
		return (s);
	}
}
