import serial
import Data_process
global com
com=serial.Serial("/dev/ttyUSB0")
com.baudrate=115200
com.parity=serial.PARITY_NONE
com.stopbits=serial.STOPBITS_ONE
com.bytesize=serial.EIGHTBITS
com.timeout=1.5
com.rtscts=0

def Serial_Init():
	if com.isOpen()==False:
		com.open()
def Frame_receive(index):
	robot_index=-1
	data=[0]*20
	sum=0
	com.flushInput()
	data[0]=ord(com.read(1))
	if data[0]!=0xFE:
		return 1	
	data[1]=ord(com.read(1))
	data_len=data[1]
	data[2]=ord(com.read(1))
	if data[2]!=0x91:
		return 1
	data[3]=ord(com.read(1))
	if data[3]!=0x90:
		return 1
	data[4]=ord(com.read(1))
	data[5]=ord(com.read(1))

	for i in range(6,data_len+2):
		data[i]=ord(com.read(1))
		if data[i]==0xFE:
			temp=ord(com.read(1))
			if temp==0xFD:
				data[i]=0xFF
			elif temp==0xFC:
				data[i]=0xFE
			else:
				return 1
	robot_index=data[4]
	if robot_index!=index:
		return 2
	if ord(com.read(1))!=0xFF:
		return 1
	Data_process.Data_prepare(*data)
	return 0
while Frame_receive(1)!=0:
	continue
