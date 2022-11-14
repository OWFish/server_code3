#ifndef _BASE_SOCKET_H_
#define _BASE_SOCKET_H_

/******************************************************************
 *
 *	$ ͨ���׽��ִ����� $
 *
 *	- ��Ҫ���� -
 *
 *	�������׽��ַ�װ�֧࣬�������ͷ�����ģʽ��
 *
 *****************************************************************/
#ifdef _MSC_VER
#define socklen_t int
#include <winsock.h>
#else
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define SOCKET	int
#define WSAGetLastError() errno
#define WSAEWOULDBLOCK EWOULDBLOCK
#define closesocket close
#define OUT

#include <errno.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

namespace net
{
/*	����TCP�׽�����
*/
class BaseSocket
{
protected:
	SOCKET		socket_;		//�׽���
	sockaddr_in	local_addr_;	//�󶨵ı��ص�ַ
	sockaddr_in	remote_addr_;	//Զ�̵�ַ
	bool		block_flag_;		//�Ƿ������ģʽ
	bool		connected_;	//�Ƿ��ѽ�������
	bool		connectint_;	//�Ƿ���������
protected:
	//�ṩ��������߼�֪ͨ���ӽ������¼�
	virtual void OnConnected();
	//�ṩ��������߼�֪ͨ���ӶϿ����¼�
	virtual void OnDisconnected();
	//�ṩ��������߼�֪ͨ���ӷ���������¼�
	virtual void OnError(int errorCode);
protected:
	//�̳���ͨ�����ش˺���������������Ҫ���еĲ���
	virtual void Connected();
	//�̳���ͨ�����ش˺�������Ͽ�������Ҫ���еĲ���
	virtual void Disconnected();
	//�̳���ͨ�����ش˺����������ӷ����˴��������Ҫ���еĲ���
	virtual void SocketError(int nErrorCode);
public:
	BaseSocket();
	virtual ~BaseSocket();

	//���SOCKET
	inline SOCKET getSocket()
	{
		return socket_;
	}
	//����SOCKET
	void setSocket(const SOCKET socket);
	//��ȡ������ģʽ��true��ʾ������false��ʾ������
	inline bool getBlockMode()
	{
		return block_flag_;
	}
	//��������ģʽ��true��ʾ������false��ʾ������������ֵΪsocket����ţ�0��ʾ�ɹ�
	int setBlockMode(const bool block);
	//�ж�SOCKET�Ƿ�������״̬
	inline bool connected()
	{
		return connected_;
	}
	//�Ͽ����Ӳ��ر��׽���
	void Close();
	//�Ͽ�����,sd��ʾ�Ͽ��ķ�ʽ,�ֱ���SD_RECEIVE��SD_SEND��SD_BOTH
	int shutDown(const int sd);
	//��ָ��32λ��IP��ַ���ַ����󶨵��ƶ��ĵ�ַ�Ͷ˿ڣ�����ֵΪsocket����ţ�0��ʾ�ɹ�
	int bind(const u_long addr, const int port);
	//ͨ��ָ��IP��ַ�ַ����Ͷ˿ڰ󶨵�ָ���ĵ�ַ�Ͷ˿ڣ�����ֵΪsocket����ţ�0��ʾ�ɹ�
	//int bind(const char* addr, const int port);
	//��ȡ�󶨵ı��ص�ַ�Ͷ˿ڵ�sockaddr_in�ṹ
	inline void getLoaclAddr(sockaddr_in* addr_in)
	{
		*addr_in = local_addr_;
	}
	//��ȡԶ�̵ĵ�ַ�Ͷ˿ڵ�sockaddr_in�ṹ
	inline void getRemoteAddr(sockaddr_in* addr_in)
	{
		*addr_in = remote_addr_;
	}
	//����Զ�̵�ַ��Ϣ
	inline void setRemoteAddr(const sockaddr_in* addr_in)
	{
		remote_addr_ = *addr_in;
	}
	//��ȡ���ջ�������С������ֵΪsocket����ţ�0��ʾ�ɹ���
	int getRecvBufSize(int* size);
	//���ý��ջ�������С������ֵΪsocket����ţ�0��ʾ�ɹ���
	int setRecvBufSize(int size);
	//��ȡ���ͻ�������С������ֵΪsocket����ţ�0��ʾ�ɹ���
	int getSendBufSize(int* size);
	//���÷��ͻ�������С������ֵΪsocket����ţ�0��ʾ�ɹ���
	int setSendBufSize(int size);
	//��ʼ������backlog��ʾÿ�οɽ��ܵ���������������ֵΪsocket����ţ�0��ʾ�ɹ�
	int listen(const int backlog = 5);
	//ͨ��32λIP��ַ���ӵ��ƶ��Ķ˿ڣ�����ֵΪsocket����ţ�0��ʾ�ɹ������ڷ�����ģʽ����0������ʾ�Ѿ���������
	int connect(const u_long addr, const int port, bool block);
	//ͨ��IP��ַ�ַ������ӵ�ָ���Ķ˿ڣ�����ֵΪsocket����ţ�0��ʾ�ɹ������ڷ�����ģʽ����0������ʾ�Ѿ���������
	//int connect(const char* addr, const int port, bool block);
	//�����µ����ӣ�wait_msec��ʾ���ȴ�����������������0��ʾ�ɹ���socket�����յ��׽�����䣬����SOCKET_ERROR-1��ʾ�ȴ���ʱ������������socket�����
	int accept(SOCKET* socket, size_t wait_msec, sockaddr_in* addr);
	//�����׽��֣�����ֵΪsocket����ţ�0��ʾ�ɹ���socket�����ݱ����Ϊ�½�����socket
	static int createSocket(OUT SOCKET* socket, const int af = AF_INET, const int type = SOCK_STREAM, const int protocol = IPPROTO_TCP);
	//��ȡ�׽������ݡ�����0��ʾ�����ѶϿ�������SOCKET_ERROR��ʾ�������󣬷���SOCKET_ERROR-1��ʾû�����ݿɶ�(�����ڷ�����ģʽ�׽���)�������ʾʵ�ʽ��յ��ֽ���
	virtual int recv(void* buf, int len, const int flags = 0);
	//���׽���д�����ݣ�����0��ʾ�����ѶϿ�������SOCKET_ERROR��ʾ�������󣬷���SOCKET_ERROR-1��ʾsend�����ᷢ��������û�����ݱ�����(�����ڷ�����ģʽ�׽���)�����򷵻ط��͵��ֽ�����
	virtual int send(void* buf, int len, const int flags = 0);
};
};

#endif

