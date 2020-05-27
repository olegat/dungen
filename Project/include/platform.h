//
//  platform.h
//  Dissert
//
//  Created by Olivier Legat on 08/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef PLATFORM_H_
#define PLATFORM_H_

#if defined (__WIN32__) || defined (_WIN32)
#	ifndef WINDOWS
#   define WINDOWS
#	define SHUT_UP_MSVC
#	endif
#	include <windows.h>
#	include <shlobj.h>
#elif defined (__APPLE_CC__) || defined (__APPLE__)
#	ifndef OSX
#   define OSX
#   endif
#endif

#ifdef SHUT_UP_MSVC
#	pragma warning (push)
#	pragma warning (disable: 4005)
#	pragma warning (disable: 4018)
#	pragma warning (disable: 4098)
#	pragma warning (disable: 4099)
#	pragma warning (disable: 4244)
#	pragma warning (disable: 4305)
#	pragma warning (disable: 4996)
#endif

/**
 * Standard C++ Includes
 */
#include <algorithm>
#include <assert.h>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

/**
 * Standard C++ Re-defines
 */
#define String std::string
#define Array std::vector
#define List std::list
#define Ifstream std::ifstream
#define Ofstream std::ofstream
#define Ostream std::ostream

/**
 * Addition C++ stuff
 */
#include <Object.h>
#define outln(x) std::cout<< (x) <<std::endl
#define interface class
#define extends :public
#define implements ,public


/**
 * Open GL + extensions
 */
#ifdef WINDOWS 
#	include <GL\GL.h>
#	include <GL\GLU.h>
#endif
#ifdef OSX 
#	include <OpenGL/gl.h>
#	include <OpenGL/glu.h>
#endif

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <soil/soil.h>

/**
 * GLM Defines
 */
#define Vector2 glm::vec2
#define Vector3 glm::vec3
#define Vector4 glm::vec4
#define Matrix4 glm::mat4
#define Matrix3 glm::mat3
#define Matrix2 glm::mat2
#define Quaternion glm::quat

#endif
