/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 23:54:06 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/24 11:30:36 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_start(t_list **alst, t_list *new)
{
	if (!new)
		return ;
	if (*alst)
		(*alst)->prev = new;
	new->next = *alst;
	*alst = new;
}
