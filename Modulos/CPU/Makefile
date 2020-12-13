obj-m += cpu_201504002.o
all:
	$(MAKE) -C /lib/modules/`uname -r`/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/`uname -r`/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod cpu_201504002.ko
	sudo rmmod cpu_201504002.ko
	dmesg