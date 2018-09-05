/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/05 23:59:20 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arch64.h"

void		print_header64(void *ptr)
{
	t_header64 *header;

	header = (t_header64*)ptr;
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
	ft_printf(" 0x%08x %-8d % 10d  0x%- 02.2x    %8d% 6d% 11d 0x%08x\n"
								, SWAP32(g_meta->swap, header->magic)
								, SWAP32(g_meta->swap, header->cputype)
								, (header->cpusubtype & 0x000000FF)
								, 0x80
								, SWAP32(g_meta->swap, header->filetype)
								, SWAP32(g_meta->swap, header->ncmds)
								, SWAP32(g_meta->swap, header->sizeofcmds)
								, SWAP32(g_meta->swap, header->flags));
}

void		print_section64(void *ptr, size_t size, char *name, uint64_t addr)
{
	size_t			i;
	int 			flag;

	i = 0;
	flag = 1;
	if (CHK_VAL(g_meta, ptr + size))
		corrupted();
	ft_printf("Contents of (%s) section\n", name);
	while (i < size)
	{
		if (flag == 1)
			ft_printf("%016llx\t", addr + i);
		ft_printf("%02x ", *(unsigned char*)ptr);
		if (flag == 16 && !(flag = 0))
			ft_printf("\n");
		++flag;
		++ptr;
		++i;
		//++addr;
	}
	if (flag - 1 < 16 && flag > 1)
	{
			ft_printf("\n");
	}
}

void 		display64(t_meta *meta, void *ptr)
{
	if (!meta)
		return ;
	if (GET_BIT(meta->options, OPT_t) && meta->sect_text)
	{
		print_section64(ptr +
				SWAP32(meta->swap ,((t_sect64*)(meta->sect_text))->offset)
					, SWAP64(meta->swap, ((t_sect64*)(meta->sect_text))->size)
					, "__TEXT,__text"
					, SWAP64(meta->swap, ((t_sect64*)(meta->sect_text))->addr));
	}
	if (GET_BIT(meta->options, OPT_d) && meta->sect_data)
	{
		print_section64(ptr +
				SWAP32(meta->swap, ((t_sect64*)(meta->sect_data))->offset)
					, SWAP64(meta->swap, ((t_sect64*)(meta->sect_data))->size)
					, "__DATA,__data"
					, SWAP64(meta->swap, ((t_sect64*)(meta->sect_data))->addr));
		
	}
	if (GET_BIT(meta->options, OPT_h))
		print_header64(ptr);
}
