import os

folder_path = os.path.dirname(os.path.abspath(__file__))  # Get the absolute path to the folder containing the script
suffix_choice = input("Enter 'add' or 'remove' to add or remove suffix: \n")

if suffix_choice == "add" or suffix_choice == "remove" :
    suffix = input("Enter the suffix you want to add or remove: \n")
    for filename in os.listdir(folder_path):
        if filename.endswith(".png"):
            file_name_without_extension = os.path.splitext(filename)[0]
            if suffix_choice == "remove":
                if file_name_without_extension.endswith(suffix):
                    old_path = os.path.join(folder_path, filename)
                    new_path = os.path.join(folder_path, file_name_without_extension[:-len(suffix)] + ".png")
                    os.rename(old_path, new_path)
            else:
                old_path = os.path.join(folder_path, filename)
                new_path = os.path.join(folder_path, file_name_without_extension + suffix + ".png")
                os.rename(old_path, new_path)
else:
    print("invalid input\n")

