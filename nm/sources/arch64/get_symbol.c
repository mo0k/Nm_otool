/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:33:21 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/02 23:40:45 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch64.h>

static char 		*get_symbol_sect64(char *buf, t_info *info, int colomn, \
																int is_external)
{
	int 		i;
	static		char *symbol_ref[SECT_ROWMAX][SECT_COLMAX] =
	{
		{"__text", "t", "__TEXT"},
		{"__data", "d", "__DATA"},
		{"__bss", "b", "__DATA"},
		{"__common", "s", "__DATA"},
		{"__const", "s", "__DATA"}
	};

	i = -1;
	colomn = colomn > SECT_COLMAX - 1 ? SECT_COLMAX - 1: colomn;
	while (++i < SECT_ROWMAX)
	{
		if (!ft_strcmp((char*)info->segname, symbol_ref[i][SEGNAME])
			&& !ft_strcmp((char*)info->sectname, symbol_ref[i][SECTNAME]))
		{
			if (!(buf = ft_strcpy(buf, symbol_ref[i][colomn])))
				return (NULL);
			if (colomn == SYMBOL_CHAR && is_external)
				buf[0] -= 32;
			return (buf);
		}
	}
	return (get_symbol_sect_nofound(buf, info, colomn, is_external));
}

static void			next_sect64(t_lc **lc, unsigned int *count, t_meta *meta, \
																t_seg64 *seg64)
{
	*count += SWAP32(meta->swap, seg64->nsects);
	*lc = (void*)*lc + SWAP32(meta->swap, (*lc)->cmdsize);
}

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
		if (CHK_VAL(g_meta, (void*)(seg64 + 1)))
			corrupted();
		if (count + seg64->nsects < index)
			next_sect64(&lc, &count, g_meta, seg64);
		else
		{
			sect64 = (t_sect64*)(seg64 + 1);
			if (CHK_VAL(g_meta, (void*)(sect64 + (index - count))))
				corrupted();
			info->segname = (void*)sect64[index - count - 1].segname;
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
	static int 		type[0x4] = {N_UNDF, N_ABS, N_INDR, N_STAB};

	if ((nlist->n_type & N_TYPE) == N_SECT)
		return (get_symbol_sect64(buf
					, get_sect64_info(g_meta->seg64, nlist->n_sect, &info)
					, colomn, (nlist->n_type & N_EXT)));
	if (nlist->n_type & N_STAB)
		return (get_ref(0x4, colomn));
	index = -0x1;
	while (++index < 0x3)
		if (type[index] == (nlist->n_type & N_TYPE))
			break;
	if (type[index] == N_UNDF && SWAP64(g_meta->swap, nlist->n_value) != 0)
		index = COMMON;
	if (index != COMMON && type[index] != (nlist->n_type & N_TYPE))
		return (" ");
	colomn = colomn > NOSECT_COLMAX - 0x1 ? NOSECT_COLMAX - 0x1: colomn;
	if (!(buf = ft_strcpy(buf, get_ref(index, colomn))))
		return (" ");
	if (colomn == SYMBOL_CHAR && (nlist->n_type & N_EXT))
		buf[0] -= 0x20;
	return (buf);
}

char 				*get_seg64_name(t_lc *lc, unsigned int index)
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
			if (CHK_VAL(g_meta, (void*)lc + lc->cmdsize))
				corrupted();
			lc = (void*)lc + lc->cmdsize;
		}
		else
			return (seg64->segname);
	}
	ft_printf("return NULL\n");
	return (NULL);
}