/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:33:21 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/04 21:28:27 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch32.h>

static char			*get_symbol_sect32(char *buf, t_info *info, int colomn, \
																int is_external)
{
	int			i;
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

static void			next_sect32(t_lc **lc, unsigned int *count, t_meta *meta, \
																t_seg32 *seg32)
{
	*count += SWAP32(meta->swap, seg32->nsects);
	*lc = (void*)*lc + SWAP32(meta->swap, (*lc)->cmdsize);
}

t_info				*get_sect32_info(t_lc *lc, unsigned int index, t_info *sect)
{
	unsigned int	count;
	t_seg32			*seg32;
	t_sect32		*sect32;

	if (!lc)
		return (NULL);
	count = 0;
	while (count < index)
	{
		seg32 = (t_seg32*)lc;
		if (CHK_VAL(g_meta, (void*)seg32 + 1))
			corrupted();
		if (count + SWAP32(g_meta->swap, seg32->nsects) < index)
			next_sect32(&lc, &count, g_meta, seg32);
		else
		{
			sect32 = (t_sect32*)(seg32 + 1);
			if (CHK_VAL(g_meta, (void*)(sect32 + (index - count))))
				corrupted();
			sect->segname = (void*)sect32[index - count -1].segname;
			sect->sectname = (void*)(sect32 + (index - count - 1))->sectname;
			return (sect);
		}
	}
	return (NULL);
}

char				*get_symbol32(char *buf, struct nlist *nlist, int colomn)
{
	int 			index;
	t_info 			info;
	static int 		type[0x4] = {N_UNDF, N_ABS, N_INDR, N_STAB};

	if ((nlist->n_type & N_TYPE) == N_SECT)
		return (get_symbol_sect32(buf
					, get_sect32_info(g_meta->seg32, nlist->n_sect, &info)
					, colomn, (nlist->n_type & N_EXT)));
	if (nlist->n_type & N_STAB)
		return (get_ref(0x4, colomn));
	index = -0x1;
	while (++index < 0x3)
		if (type[index] == (nlist->n_type & N_TYPE))
			break;
	if (type[index] == N_UNDF && SWAP32(g_meta->swap, nlist->n_value) != 0)
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

char				*get_seg32_name(t_lc *lc, unsigned int index)
{
	unsigned int 	count;
	t_seg32			*seg32;

	if (!lc)
		return (NULL);
	count = 0;
	while (count < index)
	{
		seg32 = (t_seg32*)lc;
		if (count + SWAP32(g_meta->swap, seg32->nsects) < index)
		{
			count += SWAP32(g_meta->swap, seg32->nsects);
			if (CHK_VAL(g_meta, (void*)lc + lc->cmdsize))
				corrupted();
			lc = (void*)lc + lc->cmdsize;
		}
		else
			return (seg32->segname);
	}
	return (NULL);
}