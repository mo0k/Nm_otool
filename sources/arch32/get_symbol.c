/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:33:21 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/31 12:14:36 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch32.h>

static char 		*get_symbol_sect32(char *buf, t_info *info, int colomn, \
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
			if (colomn == SYMBOL_CHAR && is_external)
				buf[0] -= 32; //upper case
			return (buf);
	
}

// Get the section name
static t_info 		*get_sect32_info(t_lc *lc, unsigned int index, t_info *sect)
{
	//static t_info *sect;
	unsigned int 	count;
	t_seg32			*seg32;
	t_sect32		*sect32;

	if (!lc)
		return (NULL);
	count = 0;
	while (count < index)
	{
		seg32 = (t_seg32*)lc;
		if (CHK_VAL(g_meta.ptr, g_meta.ptr + g_meta.size, (void*)seg32)
			|| CHK_VAL(g_meta.ptr, g_meta.ptr + g_meta.size, (void*)(seg32 + 1)))
				corrupted("get_sect32_info 1");
		if (count + seg32->nsects < index)
		{
			count += seg32->nsects;
			//if (CHK_VAL(g_meta.ptr, g_meta.ptr + g_meta.size, (void*)lc + lc->cmdsize))
			//	corrupted();
			lc = (void*)lc + lc->cmdsize;
		}
		else
		{
			//ft_printf("ok\n");
			sect32 = (t_sect32*)(seg32 + 1);
			//return ((sect32 + (index - count) - 1)->sectname);
			//ft_printf("seg32->segname:%s, sect32->sectname:%s\n", seg32->segname, sect32->sectname);
			sect->segname = (void*)seg32->segname;
			if (CHK_VAL(g_meta.ptr, g_meta.ptr + g_meta.size, (void*)(sect32 + (index - count))))
				corrupted("get_sect32_info 2");
			sect->sectname = (void*)(sect32 + (index - count) - 1)->sectname;
			//ft_printf("sect->segname:%s, sect->sectname:%s\n", (char*)sect->segname, (char*)sect->sectname);
			return (sect);
		}
	}
	return (NULL);
}

char 				*get_symbol32(char *buf, struct nlist *nlist, int colomn)
{
	int 			index;
	t_info 			info;
	static int 		type_value[0x4] = {N_UNDF, N_ABS, N_INDR, N_STAB};
	static char 	*symbol_ref[SYMBOL_REF_NOSECT_ROWMAX][SYMBOL_REF_NOSECT_COLMAX] =
	{
		{"__undefined", "u"},
		{"__absolute", "a"},
		{"__indirect", "i"},
		{"?", "-"}
	};

	if ((nlist->n_type & N_TYPE) == N_SECT)
	{
		//ft_printf("(nlist->n_type & N_EXT):%d\n", (nlist->n_type & N_EXT));
		//ft_printf("nsect:%d\n", nlist->n_sect);
		return (get_symbol_sect32(buf
					, get_sect32_info(g_meta.seg32, nlist->n_sect, &info)
					, colomn
					, (nlist->n_type & N_EXT)));
	}
	if (nlist->n_type & N_STAB)
		return (symbol_ref[0x3][colomn]);
	index = -0x1;
	while (++index < 0x3)
		if (type_value[index] == (nlist->n_type & N_TYPE))
			break;
	if (type_value[index] != (nlist->n_type & N_TYPE))
		return (" ");
	colomn = colomn > SYMBOL_REF_NOSECT_COLMAX - 0x1 ? SYMBOL_REF_NOSECT_COLMAX - 0x1: colomn;
	if (!(buf = ft_strcpy(buf, symbol_ref[index][colomn])))
		return (" ");
	if (colomn == SYMBOL_CHAR && (nlist->n_type & N_EXT))
		buf[0] -= 0x20; //32
	return (buf);
}

char 		*get_seg32_name(t_lc *lc, unsigned int index)
{
	unsigned int 	count;
	t_seg32			*seg32;
	if (!lc)
		return (NULL);
	count = 0;
	while (count < index)
	{
		seg32 = (t_seg32*)lc;
		if (count + seg32->nsects < index)
		{
			count += seg32->nsects;
			if (CHK_VAL(g_meta.ptr, g_meta.ptr + g_meta.size, (void*)lc + lc->cmdsize))
				corrupted("get_seg32_name");
			lc = (void*)lc + lc->cmdsize;
		}
		else
			return (seg32->segname);
	}
	ft_printf("return NULL\n");
	return (NULL);
}