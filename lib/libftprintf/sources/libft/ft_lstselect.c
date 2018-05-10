/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstselect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 10:43:27 by mo0ky             #+#    #+#             */
/*   Updated: 2017/01/24 10:57:51 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstselect(t_list **alst, char *elem, int (*select)(t_list*, char*))
{
	t_list *cur;

	cur = *alst;
	if (!cur)
		return (NULL);
	while (cur)
	{
		if (select(cur, elem))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
