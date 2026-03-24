##This python code is supposed to test which URL/APIs are online/offline
#Created By: JarryBarry
#V2 includes a timer

import requests
import time
import random
import datetime
import urllib3

urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

urlApi = input('Enter a file with URLs|APIs: \n')
timers = int(input('Enter the amount of time you want the program to sleep in milliseconds: \n'))
timers = (timers + random.random() * 5) / 1000

with open(urlApi, "r") as file:
    lines = file.readlines()

def urlStatusTest():
    online_urls = []    # URLs returning 2xx
    offline_urls = []   # URLs returning non-2xx
    investigate_urls = [] # URLs that threw an exception
    for line in lines:
        strLine = line.strip()
        try:
            time.sleep(timers)
            response = requests.head(strLine, verify=False, timeout=5)
            status = response.status_code
            if 200 <= status < 300:
                online_urls.append((strLine, status))
            else:
                offline_urls.append((strLine, status))
        except requests.exceptions.RequestException as e:
            print(f"The url {strLine} failed: {e}\nMoving to investigate list.\n")
            investigate_urls.append(strLine)
    return online_urls, offline_urls, investigate_urls

online_urls, offline_urls, investigate_urls = urlStatusTest()

### The Output file readable all results
date = datetime.datetime.now()
with open("ResultsStatusFilter.txt", "w") as f:
    f.write(f"====================\n{date}\n====================\n\n")
    f.write("====================\nOnline URLs\n====================\n\nAPI|URL:\n")
    for url, status in online_urls:
        f.write(f"[{status}] {url}\n")
    f.write("\n====================\nInvestigate URLs\n====================\n\nAPI|URL:\n")
    for url in investigate_urls:
        f.write(f"{url}\n")
    f.write("\n====================\nOffline URLs\n====================\n\nAPI|URL:\n")
    for url, status in offline_urls:
        f.write(f"[{status}] {url}\n")

# The Output file only the online URLs
with open("UrlsStatusFilter.txt", "w") as f:
    for url, status in online_urls:
        f.write(f"{url}\n")

# The Output file only for the investigate URLs in case they are actually live
with open("UrlsInvestigateStatusFilter.txt", "w") as f:
    for url in investigate_urls:
        f.write(f"{url}\n")

print("\nResults have been saved.")
