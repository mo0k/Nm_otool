/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/08/10 15:12:56 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch32.h>

void		handler32(void *ptr, t_meta *meta)
{
	t_header32	*header;
	t_lc		*lc;
	uint32_t	count;

	if (!ptr)
		return ;
	int first_lc_load_dylib = 1;
	int first_lc_segment = 1;
	count = 0;
	header = (t_header32*)ptr;
	lc = ptr + sizeof(t_header32);
	meta->swap = (header->magic == MH_CIGAM) ? 1 : 0;
	//printf("meta->swap:%d\n", meta->swap);
	//sleep(1);
	//ft_printf("ptr%p, ncmds:%d, cputype:%d\n",ptr,  SWAP32(meta->swap, header->ncmds), SWAP32(meta->swap, header->cputype));
	while (count < SWAP32(meta->swap, header->ncmds))
	{
		if (CHK_VAL(ptr, ptr + meta->size, (void*)lc)
			|| CHK_VAL(ptr, ptr + meta->size, (void*)lc + SWAP32(meta->swap, lc->cmdsize)))
			corrupted("handler32");
		if (SWAP32(meta->swap, lc->cmd) == LC_SYMTAB)
		{
			P_DEBUG_VARGS("SELECT LC_SYMTAB => %d\n", SWAP32(meta->swap, lc->cmd));
			meta->symtab = lc;
		}
		else if (SWAP32(meta->swap, lc->cmd) == LC_LOAD_DYLIB && first_lc_load_dylib)
		{
			P_DEBUG_VARGS("SELECT 1er LC_LOAD_DYLIB => %d\n", SWAP32(meta->swap, lc->cmd));
			meta->dylib = lc;
			first_lc_load_dylib = 0;
		}
		else if (SWAP32(meta->swap, lc->cmd) == LC_SEGMENT && first_lc_segment)
		{
			P_DEBUG_VARGS("SELECT 1er LC_SEGMENT => %d\n", SWAP32(meta->swap, lc->cmd));
			meta->seg32 = lc;
			first_lc_segment = 0;
		}
		if (SWAP32(meta->swap, lc->cmd) == LC_SEGMENT)
		{
			struct segment_command *tmp;
			tmp = (struct segment_command*)lc;
			P_DEBUG_VARGS("nsects:0x%x\n", SWAP32(meta->swap, tmp->nsects));
		}
		P_DEBUG_VARGS("cmd:%d\n", SWAP32(meta->swap, lc->cmd));
		lc = (void*)lc + SWAP32(meta->swap, lc->cmdsize);
		++count;
	}
	handler_symtab32((void*)meta->symtab, ptr, meta);
}