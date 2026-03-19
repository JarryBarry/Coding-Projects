##This python code is supposed to check if a page has a certain message which usually means
#the page doesn't actually exist to find the real pages in the pages that are alive
#Created By: JarryBarry

import requests
import fileinput
import datetime
import time
import random

urlApi = input('Enter a file with URLs|APIs: \n')
error = input('Enter the error message of the body: \n')
if error == '':
    error = 'edp[oihugvb nmjhunmlkjoi23u42klwem,dsc vbhjkdsalxz.,lc;]'
timers = int(input('Enter the amount of time you want the program to sleep in milliseconds: \n')) 
timers = (timers + random.random()*5)/1000 #To add a delay if the user wants it
file = fileinput.input(urlApi)
linebreaker = "_________________________________________________________"

def urlValidityTest():
    try:
        with open("Results.txt", "a") as f:
            date = datetime.datetime.now()
            f.write(f"{linebreaker}\n{date}\n{linebreaker}\n\n")
        bodyError = False
        rawUrl = '' #only urls to go through
        fstrUrl = '' #fake urls
        rstrUrl = '' #real urls
        istrUrl = '' #Urls needing investigation from user
        for line in file:
            bodyError = False
            time.sleep(timers)
            strLine = line.strip()
            response = requests.get(strLine, verify=False)
            temp = str(response.content)
            if error in temp:
                bodyError = True
                fstrUrl = fstrUrl + "\nApi|URL:\n" + strLine + "\nNot Real Link\n\n"
            elif bodyError == False:
                rstrUrl = rstrUrl + "\nApi|URL:\n" + strLine + "\nReal Link\n\n"
                rawUrl = rawUrl + "\n" + strLine
            else:
                print(f"The url {strLine} failed: \nStarting Second Test\n")
                istrUrl = istrUrl + "\nApi|URL:\n" + strLine + "\nInvestigate\n\n"
        with open("BodyResults.txt", "w") as f:
            f.write("Real Links URLs: \n " + rawUrl + "\n\n\n")
            f.write("Real Links: \n" + rstrUrl)
        with open("BodyResults.txt", "a") as f:
            f.write("Fake Links: \n" + fstrUrl)
            f.write("Investigate: \n" + istrUrl) 
    except requests.ConnectionError as e:
        print(f"\nConnection Error {e}")
    except Exception as e:
        print(f"\nError occured: {e} ")

urlValidityTest()
