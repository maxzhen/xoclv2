// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2019-2020 Xilinx, Inc. All rights reserved.
 *
 * Authors: Sonal.Santan@Xilinx.com
 */

#ifndef	_XMGMT_ALVEO_DRV_H_
#define	_XMGMT_ALVEO_DRV_H_

#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/pci.h>

#include "xocl-lib.h"

#define	XMGMT_MODULE_NAME	"xmgmt"
#define XMGMT_MAX_DEVICES	 24
#define XMGMT_DEFAULT            0x000e
#define XMGMT_DRIVER_VERSION    "4.0.0"

#define xmgmt_err(dev, fmt, args...)			\
	dev_err(dev, "dev %llx, %s: "fmt, (u64)dev, __func__, ##args)
#define xmgmt_warn(dev, fmt, args...)			\
	dev_warn(dev, "dev %llx, %s: "fmt, (u64)dev, __func__, ##args)
#define xmgmt_info(dev, fmt, args...)			\
	dev_info(dev, "dev %llx, %s: "fmt, (u64)dev, __func__, ##args)
#define xmgmt_dbg(dev, fmt, args...)			\
	dev_dbg(dev, "dev %llx, %s: "fmt, (u64)dev, __func__, ##args)

#define	XMGMT_DEV_ID(pdev)			\
	((pci_domain_nr(pdev->bus) << 16) |	\
	PCI_DEVID(pdev->bus->number, pdev->devfn))

struct xmgmt_drvinst {
	struct device	       *dev;
	u32			size;
	atomic_t		ref;
	bool			offline;
        /*
	 * The derived object placed inline in field "data"
	 * should be aligned at 8 byte boundary
	 */
        u64			data[1];
};

struct xmgmt_dev;

struct xmgmt_char {
	struct xmgmt_dev       *lro;
	struct cdev             chr_dev;
	struct device          *sys_device;
};

struct xmgmt_dev {
	/* the kernel pci device data structure provided by probe() */
	struct pci_dev         *pdev;
        int			dev_minor;
	int                     instance;
	struct xmgmt_char       user_char_dev;
        bool                    ready;
	struct platform_device *fmgr;
	struct xocl_dev_core    core;
	int                     part_count;
	struct xocl_region     *part[1];
};

void *xmgmt_drvinst_alloc(struct device *dev, u32 size);
void xmgmt_drvinst_free(void *data);
long xmgmt_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

#endif
