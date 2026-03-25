"""
This python code is supposed to test which URL/APIs are online/offline 
Created By: JarryBarry
"""

import requests
import urllib3
import random
import time
from pathlib import Path

# Suppress SSL Verification Warnings
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

def logmsg(label, message):
    # Print Message With Severity Label
    print(f"[{label}] {message}")

# --- Input ---
input_file = input("Enter a file with URLs/APIs:\n").strip()
output_file = "Results.txt"

# Convert String To Integer Safely
try:
    base_ms = int(input("Enter sleep time in milliseconds:\n").strip())
except (ValueError, TypeError):
    base_ms = 500

jitter_ms = 5

# Check If Path Exists
if not Path(input_file).exists():
    logmsg("!", f"File not found: {input_file}")
    exit(1)

# Read Lines From File Into List
with open(input_file, "r") as f:
    items = f.read().splitlines()

# Create Empty Named Lists
online = []
offline = []
errors = []

total = len(items)
for i, item in enumerate(items, start=1):
    # Strip Whitespace From String
    item = item.strip()
    if not item:
        continue

    # Pause With Randomized Delay
    delay = base_ms / 1000
    jitter = random.random() * jitter_ms / 1000
    time.sleep(delay + jitter)

    # Catch Exception And Continue Loop
    try:
        # Send GET Request With Timeout (HEAD variant)
        response = requests.head(item, timeout=5, verify=False)

        # Append Item To List By Condition
        if 200 <= response.status_code < 300:
            online.append(f"{response.status_code} {item}")
            logmsg("+", f"{response.status_code} {item}")
        else:
            offline.append(f"{response.status_code} {item}")
            logmsg("-", f"{response.status_code} {item}")

    except requests.exceptions.RequestException as e:
        errors.append(f"{item} : {e}")
        logmsg("!", f"{item} : {e}")

    # Track Iteration Count In Loop
    print(f"[*] {i}/{total} ", end="\r")

print()

# Write Grouped Lists To File With Section Headers
with open(output_file, "w") as f:
    sections = [
        ("Online", online),
        ("Offline", offline),
        ("Errors", errors),
    ]
    for header, group in sections:
        f.write(f"=== {header} ({len(group)}) ===\n")
        for entry in group:
            f.write(f"{entry}\n")
        f.write("\n")

logmsg("+", f"Results written to {output_file}")
