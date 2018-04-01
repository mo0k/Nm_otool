/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_symtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 06:56:27 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/31 22:52:45 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch32.h>

static void						del(void *elem, size_t size)
{
	(void)size;
	free(elem);
}

void						handler_symtab32(void* lc, void *ptr, t_meta *meta)
{
	struct symtab_command	*stab_command;
	struct nlist			*nlist;
	t_list					*list;
	uint32_t				i;

	if (!ptr)
		return ;
	i = -1;
	stab_command = (struct symtab_command*)lc;
	if (DEBUG)
	{
		ft_printf("cmd:0x%x\n", stab_command->cmd);
		ft_printf("cmdsize:%d\n", stab_command->cmdsize);
		ft_printf("symoff:%d\n", stab_command->symoff);
		ft_printf("nsyms:%d\n", stab_command->nsyms);
		ft_printf("stroff:%d\n", stab_command->stroff);
		ft_printf("strsize:%d\n", stab_command->strsize);
	}
	if (CHK_VAL(ptr, ptr + meta->size, ptr + stab_command->symoff)
		|| CHK_VAL(ptr, ptr + meta->size, ptr + stab_command->stroff))
		corrupted("handler_symtab32 1");
	nlist = ptr + stab_command->symoff;
	g_stringtab = ptr + stab_command->stroff;
	list = 0;
	//verif nsyms
	while (++i < stab_command->nsyms)
	{
		//add verif
		if (CHK_VAL(ptr, ptr + meta->size, (void*)(nlist + i + 1))
			|| CHK_VAL(ptr, ptr + meta->size, (void*)g_stringtab + nlist[i].n_un.n_strx))
			corrupted("handler_symtab32 2");
		ft_lstadd_end(&list, ft_lstnew(&nlist[i], sizeof(struct nlist_64)));
	}
	sort(&list, meta->options, meta->sortfunc);
	ft_lstiter(list, meta->printfunc);
	while (list)
		ft_lstdelfirst(&list, &del);
	//delete list chaine nlist
}