/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 05:31:33 by dohelee           #+#    #+#             */
/*   Updated: 2021/01/04 01:05:13 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *new;

	if ((new = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
