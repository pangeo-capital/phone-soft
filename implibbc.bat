.\bin\implib -a .\lib\cache_db_lib.lib .\cache_db_lib.dll
.\bin\implib -a .\lib\rstrdp.lib .\rstrdp.dll

rem ?????
rem [Linker Error] Unresolved external 'ippsIIR16sLow_G729_16s' referenced from D:\ANDREY\RASTEL\BC\SIPCLIENTDESKTOP\IPP\G729\ENCG7291.OBJ
rem .\bin\implib -a .\lib\ipps-8.0.lib .\ipps-8.0.dll
rem .\bin\implib -a .\lib\ippsc-8.0.lib .\ippsc-8.0.dll

.\bin\implib -a .\lib\rsrtp.lib .\rsrtp.dll

copy d:\andrey\Rastel\VC\sipios\Release\sipios_port.dll .\*.*
copy d:\andrey\Rastel\VC\source\sip\sipios_c.* .\sipios\include\*.*
copy d:\andrey\Rastel\VC\source\sip\sipiosWrap*.* .\sipios\include\*.*
implib -a .\lib\sipios_port.lib .\sipios_port.dll

.\bin\implib -a .\lib\tls_sock.lib .\sosock-vc90-x86.dll


.\bin\implib -a .\lib\transmit_file_lib.lib .\transmit_file_lib.dll

.\bin\implib -a .\lib\vencdec.lib .\vencdec.dll
.\bin\implib -a .\lib\videoCam.lib .\videoCam.dll 
