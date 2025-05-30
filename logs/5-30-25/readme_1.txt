bottom line is use sudo for everything



sudo hp-probe -busb

// Testpage printing
fjura@fjura:~$ sudo hp-testpage -i
warning: hp-testpage should not be run as root/superuser.

HP Linux Imaging and Printing System (ver. 3.21.12)
Testpage Print Utility ver. 6.0

Copyright (c) 2001-18 HP Development Company, LP
This software comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to distribute it
under certain conditions. See COPYING file for more details.

Printing test page to printer Main...
request id is Main-2 (1 file(s))
Test page has been sent to printer.

note: If an error occured, or the test page failed to print, refer to the HPLIP website
note: at: http://hplip.sourceforge.net for troubleshooting and support.


Done.
fjura@fjura:~$

[ Phone BLE ]           [ Phone Wi-Fi ]               [ Admin Panel ]
       |                       |                              |
       v                       v                              v
   [ ESP32 BLE ]        [ ESP32 Wi-Fi + UDP ]        [ ESP32 Web UI / OLED ]
         \                       |                         /
          \___ Trigger / Print Job Sender ___/
                          |
                       [ Raspberry Pi ]
                  CUPS Server (localhost only)
                  Handles print jobs
