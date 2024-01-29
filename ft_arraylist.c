/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 00:38:09 by maurodri          #+#    #+#             */
/*   Updated: 2024/01/29 02:23:06 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEFAULT_ARRAYLIST_SIZE 20
#include "ft_arraylist.h"
#include "ft_arraylist_internal.h"

void	*ft_free_retnull(void *to_free)
{
	free(to_free);
	return (NULL);
}

void	*ft_realloc(void *block, size_t old_size, size_t new_size)
{
	unsigned char	*old_block;
	unsigned char	*new_block;
	size_t			i;
	size_t			copy_size;
	unsigned char	temp;

	old_block = (unsigned char *) block;
	if (new_size == 0)
		new_size = 1;
	new_block = malloc(new_size);
	if (!new_block)
		return (NULL);
	if (!block)
		return (new_block);
	if (new_size > old_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	i = 0;
	while (i < copy_size)
	{
		temp = old_block[i];
		new_block[i] = temp;
		i++;
	}
	free(block);
	return ((void *) new_block);
}

/*
	Constructor function for t_arraylist.
	Receives as argument a function for
	destroying elements of t_arraylist
	that wiil be used when
	destroying t_arraylist 
 */
t_arraylist ft_arraylist_new(void (*destroy_element)(void *element))
{
	t_arraylist new_arraylist;

	if (!destroy_element)
		return (NULL);
	new_arraylist = malloc(sizeof(struct s_arraylist));
	if (!new_arraylist)
		return (NULL);
	new_arraylist->arr = malloc(DEFAULT_ARRAYLIST_SIZE * sizeof(void *));
	if (!new_arraylist->arr)
		return ft_free_retnull(new_arraylist);
	new_arraylist->capacity = DEFAULT_ARRAYLIST_SIZE;
	new_arraylist->size = 0;
	new_arraylist->destroy_element = destroy_element;
	return (new_arraylist);
}

/*
	Destructor function for t_arraylist.
  	Will free all elements of alst
	using destroy_element parameter
	passed on ft_arraylist_new and then
	call free in itself.
	It is not recomended to call free
	directly on alst prefer using this function instead.
 */
void	*ft_arraylist_destroy(t_arraylist alst)
{
	size_t	i;

	i = 0;
	while (i < alst->size)
	{
		alst->destroy_element(alst->arr[i]);
		i++;
	}
	free(alst->arr);
	free(alst);
	return (NULL);
}

size_t	ft_arraylist_len(t_arraylist alst)
{
	return (alst->size);
}

/*
	Returns the element of alst with index at
	if at is within the bounds.
	If at is out of bounds returns NULL.
	Do not call free on returned value,
	instead treat it as a borrowed value since
	alst will keep its ownership.
	If you need ownership of value make a clone.
*/
void	*ft_arraylist_get(t_arraylist alst, size_t at)
{
	if (at >= alst->size)
		return (NULL);
	return (alst->arr[at]);
}

/*
	Adds element to the end of alst.
	If there are no errors returns alst with element added.
	If reallocation is needed and fails alst is destroyed and
	NULL is returned.
	To protect against errors you should always reassign
	the old alst value with the returned value and check for NULL.
	Transfers the ownership of element to alst.
	Do not call free on element since alst will consider
	being the owner of element after element was added.
*/  
t_arraylist	ft_arraylist_add(t_arraylist alst, void *element)
{
	void	**temp;
	size_t	i;

	if(alst->capacity == alst->size)
	{
		temp = (void *) ft_realloc(
			alst->arr,
			alst->capacity * sizeof(void *),
			2 * alst->capacity * sizeof(void *));
		if (!temp)
			return (ft_arraylist_destroy(alst));
		alst->arr = temp;
	}
	alst->arr[alst->size] = element;
	alst->size++;
	return (alst);
}

/*
	Adds element to alst at index at.
	If at is bigger than size the element is just
	added after last element.
	Consider that adding to front of alst is expensive
	since elements have to be shifted to open space for new element.
	If reallocation is needed and fails alst is destroyed and
	NULL is returned.
  	To protect against errors you should always reassign
	the old alst value with the returned value and check for NULL.
  	Transfers the ownership of element to alst.
	Do not call free on element since alst will consider
	being the owner of element after element was added.
 */  
t_arraylist	ft_arraylist_addat(t_arraylist alst, void *element, size_t at)
{
	void	*last;
	size_t	i;
	
	if (at >= alst->size)
		return (ft_arraylist_add(alst, element));
	last = ft_arraylist_get(alst, alst->size - 1);
	i = alst->size - 1;
	while (i > at)
	{
		alst->arr[i] = alst->arr[i - 1];
		i--;
	}
	alst->arr[at] = element;
	return (ft_arraylist_add(alst, last));
}

void	ft_arraylist_replace(t_arraylist alst, void *element, size_t at)
{
	if (at >= alst->size)
		return ;
	alst->destroy_element(alst->arr[at]);
	alst->arr[at] = element;
}

/*
  Removes the last element of alst and return its value.
  If alst is empty returns NULL.
  The ownership of returned value is considered to be transfered
  to caller that will be responsible for destroying value returned.
  Use ft_arraylist_peek if you just want to look at last value
  without removing nor becoming owner of returned value.
 */
void 	*ft_arraylist_pop(t_arraylist alst)
{	
	if (alst->size == 0)
		return (NULL);
	return (ft_arraylist_get(alst, alst->size-- - 1));
}

/*
  Look at last element of alst without removing it.
  If alst is empty returns NULL.
  The alst will consider still being owner of returned
  value and thus you should not destroy it directly.
*/
void	*ft_arraylist_peek(t_arraylist alst)
{
	if (alst->size == 0)
		return (NULL);
	return (ft_arraylist_get(alst, alst->size - 1));
}

/*
	Calls fun with each element of alst.
	The fun should not be null.
	Not intended for mutation,
	use ft_arraylist_transformn instead.
*/
void	ft_arraylist_foreach(t_arraylist alst, void (*fun) (void *))
{
	size_t	i;

	i = 0;
	while (i < alst->size)
		fun(alst->arr[i++]);
}

/*
  	Call fun with each element of alst frees the old element
	and replaces with the return value of fun.
	The fun should not be null.
	If fun return type is the same as
	the type already on alst you may pass NULL for
	update_destroy_element, otherwise you will need
	to pass a valid update_destroy_element for the
	new type.
	For error control reasons returns the number
	of times fun returns NULL, and thus
	will return 0 if fun has never returned NULL. 
 */
int	ft_arraylist_transform(
	t_arraylist alst,
	void *(*fun)(void *),
	void (*update_destroy_element)(void *element))
{
	size_t	i;
	int		num_nulls_returned;
	void	*temp;

	num_nulls_returned = 0;
	i = 0;
	while (i < alst->size)
	{
		temp = fun(alst->arr[i]);
		if(temp == NULL)
			num_nulls_returned++;
		alst->destroy_element(alst->arr[i]);
		alst->arr[i] = temp;
		i++;
	}
	if (update_destroy_element != NULL)
		alst->destroy_element = update_destroy_element;
	return (num_nulls_returned);
}
