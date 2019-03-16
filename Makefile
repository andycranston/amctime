amctime: amctime.c
	gcc -o amctime amctime.c

userinstall:
	cp -p amctime     $(HOME)/bin/amctime
	chmod u=rwx,go=rx $(HOME)/bin/amctime

rootinstall:
	cp -p amctime     /usr/local/bin/amctime
	chmod u=rwx,go=rx /usr/local/bin/amctime
