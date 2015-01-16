// Sender.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

char * fileBytes;

int _tmain(int argc, _TCHAR* argv[])
{
	int sizeLeft = sizeof(sHeader);
	int pos = 0;
	CFileManager file = CFileManager("C:\\Users\\vitor\\AppData\\Local\\GitHub\\TheLog.txt");
	sHeader fileInfo;

	file.ReadData(fileBytes);
	file.GetInformation(fileInfo);

	sizeLeft = fileInfo.filesize;

	std::cout << "Aguardando requests.\r\n";

	if (!p_Socket->WaitConnections())
	{
		std::cout << "Erro ao receber requests\r\n";
	}

	std::cout << "Cliente conectado\r\n";
	
	if (p_Socket->Send<sHeader>(&fileInfo))
	{
		std::cout << "Header enviado.\r\n";
	}

	while (sizeLeft > 0)
	{
		if (sizeLeft < 32)
		{
			if (p_Socket->Send(&fileBytes[pos * 32], sizeLeft))
				sizeLeft = 0;
		}
		else
		{
			if (p_Socket->Send(&fileBytes[pos * 32], 32))
			{
				sizeLeft -= 32;
				pos++;
			}
		}
	}

	std::cout << "Arquivo enviado.\r\n";

	free(fileBytes);

	system("PAUSE");
	return 0;
}

