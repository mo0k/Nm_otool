/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:29 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 15:37:31 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_hexa(t_list *list)
{
	struct nlist_64*			elem;
	if (!list)
		return ;
	elem = list->content;
	printf("%016llx %02x %02x %04x %08x %s %s\n", 
									elem->n_value,
									elem->n_type,
									elem->n_sect,
									elem->n_desc,
									elem->n_un.n_strx,
									g_stringtab + elem->n_un.n_strx,
									(elem->n_type & N_TYPE) == N_UNDF
										? get_dylibname(g_meta.dylib, GET_LIBRARY_ORDINAL(elem->n_desc) - 1)
										: "");	
}
