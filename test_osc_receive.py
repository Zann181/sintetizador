import socket

UDP_IP_RECV = "127.0.0.1"
UDP_PORT_RECV = 8001

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.settimeout(5.0)
sock.bind((UDP_IP_RECV, UDP_PORT_RECV))

print("Listening for 5 seconds for background beats...")
while True:
    try:
        data, addr = sock.recvfrom(1024)
        print("Received background message:", data)
    except socket.timeout:
        print("Timeout.")
        break
