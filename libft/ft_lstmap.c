/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 08:54:12 by dohelee           #+#    #+#             */
/*   Updated: 2021/01/03 19:54:12 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_next;
	t_list	*curr;

	if (lst == NULL)
		return (NULL);
	else
	{
		if ((new_head = ft_lstnew(f(lst->content))) == NULL)
			return (NULL);
		curr = new_head;
		lst = lst->next;
		while (lst != NULL)
		{
			if ((new_next = ft_lstnew(f(lst->content))) == NULL)
			{
				ft_lstdelone(new_next, del);
				return (NULL);
			}
			curr->next = new_next;
			curr = new_next;
			lst = lst->next;
		}
	}
	return (new_head);
}
