#
# Makefile for the Linux minix filesystem routines.
# make minix fs as kernel module
obj-m += mem_drv.o
mem_drv-objs := mem_kernel.o 

KERNELDIR:=/lib/modules/4.18.0+/build/

default:
	make -C $(KERNELDIR) M=$(PWD) modules
	rm -rf *.o *.mod.c *.symvers *.order

clean:
	rm -rf *.o *.mod.c *.ko *.symvers *.order
