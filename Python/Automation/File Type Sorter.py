import os
import shutil

def organize_files_by_type(directory):
    if not os.path.isdir(directory):
        print(f"The directory '{directory}' does not exist.")
        return

    print(f"Organizing files in: {directory}")

    # List all items in the directory
    items = os.listdir(directory)

    folders_created = set()

    for item in items:
        item_path = os.path.join(directory, item)

        # Skip if it's a directory
        if os.path.isdir(item_path):
            continue

        # Skip files without an extension
        if '.' not in item or item.startswith('.'):
            continue

        # Get the file extension (without the dot)
        file_extension = item.split('.')[-1]

        # Folder name based on extension
        folder_name = file_extension
        folder_path = os.path.join(directory, folder_name)

        # Create folder if it doesn't exist
        if not os.path.exists(folder_path):
            os.makedirs(folder_path)
            folders_created.add(folder_name)

        # Move the file to the corresponding folder
        shutil.move(item_path, os.path.join(folder_path, item))
        print(f"Moved: {item} → {folder_name}/")

    if folders_created:
        print("\nFolders created:")
        for folder in folders_created:
            print(f"- {folder}")
    else:
        print("\nNo new folders were created.")

if __name__ == "__main__":
    # You can change this to a specific path or use input() to prompt the user
    directory = input("Enter the path to the directory to organize: ").strip()
    organize_files_by_type(directory)
