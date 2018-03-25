/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_none64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:47 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/25 10:42:33 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_option_none_arch64(t_list *list)
{
	struct nlist_64*			elem;
	char 						buf[85];

	if (!list)
		return ;
	elem = list->content;
	if (((elem->n_type & N_STAB) && !GET_BIT(g_meta.options, OPT_A))
		|| ((elem->n_type & N_TYPE) != N_UNDF && GET_BIT(g_meta.options, OPT_u))
		|| ((elem->n_type & N_TYPE) == N_UNDF && GET_BIT(g_meta.options, OPT_U)))
		return;
	if (elem->n_value)
		printf("%016llx ", elem->n_value);
	else
		printf("%16s ", "");
	if (elem->n_type & N_STAB)
	{
		
		printf("%s %02x %04x %5s %s\n", get_symbol64(buf, elem, SYMBOL_CHAR)
			 			, 	elem->n_sect
						,	elem->n_desc
						, get_type_stab(elem->n_type)
						, g_stringtab + elem->n_un.n_strx);
	}
	else
	{
		printf("%s %s\n", get_symbol64(buf, elem, SYMBOL_CHAR)
					, g_stringtab + elem->n_un.n_strx);
	}
}