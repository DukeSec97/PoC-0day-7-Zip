# PoC-0day-7-Zip
1. Save the code to a file: For example, generate_7z.c.

2. Compile with GCC:

gcc generate_7z.c -o generate_7z

3. Run the program:

./generate_7z

4. Check the generated file:

ls -l crafted.7z


Build and run the PoC:

bash

Copy

Edit

gcc poc.c -o poc
./poc

Then test with a vulnerable decompression tool:

bash

Copy

Edit

7z x crafted.7z
# or
some_app_that_uses_7z crafted.7z
Expected result: Crash, segmentation fault, or heap corruption.
