from PIL import Image
import os

# Directory containing images to stitch
directory = os.path.dirname(os.path.abspath(__file__))

# Find all image files in directory
files = [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]

# Find all unique prefixes in file names
prefixes = set([f.split("_")[0] for f in files])

# Loop through prefixes and stitch images with each prefix
for prefix in prefixes:

    # Find all image files with matching prefix
    files = [f for f in os.listdir(directory) if f.startswith(prefix) and f.endswith(".png")]

    # Sort files by index in file name
    files = sorted(files, key=lambda x: int(x.split('_')[-1].split('.')[0]))

    # Load first image to get dimensions
    image = Image.open(os.path.join(directory, files[0]))
    width, height = image.size

    # Create new image to contain stitched images with transparent background
    result = Image.new('RGBA', (width * len(files), height), (0, 0, 0, 0))

    # Loop through files and paste into result image
    for i, file in enumerate(files):
        filepath = os.path.join(directory, file)
        img = Image.open(filepath)
        result.paste(img, (i * width, 0), mask=img)

    # Save stitched image with transparent background
    result.save(os.path.join(directory, f"{prefix}_stitched.png"), format='png')
