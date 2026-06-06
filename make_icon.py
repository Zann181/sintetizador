import sys
from PIL import Image, ImageOps, ImageDraw

try:
    img = Image.open('Logo.png').convert('RGBA')
except Exception as e:
    print(f"Error opening image: {e}")
    sys.exit(1)

r, g, b, a = img.split()
rgb_img = Image.merge('RGB', (r, g, b))
inverted_rgb = ImageOps.invert(rgb_img)
r2, g2, b2 = inverted_rgb.split()
img_inverted = Image.merge('RGBA', (r2, g2, b2, a))

size = max(img.size)
padded_size = int(size * 1.2)
bg = Image.new('RGBA', (padded_size, padded_size), (0, 0, 0, 0))
draw = ImageDraw.Draw(bg)

circle_color = (20, 20, 20, 255)
draw.ellipse((0, 0, padded_size, padded_size), fill=circle_color)

offset = ((padded_size - img.size[0]) // 2, (padded_size - img.size[1]) // 2)
bg.paste(img_inverted, offset, mask=img_inverted)

bg.thumbnail((256, 256), Image.Resampling.LANCZOS)

bg.save('icon_bazz.ico', format='ICO')
print("Successfully generated icon_bazz.ico")
