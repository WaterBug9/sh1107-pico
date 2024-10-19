First github project, and first time using the c programming language :D

# THIS HAS ONLY BEEN TEST ON A 1.5INCH BLACK AND WHITE SCREEN

# How to display images on the screen
The screen reads images from hex arrays, specifically hex arrays from .bmp images that are black and white.
You can convert a .bmp image to a hex array with this website: https://tomeko.net/online_tools/file_to_hex.php?lang=en
The .bmp image has to be black and white, and also mirrored horizontally.

# **Commands / websites im using:**

openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program oled_display.elf verify reset exit"

make

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..

https://tomeko.net/online_tools/file_to_hex.php?lang=en

