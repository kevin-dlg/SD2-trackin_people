import io
import picamera
import cv2
import numpy
import smtplib
import RPi.GPIO as gpio
import time

#importing modules to send emails
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage

#Email variables
SERVER='smtp.gmail.com'
PORT=587
USERNAME='team4.humandetection@gmail.com'
PASSWORD='team412345'
#Initializing other variables
trigger=40
gpio.setmode(gpio.BOARD)
gpio.setup(trigger,gpio.IN)

faces=0;
class Emailer:
    def sendmail(self, recipient, subject, content, image):
        #Creating the headers
        emailData = MIMEMultipart()
        emailData['Subject']=subject
        emailData['To']=recipient
        emailData['From']=USERNAME
        
        emailData.attach(MIMEText(content))
        
        #attach image
        imageData = MIMEImage(open(image, 'rb').read(),'jpg')
        imageData.add_header('Content-Disposition', 'attachment; filename="result.jpg"')
        emailData.attach(imageData)
        
        #connecting to gmail account
        session = smtplib.SMTP(SERVER, PORT)
        session.ehlo()
        session.starttls()
        session.ehlo()
        
        #Logging into gmail and sending email
        session.login(USERNAME,PASSWORD)
        session.sendmail(USERNAME, recipient, emailData.as_string())
        session.quit
        
def sendEmail():
    print("Sending Email...")
    sender = Emailer()
    sendTo='esmermora579@gmail.com'
    emailSubject="This is a test"
    emailContent="hello"
    image='/home/pi/Documents/result.jpg'
    sender.sendmail(sendTo, emailSubject, emailContent, image)
    print("Email Sent")
def locateHuman():
    #Create a memory stream so photos doesn't need to be saved in a file
    stream = io.BytesIO()

    #Get the picture (low resolution, so it should be quite fast)
    #Here you can also specify other parameters (e.g.:rotate the image)
    with picamera.PiCamera() as camera:
        camera.resolution = (320, 240)
        camera.capture(stream, format='jpeg')
        camera.rotation=180;

    #Convert the picture into a numpy array
    buff = numpy.frombuffer(stream.getvalue(), dtype=numpy.uint8)

    #Now creates an OpenCV image
    image = cv2.imdecode(buff, 1)

    #https://github.com/opencv/opencv/blob/master/data/haarcascades/haarcascade_frontalface_default.xml
    #Load a cascade file for detecting faces
    face_cascade = cv2.CascadeClassifier('/home/pi/Human Recognition/haarcascade_frontalface_alt.xml')

    #Convert to grayscale
    gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)

    #Look for faces in the image using the loaded cascade file
    faces = face_cascade.detectMultiScale(gray, 1.1, 5)

    print ("Found " + str(len(faces)) + " human(s)")

    #Draw a rectangle around every found face
    for (x,y,w,h) in faces:
        cv2.rectangle(image,(x,y),(x+w,y+h),(255,255,0),4)

    #Save the result image
    cv2.imwrite('result.jpg',image)
    return len(faces)

#Main function
while True:
    i=gpio.input(trigger)
    #If PIR Outputs High
    if i==1:
        print("Scanning for people")
        faces=locateHuman()
        #send email if there is more than one person
        if faces>0:
            print("# of people detected: " + faces)
            sendEmail()
        else:
            pass
    else:
        pass
    
