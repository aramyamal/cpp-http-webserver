# C++ HTTP Webserver

## Overview
To get a better understanding of the HTTP protocol and TCP connections I reinvented the wheel and created this simple webserver utilizing the <sys/socket.h> C library on Linux and MacOS. Currently the webserver can only parse GET requests and serve ```index.html```, ```style.css``` and ```favicon.iso``` from the working directory it was run from.
It also handles unsupported requests by returning a *404 Not Found* response with a custom ```error_404.html``` page, also located in the same directory. Currently I've limited file serving to these explicitly defined files to ensure the server remains secure.

I've also created a simple client to test the server functionality. It can connect to an arbitrary adress and port, send user defined requests, and then display the subsequent server response.

## Usage
### Building
You can build the executable using cmake. While in the repo directory, run:
```bash
mkdir build
cd build
cmake ..
make
```
The resulting executabled are then in ```build/bin/``` and are:
```
cpp-http-webserver*
test-client*
```

### Running the server
The ```cpp-http-webserver``` executable requires two parameters:

```cpp-http-webserver* <port> <backlog>```
- ```port```: The port number the server will bind to and listen for incoming connections (e.g., ```8080```).
- ```backlog```: The maximum number of pending connections the server will queue before refusing new ones (e.g. ```10```).

When running the webserver, it uses you current working directory to serve files from it. The directory ```.testserver/``` contains appropiate files to serve for testing the server. This you can do by running the executable ```cpp-htt-webserver*``` while your current working directory is ```.testserver/```:
```bash

cd .testserver/
../build/bin/cpp-hhtp-webserver <port> <backlog>
```
You can then connect to the server through ```http://localhost:<port>```.

### Using the test client
The ```test-client``` executable allows you to connect to any adress and port and send it a request, then display the subsequent response. This can be used to test wether or not the webserver is working. 

```test-client``` requires three parameters:

```test-client <address> <port> <message>```
- ```address```: The address the client should connect to (e.g., ```127.0.0.1```, ```1.1.1.1```)
- ```port```: The port number the client should connect to (e.g., ```8080```).
- ```message```: The message that should be sent to the given address and port if connection is estabished (e.g. ```"GET /index.html HTTP/1.1"```).

The cient then outputs the response it recieves back from the server it connected to.
