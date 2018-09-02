/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_symtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 06:56:27 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/02 22:59:06 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch64.h>

void						handler_symtab64(void* lc, void *ptr, t_meta *meta)
{
	struct symtab_command	*stab_command;
	struct nlist_64			*nlist;
	t_list					*list;
	uint32_t				i;

	if (!ptr)
		return ;
	i = -1;
	stab_command = (struct symtab_command*)lc;
	if (CHK_VAL(meta, ptr + stab_command->symoff)
		|| CHK_VAL(meta, ptr + stab_command->stroff))
		corrupted();
	nlist = ptr + stab_command->symoff;
	g_stringtab = ptr + stab_command->stroff;
	list = 0;
	while (++i < stab_command->nsyms)
	{
		if (CHK_VAL(meta, (void*)(nlist + i + 1)) ||
			CHK_VAL(meta, 
				(void*)g_stringtab + SWAP32(meta->swap, nlist[i].n_un.n_strx)))
			corrupted();
		ft_lstadd_end(&list, ft_lstnew(&nlist[i], sizeof(struct nlist_64)));
	}
	sort_display_clean(&list, meta);
}
