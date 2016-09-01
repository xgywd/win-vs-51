#include <reg51.h>
#define MAX_TASKS 2          //任务槽个数.必须和实际任务数一至   
#define MAX_TASK_DEP 12      //最大栈深.最低不得少于2个,保守值为12.

unsigned char idata task_stack[MAX_TASKS][MAX_TASK_DEP];  //任务堆栈.

unsigned char task_id;        //当前活动任务号   //任务切换函数(任务调度器)

void task_switch()
{
	task_sp[task_id] = SP;
	if(++task_id == MAX_TASKS)
	task_id = 0; 
	SP = task_sp[task_id];
}
//任务装入函数.将指定的函数(参数1)装入指定(参数2)的任务槽中.如果该槽中原来就有任务,则原任务丢失,但系统本身不会发生错误.
void task_load(unsigned int fn, unsigned char tid)
{
	task_sp[tid] = task_stack[tid] + 1;
	task_stack[tid][0] = (unsigned int)fn & 0xff;
	task_stack[tid][1] = (unsigned int)fn>>8; 
}
//从指定的任务开始运行任务调度.调用该宏后,将永不返回.

#define os_start(tid) {task_id = tid,SP = task_sp[tid]; return;} 

  /*======================以下为测试代码======================*/

void task1() 
{        
	static unsigned char i;
	          
	while(1)
	{
		i++; 
		task_switch();      //编译后在这里打上断点
	}
}
void task2()
{
	static unsigned char j;
	
	while(1)
	{
		j+=2;
		task_switch();      //编译后在这里打上断点
	} 
} 
void main()
{
	//这里装载了两个任务,因此在定义MAX_TASKS时也必须定义为2          
	task_load(task1, 0);       //将task1函数装入0号槽           
	task_load(task2, 1);       //将task2函数装入1号槽        
	os_start(0);
}












