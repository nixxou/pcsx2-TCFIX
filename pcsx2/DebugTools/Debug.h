/*  Pcsx2 - Pc Ps2 Emulator
 *  Copyright (C) 2002-2008  Pcsx2 Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */


#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <zlib.h>
#include <string>

#include "Misc.h"

extern FILE *emuLog;

void disR5900F( std::string& output, u32 code, u32 pc);
void disR5900Fasm( std::string& output, u32 code, u32 pc);
char* disR3000Fasm(u32 code, u32 pc);

void  disR5900AddSym(u32 addr, const char *name);
const char* disR5900GetSym(u32 addr);
const char* disR5900GetUpperSym(u32 addr);
void  disR5900FreeSyms();
void dFindSym( std::string& output, u32 addr );

void strAppend( std::string& output, const char *fmt, ... );

char* disVU0MicroUF(u32 code, u32 pc);
char* disVU0MicroLF(u32 code, u32 pc);
char* disVU1MicroUF(u32 code, u32 pc);
char* disVU1MicroLF(u32 code, u32 pc);

char* disR3000AF(u32 code, u32 pc);

extern const char *CP2VFnames[];
extern const char *disRNameCP2f[];
extern const char *disRNameCP2i[];

// A helper class for getting a quick and efficient string representation of the
// R5900's current instruction.  This class is *not* thread safe!
class DisR5900CurrentState
{
protected:
	std::string result;

public:
	const char* getString();
};

extern DisR5900CurrentState disR5900Current;

//that way is slower but you now not need to compile every time ;P
#ifdef PCSX2_DEVBUILD

extern int Log;
extern u32 varLog;

void SourceLog( u16 protocol, u8 source, u32 cpuPc, u32 cpuCycle, const char *fmt, ...);
void __Log( const char* fmt, ... );

extern void SrcLog_CPU( const char* fmt, ... );
extern void SrcLog_COP0( const char* fmt, ... );
extern void SrcLog_FPU( const char* fmt, ... );
extern void SrcLog_MMI( const char* fmt, ... );

extern void SrcLog_MEM( const char* fmt, ... );
extern void SrcLog_HW( const char* fmt, ... );
extern void SrcLog_DMA( const char* fmt, ... );
extern void SrcLog_BIOS( const char* fmt, ... );
extern void SrcLog_ELF( const char* fmt, ... );
extern void SrcLog_VU0( const char* fmt, ... );

extern void SrcLog_VIF( const char* fmt, ... );
extern void SrcLog_SPR( const char* fmt, ... );
extern void SrcLog_GIF( const char* fmt, ... );
extern void SrcLog_SIF( const char* fmt, ... );
extern void SrcLog_IPU( const char* fmt, ... );
extern void SrcLog_VUM( const char* fmt, ... );
extern void SrcLog_RPC( const char* fmt, ... );
extern void SrcLog_EECNT( const char* fmt, ... );

extern void SrcLog_PSXCPU( const char* fmt, ... );
extern void SrcLog_PSXMEM( const char* fmt, ... );
extern void SrcLog_PSXHW( const char* fmt, ... );
extern void SrcLog_PSXBIOS( const char* fmt, ... );
extern void SrcLog_PSXDMA( const char* fmt, ... );
extern void SrcLog_PSXCNT( const char* fmt, ... );

extern void SrcLog_MEMCARDS( const char* fmt, ... );
extern void SrcLog_PAD( const char* fmt, ... );
extern void SrcLog_GTE( const char* fmt, ... );
extern void SrcLog_CDR( const char* fmt, ... );
extern void SrcLog_GPU( const char* fmt, ... );

#define CPU_LOG  if (varLog & 0x00000001) SrcLog_CPU
#define MEM_LOG  if (varLog & 0x00000002) SrcLog_MEM
#define HW_LOG   if (varLog & 0x00000004) SrcLog_HW
#define DMA_LOG  if (varLog & 0x00000008) SrcLog_DMA
#define BIOS_LOG if (varLog & 0x00000010) SrcLog_BIOS
#define ELF_LOG  if (varLog & 0x00000020) SrcLog_ELF
#define FPU_LOG  if (varLog & 0x00000040) SrcLog_FPU
#define MMI_LOG  if (varLog & 0x00000080) SrcLog_MMI
#define VU0_LOG  if (varLog & 0x00000100) SrcLog_VU0
#define COP0_LOG if (varLog & 0x00000200) SrcLog_COP0
#define VIF_LOG  if (varLog & 0x00000400) SrcLog_VIF
#define SPR_LOG  if (varLog & 0x00000800) SrcLog_SPR
#define GIF_LOG  if (varLog & 0x00001000) SrcLog_GIF
#define SIF_LOG  if (varLog & 0x00002000) SrcLog_SIF
#define IPU_LOG  if (varLog & 0x00004000) SrcLog_IPU
#define VUM_LOG  if (varLog & 0x00008000) SrcLog_VUM
#define RPC_LOG  if (varLog & 0x00010000) SrcLog_RPC
#define EECNT_LOG  if (varLog & 0x40000000) SrcLog_EECNT

#define PSXCPU_LOG  if (varLog & 0x00100000) SrcLog_PSXCPU
#define PSXMEM_LOG  if (varLog & 0x00200000) SrcLog_PSXMEM
#define PSXHW_LOG   if (varLog & 0x00400000) SrcLog_PSXHW
#define PSXBIOS_LOG if (varLog & 0x00800000) SrcLog_PSXBIOS
#define PSXDMA_LOG  if (varLog & 0x01000000) SrcLog_PSXDMA
#define PSXCNT_LOG  if (varLog & 0x20000000) SrcLog_PSXCNT

//memcard has the same number as PAD_LOG for now
#define MEMCARDS_LOG if (varLog & 0x02000000) SrcLog_MEMCARDS
#define PAD_LOG  if (varLog & 0x02000000) SrcLog_PAD
#define GTE_LOG  if (varLog & 0x04000000) SrcLog_GTE
#define CDR_LOG  if (varLog & 0x08000000) SrcLog_CDR
#define GPU_LOG  if (varLog & 0x10000000) SrcLog_GPU

// fixme - currently we don't log cache
#define CACHE_LOG 0&&

#else // PCSX2_DEVBUILD

#define varLog 0
#define Log 0

#define CPU_LOG  0&&
#define MEM_LOG  0&&
#define HW_LOG   0&&
#define DMA_LOG  0&&
#define BIOS_LOG 0&&
#define ELF_LOG  0&&
#define FPU_LOG  0&&
#define MMI_LOG  0&&
#define VU0_LOG  0&&
#define COP0_LOG 0&&
#define VIF_LOG  0&&
#define SPR_LOG  0&&
#define GIF_LOG  0&&
#define SIF_LOG  0&&
#define IPU_LOG  0&&
#define VUM_LOG  0&&
#define RPC_LOG  0&&

#define PSXCPU_LOG  0&&
#define PSXMEM_LOG  0&&
#define PSXHW_LOG   0&&
#define PSXBIOS_LOG 0&&
#define PSXDMA_LOG  0&&

#define PAD_LOG  0&&
#define GTE_LOG  0&&
#define CDR_LOG  0&&
#define GPU_LOG  0&&
#define PSXCNT_LOG 0&&
#define EECNT_LOG 0&&

#define EMU_LOG 0&&
#define CACHE_LOG 0&&
#define MEMCARDS_LOG 0&&
#endif

#ifdef VIFUNPACKDEBUG
#define VIFUNPACK_LOG VIF_LOG
#else
#define VIFUNPACK_LOG 0&&
#endif

#endif /* __DEBUG_H__ */
