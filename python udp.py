import socket
import numpy as np
import time

import cv2
import numpy as np

bgr = cv2.imread('shenLong2.bmp')
rgb = cv2.cvtColor(bgr,cv2.COLOR_BGR2RGB)


rgb = rgb
#bgr = np.array(bgr,dtype=np.uint8)
print(rgb[:,16:32,:].shape)
 
UDP_IP = "192.168.1.26"
UDP_PORT = 4210
MESSAGE = "   zzz   zzz   zzz"

print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
print("message:", MESSAGE)

sock = socket.socket(socket.AF_INET, # Internet
             socket.SOCK_DGRAM) # UDP


##sock.sendto(rgb, (UDP_IP, UDP_PORT))

for j in range(100):
    for i in range(23):
        a = np.array(rgb[:,i:i+16,:])
        sock.sendto(a, (UDP_IP, UDP_PORT))
        time.sleep(0.1)
