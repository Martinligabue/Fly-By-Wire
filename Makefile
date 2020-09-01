prefix_modules=src/tests/modules/
prefix_strings=src/tests/strings/
prefix_errors=src/tests/errors/
prefix_process=src/tests/process/
prefix_signals=src/tests/signals/
prefix_comm=src/tests/communication/
prefix_sockcc=src/tests/sockets_cc/
prefix_sockes=src/tests/sockets_es/
bindir=bin/

all: run_mod

clean:
	@ rm -r *.o run ciao.txt bin/

# Modules
run_mod: install
	@ ./$(bindir)run
install: clean_mod rev pal mod 
	@ clang mod.o pal.o rev.o -o run
	@ mv run $(bindir)/
mod: pal 
	@ echo "Start compile mod"
	@ clang -c $(prefix_modules)mod.c
	@ echo "Done compile mod"
pal: rev
	@ echo "Start compile pal"
	@ clang -c $(prefix_modules)pal.c
	@ echo "Done compile pal"
rev:
	@ echo "Start compile rev"
	@ clang -c $(prefix_modules)rev.c
	@ echo "Done compile rev"
clean_mod:
	@ echo "Cleaning the garbage"
	@ rm -f mod.o pal.o rev.o $(bindir)run

# Strings
run_str: compile_strings
	@ ./run
compile_strings: strings
	@ clang strings.o -o run
strings:
	@ clang -c $(prefix_strings)strings.c
clean_strings:
	@ rm strings.o run

errors:
	@ clang -c $(prefix_errors)error.c
	@ clang error.o -o run
	@ ./run

process:
	@ clang -c $(prefix_process)process.c
	@ clang process.o -o run
	@ ./run

summers:
	@ clang -c $(prefix_process)summers.c
	@ clang summers.o -o run
	@ ./run 

file_writer:
	@ clang -c $(prefix_process)file_writer.c
	@ clang file_writer.o -o run
	@ ./run ciao.txt

signals:
	@ clang -c $(prefix_signals)signals.c
	@ clang signals.o -o run
	@ ./run

toggle:
	@ clang -c $(prefix_signals)toggle.c
	@ clang toggle.o -o run
	@ ./run

pipe:
	@ clang -c $(prefix_comm)pipe.c
	@ clang pipe.o -o run
	@ ./run

rd_wr: read write
	@ ./reader & ./writer & ./writer

read:
	@ clang -c $(prefix_comm)reader.c
	@ clang reader.o -o reader

write:
	@ clang -c $(prefix_comm)writer.c
	@ clang writer.o -o writer

ch_ck: chef cook
	@ ./chef &
	@ ./cook 
	@ ./cook 
	@ ./cook 
	@ ./cook 

cook:
	@ clang -c $(prefix_sockcc)cook.c
	@ clang cook.o -o cook

chef:
	@ clang -c $(prefix_sockcc)chef.c
	@ clang chef.o -o chef

echo_c_s: eserver eclient


eserver:
	@ clang -c $(prefix_sockes)echoserver.c
	@ clang echoserver.o -o server

eclient:
	@ clang -c $(prefix_sockes)echoclient.c
	@ clang echoclient.o -o client