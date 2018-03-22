device_list={0:"RC",1:"IMU",2:"ZGYR0",3:"MOTOR1",4:"MOTOR2",5:"MOTOR3",6:"MOTOR4",7:"MOTOR5",8:"MOTOR6",9:"CALI",10:"TIMEOUT"}
device_state=[[0]*16,[0]*16,[0]*16,[0]*16,[0]*16]
def Data_prepare(*data):
	#device_state=[0]*11
	#os.system("clear")
	#print data[7]
	robot_index=data[4]-1
	for i in range(0,8):
		if data[9]&(1<<i)!=0:
			device_state[robot_index][i]=1
		else:	
			device_state[robot_index][i]=0	
	for i in range(0,8):
		if data[8]&(1<<i)!=0:
			device_state[robot_index][i+8]=1
		else:	
			device_state[robot_index][i+8]=0	
def Get_state(rindex,dindex):
	return device_state[rindex][dindex]
