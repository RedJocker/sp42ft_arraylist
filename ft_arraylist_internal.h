/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylist_internal.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:01:30 by maurodri          #+#    #+#             */
/*   Updated: 2024/01/27 18:49:33 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARRAYLIST_INTERNAL_H
# define FT_ARRAYLIST_INTERNAL_H

// move elsewhere
void	*ft_free_retnull(void *to_free);
void	*ft_realloc(void *block, size_t old_size, size_t new_size);
//

struct s_arraylist {
	void	**arr;
	size_t	size;
	size_t	capacity;
	void 	(*destroy_element)(void *element);
};

#endif
