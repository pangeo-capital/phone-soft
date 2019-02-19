	.686p
	ifdef ??version
	if    ??version GT 500H
	.mmx
	endif
	endif
	model flat
	ifndef	??version
	?debug	macro
	endm
	endif
	?debug	S "C:\asst\Sip_Client\pj_os.cpp"
	?debug	T "C:\asst\Sip_Client\pj_os.cpp"
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
_DATA	segment dword public use32 'DATA'
_DATA	ends
_BSS	segment dword public use32 'BSS'
_BSS	ends
DGROUP	group	_BSS,_DATA
_BSS	segment dword public use32 'BSS'
	align	4
_base_time	label	byte
	db	8	dup(?)
_BSS	ends
_TEXT	segment dword public use32 'CODE'
@pj_gettimeofday$qp11pj_time_val	segment virtual
	align	2
@@pj_gettimeofday$qp11pj_time_val	proc	near
?live16385@0:
@1:
	push      ebp
	mov       ebp,esp
	add       esp,-32
?live16385@16: ; EBX = tv
	cmp       dword ptr [_base_time+4],0
?live16385@32: ; 
	push      ebx
	mov       ebx,dword ptr [ebp+8]
?live16385@48: ; EBX = tv
	jne       short @2
	cmp       dword ptr [_base_time],0
	jne       short @2
	call      @@get_base_time$qv
?live16385@80: ; EBX = tv, EAX = status
	test      eax,eax
	jne       short @5
?live16385@96: ; EAX = status
@2:
	lea       eax,dword ptr [ebp-32]
	push      eax
	call      @GetLocalTime
?live16385@112: ; EBX = tv
	lea       edx,dword ptr [ebp-8]
	push      edx
	lea       ecx,dword ptr [ebp-32]
	push      ecx
	call      @SystemTimeToFileTime
	mov       eax,dword ptr [ebp-8]
	mov       dword ptr [ebp-16],eax
	mov       edx,dword ptr [ebp-4]
	mov       dword ptr [ebp-12],edx
	push      0
	push      10000000
	mov       eax,dword ptr [ebp-16]
	mov       edx,dword ptr [ebp-12]
	call      __lldiv
	mov       dword ptr [ebp-16],eax
	mov       dword ptr [ebp-12],edx
	mov       eax,dword ptr [_base_time]
	mov       edx,dword ptr [_base_time+4]
	sub       dword ptr [ebp-16],eax
	sbb       dword ptr [ebp-12],edx
	mov       ecx,dword ptr [ebp-16]
	mov       dword ptr [ebx],ecx
	movzx     eax,word ptr [ebp-18]
	mov       dword ptr [ebx+4],eax
?live16385@224: ; 
	xor       eax,eax
@6:
@5:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@@pj_gettimeofday$qp11pj_time_val	endp
@pj_gettimeofday$qp11pj_time_val	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
	align	4
@get_base_time$qv	proc	near
@@get_base_time$qv equ @get_base_time$qv
?live1@0:
@7:
	push      ebx
	add       esp,-24
	xor       ebx,ebx
?live1@32: ; EBX = status
	push      16
	push      0
	lea       eax,dword ptr [esp+16]
	push      eax
	call      @_memset
	add       esp,12
	mov       word ptr [esp+8],1970
	mov       word ptr [esp+10],1
	mov       word ptr [esp+14],1
	push      esp
	lea       edx,dword ptr [esp+12]
	push      edx
	call      @SystemTimeToFileTime
	mov       ecx,dword ptr [esp]
	mov       dword ptr [_base_time],ecx
	mov       eax,dword ptr [esp+4]
	mov       dword ptr [_base_time+4],eax
	push      0
	push      10000000
	mov       eax,dword ptr [_base_time]
	mov       edx,dword ptr [_base_time+4]
	call      __lldiv
	mov       dword ptr [_base_time],eax
	mov       dword ptr [_base_time+4],edx
	mov       eax,ebx
?live1@176: ; 
@9:
@8:
	add       esp,24
	pop       ebx
	ret 
@get_base_time$qv	endp
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@rdtsc$qv	segment virtual
	align	2
@@rdtsc$qv	proc	near
?live16386@0:
@10:
	RDTSC	
	RET	
@11:
@@rdtsc$qv	endp
@rdtsc$qv	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@pj_get_timestamp$qp12pj_timestamp	segment virtual
	align	2
@@pj_get_timestamp$qp12pj_timestamp	proc	near
?live16387@0:
@12:
	push      ebp
	mov       ebp,esp
	call      @@rdtsc$qv
	mov       ecx,dword ptr [ebp+8]
	mov       dword ptr [ecx],eax
	mov       dword ptr [ecx+4],edx
	xor       eax,eax
@14:
@13:
	pop       ebp
	ret 
@@pj_get_timestamp$qp12pj_timestamp	endp
@pj_get_timestamp$qp12pj_timestamp	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
@GetLocalTime equ GetLocalTime
 extrn   GetLocalTime:near
@SystemTimeToFileTime equ SystemTimeToFileTime
 extrn   SystemTimeToFileTime:near
 extrn   __lldiv:near
@_memset equ _memset
 extrn   _memset:near
 ?debug  C 9F757569642E6C6962
 ?debug  C 9F757569642E6C6962
 ?debug  C 9F76636C6535302E6C6962
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\SysConst.hpp" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\SysUtils.hpp" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\wintrust.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\sysvari.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\sysopen.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\sysdyn.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\systvar.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\sysset.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\syscomp.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\syscurr.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\systdate.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\systobj.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\wstring.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\sysmac.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\dstring.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\sysclass.H" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\basetyps.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\imm.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\mcx.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winsvc.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\commdlg.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\oleauto.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\propidl.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\oaidl.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\msxml.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\servprov.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\oleidl.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\urlmon.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\cguid.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\objidl.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\unknwn.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\search.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\stdlib.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\objbase.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\ole2.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\prsht.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winspool.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winsmcrd.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winioctl.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\rpcnsip.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\rpcndr.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\wtypes.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winscard.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winefs.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\wincrypt.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\qos.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winsock2.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winperf.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\shellapi.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\rpcasync.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\rpcnterr.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\rpcnsi.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\rpcdcep.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\rpcdce.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\rpc.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\nb30.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\mmsystem.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\lzexpand.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\dlgs.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\ddeml.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\dde.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\cderr.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winnetwk.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winreg.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winver.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\wincon.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winnls.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\tvout.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winuser.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\pshpack1.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\wingdi.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winerror.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winbase.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\pshpack8.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\pshpack2.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\poppack.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\pshpack4.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\_loc.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\locale.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\_str.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\string.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\guiddef.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\basetsd.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\mbctype.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\ctype.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\winnt.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\windef.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\stdarg.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\excpt.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\windows.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\sysmac.H" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\System.hpp" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\SysInit.hpp" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\Windows.hpp" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\VCL\CLASSES.HPP" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\_null.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\_defs.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\_stddef.h" 10303 8192
	?debug	D "C:\PROGRAM FILES (X86)\BORLAND\CBUILDER5\INCLUDE\mem.h" 10303 8192
	?debug	D "C:\asst\Sip_Client\pj_types.h" 18507 34373
	?debug	D "C:\asst\Sip_Client\pj_config.h" 18507 28231
	?debug	D "C:\asst\Sip_Client\PJ_OS.H" 18507 44473
	?debug	D "C:\asst\Sip_Client\pj_os.cpp" 18507 44273
	end
