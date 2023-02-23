import os

# get the directory path of the script
script_dir = os.path.dirname(os.path.abspath(__file__))

# set the extension to filter by and the output filename
extension = ".png" # file extension to filter by, change this to the desired extension
output_filename = os.path.join(script_dir, os.path.splitext(os.path.basename(__file__))[0] + ".txt")

# get a list of all files in the directory that match the given extension
files = [filename for filename in os.listdir(script_dir) if filename.endswith(extension)]

# extract the filename without extension for each file
filenames = [os.path.splitext(filename)[0] for filename in files]

# save the list of filenames to a new text file in the same directory as the script
with open(output_filename, "w") as output_file:
    output_file.write("\n".join(filenames))