/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/10 14:52:25 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arch64.h"

void		print_header64(void *ptr)
{
	(void)ptr;
	t_header64 *header;

	header = (t_header64*)ptr;
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
								, header->magic
								, header->cputype
								, (header->cpusubtype & 0x000000FF)
								, 0x80
								, header->filetype
								, header->ncmds
								, header->sizeofcmds
								, header->flags);
}

void		print_section64(void *ptr, size_t size, char *name, uint64_t addr)
{
	size_t			i;
	int 			flag;

	i = 0;
	flag = 1;
	if (CHK_VAL(g_meta.ptr, g_meta.ptr + g_meta.size, ptr + size))
		corrupted("handler64 4");
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
		print_section64(ptr + SWAP32(meta->swap ,((t_sect64*)(meta->sect_text))->offset)
						, SWAP64(meta->swap, ((t_sect64*)(meta->sect_text))->size)
						, "__TEXT,__text"
						, SWAP64(meta->swap, ((t_sect64*)(meta->sect_text))->addr));
	}
	if (GET_BIT(meta->options, OPT_d) && meta->sect_data)
	{
		print_section64(ptr + SWAP32(meta->swap, ((t_sect64*)(meta->sect_data))->offset)
						, SWAP64(meta->swap, ((t_sect64*)(meta->sect_data))->size)
						, "__DATA,__data"
						, SWAP64(meta->swap, ((t_sect64*)(meta->sect_data))->addr));
		
	}
	if (GET_BIT(meta->options, OPT_h))
	{
		print_header64(ptr);
	}

}

void 		*get_addr_sect64(t_seg64 *seg64, char *sectname)
{
	t_sect64 	*sect64;
	unsigned int 		i;

	i = 0;
	if (!seg64)
		return (0);
	sect64 = (t_sect64*)(seg64 + 1);
	if (CHK_VAL(g_meta.ptr, g_meta.ptr + g_meta.size, (void*)(seg64 + 1)))
		corrupted("handler64 5");
	while (i < SWAP32(g_meta.swap, seg64->nsects))
	{
		if (CHK_VAL(g_meta.ptr, g_meta.ptr + g_meta.size, (void*)(sect64 + 1)))
			corrupted("handler64 6");
		P_DEBUG_VARGS("%s\n", sect64->sectname);
		if (!ft_strcmp(sect64->sectname, sectname))
			return (sect64);
		++sect64;
		++i;
	}
	return (0);
}

void		handler64(void *ptr, t_meta *meta)
{
	t_header64	*header;
	t_lc		*lc;
	uint32_t	count;

	if (!ptr)
		return ;
	count = 0;
	header = (t_header64*)ptr;
	if (CHK_VAL(ptr, ptr + meta->size, (void*)header))
		corrupted("handler64 1");
	lc = ptr + sizeof(t_header64);
	meta->swap = (header->magic == MH_CIGAM_64) ? 1 : 0;
	while (count < SWAP32(meta->swap, header->ncmds)
			&& (GET_BIT(meta->options, OPT_d) || GET_BIT(meta->options, OPT_t)))
	{
		if (CHK_VAL(ptr, ptr + meta->size, (void*)lc)
			|| CHK_VAL(ptr, ptr + meta->size, (void*)lc + SWAP32(meta->swap, lc->cmdsize)))
			corrupted("handler64 2");
		else if (lc->cmd == LC_SEGMENT_64)
		{
			if (!ft_strcmp((char*)lc+8, "__TEXT") && GET_BIT(meta->options, OPT_t)
				&& !meta->sect_text)
			{
				P_DEBUG("go find section _text in _TEXT\n");
				meta->sect_text = get_addr_sect64((t_seg64*)lc, "__text");
			}
			else if (!ft_strcmp((char*)lc+8, "__DATA") && GET_BIT(meta->options, OPT_d)
				&& !meta->sect_data)
			{
				P_DEBUG("go find section _data in _DATA\n");
				meta->sect_data = get_addr_sect64((t_seg64*)lc, "__data");
				//ft_printf("meta->sect_data:%p\n", meta->sect_data);
			}
		}
		lc = (void*)lc + SWAP32(meta->swap, lc->cmdsize);
		++count;
	}
	display64(meta, ptr);
}