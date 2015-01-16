// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	sHeader fileInfo;
	int sizeRecived = 0;
	int pos = 0;
	char * fileBuffer;

	if (!p_Socket->Connect("127.0.0.1"))
	{
		std::cout << "Impossivel conectar. Sem resposta.\r\n";

		p_Socket->Clean();
		system("PAUSE");
		return 0;
	}
	else
	{
		std::cout << "Aguardando headers...\r\n";
	}
	
	//aguarda o recebimento do cabeçalho
	for (;;)
	{
		if (p_Socket->Recv<sHeader>(&fileInfo))
		{
			std::cout << "Header recebido. Tamanho: " << fileInfo.filesize << "\r\n";
			break;
		}
	}
	//prepara para recebimento
	
	fileBuffer = (char *)malloc(fileInfo.filesize);

	//recebe arquivo

	while (sizeRecived < fileInfo.filesize)
	{
		if ((fileInfo.filesize - sizeRecived) < 14)
		{
			if (p_Socket->Recv(&fileBuffer[pos * 14], (fileInfo.filesize - sizeRecived)))
			{
				sizeRecived = fileInfo.filesize;
			}
		}
		else
		{
			if (p_Socket->Recv(&fileBuffer[pos * 14], 14))
			{
				pos++;
				sizeRecived += 14;
			}
		}
	}

	std::cout << "Arquivo recebido.\r\n";

	p_Socket->Clean();
	system("PAUSE");
	return 0;
}

