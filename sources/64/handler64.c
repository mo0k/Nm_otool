/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 14:45:45 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <handler.h>

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
	header = (struct mach_header_64*)ptr;
	lc = ptr + sizeof(struct mach_header_64);
	while (count < header->ncmds)
	{
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
		lc = (void*)lc + lc->cmdsize;
		++count;
	}
	handler_systab((void*)meta->symtab, ptr, meta);
}