/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/10 15:03:45 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arch32.h"

void		print_header32(void *ptr)
{
	(void)ptr;
	t_header32 *header;

	header = (t_header32*)ptr;
	ft_printf("Mach header\n % 10s %s %- 10s %5s    %- 9s%- 6s%- 11s% 10s\n"
								, "magic"
								, "cputype"
								, "cpusubtype"
								, "caps"
								, "filetype"
								, "ncmds"
								, "sizeofcmds"
								, "flags");
	ft_printf(" 0x%08x % 7d % 10d  0x%-02.2x    %8d% 6d% 11d 0x%08x\n"
								, header->magic
								, header->cputype
								, (header->cpusubtype & 0x000000FF)
								, (header->cpusubtype & CPU_ARCH_MASK)
								, header->filetype
								, header->ncmds
								, header->sizeofcmds
								, header->flags);
}

void		print_section32(void *ptr, size_t size, char *name, uint32_t addr)
{
	size_t			i;
	int 			flag;

	i = 0;
	flag = 1;
	if (CHK_VAL(g_meta.ptr, g_meta.ptr + g_meta.size, ptr + size))
		corrupted("handler32 4");
	ft_printf("Contents of (%s) section\n", name);
	while (i < size)
	{
		if (flag == 1)
			ft_printf("%08x\t", addr + i);
		ft_printf("%02x ", *(unsigned char*)ptr);
		if (flag == 16 && !(flag = 0))
			ft_printf("\n");
		++flag;
		++ptr;
		++i;
	}
	if (flag - 1 < 16 && flag > 1)
	{
			ft_printf("\n");
	}
}

void 		display32(t_meta *meta, void *ptr)
{
	if (!meta)
		return ;
	if (GET_BIT(meta->options, OPT_t) && meta->sect_text)
	{
		print_section32(ptr +  SWAP32(meta->swap, ((t_sect32*)(meta->sect_text))->offset)
						,  SWAP32(meta->swap, ((t_sect32*)(meta->sect_text))->size)
						, "__TEXT,__text"
						,  SWAP32(meta->swap, ((t_sect32*)(meta->sect_text))->addr));
	}
	if (GET_BIT(meta->options, OPT_d) && meta->sect_data)
	{
		print_section32(ptr +  SWAP32(meta->swap, ((t_sect32*)(meta->sect_data))->offset)
						,  SWAP32(meta->swap, ((t_sect32*)(meta->sect_data))->size)
						, "__DATA,__data"
						,  SWAP32(meta->swap, ((t_sect32*)(meta->sect_data))->addr));
		
	}
	if (GET_BIT(meta->options, OPT_h))
	{
		print_header32(ptr);
	}

}

void 		*get_addr_sect32(t_seg32 *seg32, char *sectname)
{
	t_sect32 	*sect32;
	unsigned int 		i;

	i = 0;
	if (!seg32)
		return (0);
	sect32 = (t_sect32*)(seg32 + 1);
	if (CHK_VAL(g_meta.ptr, g_meta.ptr + g_meta.size, (void*)(seg32 + 1)))
		corrupted("handler32 5");
	while (i < SWAP32(g_meta.swap, seg32->nsects))
	{
		if (CHK_VAL(g_meta.ptr, g_meta.ptr + g_meta.size, (void*)(sect32 + 1)))
			corrupted("handler32 6");
		P_DEBUG_VARGS("%s\n", sect32->sectname);
		if (!ft_strcmp(sect32->sectname, sectname))
			return (sect32);
		++sect32;
		++i;
	}
	return (0);
}

void		handler32(void *ptr, t_meta *meta)
{
	t_header32	*header;
	t_lc		*lc;
	uint32_t	count;

	if (!ptr)
		return ;
	count = 0;
	header = (t_header32*)ptr;
	lc = ptr + sizeof(t_header32);
	meta->swap = (header->magic == MH_CIGAM) ? 1 : 0;
	while (count < SWAP32(meta->swap, header->ncmds)
			&& (GET_BIT(meta->options, OPT_d) || GET_BIT(meta->options, OPT_t)))
	{
		if (CHK_VAL(ptr, ptr + meta->size, (void*)lc)
			|| CHK_VAL(ptr, ptr + meta->size, (void*)lc + SWAP32(meta->swap, lc->cmdsize)))
			corrupted("handler32");
		else if (lc->cmd == LC_SEGMENT)
		{
			if (!ft_strcmp((char*)lc+8, "__TEXT") && GET_BIT(meta->options, OPT_t)
				&& !meta->sect_text)
				meta->sect_text = get_addr_sect32((t_seg32*)lc, "__text");
			else if (!ft_strcmp((char*)lc+8, "__DATA") && GET_BIT(meta->options, OPT_d)
				&& !meta->sect_data)
				meta->sect_data = get_addr_sect32((t_seg32*)lc, "__data");
		}
		lc = (void*)lc + SWAP32(meta->swap, lc->cmdsize);
		++count;
	}
	display32(meta, ptr);
}