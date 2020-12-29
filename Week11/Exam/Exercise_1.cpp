#include "Exercise_1.h"

void X::inputProgram(string s) {
    // ÿ�е�����������̱�ţ��������ȼ������̿�ʼʱ�䣬һ�������ý�����Ҫִ�������ʱ��Ƭ����
            // [PID ���ȼ� ��ʼʱ�� ʱ��Ƭ1 ʱ��Ƭ2 ��]��
    s = s.substr(2, s.length() - 3);
    stringstream ss(s);
    int pid, pri;
    // ����ʱ������Ϊ���������͡�
    long int start;
    ss >> pid >> pri >> start;
    program p(pid, pri, start);
    long int timespan;
    while (ss >> timespan) 
        p.timespans.push(timespan);
    pp.enQueue(p);
}

/// <summary>
/// ִ����һʱ��Ƭ
/// </summary>
/// <returns>ִ����ɵĳ�����ţ����򷵻�0</returns>
int X::oexecute() {

    // û����� �ȴ��к�δ��ʼ��

    // ��ǰ����Piִ���굱ǰʱ��Ƭ��������ʱ��Ƭ�в��ܱ���ϣ������ǻ��߼���ִ�б����̣�����ִ��һ����ռ�Ľ��̣��������ѿ�ʼ�Ľ�������ѡ��һ������������ȼ��Ľ��̽���ִ�У�
    //Piÿִ���굱ǰʱ��Ƭ�������ȼ��½�1�������ȴ��еĽ������ȼ�����1��
    //�����в���������ͬʱ��ʼ�Ľ��̡�
    program* next_executing;
    program tp = pp.deQueue();
    if (executing.pid == 0) { // �޽��̣�������һ��
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
        tp.pri - executing.pri >= 2 || // ��Pi����ʱ��������ڱ�Pi���ȼ��� 2 �Ľ��̣�������ռִ�С�
        executing.timespans.size() == 1         // ִ�м�������
        ) && tp.start >= clock) {
        next_executing = &tp;
    }
    else { 
        next_executing = &executing; 
        tp.pri--;                           // ����
        pp.enQueue(tp);
    }

    //��ʽִ��
    if (!executing.timespans.empty()) {
        clock += executing.timespans.front();
        executing.timespans.pop();
        executing.pri--;
        pp.plus();
    }

    //�������ʱ��Ƭ���ƻ�
    if (next_executing->pid != executing.pid && !executing.timespans.empty())
        pp.enQueue(executing);
    else if (executing.timespans.empty())
        return executing.pid;


    return 0;
}

void X::outputQueue() {

    // ���������ɵĽ���ʱ�����У���ʽ���£�P1 P2 P3 ��
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

    //while (/* �˿Ͷ��зǿ� */) {  //Ϊ����ʱ���ṩ����
    ////ȡ���׹˿�
    //    if (/* ����ʱ��>��ǰʱ�� */)
    //        //ֱ�ӽ�ʱ�Ӳ����¼�������ʱ��
    //    else
    //        //�ռ��ù˿͵ĵȴ�ʱ��
    //    //���ɷ���ʱ��
    //    //��ʱ�Ӳ���������ɵ�ʱ��
    //}
    //
}