from Tkinter import *           
import tkFont
import Data_transfer
import Data_process
device_list={0:"RC",1:"IMU",2:"ZGYR0",3:"MOTOR1",4:"MOTOR2",5:"MOTOR3",6:"MOTOR4",7:"MOTOR5",8:"MOTOR6",9:"CALI",10:"TIMEOUT"}
root = Tk()                   
ft=tkFont.Font(size=10)
listb =[Listbox(root,width=15,height=11,font=ft),Listbox(root,width=15,height=11,font=ft),Listbox(root,width=15,height=11,font=ft),Listbox(root,width=15,height=11,font=ft),Listbox(root,width=15,height=11,font=ft)]
label1=Label(root,text='Robot1')
label2=Label(root,text='Robot2')
label3=Label(root,text='Robot3')
label4=Label(root,text='Robot4')
label5=Label(root,text='Robot5')

noresponse=[0]*5
                      
def Gui_mainloop():
	Error_list=[['']*11,['']*11,['']*11,['']*11,['']*11]
	for robot_index in range(0,5):
		if noresponse[robot_index]==1:
			Error_list[robot_index][10]="No response"
			for i in range(0,10):
				Error_list[robot_index][i]=""
		else:	
			for i in range(0,11):
				if Data_process.Get_state(robot_index,i)==1:
					Error_list[robot_index][i]="%s : %s"%(device_list[i],"Error")
				else:
					Error_list[robot_index][i]="%s : %s"%(device_list[i],"Working")

	listb[0].delete(0,END)
	for item in Error_list[0]:              
    		listb[0].insert(0,item)
	listb[1].delete(0,END)
	for item in Error_list[1]:              
    		listb[1].insert(0,item)
	listb[2].delete(0,END)
	for item in Error_list[2]:              
    		listb[2].insert(0,item)
	listb[3].delete(0,END)
	for item in Error_list[3]:              
    		listb[3].insert(0,item)
	listb[4].delete(0,END)
	for item in Error_list[4]:              
    		listb[4].insert(0,item)
	#for i in range(0,5):
	#	listb[i].grid(row=1,column=i)
	listb[0].grid(row=1,column=0)
	listb[1].grid(row=1,column=1)
	listb[2].grid(row=1,column=2)
	listb[3].grid(row=1,column=3)
	listb[4].grid(row=1,column=4)
	label1.grid(row=0,column=0)                 
	label2.grid(row=0,column=1)                 
	label3.grid(row=0,column=2)                 
	label4.grid(row=0,column=3)                 
	label5.grid(row=0,column=4)                 
	root.mainloop()			
def refresh():
	for ri in range(1,6):
		flag=1
		try_count=0
		while flag!=0 and try_count<40:
			flag=Data_transfer.Frame_receive(ri)
			if flag==2:
				try_count+=1
		if try_count==40:
			noresponse[ri-1]=1
	Gui_mainloop()
bt1=Button(root,text="Refresh",command=refresh)
bt1.grid(row=2,column=0)
refresh()      
Gui_mainloop()			
