# import curses and GPIO library
import curses
import RPi.GPIO as io
From datetime import datetime

io.setmode(GPIO.BCM)    #using the software defined pin numbers
motor1A = 7     #In1
motor1B = 8     #In2
motor2A = 9     #In3
motor2B = 10    #in4
PIR_left=11
PIR_right=13

#assigning motor pins as output pins and PIR pins as input pins
io.setup(motor1A,io.OUT)
io.setup(motor1B,io.OUT)
io.setup(motor2A,io.OUT)
io.setup(motor2B,io.OUT)
io.setup(PIR_left, io.IN)
io.setup(PIR_right, io.IN)

#enable input from keyboard arrow keys
screen.keypad(True)
screen = curses.initscr()
curses.noecho()
curses.cbreak()


try:
        while True:
            char = screen.getch() #get character input
            if char == ord('q'): #press q key to quit
                break
            elif char == curses.KEY_UP:
                io.output(motor1A,False)
                io.output(motor1B,True)
                io.output(motor2A,False)
                io.output(motor2B,True)
            elif char == curses.KEY_DOWN:
                io.output(motor1A,True)
                io.output(motor1B,False)
                io.output(motor2A,True)
                io.output(motor2B,False)
            elif char == curses.KEY_DOWN:
                io.output(motor1A,True)
                io.output(motor1B,False)
                io.output(motor2A,True)
                io.output(motor2B,False)
       elif char == curses.KEY_RIGHT:
                io.output(motor1A,True)
                io.output(motor1B,False)
                io.output(motor2A,False)
                io.output(motor2B,True)
        elif char == curses.KEY_LEFT:
                io.output(motor1A,False)
                io.output(motor1B,True)
                io.output(motor2A,True)
                io.output(motor2B,False)
        #enter key is used as a stop button
        elif char == 10:
                io.output(motor1A,False)
                io.output(motor1B,False)
                io.output(motor2A,False)
                io.output(motor2B,False)


while True:
    #store the current time
    now = datetime.now()
    current_time = now.strftime(“%H:%H:”)

    i = io.input(PIR_right)
    j = io.input(PIR_left)
    if i==0 & j==0:
        print (“No people detected”)
    elif j==1:
        print (“Person on the right detected at ”, current_time)
    elif i==1:
        print (“Person on the left detected at ”, current_time)
finally:
    curses.nocbreak(); screen.keypad(0); curses.echo()
    curses.endwin()
    io.cleanup()
