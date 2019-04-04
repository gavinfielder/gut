/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 22:14:09 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/04 01:17:17 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSERT_H
# define ASSERT_H

# define AR_RESETVAL 0
# define AR_PASS 0
# define AR_FAIL 1
# define AR_UNSET -1

typedef struct	s_assertresult
{
	char	*expected;	//string representing expected value, set on fail
	char	*actual;	//string representing actual value, set on fail
	int		result;		//one of AR_[RESULT] values
	int		completed;	//0 if the assert was not completed, 1 if it was
	struct s_assertresult *next; //allows linked list function
}				t_assertresult;

//Assert-level reporting
void			ar_report(t_assertresult *rs);

//t_assertresult management functions
t_assertresult	*new_assertresult();
void			reset_assertresult(t_assertresult *rs);
void			del_assertresult_lst(t_assertresult **rs);
int				get_list_size(t_assertresult *rs);

//Global test results management
t_assertresult	*get_results();
void			flush_results();

//Assertions
int	assert_str_eq(char *actual, char *expected);
int	assert_str_neq(char *actual, char *expected);

int	assert_int_eq(int actual, int expected);
int	assert_int_neq(int actual, int expected);
int	assert_int_gt(int actual, int than);
int	assert_int_gteq(int actual, int than);
int	assert_int_lt(int actual, int than);
int	assert_int_lteq(int actual, int than);

int	assert_uint_eq(unsigned int actual, unsigned int expected);
int	assert_uint_neq(unsigned int actual, unsigned int expected);
int	assert_uint_gt(unsigned int actual, unsigned int than);
int	assert_uint_gteq(unsigned int actual, unsigned int than);
int	assert_uint_lt(unsigned int actual, unsigned int than);
int	assert_uint_lteq(unsigned int actual, unsigned int than);

int	assert_long_eq(long actual, long expected);
int	assert_long_neq(long actual, long expected);
int	assert_long_gt(long actual, long than);
int	assert_long_gteq(long actual, long than);
int	assert_long_lt(long actual, long than);
int	assert_long_lteq(long actual, long than);

int	assert_ulong_eq(unsigned long actual, unsigned long expected);
int	assert_ulong_neq(unsigned long actual, unsigned long expected);
int	assert_ulong_gt(unsigned long actual, unsigned long than);
int	assert_ulong_gteq(unsigned long actual, unsigned long than);
int	assert_ulong_lt(unsigned long actual, unsigned long than);
int	assert_ulong_lteq(unsigned long actual, unsigned long than);

int	assert_char_eq(char actual, char expected);
int	assert_char_neq(char actual, char expected);
int	assert_char_gt(char actual, char than);
int	assert_char_gteq(char actual, char than);
int	assert_char_lt(char actual, char than);
int	assert_char_lteq(char actual, char than);

#endif
