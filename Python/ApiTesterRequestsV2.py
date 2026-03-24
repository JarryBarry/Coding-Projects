##This python code is supposed to filter fake 200 OK pages from real ones using error signatures
#Created By: JarryBarry
#V3 includes evidence logging, multi-signature support, and classified failure reasons

import requests
import time
import random
import sys
import urllib3

urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning) #Stop SSL from being displayed constantly

#----------------------------------------------------------
# Input Functions
#----------------------------------------------------------

def load_urls(filepath):
    #Load URLs from file, skip empty lines
    try:
        with open(filepath, "r") as file:
            urls = [line.strip() for line in file.readlines() if line.strip()]
        if not urls:
            print("Error: URL file is empty. Cannot continue.")
            sys.exit(1)
        return urls
    except FileNotFoundError:
        print(f"Error: URL file '{filepath}' not found. Cannot continue.")
        sys.exit(1)

def load_signatures():
    #Get error signatures — either a single string or a file of signatures
    error = input('Enter the error message of the body (or leave blank to load from file): \n')
    if error.strip():
        return [error.strip()]

    sig_file = input('Enter a file containing error signatures (one per line): \n')
    if not sig_file.strip():
        print("Error: No signature provided and no signature file given. Cannot continue.")
        sys.exit(1)

    try:
        with open(sig_file.strip(), "r") as f:
            signatures = [line.strip() for line in f.readlines() if line.strip()]
        if not signatures:
            print("Error: Signature file is empty. Cannot continue.")
            sys.exit(1)
        return signatures
    except FileNotFoundError:
        print(f"Error: Signature file '{sig_file.strip()}' not found. Cannot continue.")
        sys.exit(1)

#----------------------------------------------------------
# Processing Functions
#----------------------------------------------------------

def fetch_url(url, delay):
    #Fetch a single URL with jitter delay, return response or exception
    time.sleep(delay)
    try:
        response = requests.get(url, verify=False, timeout=5)
        return response, None
    except requests.exceptions.RequestException as e:
        return None, e

def detect_signature(response, signatures):
    #Check if any signature matches in response body (text + bytes, case-insensitive text)
    for sig in signatures:
        text_match = sig.lower() in response.text.lower()
        byte_match = sig.encode() in response.content
        if text_match or byte_match:
            return sig
    return None

def classify_failure(e):
    #Return a human-readable failure reason from exception type
    if isinstance(e, requests.exceptions.SSLError):
        return "SSL Error"
    elif isinstance(e, requests.exceptions.Timeout):
        return "Timeout"
    elif isinstance(e, requests.exceptions.TooManyRedirects):
        return "Too Many Redirects"
    elif isinstance(e, requests.exceptions.ConnectionError):
        return "Connection Error"
    else:
        return f"Request Exception: {e}"

def classify_urls(urls, signatures, delay):
    #Classify each URL as real, fake, or investigate — with evidence
    real_urls = []        #(url, status_code)
    fake_urls = []        #(url, matched_signature, status_code)
    investigate_urls = [] #(url, failure_reason)
    for url in urls:
        response, error = fetch_url(url, delay)
        if error:
            reason = classify_failure(error)
            print(f"[FAILED] {url} — {reason}")
            investigate_urls.append((url, reason))
            continue
        matched = detect_signature(response, signatures)
        if matched:
            fake_urls.append((url, matched, response.status_code))
        else:
            real_urls.append((url, response.status_code))
    return real_urls, fake_urls, investigate_urls

#----------------------------------------------------------
# Output Functions
#----------------------------------------------------------

def write_outputs(real_urls, fake_urls, investigate_urls):
    #Write all three output files with evidence

    ###The Output file readable all results
    with open("ResultsErrorPageFilter.txt", "w") as f:
        f.write("====================\nReal URLs\n====================\n\nAPI|URL:\n")
        for url, status in real_urls:
            f.write(f"[{status}] {url}\n")
        f.write("\n====================\nInvestigate URLs\n====================\n\nAPI|URL:\n")
        for url, reason in investigate_urls:
            f.write(f"{url} — Reason: {reason}\n")
        f.write("\n====================\nFake URLs\n====================\n\nAPI|URL:\n")
        for url, sig, status in fake_urls:
            f.write(f"[{status}] {url} — Matched: \"{sig}\"\n")

    #The Output file only the real URLs
    with open("UrlsErrorPageFilter.txt", "w") as f:
        for url, status in real_urls:
            f.write(f"{url}\n")

    #The Output file only for the investigate URLs incase they are actually live
    with open("InvestigateErrorPageFilter.txt", "w") as f:
        for url, reason in investigate_urls:
            f.write(f"{url}\n")

#----------------------------------------------------------
# Main
#----------------------------------------------------------

urlApi = input('Enter a file with URLs|APIs: \n')
signatures = load_signatures()
timers = int(input('Enter the amount of time you want the program to sleep in milliseconds: \n'))
timers = (timers + random.random() * 5) / 1000 #To add a delay if the user wants it

urls = load_urls(urlApi)
print(f"\nLoaded {len(urls)} URLs and {len(signatures)} signature(s). Starting scan...\n")

real_urls, fake_urls, investigate_urls = classify_urls(urls, signatures, timers)
write_outputs(real_urls, fake_urls, investigate_urls)

print(f"\nDone. Real: {len(real_urls)} | Fake: {len(fake_urls)} | Investigate: {len(investigate_urls)}")
print("Results saved to ResultsErrorPageFilter.txt, UrlsErrorPageFilter.txt, InvestigateErrorPageFilter.txt")
