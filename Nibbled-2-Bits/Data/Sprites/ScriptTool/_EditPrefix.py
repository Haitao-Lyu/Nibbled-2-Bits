import os

folder_path = os.path.dirname(os.path.abspath(__file__))  # Get the absolute path to the folder containing the script
prefix_choice = input("Enter 'add' or 'remove' to add or remove prefix: \n")

if prefix_choice == "add" or prefix_choice == "remove" :
    prefix = input("Enter the prefix you want to add or remove: \n")
    for filename in os.listdir(folder_path):
        if filename.endswith(".png"):
            if prefix_choice == "remove":
                if filename.startswith(prefix):
                    old_path = os.path.join(folder_path, filename)
                    new_path = os.path.join(folder_path, filename[len(prefix):])
                    os.rename(old_path, new_path)
                    print("remove prefix:", prefix, " successful")
            else:
                old_path = os.path.join(folder_path, filename)
                new_path = os.path.join(folder_path, prefix + filename)
                os.rename(old_path, new_path)
                print("Add prefix:", prefix, " successful")
else:
    print("invalid input\n")