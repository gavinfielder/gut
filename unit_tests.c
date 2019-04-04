/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 21:15:57 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/04 14:38:46 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"
#include "test_main.h"

/* -----------------------------------------------------------------------------
** Add unit tests to this file
**
** A valid unit test is prototyped 
**
**    int   foo(void)
**
** Return 0 if pass, 1 if failure
**
** Asserts also return 0 if pass, 1 if failure.
** The general form of an assertion is assert_type_is(actual, expected).
** See assert.h for a list of provided assert functions.
**
** ---------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------
** unit tests that start with "nocrash_" will always pass 
**     (provided it doesn't crash)
** ---------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------
** A unit test is ENABLED if it has no whitespace preceding it
** A unit test is DISABLED if it has whitespace preceding it
**
** scripts are provided to enable and disable tests by prefix
** ---------------------------------------------------------------------------*/

//The following unit tests are examples. You may delete them if you wish.
int		sanity_check(void)
{
	int ret = assert_int_eq(2 + 2, 4);
	return ret;
}

int		obrien_should_fail(void)
{
	int ret = assert_int_eq(2 + 2, 5);
	return ret;
}

int		deliberate_buserror(void)
{
	char *str = "Hello, world!";
	str[3] = '7';
	return (0);
}

int		obrien_should_fail_multiple(void)
{
	int ret = (assert_int_eq(2 + 2, 5) |
			   assert_str_eq("2 + 2 is 5", "No, 2 + 2 is 4!") |
			   assert_int_gt(5, 2) |
			   assert_int_lteq(8, 5) |
			   assert_str_eq("Winston", "Citizen"));
	return ret;
}
