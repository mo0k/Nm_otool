/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 20:37:50 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/19 18:17:53 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_option_m(t_list *list)
{
	struct nlist_64*			elem;
	char  						buf1[255];
	char  						buf2[255];

	memset(buf1, 0, 255);
	memset(buf2, 0, 255);
	if (!list)
		return ;
	elem = list->content;
	if (((elem->n_type & N_STAB) && !GET_BIT(g_meta.options, OPT_A))
		|| ((elem->n_type & N_TYPE) != N_UNDF && GET_BIT(g_meta.options, OPT_u))
		|| ((elem->n_type & N_TYPE) == N_UNDF && GET_BIT(g_meta.options, OPT_U)))
		return ;
	if (elem->n_value)
		printf("%016llx ", elem->n_value);
	else
		printf("%16s ", "");
	if ((elem->n_type & N_TYPE) == N_SECT)
	{
		printf("(%s,%s) %s %s", get_seg64_name(g_meta.seg64, elem->n_sect)
			 			, get_symbol64(buf1, elem, STRING)
						, get_infos_external(elem, buf2)
						, g_stringtab + elem->n_un.n_strx);
	}
	else
	{
		printf("(%s) %s %s", get_symbol64(buf1, elem, STRING)
						, get_infos_external(elem, buf2)
						, g_stringtab + elem->n_un.n_strx);
		if ((elem->n_type & N_TYPE) == N_UNDF)
		{
			char *ptr = get_dylibname(g_meta.dylib, GET_LIBRARY_ORDINAL(elem->n_desc) - 1);
			//memmove(buf1, ptr, ft_strlen(ptr));
			printf(" (from %s)\n", ptr);
			return ;
		}
		printf("\n");
	}
}

//0000000014 (SEG)(SECT) (EXT) (DYNAMIC) (from dylib) string
//0000000014 (NO_SECT) (EXT) (DYNAMIC) (from dylib) string