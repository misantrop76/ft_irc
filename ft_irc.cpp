#include "ft_irc.hpp"

int serv(int port) 
{
    // Variables
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* welcome_message = "Welcome to the server\n";

    // Créer le socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{
        std::cerr << "socket error" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Configuration du port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{
        std::cerr << "setsockopt error" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

	//Attachement du socket au port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
	{
        std::cerr << "bind error" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Écouter sur le port
    if (listen(server_fd, 3) < 0) 
	{
        std::cerr << "listen error" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    std::cout << "Server is listening on port " << port << std::endl;

    // Accepter les connexions
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) 
	{
        std::cerr << "accept error" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Écrire un message au client
    send(client_fd, welcome_message, strlen(welcome_message), 0);
    std::cout << "Welcome message sent to client" << std::endl;

    // Lire le message du client
    int valread = read(client_fd, buffer, 1024);
	if (valread > 0)
    	std::cout << "Client says: " << buffer << std::endl;

    // Fermer les sockets
    close(client_fd);
    close(server_fd);
    return 0;
}


int ft_atoi(char *str)
{
	int nbr;
	int i;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	if (nbr > 65535)
		return (-1);
	return (nbr);
}

int main(int ac, char **av)
{
	int				port;
	std::string		pass;

	if (ac != 3)
	{
		std::cerr << "Wrong number of arguments !" << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "./ft_ircserv <port> <password>" << std::endl;
		return (1);
	}
	port = ft_atoi(av[1]);
	pass = av[2];
	if (port == -1)
	{
		std::cerr << "Error with port number !" << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "./ft_ircserv <port> <password>" << std::endl;
		return (1);
	}
	serv(port);
}
