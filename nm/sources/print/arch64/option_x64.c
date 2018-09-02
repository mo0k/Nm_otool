/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_x64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:29 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/03 00:10:29 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_option_x_arch64(t_list *list)
{
	struct nlist_64*			e;

	if (!list)
		return ;
	e = list->content;
	if (((e->n_type & N_STAB) && !GET_BIT(g_meta->options, OPT_a))
		|| ((e->n_type & N_TYPE) != N_UNDF && GET_BIT(g_meta->options, OPT_u))
		|| ((e->n_type & N_TYPE) == N_UNDF && GET_BIT(g_meta->options, OPT_U)))
		return;
	ft_printf("%016llx %02x %02x %04x %08x %s", 
					SWAP64(g_meta->swap, e->n_value),
					e->n_type,
					e->n_sect,
					SWAP16(g_meta->swap, e->n_desc),
					e->n_un.n_strx,
					g_stringtab + SWAP32(g_meta->swap, e->n_un.n_strx)
					);
	if ((e->n_type & N_TYPE) == N_INDR)
		ft_printf(" (indirect for %016llx %s)\n", SWAP64(g_meta->swap, e->n_value)
					, g_stringtab + SWAP32(g_meta->swap, e->n_un.n_strx));
	else
		ft_printf("\n");
}
