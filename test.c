/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maurodri <maurodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:50:35 by maurodri          #+#    #+#             */
/*   Updated: 2024/01/29 02:30:14 by maurodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arraylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
char g_ch;

void assert_str_alst(char *actual_str)
{
	char	expect_str[20];

	snprintf(expect_str, 20, "str_%c", g_ch);
	assert(strcmp(expect_str, actual_str) == 0);
	g_ch++;
}

void test_add_string()
{
	t_arraylist	alst;
	char *str;
	printf("test_add_string: ");
	alst = ft_arraylist_new(free);

	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		str = malloc(20);
		snprintf(str, 20, "str_%c", ch);
		alst = ft_arraylist_add(alst, str);
		if (!alst)
		{
			printf("Failed increasing memory for adding");
			exit(1);
		}
	}
	assert(ft_arraylist_len(alst) == 26);
	g_ch = 'a';
	ft_arraylist_foreach(alst, (void (*) (void *)) assert_str_alst);
	g_ch = 'a';
	for (int i = 0; i < 26; i++)
	{
		assert_str_alst(ft_arraylist_get(alst, i));
	}
	ft_arraylist_destroy(alst);
	printf("[OK]\n");
}

void test_replace_string()
{
	t_arraylist	alst;
	char *str;
	printf("test_replace_string: ");
	alst = ft_arraylist_new(free);

	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		str = malloc(20);
		snprintf(str, 20, "str_%c", ch);
		alst = ft_arraylist_add(alst, str);
		if (!alst)
		{
			printf("Failed increasing memory for adding");
			exit(1);
		}
	}
	assert(ft_arraylist_len(alst) == 26);
	g_ch = 'a';
	str = malloc(20);
	snprintf(str, 20, "some string");
	ft_arraylist_replace(alst, str, 5);
	assert(strcmp(ft_arraylist_get(alst, 5), "some string") == 0);
	ft_arraylist_destroy(alst);
	printf("[OK]\n");
}

typedef struct s_test_struct
{
	char	*str;
	int		*num;
} 	t_test_struct;

void free_struct(t_test_struct *ts)
{
	free(ts->str);
	free(ts->num);
	free(ts);
}

void test_add_struct()
{
	t_test_struct	*ts;
	t_arraylist	alst;
	char *str;
	
	printf("test_add_struct: ");
	alst = ft_arraylist_new((void (*) (void *))free_struct);
	ts = malloc(sizeof(t_test_struct));
	ts->num = malloc(sizeof(int));
	*(ts->num) = 10;
	ts->str = strdup("HELLO");
	alst = ft_arraylist_add(alst, ts);
	if (!alst)
	{
		printf("Failed increasing memory for adding");
		exit(1);
	}
	assert(ft_arraylist_len(alst) == 1);
	assert((*((t_test_struct *) ft_arraylist_get(alst, 0))->num) == 10);
	assert(strcmp(
				  ((t_test_struct *) ft_arraylist_get(alst, 0))->str,
				  "HELLO")
		   == 0 );
	ft_arraylist_destroy(alst);
	printf("[OK]\n");
}

t_test_struct	*str_to_test_struct(char *str)
{
	t_test_struct	*ts;
	ts = malloc(sizeof(t_test_struct));
	ts->num = malloc(sizeof(int));
	*(ts->num) = (int) strlen(str);
	ts->str = strdup(str);
	return ts;
}

void	test_transform_string_to_struct()
{
	t_arraylist		alst;
	t_test_struct 	*ralst;
	char 			*str;
	printf("test_transform_string_to_struct: ");
	alst = ft_arraylist_new(free);

	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		str = malloc(20);
		snprintf(str, 20, "str_%c", ch);
		alst = ft_arraylist_add(alst, str);
		if (!alst)
		{
			printf("Failed increasing memory for adding");
			exit(1);
		}
	}
	assert(ft_arraylist_len(alst) == 26);
	ft_arraylist_transform(
						   alst,
						   (void *(*)(void *))str_to_test_struct,
						   (void (*) (void *))free_struct);
	g_ch = 'a';
	for (int i = 0; i < 26; i++)
	{
	  ralst = (t_test_struct *) ft_arraylist_get(alst, i);
	  assert(*(ralst->num) == 5);
	  assert_str_alst(ralst->str);
	}
	ft_arraylist_destroy(alst);
	printf("[OK]\n");
}

int	main(void)
{
	test_add_string();
	test_replace_string();
	test_add_struct();
	test_transform_string_to_struct();
}
