rmmod xclmgmt
modprobe fpga_mgr
modprobe fpga_region
insmod ./xmgmt-fmgr.ko
insmod ./xocl-lib.ko
insmod ./xmgmt.ko
