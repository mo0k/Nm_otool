/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_m32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 20:37:50 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/01 22:31:15 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_option_m_arch32(t_list *list)
{
	struct nlist*				elem;
	char  						buf1[255];
	char  						buf2[255];

	memset(buf1, 0, 255);
	memset(buf2, 0, 255);
	if (!list)
		return ;
	elem = list->content;
	if (((elem->n_type & N_STAB) && !GET_BIT(g_meta->options, OPT_a))
		|| ((elem->n_type & N_TYPE) != N_UNDF && GET_BIT(g_meta->options, OPT_u))
		|| ((elem->n_type & N_TYPE) == N_UNDF && GET_BIT(g_meta->options, OPT_U)))
		return ;
	if (SWAP32(g_meta->swap, elem->n_value) || (GET_BIT(g_meta->options, OPT_a) && (elem->n_type & N_STAB)))
		ft_printf("%08x ", SWAP32(g_meta->swap, elem->n_value));
	else
		ft_printf("%8s ", "");
	if ((elem->n_type & N_TYPE) == N_SECT)
	{
		ft_printf("(%s,%s) %s %s\n", get_seg32_name(g_meta->seg32, elem->n_sect)
			 			, get_symbol32(buf1, elem, SECTNAME)
						, get_infos_external32(elem, buf2)
						, g_stringtab + SWAP32(g_meta->swap, elem->n_un.n_strx));
	}
	else
	{
		ft_printf("(%s) %s %s", get_symbol32(buf1, elem, SECTNAME)
						, get_infos_external32(elem, buf2)
						, g_stringtab + SWAP32(g_meta->swap, elem->n_un.n_strx));
		if ((elem->n_type & N_TYPE) == N_UNDF
			&& GET_LIBRARY_ORDINAL(SWAP16(g_meta->swap, elem->n_desc)) > 0)
		{
			char *ptr = get_dylibname(g_meta->dylib, GET_LIBRARY_ORDINAL(SWAP16(g_meta->swap, elem->n_desc)) - 1);
			//memmove(buf1, ptr, ft_strlen(ptr));
			ft_printf("\nptr:%s\n", ptr);
			ft_memmove(buf1, ptr, ft_strlen(ptr));
			buf1[ft_strlen(ptr)] = 0;
			char *end;
			if ((end = ft_strchr(buf1, '.')))
			{
				/*ft_printf("end:%s\n", end);
				while (*(end+1) && *(end+1) >= '0' && *(end+1) <= '9')
				{
					++end;
					ft_printf("end++:%c\n", *end);
				}
				if (*end >= '0' && *end <= '9') 
					++end;*/
				*end = 0;
			}
			ft_printf(" (from %s)\n", buf1);
			return ;
		}
		ft_printf("\n");
	}
}

//0000000014 (SEG)(SECT) (EXT) (DYNAMIC) (from dylib) string
//0000000014 (NO_SECT) (EXT) (DYNAMIC) (from dylib) string