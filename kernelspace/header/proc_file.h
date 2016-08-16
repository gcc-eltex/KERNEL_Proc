#ifndef _PROC_HEADER_PROCFILE_H
#define _PROC_HEADER_PROCFILE_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define NAME_PROC_FILE "my_proc_file"
#define MAX_LEN_MSG	64

static struct proc_dir_entry	*pde;
static struct file_operations	fops;

int init_module(void);
void cleanup_module(void);

static ssize_t read_proc(struct file *, char __user *, size_t, loff_t *);
static ssize_t write_proc(struct file *, const char __user *, size_t, 
	loff_t *);

static struct file_operations	fops = {
	.read	= read_proc,
	.write	= write_proc
};

#endif	/* _PROC_HEADER_PROCFILE_H */