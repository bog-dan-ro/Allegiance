//////////////////////////////////////////////////////////////////////////////
//
// PCH.H
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _PCH_H_
#define _PCH_H_

// __MODULE__ is used by ZAssert
#define __MODULE__ "EngineApp"

//////////////////////////////////////////////////////////////////////////////
//
// Disable some warnings
//
//////////////////////////////////////////////////////////////////////////////

// conversion from 'float' to 'int', possible loss of data
//#pragma warning(disable : 4244)

// 'this' : used in base member initializer list
#pragma warning(disable : 4355)

// identifier was truncated to '255' characters in the debug information
#pragma warning(disable : 4786)


//////////////////////////////////////////////////////////////////////////////
//
// The include files
//
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "windows.h"

#include <base.h>
#include <zassert.h>
#include <ztime.h>
#include <tref.h>
#include <zstring.h>
#include <token.h>

#include "engine.h"
#include "effect.h"
#include <geometry.h>
#include <frameimage.h>
#include <D3DDevice9.h>
#include <LogFile.h>
#include <VertexGenerator.h>

#endif
