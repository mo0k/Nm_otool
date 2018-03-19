/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbol64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:33:21 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/19 14:59:18 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <symbol.h>

static char 		*get_symbol_sect64(char *buf, char *sectname, int colomn, \
																int is_external)
{
	int 		i;
	static		char *symbol_ref[SYMBOL_REF_SECT_ROWMAX][SYMBOL_REF_COLMAX] =
	{
		{"__text", "t"},
		{"__data", "d"},
		{"__bss", "b"},
		{"__common", "s"}
	};
	i = -1;
	colomn = colomn > SYMBOL_REF_COLMAX - 1 ? SYMBOL_REF_COLMAX - 1: colomn;
	while (++i < SYMBOL_REF_SECT_ROWMAX)
	{
		if (!ft_strcmp(sectname, symbol_ref[i][STRING]))
		{
			if (!(buf = ft_strcpy(buf, symbol_ref[i][colomn])))
				return (NULL);
			if (colomn == CHAR && is_external)
				buf[0] -= 32; //upper case
			return (buf);
		}
	}
	return (NULL);
	
}

// Get the section name
static char 		*get_sect64_name(t_lc *lc, unsigned int index)
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
			lc = (void*)lc + lc->cmdsize;
		}
		else
		{
			sect64 = (t_sect64*)(seg64 + 1);
			return ((sect64 + (index - count) - 1)->sectname);
		}
	}
	return (NULL);
}

char 				*get_symbol64(char *buf, struct nlist_64 *nlist, int colomn)
{
	int 			index;
	static int 		type_value[0x4] = {N_UNDF, N_ABS, N_INDR, N_STAB};
	static char 	*symbol_ref[SYMBOL_REF_NOSECT_ROWMAX][SYMBOL_REF_COLMAX] =
	{
		{"undefined", "u"},
		{"absolute", "a"},
		{"indirect", "i"},
		{"?", "-"}
	};

	if ((nlist->n_type & N_TYPE) == N_SECT)
		return (get_symbol_sect64(buf
					, get_sect64_name(g_meta.seg64, nlist->n_sect)
					, colomn, (nlist->n_type & N_EXT)));
	if (nlist->n_type & N_STAB)
		return (symbol_ref[0x3][colomn]);
	index = -0x1;
	while (++index < 0x3)
		if (type_value[index] == (nlist->n_type & N_TYPE))
			break;
	if (type_value[index] != (nlist->n_type & N_TYPE))
		return (" ");
	colomn = colomn > SYMBOL_REF_COLMAX - 0x1 ? SYMBOL_REF_COLMAX - 0x1: colomn;
	if (!(buf = ft_strcpy(buf, symbol_ref[index][colomn])))
		return (" ");
	if (colomn == CHAR && (nlist->n_type & N_EXT))
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
			lc = (void*)lc + lc->cmdsize;
		}
		else
			return (seg64->segname);
	}
	ft_printf("return NULL\n");
	return (NULL);
}