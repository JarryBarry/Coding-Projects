##This python code is supposed to test which URL/APIs are online/offline 
#Created By: ARandomManInTheWilds (Me)
#V2 includes a timer

import requests
import fileinput
import datetime
import time
import random

urlApi = input('Enter a file with URLs|APIs: \n')
timers = int(input('Enter the amount of time you want the program to sleep in milliseconds: \n')) 
timers = (timers + random.random()*5)/1000
file = fileinput.input(urlApi)
linebreaker = "_________________________________________________________"

def apiTest():
    try:
        with open("Results.txt", "a") as f:
            date = datetime.datetime.now()
            f.write(f"{linebreaker}\n{date}\n{linebreaker}\n\n")
        apiOnlineStatus = False
        strUrl = ''
        rawUrl = '' #Used to get the URL's alone 
        for line in file:
            apiOnlineStatus = False
            time.sleep(timers)
            strLine = line.strip()
            response = requests.head(strLine, verify=False)
            strUrl = strUrl + f"{response.status_code}" + " "
            if 200 <= response.status_code < 300:
                apiOnlineStatus = True
            if apiOnlineStatus == True:
                strUrl = strUrl + "\nApi|URL:\n" + strLine + "\nOnline\n\n"
                rawUrl = rawUrl + "\n" + strLine
            else:
                strUrl = strUrl + "\nApi|URL:\n" + strLine + "\nOffline\n\n"
        print(strUrl)
        with open("Results.txt", "a") as f:
            f.write("Working URLs: \n" + rawUrl + "\n\n\n\n")
            f.write(strUrl)
    except requests.ConnectionError as e:
        print(f"\nConnection Error {e}")
    except Exception as e:
        print(f"\nError occured: {e} ")

apiTest()
print ("\nDocument Results has been updated")


