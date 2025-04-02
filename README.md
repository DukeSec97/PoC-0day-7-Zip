# PoC-0day-7-Zip

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
