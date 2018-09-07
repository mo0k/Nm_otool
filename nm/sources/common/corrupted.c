/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrupted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 22:59:54 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/07 11:45:46 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

void corrupted()
{
	//free all mem
	while (g_meta->nlist)
		ft_lstdelfirst(&g_meta->nlist, &del);
	ft_dprintf(2, "Corrupted\n");
	exit(EXIT_FAILURE);
}
