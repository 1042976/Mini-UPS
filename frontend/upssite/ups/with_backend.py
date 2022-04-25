# Socket client example in python
from _socket import htons

from google.protobuf.internal.decoder import _DecodeVarint32
from google.protobuf.internal.encoder import _EncodeVarint

import socket
import sys

from ups import frontend_pb2
import psycopg2

host = 'vcm-25919.vm.duke.edu'
port = 45678
#
# create socket
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
    sys.exit()

# try:
#     remote_ip = socket.gethostbyname(host)
# except socket.gaierror:
#     sys.exit()

# Connect to remote server

s.connect((host, port))
# msg = "hello"
# s.send(msg.encode('utf-8'))

def handleF2BChangeAddress(package_id, new_x, new_y):

    f2BChangeAddress = frontend_pb2.F2BChangeAddress()
    f2BChangeAddress.seqnum = 1
    f2BChangeAddress.shipid = int(package_id)
    f2BChangeAddress.x = int(new_x)
    f2BChangeAddress.y = int(new_y)
    protobuf_data = f2BChangeAddress.SerializeToString()
    _EncodeVarint(s.send, len(protobuf_data), None)
    s.send(protobuf_data)
    var_int_buff = []
    while True:
        buf = s.recv(1)
        var_int_buff += buf
        msg_len, new_pos = _DecodeVarint32(var_int_buff, 0)
        if new_pos != 0:
            break
    whole_message = s.recv(msg_len)
    b2FChangeAddressResp = frontend_pb2.B2FChangeAddressResp()
    b2FChangeAddressResp.ParseFromString(whole_message)
    return b2FChangeAddressResp.shipid, b2FChangeAddressResp.result

