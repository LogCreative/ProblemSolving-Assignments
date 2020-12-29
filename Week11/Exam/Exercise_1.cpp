#include "Exercise_1.h"

void X::inputProgram(string s) {
    // 每行的输入包括进程编号，进程优先级，进程开始时间，一个或多个该进程需要执行任务的时间片长度
            // [PID 优先级 开始时间 时间片1 时间片2 …]，
    s = s.substr(2, s.length() - 3);
    stringstream ss(s);
    int pid, pri;
    // 其中时间类型为（长）整型。
    long int start;
    ss >> pid >> pri >> start;
    program p(pid, pri, start);
    long int timespan;
    while (ss >> timespan) 
        p.timespans.push(timespan);
    pp.enQueue(p);
}

/// <summary>
/// 执行下一时间片
/// </summary>
/// <returns>执行完成的程序代号，无则返回0</returns>
int X::oexecute() {

    // 没讲清楚 等待中和未开始！

    // 当前进程Pi执行完当前时间片（进程在时间片中不能被打断），我们或者继续执行本进程，或者执行一个抢占的进程；从所有已开始的进程中挑选出一个具有最高优先级的进程进行执行；
    //Pi每执行完当前时间片，其优先级下降1，其它等待中的进程优先级上升1。
    //输入中不存在两个同时开始的进程。
    program* next_executing;
    program tp = pp.deQueue();
    if (executing.pid == 0) { // 无进程，调到下一个
        executing = tp;
        clock = executing.start + executing.timespans.front();
        executing.timespans.pop();
        executing.pri--;
        pp.plus();
        if (executing.timespans.empty()) {
            int tmp = executing.pid;
            executing = program();
            return tmp;
        }
        else return 0;
    }

    if ((
        tp.pri - executing.pri >= 2 || // 当Pi运行时，如果存在比Pi优先级高 2 的进程，可以抢占执行。
        executing.timespans.size() == 1         // 执行即将结束
        ) && tp.start >= clock) {
        next_executing = &tp;
    }
    else { 
        next_executing = &executing; 
        tp.pri--;                           // 补偿
        pp.enQueue(tp);
    }

    //正式执行
    if (!executing.timespans.empty()) {
        clock += executing.timespans.front();
        executing.timespans.pop();
        executing.pri--;
        pp.plus();
    }

    //如果还有时间片，推回
    if (next_executing->pid != executing.pid && !executing.timespans.empty())
        pp.enQueue(executing);
    else if (executing.timespans.empty())
        return executing.pid;


    return 0;
}

void X::outputQueue() {

    // 输出进程完成的结束时间序列，格式如下：P1 P2 P3 …
    while (!pp.isEmpty()) {
        int res = oexecute();
        if (res != 0) { cout << 'P' << res << ' ';}
    }

    //do {
    //    
    //  /*  program p = pp.deQueue();
    //    cout << p.pid << ' ' << p.pri << ' ' << p.start << endl;*/
    //} while (!pp.isEmpty());
    cout << endl;

    //while (/* 顾客队列非空 */) {  //为到达时间提供服务
    ////取队首顾客
    //    if (/* 到达时间>当前时间 */)
    //        //直接将时钟拨到事件发生的时间
    //    else
    //        //收集该顾客的等待时间
    //    //生成服务时间
    //    //将时钟拨到服务完成的时间
    //}
    //
}