#include <linux/mm.h>
//#include <linux/sched.h>
#include <linux/module.h>
#include <asm/pgtable.h>
#include <asm/pgalloc.h>

static int pid = 1;
module_param(pid, int, 0644);

static unsigned long address = 0;
module_param(address, long, 0644);

static pte_t* virt_to_phy(struct task_struct *task, unsigned long address)
{
	pgd_t* pgd;
	p4d_t *p4d;
	pud_t* pud;
	pmd_t* pmd;
	pte_t* pte;
	
	struct mm_struct *mm = task->mm;

	pgd = pgd_offset(mm, address);
	if(pgd_none(*pgd) || pgd_bad(*pgd))
		return NULL;
	
	p4d = p4d_offset(pgd, address);
	if (p4d_none(*p4d)) {
		return NULL;
	}
	
	pud = pud_offset(p4d, address);
	if(pud_none(*pud) || pud_bad(*pud))
		return NULL;

	pmd = pmd_offset(pud, address);
	if(pmd_none(*pmd) || pmd_bad(*pmd))
		return NULL;

	pte = pte_offset_kernel(pmd, address);
	if(pte_none(*pte))
		return NULL;

	return pte;
}

static int mem_dev_init(void)
{
	struct task_struct  *task;
	pte_t* pte;
	struct page* page;
	
	task = pid_task(find_pid_ns(pid, &init_pid_ns), PIDTYPE_PID);
	if (task == NULL)
    {
		printk(KERN_INFO"Can't find the task %d .\n", pid);
		return -1;
    }
	
	if (!find_vma(task->mm, address))
	{
		printk(KERN_INFO"virt_addr 0x%lx not available.\n", address);
		return -1;
	}
	
	if(!(pte = virt_to_phy(task, address)))
	{
		printk(KERN_INFO"Can't find the task %d .\n", pid);
		return -1;
	}

	page = pte_page(*pte);
	address = page_address(page);
	
	strcpy(address, (char *)"MMU TEST DEMO!!!!!!!!!!!");

	return 0;
}

static void mem_dev_exit(void)
{
	printk("memory test exit\n");
}

module_init(mem_dev_init);
module_exit(mem_dev_exit);
MODULE_LICENSE("GPL");
