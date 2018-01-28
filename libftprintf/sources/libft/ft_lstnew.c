/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:45:24 by jmoucade          #+#    #+#             */
/*   Updated: 2017/04/25 11:25:44 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if (!(list = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		list->content_size = 0;
		list->content = NULL;
	}
	else
	{
		if (!(list->content = (void*)malloc(content_size)))
		{
			free(list);
			return (NULL);
		}
		list->content = ft_memmove(list->content, content, content_size);
		list->content_size = content_size;
	}
	list->next = NULL;
	list->prev = NULL;
	return (list);
}
