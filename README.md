# amctime

UNIX / Linux filter to display files which have been recently accessed, modified or chmod'ed

Handy to see which files got looked at after an action was take - for example starting a service.

## Compiling

Use the Makefile as follows:

```
$ make
$ make userinstall
$
```

The `make` compiles to the current directory and the `make userinstall`
copied the compiled executable `amctime` to the `$HOME/bin` directory.

## Basic usage

The `amctime` command reads file names from standard input one file
name per line.  If the file has been accessed or modified or had the
file mode changed with the `chmod` command in the last 60 seconds the
file name is displayed on standard output prefixed with an indication
of access, modification or chmod'ing.  An example makes this clearer:

```
$ cd /var/tmp
$ mkdir foo
$ cd foo
$ touch bar
$ ls | amctime
[amc] bar
$
```

By default a file that has been accessed, modificed or chmod'ed in the last
60 seconds is displayed.  A different time interval can be specified on the command line in seconds.  For example:

```
$ touch bar
$ sleep 10
$ ls | amctime 10
$ ls | amctime 30
[amc] bar
$
```



