# No hints. No clues.

**Category:** App Sec
**Difficulty:** Easy  
**Points:** 150  

## Challenge Description

Just install the APK and suffer.
iPhone users? Sorry boss, not your game.

[Download APK](/appsec/pbctf.apk)

## Solution Path

1. **Convert APK to ZIP**
   
   APK files are just ZIP archives. Rename the file extension to `.zip`:
   
   ```sh
   mv pbctf.apk pbctf.zip
   ```
   
2. **Extract the ZIP Archive**
   
   Unzip the file to view its contents:
   
   ```sh
   unzip pbctf.zip -d appsec/
   ```
   
3. **Search for the Flag**
   
   The challenge hints at secret files, specifically `.env`. You can search for the flag using `grep`:
   
   ```sh
   grep -r "pbctf{" appsec/
   ```
   
   Or, locate `.env` files directly:
   
   ```sh
   find appsec/ -name ".env"
   cat appsec/path/to/.env
   ```
   
   The flag will be present in the `.env` file inside the extracted folder.
