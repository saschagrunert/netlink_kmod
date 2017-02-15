TARGET = netlink
SRC_DIR = src

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

obj-m := ${TARGET}.o
${TARGET}-objs := ${SRC_DIR}/netlink.o ${SRC_DIR}/main.o

ccflags-y := -I$(PWD)/include -Wall -Werror
asflags-y :=
ldflags-y :=

all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean

insmod:
	sudo insmod ${TARGET}.ko

rmmod:
	sudo rmmod ${TARGET}.ko

test: all insmod rmmod
	dmesg -H | tail -10
