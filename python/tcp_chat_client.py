import socket
import threading


class Tcp_client():
    def __init__(self,message):
        self.message = message
        self.client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        print("[TCP客户端] 正在连接服务器")
        self.client.connect(("192.168.114.12",8023))
        print("[TCP客户端] 连接到服务器")
        self.client.send(self.message.encode())
    def receive(self):
        while True:
            data = self.client.recv(1024)
            print(f"[TCP客户端] 收到消息:{data.decode()}")
            if data.decode() == "TCP服务器即将关闭":
               print("即将关闭TCP客户端")
               self.client.close()
               print("TCP客户端已关闭")
               break
        
    def send_to(self):
        while True:
            message = input("[TCP客户端] 请输入消息:")
            if message == "exit":
                self.client.send("TCP客户端即将关闭".encode())
                self.client.close()
                print("[TCP客户端] 已关闭")
                break
            else:
                print("[TCP客户端] 正在发送消息")
                self.client.send(message.encode())


tcp = Tcp_client("Hello Server")
send_thread = threading.Thread(target=tcp.send_to)
receive_thread = threading.Thread(target=tcp.receive)
send_thread.start()
receive_thread.start()
send_thread.join()
receive_thread.join()
