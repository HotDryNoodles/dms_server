#include "header/client_thread.h"
#include "header/data.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <header/log_queue.h>
#include <iostream>
#include <header/data.h>
#include "header/server_exception.h"

#define _DEBUG

using std::cout;
using std::endl;

ClientThread::ClientThread(int conn_fd) : conn_fd(conn_fd)
{

}

ClientThread::~ClientThread()
{
    // close this thread
    pthread_exit(NULL);
}

/**************************************************
*作者：Liu Chaoyang
*日期：2017.06.26
*函数名：run
*功能：receive message from clients
*输入参数：none
*输出参数：none
*返回值：none
**************************************************/

void ClientThread::run()
{
    cout << "Client thread starts running..." << endl;
    int rlen;
    MatchedLogRec buf;
#ifdef _DEBUG
    int rcv_count = 0;      // count the number of received logs
#endif
    while (true)
    {
        rlen = recv(conn_fd, (MatchedLogRec*)&buf, sizeof(MatchedLogRec), 0);
        if (rlen < 0)
        {
#ifdef _DEBUG
            cout << "Receiving data failed!" << endl;
#endif
            throw ServerException("Receiving data failed!");
        }
        else if (rlen == 0)
        {
            cout << "OK:data receiving finished." << endl;
#ifdef _DEBUG
            cout << "Received: " << rcv_count << endl;
#endif
            delete this;
        }
        else
        {
#ifdef _DEBUG
            rcv_count++;           
            // print data received to console(just for test)
            cout << buf << endl;
#endif
            // insert data received into log queue
            g_log_queue << buf;
        }
    }
}
