# Secrets in Plain Sight

**Category:** App Sec  
**Difficulty:** Easy  
**Points:** 150  

## Challenge Description

### One APK, Two Headaches

Too lazy to download another APK?
Don't worry, we got you - there's another flag hidden in the same one.
Dig deeper. Cry harder. 

Real devs don't use secret files — they hardcode everything.
Why hide when you can commit your secrets like a legend?

Just go through my code and get the flag.
But oops… you don't have the codebase.

[Download APK](/appsec/pbctf.apk)

## Solution Path

1. **Extract and Locate Binary Files**
   
   After extracting the APK (as shown in [part 1](/appsec/No_hint_just_APK/README.md)), search for binary files that might contain hardcoded strings:
   
   ```sh
   cd appsec/
   ```

2. **Search Through Binary Files**
   
   Use the `strings` command to extract readable text from binary files and search for the flag pattern:
   
   ```sh
   strings lib/arm64-v8a/libapp.so | grep "pbctf{" 
   ```

3. **Find the Flag**
   
   The flag should be visible in the output of the strings command, as it was hardcoded into the binary files during compilation.

