//
// Created by lbb on 2022/12/27.
//
#include "TcpServer.h"

using namespace hv;

#include "../protorpc.h"
#include "../router.h"
#include "../handler/handler.h"
#include "../handler/calc.h"
#include "../handler/login.h"

// valgrind --leak-check=full --show-leak-kinds=all
class ProtobufRAII {
public:
    ProtobufRAII() {
    }
    ~ProtobufRAII() {
        google::protobuf::ShutdownProtobufLibrary();
    }
};
static ProtobufRAII s_protobuf;

protorpc_router router[] = {
        {"add", calc_add},
        {"sub", calc_sub},
        {"mul", calc_mul},
        {"div", calc_div},
        {"login", login},
};
#define PROTORPC_ROUTER_NUM  (sizeof(router)/sizeof(router[0]))

class ProtoRpcServer : public TcpServer {
public:
    ProtoRpcServer() : TcpServer()
    {
        onConnection = [](const SocketChannelPtr& channel) {
            std::string peeraddr = channel->peeraddr();
            if (channel->isConnected()) {
                printf("%s connected! connfd=%d\n", peeraddr.c_str(), channel->fd());
            } else {
                printf("%s disconnected! connfd=%d\n", peeraddr.c_str(), channel->fd());
            }
        };
        onMessage = handleMessage;
        // init protorpc_unpack_setting
        unpack_setting_t protorpc_unpack_setting;
        memset(&protorpc_unpack_setting, 0, sizeof(unpack_setting_t));
        protorpc_unpack_setting.mode = UNPACK_BY_LENGTH_FIELD;
        protorpc_unpack_setting.package_max_length = DEFAULT_PACKAGE_MAX_LENGTH;
        protorpc_unpack_setting.body_offset = PROTORPC_HEAD_LENGTH;
        protorpc_unpack_setting.length_field_offset = PROTORPC_HEAD_LENGTH_FIELD_OFFSET;
        protorpc_unpack_setting.length_field_bytes = PROTORPC_HEAD_LENGTH_FIELD_BYTES;  // int占4字节
        protorpc_unpack_setting.length_field_coding = ENCODE_BY_BIG_ENDIAN;
        setUnpack(&protorpc_unpack_setting);
    }

    int listen(int port) { return createsocket(port); }

private:
    static void handleMessage(const SocketChannelPtr& channel, Buffer* buf) {
        // unpack -> Request::ParseFromArray -> router -> Response::SerializeToArray -> pack -> Channel::write
        // protorpc_unpack
        protorpc_message msg;
        memset(&msg, 0, sizeof(msg));
        int packlen = protorpc_unpack(&msg, buf->data(), buf->size());
        if (packlen < 0) {
            printf("protorpc_unpack failed!\n");
            return;
        }
        assert(packlen == buf->size());
        if (protorpc_head_check(&msg.head) != 0) {
            printf("protorpc_head_check failed!\n");
            return;
        }

        // Request::ParseFromArray
        protorpc::Request req;
        protorpc::Response res;
        if (req.ParseFromArray(msg.body, msg.head.length)) {
            printf("> %s\n", req.DebugString().c_str());
            res.set_id(req.id());
            // router
            const char* method = req.method().c_str();
            bool found = false;
            for (int i = 0; i < PROTORPC_ROUTER_NUM; ++i) {
                if (strcmp(method, router[i].method) == 0) {
                    found = true;
                    router[i].handler(req, &res);
                    break;
                }
            }
            if (!found) {
                not_found(req, &res);
            }
        } else {
            bad_request(req, &res);
        }

        // Response::SerializeToArray + protorpc_pack
        protorpc_message_init(&msg);
        msg.head.length = res.ByteSizeLong();
        packlen = protorpc_package_length(&msg.head);
        unsigned char* writebuf = NULL;
        HV_STACK_ALLOC(writebuf, packlen);
        packlen = protorpc_pack(&msg, writebuf, packlen);
        if (packlen > 0) {
            printf("< %s\n", res.DebugString().c_str());

             //writebuf 为char * , 即指针，  writebuf + PROTORPC_HEAD_LENGTH， 指针和整数的加减运算，
            //            比如指针 + 1，并不是在指针地址的基础之上加 1 个地址，而是在这个指针地址的 基础上加 1 个元素占用的字节数：
            //             如果指针的类型是 char*，那么这个时候 1 代表 1 个字节地址；
            //             如果指针的类型是 int*，那么这个时候 1 代表 4 个字节地址；
            //             如果指针的类型是 float*，那么这个时候 1 代表 4 个字节地址；
            //             如果指针的类型是 double*，那么这个时候 1 代表 8 个字节地址。

            res.SerializeToArray(writebuf + PROTORPC_HEAD_LENGTH, msg.head.length);
            channel->write(writebuf, packlen);
        }
        HV_STACK_FREE(writebuf);
    }
};

int main(int argc, char** argv) {
//    if (argc < 2) {
//        printf("Usage: %s port\n", argv[0]);
//        return -10;
//    }
//    int port = atoi(argv[1]);
    int port = 9999;

    ProtoRpcServer srv;
    int listenfd = srv.listen(port);
    if (listenfd < 0) {
        return -20;
    }
    printf("protorpc_server listen on port %d, listenfd=%d ...\n", port, listenfd);
    srv.setThreadNum(4);
    srv.start();

    while (1) hv_sleep(1);
    return 0;
}