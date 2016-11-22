#!/usr/bin/env python3

import socket

MSG_SIZE = 2048

print('Executing STAC Testing script')

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = socket.gethostbyname('localhost')

s.connect((host, 1025))
hrbt = 'HRBT'
loga = 'LOGA "ejohn" "rocketman"'
csrc = 'CSRC "" ""'

s.send(loga.encode())
msg_buf = s.recv(MSG_SIZE)

msg = msg_buf.decode()
print('Message received: {0}'.format(msg.strip()))

s.send(csrc.encode())
msg_buf = s.recv(MSG_SIZE)
msg = msg_buf.decode()
print('Message received: {0}'.format(msg.strip()))

csrr = 'CSRR S'
if msg.startswith(csrr):
    id_str = msg[len(csrr) + 1:]
    ids = id_str.split()
    for cls_id in ids:
        cdtl = 'CDTL {0}'.format(cls_id.strip())
        s.send(cdtl.encode())
        cdtl_msg = s.recv(MSG_SIZE * 2).decode()
        print('CDTL response: {0}'.format(cdtl_msg.strip()))

s.send('LOGO'.encode())