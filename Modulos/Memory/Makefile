obj-m += memo_201504002.o
all:
	$(MAKE) -C /lib/modules/`uname -r`/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/`uname -r`/build M=$(PWD) clean
test:
	-sudo rmmod memo_201504002
	sudo dmesg -C
	sudo insmod memo_201504002.ko
	dmesg