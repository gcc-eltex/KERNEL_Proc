#include "header/proc_file.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ivannikov Igor");

int init_module(void)
{
	pde = proc_create(NAME_PROC_FILE, S_IRWXU | S_IRWXG | S_IRWXO,
			  NULL, &fops);
	if (pde == NULL)
		goto err;
	printk("init_module: created the file in /proc\n");
	return 0;
err:
	printk("init_module: error creating file in /proc\n");
	return -1;
}

void cleanup_module(void)
{
	proc_remove(pde);
	printk("cleanup_module: deleted files from /proc\n");
}

/*
 * read_proc - производит копирование приветственного сообщения из kernel
 * space в user space при вызове read() в последнем.
 *
 * Возвращает 0 при успешном завершении, -1 при ошибке.
 */
ssize_t read_proc(struct file *filep, char *buffer, size_t len,
		  loff_t *offset)
{
	/*
	 * Укорачиваем длину требуемых данных, чтобы не выйти за границу
	 * сообщения.
	 */
	if (len > 13)
		len = 13;
	if (copy_to_user(buffer, "Hello, user!\0", len))
		goto err;
	return len;
err:
	printk("read_proc: error copying data to user space\n");
	return -1;
}

ssize_t write_proc(struct file *filep, const char *buffer, size_t len,
		   loff_t *offset)
{
	char send_msg[MAX_LEN_MSG];

	/*
	 * Укорачиваем длину требуемых данных, чтобы не выйти за границу
	 * буфера для сообщения.
	 */
	if (len > MAX_LEN_MSG)
		len = MAX_LEN_MSG;
	if (copy_from_user(send_msg, buffer, len))
		goto err;
	printk("write_proc: get from user space %s\n", send_msg);
	return len;
err:
	printk("read_proc: error copying data from user space\n");
	return -1;
}