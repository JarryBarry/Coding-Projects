"""
Filter fake 200 responses by detecting known error page signatures
in the response body using both decoded text and raw byte matching.
Created By: JarryBarry
"""

import requests
import time
import random
import urllib3

# --- Suppress SSL Warnings ---
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

# --- Input ---
input_file = input("Enter a file with URLs|APIs:\n")
signature = input("Enter the error message of the body:\n")

if not signature:
    signature = "edp[oihugvb nmjhunmlkjoi23u42klwem,dsc vbhjkdsalxz.,lc;]"

base_ms = int(input("Enter the amount of time you want the program to sleep in milliseconds:\n"))
jitter_ms = 5

# --- Load Targets ---
with open(input_file, "r") as f:
    items = f.read().splitlines()

# --- Classification ---
def classify(items, signature, base_ms, jitter_ms):
    passed = []
    failed = []
    review = []

    total = len(items)
    for i, item in enumerate(items, start=1):
        try:
            # delay with jitter
            delay = base_ms / 1000
            jitter = random.random() * jitter_ms / 1000
            time.sleep(delay + jitter)

            # request
            response = requests.get(item, timeout=5, verify=False)

            # match signature
            text_match = signature.lower() in response.text.lower()
            byte_match = signature.encode() in response.content
            is_match = text_match or byte_match

            # route to bucket
            if is_match:
                failed.append(item)
            else:
                passed.append(item)

        except requests.exceptions.RequestException as e:
            review.append(item)
            print(f"[!] {item}: {e}")

        # progress
        print(f"[*] {i}/{total}   ", end="\r")

    print()
    return passed, failed, review

passed, failed, review = classify(items, signature, base_ms, jitter_ms)

# --- Grouped Report ---
with open("ResultsErrorPageFilter.txt", "w") as f:
    sections = [
        ("Passed", passed),
        ("Review", review),
        ("Failed", failed),
    ]
    for header, group in sections:
        f.write(f"=== {header} ({len(group)}) ===\n")
        for item in group:
            f.write(f"{item}\n")
        f.write("\n")

# --- Flat Output: Passed Only ---
with open("UrlsErrorPageFilter.txt", "w") as f:
    for item in passed:
        f.write(f"{item}\n")

# --- Flat Output: Review Only ---
with open("InvestigateErrorPageFilter.txt", "w") as f:
    for item in review:
        f.write(f"{item}\n")