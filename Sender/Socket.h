#pragma once
#include "stdafx.h"

class CSocketClient
{
private:
	WSADATA WsaDat;
	SOCKADDR_IN SockAddr;
	SOCKET m_Socket;
	struct hostent *host;

public:
	bool Connect(char * ip); //client only
	bool WaitConnections(); //server only
	void Clean();

	bool Send(char * Buffer, int size)
	{
		int nError;

		send(m_Socket, Buffer, size, 0);
		nError = WSAGetLastError();

		if (nError != WSAEWOULDBLOCK&&nError != 0)
			return false;
		else
			return true;
	}

	bool Recv(char * Buffer, int size)
	{
		int nError;

		recv(m_Socket, Buffer, size, 0);
		nError = WSAGetLastError();

		if (nError != WSAEWOULDBLOCK&&nError != 0)
			return false;
		else
			return true;
	}

	template<class T> bool Send(T * buffer)
	{
		int nError;

		send(m_Socket, (char *)buffer, sizeof(T), 0);
		nError = WSAGetLastError();

		if (nError != WSAEWOULDBLOCK&&nError != 0)
			return false;
		else
			return true;
	}

	template<class T> bool Recv(T * buffer)
	{
		int nError;

		if (recv(m_Socket, (char *)buffer, sizeof(T), 0) == sizeof(T))
			return true;
		else
			return false;

		nError = WSAGetLastError();

		if (nError != WSAEWOULDBLOCK&&nError != 0)
			return false;
		else
			return true;
	}

	CSocketClient();
	~CSocketClient();
};

extern CSocketClient * p_Socket;