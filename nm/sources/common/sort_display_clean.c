/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_display_clean.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 22:51:29 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/02 22:51:57 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

void		sort_display_clean(t_list **list, t_meta *meta)
{
	sort(list, meta->options, meta->sortfunc);
	ft_lstiter(*list, meta->printfunc);
	while (*list)
		ft_lstdelfirst(list, &del);
}