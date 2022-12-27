//
// Created by lbb on 2022/12/27.
//
#include "TcpServer.h"

using namespace hv;


static unpack_setting_t jsonrpc_unpack_setting;

//TCP是流式协议，实际应用中请务必添加边界进行拆包。通过setUnpack（c接口即hio_set_unpack）设置拆包规则，支持固定包长、分隔符、头部长度字段三种常见的拆包方式，
//内部根据拆包规则处理粘包与分包，保证onMessage回调上来的是完整的一包数据，
//不想自定义协议和拆包组包的可直接使用现成的HTTP/WebSocket协议。
int main() {
    int port = 8999;
    TcpServer srv;
    int listenfd = srv.createsocket(port);
    if (listenfd < 0) {
        return -1;
    }
    srv.onConnection = [](const SocketChannelPtr & channel){
        std::string  peerAddr = channel->peeraddr();
        printf("accepting connection, ip : %s ...\n", peerAddr.c_str());
        if (channel->isConnected()) {
            printf("%s connected! connfd=%d\n", peerAddr.c_str(), channel->fd());
        } else {
            printf("%s disconnected! connfd=%d\n", peerAddr.c_str(), channel->fd());
        }
    };
    srv.onMessage = [](const SocketChannelPtr& channel, Buffer* buf) {
        // echo
//        channel->write（c接口即hio_write）是非阻塞的（事件循环异步编程里所有的一切都要求是非阻塞的），且多线程安全的。
//        发送大数据时应该做流控，通过onWriteComplete监听写完成事件，在可写时再发送下一帧数据。

        printf("rev data %s ...\n",     buf->data());
        channel->write(buf);
    };

    // 分隔符：@，  适用于文本协议，
    memset(&jsonrpc_unpack_setting, 0, sizeof(unpack_setting_t));
    jsonrpc_unpack_setting.mode = UNPACK_BY_DELIMITER;
    jsonrpc_unpack_setting.package_max_length = DEFAULT_PACKAGE_MAX_LENGTH;
    jsonrpc_unpack_setting.delimiter[0] = '@';
    jsonrpc_unpack_setting.delimiter_bytes = 1;
    srv.setUnpack(&jsonrpc_unpack_setting);


    // 固定首部， 适用于二进制协议，二进制协议建议加上自定义协议头，通过头部长度字段表明负载长度



    srv.setThreadNum(4);
    //srv.start() 并不会阻塞线程
    srv.start();
    printf("server listen on port %d, listenfd=%d ...\n", port, listenfd);
    // press Enter to stop
    while (getchar() != '\n');
    return  0;
}