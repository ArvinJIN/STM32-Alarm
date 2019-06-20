SET PATH=C:\Arvin\Keil\ARM\ARMCC\Bin;C:\Arvin\SecureCRT\;C:\Program Files (x86)\Parallels\Parallels Tools\Applications;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\bin;C:\Program Files (x86)\Git\cmd;C:\Program Files (x86)\Git\bin;C:\Users\arvin_jin\AppData\Local\Microsoft\WindowsApps;C:\Users\arvin_jin\go\bin;C:\Users\arvin_jin\AppData\Local\Programs\Microsoft VS Code\bin
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32F103ZE
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_stm32f10x_hd._ia"
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\main.__i"
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\delay.__i"
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\define.__i"
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\led.__i"
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\beep.__i"
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\lcd.__i"
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\rtc.__i"
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\touch.__i"
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\key.__i"
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\usart.__i"
"C:\Arvin\Keil\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\alarm.lnp"
"C:\Arvin\Keil\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\alarm.axf" --i32combined --output ".\Objects\alarm.hex"
