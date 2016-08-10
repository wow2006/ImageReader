import os, sys
import PIL
from PIL import Image

size = (512 * 4, 512 * 4)

if len(sys.argv) > 1:
    image = Image.open(sys.argv[1])
    resizedImage = image.resize(size, PIL.Image.NEAREST)
    resizedImage.save("0-NEAREST.png")


    resizedImage = image.resize(size, PIL.Image.BILINEAR)
    resizedImage.save("1-BILINEAR.png")


    resizedImage = image.resize(size, PIL.Image.BICUBIC)
    resizedImage.save("2-BICUBIC.png")

    resizedImage = image.resize(size, PIL.Image.ANTIALIAS)
    resizedImage.save("3-ANTIALIAS.png")
