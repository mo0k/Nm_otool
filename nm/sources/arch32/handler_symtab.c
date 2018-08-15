/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_symtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 06:56:27 by mo0k              #+#    #+#             */
/*   Updated: 2018/08/10 14:47:31 by mo0k             ###   ########.fr       */
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
		ft_printf("cmd:0x%x\n", SWAP32(meta->swap, stab_command->cmd));
		ft_printf("cmdsize:%d\n", SWAP32(meta->swap, stab_command->cmdsize));
		ft_printf("symoff:%d\n", SWAP32(meta->swap, stab_command->symoff));
		ft_printf("nsyms:%d\n", SWAP32(meta->swap, stab_command->nsyms));
		ft_printf("stroff:%d\n", SWAP32(meta->swap, stab_command->stroff));
		ft_printf("strsize:%d\n", SWAP32(meta->swap, stab_command->strsize));
	}
	if (CHK_VAL(ptr, ptr + meta->size, ptr + SWAP32(meta->swap, stab_command->symoff))
		|| CHK_VAL(ptr, ptr + meta->size, ptr + SWAP32(meta->swap, stab_command->stroff)))
		corrupted("handler_symtab32 1");
	nlist = (struct nlist*)(ptr + SWAP32(meta->swap, stab_command->symoff));
	//ft_printf("nlist:%p\n", nlist);
	g_stringtab = ptr + SWAP32(meta->swap, stab_command->stroff);
	list = 0;
	//verif nsyms
	while (++i < SWAP32(meta->swap, stab_command->nsyms))
	{
		//add verif
		//printf("i:%d\n", i);
		if (CHK_VAL(ptr, ptr + meta->size, (void*)(nlist + i + 1)))
			corrupted("handler_symtab32 2");
		//ft_printf("g_stringtab:%p\nadd:%d\nptr:%p\nend:%p\n", g_stringtab, SWAP32(meta->swap, nlist[i].n_un.n_strx), ptr, ptr + meta->size);
		//printf("str:%s\n", g_stringtab + SWAP32(meta->swap, nlist[i].n_un.n_strx));
		if (CHK_VAL(ptr, ptr + meta->size, (void*)g_stringtab + SWAP32(meta->swap, nlist[i].n_un.n_strx)))
			corrupted("handler_symtab32 3");
		P_DEBUG_VARGS("str:%s\nsect:0x%x\n\n", g_stringtab + SWAP32(g_meta->swap, nlist[i].n_un.n_strx), nlist[i].n_sect);
		ft_lstadd_end(&list, ft_lstnew(&nlist[i], sizeof(struct nlist)));
		//sleep(1);
	}
	sort(&list, meta->options, meta->sortfunc);
	ft_lstiter(list, meta->printfunc);
	while (list)
		ft_lstdelfirst(&list, &del);
	//delete list chaine nlist
}
