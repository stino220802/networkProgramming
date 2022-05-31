import zmq
import PySimpleGUI as sg

context = zmq.Context()

pusher = context.socket(zmq.PUSH)
pusher.connect("tcp://benternet.pxl-ea-ict.be:24041")
subber = context.socket(zmq.SUB)
subber.connect("tcp://benternet.pxl-ea-ict.be:24042")

sg.theme('BluePurple')

layout = [[sg.Text('welcome to the amazingService')],
           [sg.Text('Enter victim and press button'), sg.InputText()],
          [sg.Button('spammer'),sg.Button('Exit')]]

window = sg.Window('honeynetClient', layout)


    #subber.setsockopt_string( zmq.SUBSCRIBE, "amazingService?>")
while True:

    event, values = window.read()
    print(event, values)

    if event in (None, 'Exit'):
        break

    if event == 'spammer':
        print(values[0])
        temp = "amazingService!>activateSpammer>" + values[0]

        print(temp)
        pusher.send_string(temp)

   """ if event == 'Request recent subs':
        # Update the "output" text element
        # to be the value of "input" element
        #window['-OUTPUT-'].update(values['-IN-'])
        pusher.send(str.encode("amazingService!>requestRecentSubs"))
      #  message = subber.recv()
     #   print(message)
"""

    #if message == "b'amazingService?>size>":
     #   print(message)
window.close()
#  Socket to talk to server
"""print("Connecting to hello world server…")
pusher = context.socket(zmq.PUSH)
pusher.connect("tcp://benternet.pxl-ea-ict.be:24041")
subber = context.socket(zmq.SUB)
subber.connect("tcp://benternet.pxl-ea-ict.be:24042")
"""


