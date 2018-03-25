/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_j.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:40 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/22 21:14:36 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_option_j_arch64(t_list *list)
{
	struct nlist_64*			elem;

	if (!list)
		return ;
	elem = list->content;
	if ((elem->n_type & N_STAB && !GET_BIT(g_meta.options, OPT_A))
		|| ((elem->n_type & N_TYPE) != N_UNDF && GET_BIT(g_meta.options, OPT_u))
		|| ((elem->n_type & N_TYPE) == N_UNDF && GET_BIT(g_meta.options, OPT_U)))
		return;
	printf("%s\n", g_stringtab + ((struct nlist_64*)(list->content))->n_un.n_strx);
}
