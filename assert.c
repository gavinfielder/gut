/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 22:18:49 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/04 00:50:40 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "assert.h"

/*
** -----------------------------------------------------------------------------
**    Assert Reporting: Every assert will call this function before exiting
** -----------------------------------------------------------------------------
*/

void			ar_report(t_assertresult *rs)
{
	if (rs->result == AR_FAIL)
	{
		//do something maybe
	}
}

/*
** -----------------------------------------------------------------------------
**    t_assertresult management functions
** -----------------------------------------------------------------------------
*/
t_assertresult	*new_assertresult()
{
	t_assertresult	*rs = (t_assertresult *)malloc(sizeof(t_assertresult));
	rs->expected = NULL;
	rs->actual = NULL;
	rs->result = AR_RESETVAL;
	rs->completed = 0;
	rs->next = NULL;
	return (rs);
}

void			reset_assertresult(t_assertresult *rs)
{
	if (rs->expected) { free(rs->expected); rs->expected = NULL; }
	if (rs->actual) { free(rs->actual); rs->expected = NULL; }
	rs->expected = NULL;
	rs->actual = NULL;
	rs->result = AR_RESETVAL;
	rs->completed = 0;
}

void			del_assertresult_lst(t_assertresult **rs)
{
	t_assertresult *tmp;

	while (rs && *rs)
	{
		reset_assertresult(*rs);
		tmp = (*rs)->next;
		(*rs)->next = NULL;
		free(*rs);
		*rs = tmp;
	}
}

int				get_list_size(t_assertresult *rs)
{
	int		count = 0;
	while (rs)
	{
		count++;
		rs = rs->next;
	}
	return (count);
}

/*
** -----------------------------------------------------------------------------
**    Global test results management
** -----------------------------------------------------------------------------
*/

//File scope static to hold assert results of last test
static t_assertresult *r;

t_assertresult	*get_results()
{
	return (r);
}

void			flush_results()
{
	del_assertresult_lst(&r);
	r = NULL;
}

void			new_result_node()
{
	if (r == NULL)
		r = new_assertresult();
	else
	{
		t_assertresult *rs = r;
		r = new_assertresult();
		r->next = rs;
	}
}

/*
** -----------------------------------------------------------------------------
**    Dispatcher (WIP)
** -----------------------------------------------------------------------------
*/

/* 
 * Dispatch function (for future development)
 *    ex. assert("int eq", 5, 5)
 *
int				assert(char *spec, ...)
{
	(void)r;
	(void)spec;
	return 0;
}
*/

/*
** -----------------------------------------------------------------------------
**    Integers
** -----------------------------------------------------------------------------
*/

int	assert_int_eq(int actual, int expected) {
	new_result_node();
	if (actual == expected)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "%i", expected);
		asprintf(&(r->actual), "%i", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_int_neq(int actual, int expected) {
	new_result_node();
	if (actual != expected)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "NOT %i", expected);
		asprintf(&(r->actual), "%i", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_int_gt(int actual, int than) {
	new_result_node();
	if (actual > than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), ">%i", than);
		asprintf(&(r->actual), "%i", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_int_gteq(int actual, int than) {
	new_result_node();
	if (actual >= than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), ">=%i", than);
		asprintf(&(r->actual), "%i", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_int_lt(int actual, int than) {
	new_result_node();
	if (actual < than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "<%i", than);
		asprintf(&(r->actual), "%i", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_int_lteq(int actual, int than) {
	new_result_node();
	if (actual <= than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "<=%i", than);
		asprintf(&(r->actual), "%i", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

/*
** -----------------------------------------------------------------------------
**    Unsigned Integers
** -----------------------------------------------------------------------------
*/

int	assert_uint_eq(unsigned int actual, unsigned int expected) {
	new_result_node();
	if (actual == expected)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "%u", expected);
		asprintf(&(r->actual), "%u", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_uint_neq(unsigned int actual, unsigned int expected) {
	new_result_node();
	if (actual != expected)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "NOT %u", expected);
		asprintf(&(r->actual), "%u", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_uint_gt(unsigned int actual, unsigned int than) {
	new_result_node();
	if (actual > than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), ">%u", than);
		asprintf(&(r->actual), "%u", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_uint_gteq(unsigned int actual, unsigned int than) {
	new_result_node();
	if (actual >= than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), ">=%u", than);
		asprintf(&(r->actual), "%u", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_uint_lt(unsigned int actual, unsigned int than) {
	new_result_node();
	if (actual < than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "<%u", than);
		asprintf(&(r->actual), "%u", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_uint_lteq(unsigned int actual, unsigned int than) {
	new_result_node();
	if (actual <= than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "<=%u", than);
		asprintf(&(r->actual), "%u", actual); }
	r->completed = 1; ar_report(r); return (r->result); }


/*
** -----------------------------------------------------------------------------
**    Long
** -----------------------------------------------------------------------------
*/

int	assert_long_eq(long actual, long expected) {
	new_result_node();
	if (actual == expected)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "%li", expected);
		asprintf(&(r->actual), "%li", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_long_neq(long actual, long expected) {
	new_result_node();
	if (actual != expected)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "NOT %li", expected);
		asprintf(&(r->actual), "%li", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_long_gt(long actual, long than) {
	new_result_node();
	if (actual > than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), ">%li", than);
		asprintf(&(r->actual), "%li", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_long_gteq(long actual, long than) {
	new_result_node();
	if (actual >= than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), ">=%li", than);
		asprintf(&(r->actual), "%li", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_long_lt(long actual, long than) {
	new_result_node();
	if (actual < than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "<%li", than);
		asprintf(&(r->actual), "%li", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_long_lteq(long actual, long than) {
	new_result_node();
	if (actual <= than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "<=%li", than);
		asprintf(&(r->actual), "%li", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

/*
** -----------------------------------------------------------------------------
**    Unsigned Long
** -----------------------------------------------------------------------------
*/

int	assert_ulong_eq(unsigned long actual, unsigned long expected) {
	new_result_node();
	if (actual == expected)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "%lu", expected);
		asprintf(&(r->actual), "%lu", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_ulong_neq(unsigned long actual, unsigned long expected) {
	new_result_node();
	if (actual != expected)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "NOT %lu", expected);
		asprintf(&(r->actual), "%lu", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_ulong_gt(unsigned long actual, unsigned long than) {
	new_result_node();
	if (actual > than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), ">%lu", than);
		asprintf(&(r->actual), "%lu", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_ulong_gteq(unsigned long actual, unsigned long than) {
	new_result_node();
	if (actual >= than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), ">=%lu", than);
		asprintf(&(r->actual), "%lu", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_ulong_lt(unsigned long actual, unsigned long than) {
	new_result_node();
	if (actual < than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "<%lu", than);
		asprintf(&(r->actual), "%lu", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_ulong_lteq(unsigned long actual, unsigned long than) {
	new_result_node();
	if (actual <= than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "<=%lu", than);
		asprintf(&(r->actual), "%lu", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

/*
** -----------------------------------------------------------------------------
**    Chars
** -----------------------------------------------------------------------------
*/

int	assert_char_eq(char actual, char expected) {
	new_result_node();
	if (actual == expected)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "'%c'", expected);
		asprintf(&(r->actual), "'%c'", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_char_neq(char actual, char expected) {
	new_result_node();
	if (actual != expected)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "NOT '%c'", expected);
		asprintf(&(r->actual), "'%c'", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_char_gt(char actual, char than) {
	new_result_node();
	if (actual > than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), ">'%c'", than);
		asprintf(&(r->actual), "'%c'", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_char_gteq(char actual, char than) {
	new_result_node();
	if (actual >= than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), ">='%c'", than);
		asprintf(&(r->actual), "'%c'", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_char_lt(char actual, char than) {
	new_result_node();
	if (actual < than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "<'%c'", than);
		asprintf(&(r->actual), "'%c'", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_char_lteq(char actual, char than) {
	new_result_node();
	if (actual <= than)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "<='%c'", than);
		asprintf(&(r->actual), "'%c'", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

/*
** -----------------------------------------------------------------------------
**    Strings
** -----------------------------------------------------------------------------
*/

int	assert_str_eq(char *actual, char *expected) {
	new_result_node();
	if (strcmp(actual, expected) == 0)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "\"%s\"", expected);
		asprintf(&(r->actual), "\"%s\"", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

int	assert_str_neq(char *actual, char *expected) {
	new_result_node();
	if (strcmp(actual, expected) != 0)
		r->result = AR_PASS;
	else {
		r->result = AR_FAIL;
		asprintf(&(r->expected), "NOT \"%s\"", expected);
		asprintf(&(r->actual), "\"%s\"", actual); }
	r->completed = 1; ar_report(r); return (r->result); }

