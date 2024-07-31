First github project, and first time using the c programming language :D

Commands / websites im using:
openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program oled_display.elf verify reset exit"
make
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
https://tomeko.net/online_tools/file_to_hex.php?lang=en