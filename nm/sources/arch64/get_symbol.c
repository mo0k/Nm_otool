/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:33:21 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/01 17:56:09 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch64.h>

static char 		*get_symbol_sect64(char *buf, t_info *info, int colomn, \
																int is_external)
{
	int 		i;
	static		char *symbol_ref[SYMBOL_REF_SECT_ROWMAX][SYMBOL_REF_SECT_COLMAX] =
	{
		{"__text", "t", "__TEXT"},
		{"__data", "d", "__DATA"},
		{"__bss", "b", "__DATA"},
		{"__common", "s", "__DATA"},
		{"__const", "s", "__DATA"}
	};
	i = -1;
	colomn = colomn > SYMBOL_REF_SECT_COLMAX - 1 ? SYMBOL_REF_SECT_COLMAX - 1: colomn;
	while (++i < SYMBOL_REF_SECT_ROWMAX)
	{
		//printf("test\n");
		//ft_printf("ssymbol_ref[i][SEGNAME]:%s, symbol_ref[i][SECTNAME]:%s\n", symbol_ref[i][SEGNAME], symbol_ref[i][SECTNAME]);
		//ft_printf("((t_seg64*)(info))->segname:%s, ((t_sect64*)(info))->sectname:%s\n", ((t_seg64*)(info))->segname, ((t_sect64*)(info))->sectname);
		if (!ft_strcmp((char*)info->segname, symbol_ref[i][SEGNAME])
			&& !ft_strcmp((char*)info->sectname, symbol_ref[i][SECTNAME]))
		{
			if (!(buf = ft_strcpy(buf, symbol_ref[i][colomn])))
				return (NULL);
			if (colomn == SYMBOL_CHAR && is_external)
				buf[0] -= 32; //upper case
			return (buf);
		}
	}
	if (!(buf = ft_strcpy(buf, colomn == SECTNAME ? (char*)info->sectname : "s")))
				return (NULL);
			//ft_printf("debug:%s\n", buf);
			if (colomn == SYMBOL_CHAR && is_external)
				buf[0] -= 32; //upper case
			return (buf);
	return (NULL);
	
}

// Get the section name
static t_info 		*get_sect64_info(t_lc *lc, unsigned int index, t_info *info)
{
	unsigned int 	count;
	t_seg64		*seg64;
	t_sect64	*sect64;

	if (!lc)
		return (NULL);
	count = 0;
	while (count < index)
	{
		seg64 = (t_seg64*)lc;
		if (count + seg64->nsects < index)
		{
			count += seg64->nsects;
			if (CHK_VAL(g_meta->ptr, g_meta->ptr + g_meta->size, (void*)lc + lc->cmdsize))
				corrupted("get_sect64_info");
			lc = (void*)lc + lc->cmdsize;
		}
		else
		{
			sect64 = (t_sect64*)(seg64 + 1);
			info->segname = (void*)(sect64 + (index - count) - 1)->segname;
			info->sectname = (void*)(sect64 + (index - count) - 1)->sectname;
			return (info);
		}
	}
	return (NULL);
}

char 				*get_symbol64(char *buf, struct nlist_64 *nlist, int colomn)
{
	int 			index;
	t_info 			info;
	static int 		type_value[0x4] = {N_UNDF, N_ABS, N_INDR, N_STAB};
	static char 	*symbol_ref[SYMBOL_REF_NOSECT_ROWMAX][SYMBOL_REF_NOSECT_COLMAX] =
	{
		{"undefined", "u"},
		{"absolute", "a"},
		{"indirect", "i"},
		{"common", "c"},
		{"?", "-"}
	};

	if ((nlist->n_type & N_TYPE) == N_SECT)
		return (get_symbol_sect64(buf
					, get_sect64_info(g_meta->seg64, nlist->n_sect, &info)
					, colomn, (nlist->n_type & N_EXT)));
	if (nlist->n_type & N_STAB)
		return (symbol_ref[0x4][colomn]);
	index = -0x1;
	while (++index < 0x3)
		if (type_value[index] == (nlist->n_type & N_TYPE))
			break;
	if (type_value[index] == N_UNDF && SWAP64(g_meta->swap, nlist->n_value) != 0)
		index = COMMON;
	if (index != COMMON && type_value[index] != (nlist->n_type & N_TYPE))
		return (" ");
	colomn = colomn > SYMBOL_REF_NOSECT_COLMAX - 0x1 ? SYMBOL_REF_NOSECT_COLMAX - 0x1: colomn;
	if (!(buf = ft_strcpy(buf, symbol_ref[index][colomn])))
		return (" ");
	if (colomn == SYMBOL_CHAR && (nlist->n_type & N_EXT))
		buf[0] -= 0x20; //32
	return (buf);
}

char 		*get_seg64_name(t_lc *lc, unsigned int index)
{
	unsigned int 	count;
	t_seg64			*seg64;
	if (!lc)
		return (NULL);
	count = 0;
	while (count < index)
	{
		seg64 = (t_seg64*)lc;
		if (count + seg64->nsects < index)
		{
			count += seg64->nsects;
			if (CHK_VAL(g_meta->ptr, g_meta->ptr + g_meta->size, (void*)lc + lc->cmdsize))
				corrupted("get_seg64_name");
			lc = (void*)lc + lc->cmdsize;
		}
		else
			return (seg64->segname);
	}
	ft_printf("return NULL\n");
	return (NULL);
}