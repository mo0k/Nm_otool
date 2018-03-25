/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_symtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:48:15 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/22 22:55:10 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <handler.h>

void						handler_systab64(void* lc, void *ptr, t_meta *meta)
{
	struct symtab_command	*stab_command;
	struct nlist_64			*nlist;
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
	nlist = ptr + stab_command->symoff;
	g_stringtab = ptr + stab_command->stroff;
	list = 0;
	while (++i < stab_command->nsyms)
		ft_lstadd_end(&list, ft_lstnew(&nlist[i], sizeof(struct nlist_64)));
	sort(&list, meta->options, meta->sortfunc);
	ft_lstiter(list, meta->printfunc);
	//delete list chaine nlist
}

void						handler_systab32(void* lc, void *ptr, t_meta *meta)
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
	nlist = ptr + stab_command->symoff;
	g_stringtab = ptr + stab_command->stroff;
	list = 0;
	while (++i < stab_command->nsyms)
		ft_lstadd_end(&list, ft_lstnew(&nlist[i], sizeof(struct nlist_64)));
	sort(&list, meta->options, meta->sortfunc);
	ft_lstiter(list, meta->printfunc);
	//delete list chaine nlist
}