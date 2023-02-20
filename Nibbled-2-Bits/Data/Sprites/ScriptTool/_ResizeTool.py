from PIL import Image
import os

def resize_images(path, scaling_ratio):
    for filename in os.listdir(path):
        if filename.endswith('.png'):
            filepath = os.path.join(path, filename)
            with Image.open(filepath) as img:
                width, height = img.size
                new_width = int(width * scaling_ratio)
                new_height = int(height * scaling_ratio)
                img_resized = img.resize((new_width, new_height))
                img_resized.save(filepath)

# Usage example
path = os.path.dirname(os.path.abspath(__file__))
scaling_ratio = float(input("Type in the scale ratio:"))  # resizes to 50% of the original size
resize_images(path, scaling_ratio)
