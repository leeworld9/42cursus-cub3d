/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:28:29 by dohelee           #+#    #+#             */
/*   Updated: 2021/01/02 21:46:20 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (fd > 0 && s != NULL)
	{
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
	}
	else
		return ;
}
