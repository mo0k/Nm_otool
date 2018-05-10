/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/31 14:59:46 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch64.h>

void		handler64(void *ptr, t_meta *meta)
{
	t_header64	*header;
	t_lc		*lc;
	uint32_t	count;

	if (!ptr)
		return ;
	int first_lc_load_dylib = 1;
	int first_lc_segment = 1;
	count = 0;
	header = (t_header64*)ptr;
	if (CHK_VAL(ptr, ptr + meta->size, (void*)header))
		corrupted("handler64 1");
	lc = ptr + sizeof(t_header64);
	meta->swap = (header->magic == MH_CIGAM_64) ? 1 : 0;
	while (count < SWAP32(meta->swap, header->ncmds))
	{
		if (CHK_VAL(ptr, ptr + meta->size, (void*)lc)
			|| CHK_VAL(ptr, ptr + meta->size, (void*)lc + SWAP32(meta->swap, lc->cmdsize)))
			corrupted("handler64 2");
		if (lc->cmd == LC_SYMTAB)
			meta->symtab = lc;
		else if (lc->cmd == LC_LOAD_DYLIB && first_lc_load_dylib)
		{
			meta->dylib = lc;
			first_lc_load_dylib = 0;
		}
		else if (lc->cmd == LC_SEGMENT_64 && first_lc_segment)
		{
			meta->seg64 = lc;
			first_lc_segment = 0;
		}
		lc = (void*)lc + SWAP32(meta->swap, lc->cmdsize);
		++count;
	}
	handler_symtab64((void*)meta->symtab, ptr, meta);
}