import os

script_name = os.path.basename(__file__)

def organize_directory(directory):
    try:
        if os.path.isdir(directory):
            os.chdir(directory)
            for i in os.listdir(directory):
                    if not os.path.isdir(i) and not i == script_name:
                        try:
                            extension = i.split(".")[-1]
                            if not os.path.isdir(extension):
                                os.mkdir(extension)
                            if os.path.exists(f"{extension}/{i}"):
                                print("File already exists in this location")
                            else:
                                os.rename(i, f"{extension}/{i}")
                            
                        except FileExistsError:
                            print(f"{i} is typeless it will not be moved to any folder")
    except FileNotFoundError:
        print("Invalid Directory")

directory = input("Enter the directory you want, in the format C:\Example\Location")
organize_directory(directory)
