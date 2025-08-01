REM Give all arguments a more readable local variable name
Set compilerDir=%1
Set projectDir=%~2
Set imageDir=%~3
Set imageName=%~4
Set isDebug=%5

REM Local Variables
Set reset=[0m
Set cyan=[46m

if %isDebug%=="true" (
echo %cyan% NOTE: You have built in DEBUG mode, therefore a .hex file was not generated. If you would like to generate a .hex file, please build in production mode. For more information, please open MCC and click on the question mark symbol next to the 16-bit Bootloader Library under Resource Management. %reset%
exit 0
)

hexmate r0-47FF,"%projectDir%\%imageDir%\%imageName%" r4808-FFFFFFFF,"%projectDir%\%imageDir%\%imageName%" -O"%projectDir%\%imageDir%\temp_original_copy.X.production.hex" -FILL=w1:0x00,0x00,0x00,0x00@0x4800:0x4807
hexmate r4800-FFFFFFFF,"%projectDir%\%imageDir%\temp_original_copy.X.production.hex" -O"%projectDir%\%imageDir%\temp_crc.X.production.hex" -FILL=w1:0xFF,0xFF,0xFF,0x00@0x4800:0x2A7FF +-CK=4800-2A7FF@2A800w-4g5p814141AB
hexmate r2A800-2A801s-26000,"%projectDir%\%imageDir%\temp_crc.X.production.hex" r2A802-2A803s-25FFE,"%projectDir%\%imageDir%\temp_crc.X.production.hex" r4806-FFFFFFFF,"%projectDir%\%imageDir%\%imageName%" r4802-4803,"%projectDir%\%imageDir%\%imageName%" r0-47FF,"%projectDir%\%imageDir%\%imageName%" -O"%projectDir%\%imageDir%\%imageName%"
del "%projectDir%\%imageDir%\temp_original_copy.X.production.hex"
del "%projectDir%\%imageDir%\temp_crc.X.production.hex"