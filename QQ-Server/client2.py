import ujson as json
import socket               # 导入 socket 模块

s = socket.socket()         # 创建 socket 对象
port = 9987                # 设置端口号

msg = {
    'type': 'login',
    'payload': {
        "username": "peter2",
        "password": "abc123_"
    }
}

hello_msg = {
    'type': 'send_msg',
    'payload': {
        "username": "peter1",
        "message": "hello peter1"
    }
}

s.connect(('192.168.1.183', port))
msg = json.dumps(hello_msg)
s.send(msg.encode('utf-8'))
data = s.recv(512)
print('recv:', data.decode('utf-8'))

s.close()