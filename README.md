# amctime

UNIX / Linux filter to display files which have been recently accessed,
modified or chmod'ed.

Handy to see which files got looked at after an action was take - for
example starting a service.

## Compiling

Use the Makefile as follows:

```
$ make
$ make userinstall
```

The `make` compiles to the current directory and the `make userinstall`
copied the compiled executable `amctime` to the `$HOME/bin` directory.

## Usage

The `amctime` command reads file names from standard input one file name
per line.  If the file has been accessed or modified or had the file mode
changed with the `chmod` command in the last 60 seconds the file name
is displayed on standard output prefixed with an indication of access,
modification or chmod'ing.  An example makes this clearer:

```
$ cd /var/tmp
$ mkdir foo
$ cd foo
$ touch bar
$ ls | amctime
[amc] bar
```

By default a file that has been accessed, modified or chmod'ed in the
last 60 seconds is displayed.  A different time interval can be specified
on the command line in seconds.  For example:

```
$ touch bar
$ sleep 10
$ ls | amctime 10
$ ls | amctime 30
[amc] bar
```

The above examples use the `ls` command to generate the file names
which are then fed to the `amctime` command via a pipe.  The `find`
command can also be used.  For example while logged in as the `root` user:

```
# find / -type f -print | /home/andyc/bin/amctime
```

generates a lot of output but the results may surprise you.  Note that
because the root user is running this command the full path name of the
`amctime` command needed to be entered.

As a more practical example suppose you want to see which files are
accessed by a user when they login.  Ask the user (in this example user
`andyc`) to login and then type:

```
# find /home/andyc -type f -print | /home/andyc/bin/amctime
```

The output might look like:

```
[a--] /home/andyc/.bash_profile
[a--] /home/andyc/.profile
[a--] /home/andyc/bin/amctime
[a--] /home/andyc/.bash_history
```

Note how the `/home/andyc/bin/amctime` file appears in the output.
This is because the command itself was accessed.

## A note on access times

Most modern UNIX / Linux systems generally do not maintain file access
times accurately.  The main reason for this is performance.  If the system
does maintain access times strictly then just reading the content of a
file will cause a write to the file system as the access time for that
file needs to be written to the inode for the file.

Access times are generally only updated when a file is created or
modified.  The exact way your system will update access times will depend
on the kernel and certain options on the various file systems.

If you want accurate file access times to be maintained on your system
look into the `strictatime` file system mount option.

So if the `amctime` does not appear to give reliable results when
files are accessed it will be down to the kernel and the filesystem
mount options.

Generally I enable `strictatime` on my development systems but set a
more performance friendly `noatime` or `relatime` on everything else.
Your milage will most definitely vary!

----------------

End of file
