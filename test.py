#!/usr/bin/env python3

import socket

MSG_SIZE = 1024

print("Executing STAC Testing script")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = socket.gethostbyname("localhost")

s.connect((host, 1025))

command = ''
while command != 'exit':
    command = input('>>>')
    command += '\n'
    s.send(command.encode())
    buff = b''
    try:
        buff = s.recv(1024)
    except socket.error as err:
        print("Socket error: {0}".format(err))
        break
    if len(buff) == 0:
        break
    print(buff.decode())

print("Closing socket")
s.close()
