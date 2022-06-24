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
          [sg.Button('spammer'),sg.Button('send'), sg.Button('loadSpammer'), sg.Button('activateEchoSpammer'), sg.Button('deactivateEchoSpammer'),sg.Button('Exit')]]

window = sg.Window('honeynetClient', layout)

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

    if event == 'loadSpammer':
        temp3 = "amazingService!>activateLoadSpammer>" + values[0]

        print(temp3)
        pusher.send_string(temp3)

    if event == 'activateEchoSpammer':
        temp4 = "amazingService!>activateEchoSpammer>" + values[0]
        print(temp4)

        pusher.send_string(temp4)
    if event == 'deactivateEchoSpammer':
        temp5 = "amazingService!>deactivateEchoSpammer>"

        pusher.send_string(temp5)

    if event == 'send':
        temp2 = "amazingService!>reverseShell" + values[0]
        pusher.send_string(temp2)

window.close()

