UNAME	:= $(shell uname -r)
KDIR	:= /lib/modules/$(UNAME)/build
PWD	:= $(shell pwd)

obj-m	+= sim_dev.o
simdev-m	:= sim_dev.o sim_dev.ko

all::	test_sim_dev
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	
#test_sim_dev: test_sim_dev.c
#	gcc -o $@ $<

clean::
	$(RM) test_sim_dev 
	$(RM) read_test
	$(RM) write_test
	clear

run::
	./read_test
	

msg::
	dmesg

read:
	gcc read_test.c -g -lrt -Wall -o read_test
	./read_test

write:
	gcc write_test.c -g -lrt -Wall -o write_test
	./write_test

# setup insmod sim_dev.ko mknod /dev/sim_dev c 567 0 chmod a+w /dev/sim_dev

