#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

int first = 0;
int second = 0;
char operation = '*';

static int calc_proc_show(struct seq_file *m, void *v)
{
	int result;
	switch(operation) {
	case '+':
		result = first + second;
		break;
	case '-':
		result = first - second;
		break;
	case '*':
		result = first * second;
		break;
	case '/':
		if(second != 0)
			result = first / second;
		else {
			seq_printf(m, "Division by zero\n");
			return 0;
		}
		break;
	default:
		seq_printf(m, "Incorrect operation\n");
		return 0;
	}
	seq_printf(m, "%d %c %d = %d\n", first, operation, second, result);
	return 0;
}

int first_write(struct file *file, const char *buf, int count, void *data)
{
	int i;
	for(i = 0, first = 0; i < count - 1; i++)
		first = first * 10 + buf[i] - '0';
	return count;
}

int second_write(struct file *file, const char *buf, int count, void *data)
{
	int i;
	for(i = 0, second = 0; i < count - 1; i++)
		second = second * 10 + buf[i] - '0';
	return count;
}

int operation_write(struct file *file, const char *buf, int count, void *data)
{
	operation = buf[0];
	return count;
}

static int result_open(struct inode *inode, struct file *file)
{
	return single_open(file, calc_proc_show, NULL);
}

static const struct file_operations first_fops = {
	.owner = THIS_MODULE,
	.write = first_write,
};

static const struct file_operations second_fops = {
	.owner = THIS_MODULE,
	.write = second_write,
};

static const struct file_operations operator_fops = {
	.owner = THIS_MODULE,
	.write = operation_write,
};

static const struct file_operations result_fops = {
	.owner = THIS_MODULE,
	.open = result_open,
	.read = seq_read,
};

static int __init calc_proc_init(void) {
	proc_create("calc_first", 0666, NULL, &first_fops);
	proc_create("calc_second", 0666, NULL, &second_fops);
	proc_create("calc_operator", 0666, NULL, &operator_fops);
	proc_create("calc_result", 0, NULL, &result_fops);
	return 0;
}

static void __exit calc_proc_exit(void) {
	remove_proc_entry("calc_first", NULL);
	remove_proc_entry("calc_second", NULL);
	remove_proc_entry("calc_operator", NULL);
	remove_proc_entry("calc_result", NULL);
}

MODULE_LICENSE("GPL");
module_init (calc_proc_init);
module_exit (calc_proc_exit);
