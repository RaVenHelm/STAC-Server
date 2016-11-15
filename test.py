#!/usr/bin/env python3

import socket

MSG_SIZE = 2048

def debug(command):
    print('Executing command: ' + command)


def close(sock):
    print('Closing socket')
    sock.close()


def msg_err(expected, msg):
    print('ERROR!\nExpected: {0}\nGot: {1}'.format(expected, msg))


def main():
    print('Executing STAC Testing script')

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    host = socket.gethostbyname('localhost')

    s.connect((host, 1025))
    hrbt = 'HRBT'
    loga = 'LOGA "ejohn" "rocketman"'
    cls_list = 'CLST'

    msg_buff = b''
    msg      = ''

    # Heartbeat
    debug(hrbt)
    s.send(hrbt.encode())
    msg_buff = s.recv(MSG_SIZE)
    msg = msg_buff.decode()

    expected = 'OK'
    if msg.strip() != expected:
        msg_err(expected, msg)
        close(s)
        return
    
    print(msg.strip())

    # Log in admin
    debug(loga)
    s.send(loga.encode())
    msg_buff = s.recv(MSG_SIZE)
    msg = msg_buff.decode()

    expected = 'LOGR S'
    if msg.strip() != expected:
        msg_err(expected, msg)
        close(s)
        return
    
    print(msg.strip())

    # Get class list
    debug(cls_list)

    s.send(cls_list.encode())
    msg_buff = s.recv(MSG_SIZE)
    msg = msg_buff.decode()

    expected = 'CLSR S'
    if not msg.startswith(expected):
        msg_err(expected, msg)
        close(s)
        return
    
    print(msg.strip())


    s.close()

if __name__ == '__main__':
    main()
