#include "stdafx.h"
#include "Socket.h"

CSocketClient * p_Socket = new CSocketClient();

bool CSocketClient::WaitConnections()
{
	SOCKADDR_IN serverInf;
	serverInf.sin_family = AF_INET;
	serverInf.sin_addr.s_addr = INADDR_ANY;
	serverInf.sin_port = htons(8888);

	if (bind(m_Socket, (SOCKADDR*)(&serverInf), sizeof(serverInf)) == SOCKET_ERROR)
	{
		//erro ao bindar socket
		WSACleanup();
		return false;
	}

	listen(m_Socket, 1);

	SOCKET TempSock = SOCKET_ERROR;
	while (TempSock == SOCKET_ERROR)
	{
		//aguardando clientes
		TempSock = accept(m_Socket, NULL, NULL);
	}

	u_long iMode = 1;
	ioctlsocket(m_Socket, FIONBIO, &iMode);

	m_Socket = TempSock;
	//cliente conectado

	return true;
}

bool CSocketClient::Connect(char * ip)
{
	if ((host = gethostbyname(ip)) == NULL)
	{
		//Erro ao encontrar o server
		WSACleanup();
		return false;
	}

	SockAddr.sin_port = htons(8888);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	// Tenta se conectar no servidor
	if (connect(m_Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		//Falha ao conectar
		WSACleanup();
		return false;
	}
	else
	{
		//conectado
		u_long iMode = 1;
		ioctlsocket(m_Socket, FIONBIO, &iMode);
		return true;
	}
}

void CSocketClient::Clean()
{
	WSACleanup();
}

CSocketClient::CSocketClient()
{
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{
		//Erro ao inicializar winsock
		WSACleanup();
	}

	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_Socket == INVALID_SOCKET)
	{
		//Erro ao criar socket
		WSACleanup();
	}
}


CSocketClient::~CSocketClient()
{
}
