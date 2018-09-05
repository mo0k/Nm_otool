/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/05 23:57:48 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arch32.h"

static void		print_header32(void *ptr)
{
	t_header32 *header;

	header = (t_header32*)ptr;
	if (CHK_VAL(g_meta, (void*)(header + 1)))
		corrupted();
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
								, SWAP32(g_meta->swap, header->magic)
								, SWAP32(g_meta->swap, header->cputype)
								, (header->cpusubtype & 0x000000FF)
								, (header->cpusubtype & CPU_ARCH_MASK)
								, SWAP32(g_meta->swap, header->filetype)
								, SWAP32(g_meta->swap, header->ncmds)
								, SWAP32(g_meta->swap, header->sizeofcmds)
								, SWAP32(g_meta->swap, header->flags));
}

static void		print_section32(void *ptr, size_t size, char *name, uint32_t addr)
{
	size_t			i;
	int				flag;

	i = 0;
	flag = 1;
	if (CHK_VAL(g_meta, ptr + size))
		corrupted();
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
			ft_printf("\n");
}

void			display32(t_meta *meta, void *ptr)
{
	if (!meta)
		return ;
	if (GET_BIT(meta->options, OPT_t) && meta->sect_text)
	{
		print_section32(ptr + 
			SWAP32(meta->swap, ((t_sect32*)(meta->sect_text))->offset)
					, SWAP32(meta->swap, ((t_sect32*)(meta->sect_text))->size)
					, "__TEXT,__text"
					, SWAP32(meta->swap, ((t_sect32*)(meta->sect_text))->addr));
	}
	if (GET_BIT(meta->options, OPT_d) && meta->sect_data)
	{
		print_section32(ptr + 
			SWAP32(meta->swap, ((t_sect32*)(meta->sect_data))->offset)
					, SWAP32(meta->swap, ((t_sect32*)(meta->sect_data))->size)
					, "__DATA,__data"
					, SWAP32(meta->swap, ((t_sect32*)(meta->sect_data))->addr));
		
	}
	if (GET_BIT(meta->options, OPT_h))
		print_header32(ptr);
}
