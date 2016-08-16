KERNELDIR:=/usr/src/linux-headers-$(shell uname -r)
PWD := $(shell pwd)
ccflags-y := -std=gnu99
obj-m += proc_file.o

all:
	sudo $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install:
	sudo insmod ./proc_file.ko

delete:
	sudo rmmod proc_file

clean:
	rm -rf *.o *.ko *.order *.symvers *.mod.c .proc_file.* .tmp_versions

log:
	sudo vim /var/log/syslog

lclean:
	>/var/log/syslog

check:
	./../../checkpatch.pl --no-tree -f proc_file.c
