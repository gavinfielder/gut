# GüT
## C unit testing framework and test runner

This is a unit testing framework for C. It adds to your makefile a target `gut`, which will make a unit test runner containing all the unit tests you write into gut/unit\_tests.c

## Installation
In your root project folder:
```bash
git clone https://github.com/gavinfielder/gut gut
sh gut/install.sh
```
This depends on the following assumptions:
 - You have put your source files into a "SRC" variable, and they do not include a main.
 - You have put your -I includes into an "INC" variable, and it includes the -I flag
 - You have put your -L/-l library compile flags into a "LIB" variable and it includes -L/-l

If these assumptions are incorrect, you'll have to tweak the makefile after installation to set up properly. Instructions are provided in the Makefile.  

## Usage

In your root project folder (not in gut/ )
```bash
make gut
./test
```
You can add your own unit tests to gut/unit\_tests.c. You do not need to anything except write the function and remake.

You can run specific tests by supplying arguments:
 - `./test prefix` runs all the enabled tests whose name starts with 'prefix'
 - `./test "search-pattern"` runs all the enabled tests whose name matches a wildcard-based ('\*') search
 - `./test 42 84` runs (enabled) test number 42 through test 84
 - `./test 42` runs enabled tests from 42 to the end of all the enabled tests
 - `./test` runs all the enabled tests

You can enable and disable tests with the provided scripts:

```bash
Simple prefix-based search:
 ./disable-test s                         # All the tests that start with 's' are disabled
 ./enable-test s_null_                    # All the tests that start with 's_null_' are enabled
 ./disable-test "" && ./enable-test s     # Disables all tests except tests that start with 's'

Wildcard search:
 ./disable-test "*zeropad"      # Disables all the tests that have 'zeropad' anywhere in the name
 ./enable-test "*null*prec"     # Enables all the tests that have a 'null' followed by a 'prec'
 ./enable-test "s_*prec"        # Enables all tests that start with 's_' and have a 'prec' in the name
```

# Credits

All code was written by me.
