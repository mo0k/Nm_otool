/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ref.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 23:40:56 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/02 23:41:37 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

char	*get_ref(int row, int column)
{
	static char	*symbol_ref3[NOSECT_ROWMAX][NOSECT_COLMAX] =
	{
		{"undefined", "u"},
		{"absolute", "a"},
		{"indirect", "i"},
		{"common", "c"},
		{"?", "-"}
	};

	return (symbol_ref3[row][column]);
}
