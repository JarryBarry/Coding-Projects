##This Python tool filters out fake 200 responses by detecting known error page signatures in 
# the response body using both decoded text and raw byte matching.
#Created By: JarryBarry

import requests
import time
import random
import urllib3

urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)
urlApi = input('Enter a file with URLs|APIs: \n')
error = input('Enter the error message of the body: \n')
if error == '':
    error = 'edp[oihugvb nmjhunmlkjoi23u42klwem,dsc vbhjkdsalxz.,lc;]'
timers = int(input('Enter the amount of time you want the program to sleep in milliseconds: \n')) 
timers = (timers + random.random()*5)/1000 #To add a delay if the user wants it
with open(urlApi, "r") as file:
    lines = file.readlines()

def urlValidityTest():
    fake_urls = [] #fake urls
    real_urls = [] #real urls
    investigate_urls = [] #Urls needing investigation from user
    for line in lines:
        try:
            time.sleep(timers)
            strLine = line.strip()
            response = requests.get(strLine, verify=False, timeout=5)
            text_match = error.lower() in response.text.lower()
            byte_match = error.encode() in response.content
            if text_match or byte_match:
                fake_urls.append(strLine)
            else:
                real_urls.append(strLine)
        except requests.exceptions.RequestException as e:
                    print(f"The url {strLine} failed: \nStarting Second Test\n")
                    investigate_urls.append(strLine)
    return real_urls, fake_urls, investigate_urls

real_urls, fake_urls, investigate_urls = urlValidityTest()

###The Output file readable all results
with open("ResultsErrorPageFilter.txt", "w") as f: 
    f.write("====================\nReal Urls\n====================\n\nAPI|URL:\n")
    for r in real_urls:
        f.write(f"{r}\n")
    f.write("\n====================\nInvestigate Urls\n====================\n\nAPI|URL:\n")
    for r in investigate_urls:
        f.write(f"{r}\n")
    f.write("\n====================\nFake Urls\n====================\n\nAPI|URL:\n")
    for r in fake_urls:
        f.write(f"{r}\n")

#The Output file only the alive URLs
with open("UrlsErrorPageFilter.txt", "w") as f:
    for r in real_urls:
        f.write(f"{r}\n")

#The Output file only for the investigate URLs incase they are actually live
with open("UrlsErrorPageFilter.txt", "w") as f:
    for r in investigate_urls:
        f.write(f"{r}\n")
