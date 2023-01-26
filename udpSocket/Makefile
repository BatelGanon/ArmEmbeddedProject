client_udp: main.c client_udp.c
	gcc -Wall -Wextra -Wpedantic -std=c11 main.c client_udp.c -o client_udp

all: client_udp

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions client_udp

.PHONY: clean