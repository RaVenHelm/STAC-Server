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
    logu = 'LOGU "ejohn" "rocketman"'
    create_class = 'CRCR "TestClass" "UNC-Test" "08-08-2016" "12-12-2112" "1.2.3.4" "T1230-1545;R1425-1725"'
    cls_list = 'CLST'
    logo = 'LOGO'

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

    # Create class
    debug(create_class)

    s.send(create_class.encode())
    msg_buff = s.recv(MSG_SIZE)
    msg = msg_buff.decode()

    expected = 'CRER S'
    if not msg.startswith(expected):
        msg_err(expected, msg)
        close(s)
        return
    
    print(msg.strip())

    # Log out admin
    debug(logo)
    s.send(logo.encode())
    msg_buff = s.recv(MSG_SIZE)
    msg = msg_buff.decode()

    # Logout
    expected = 'LOGO S'
    if msg.strip() != expected:
        msg_err(expected, msg)
        close(s)
        return
    
    print(msg.strip())

    s.connect((host, 1025))

    # Log in user
    debug(logu)
    s.send(logu.encode())
    msg_buff = s.recv(MSG_SIZE)
    msg = msg_buff.decode()

    # Login
    expected = 'LOGR S'
    if msg.strip() != expected:
        msg_err(expected, msg)
        close(s)
        return
    
    s.close()

if __name__ == '__main__':
    main()
