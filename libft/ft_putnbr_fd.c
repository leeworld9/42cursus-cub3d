/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:30:57 by dohelee           #+#    #+#             */
/*   Updated: 2021/01/04 07:53:04 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int n)
{
	return ((n < 0) ? -n : n);
}

void		ft_putnbr_fd(int n, int fd)
{
	char c;

	c = '0';
	if (fd > 0)
	{
		if (n != 0)
		{
			c = ft_abs(n % 10) + '0';
			if ((n / 10) != 0)
				ft_putnbr_fd(n / 10, fd);
			else
			{
				if (n < 0)
					ft_putchar_fd('-', fd);
			}
			ft_putchar_fd(c, fd);
		}
		else
			ft_putchar_fd(c, fd);
	}
	else
		return ;
}
