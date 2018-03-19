/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:29 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 21:30:59 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_option_x(t_list *list)
{
	struct nlist_64*			elem;

	if (!list)
		return ;
	elem = list->content;
	if ((elem->n_type & N_STAB) && !GET_BIT(g_meta.options, OPT_A))
		return;
	printf("%016llx %02x %02x %04x %08x %s\n", 
									elem->n_value,
									elem->n_type,
									elem->n_sect,
									elem->n_desc,
									elem->n_un.n_strx,
									g_stringtab + elem->n_un.n_strx
									);	
}
