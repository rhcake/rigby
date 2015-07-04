%module RigbyBridge

%{
#include <api/Rigby/AssetLoader.h>
#include <api/Rigby/Math/Matrix.h>
#include <api/Rigby/RawAsset.h>
#include <api/Rigby/Window.h>
%}

%include <C:/swig/Lib/windows.i>

%include "inc/api/Rigby/AssetLoader.h"

%nspace Math::Matrix;
namespace Math {
%include "inc/api/Rigby/Math/Matrix.h"
}

%include "inc/api/Rigby/RawAsset.h"

%include "inc/api/Rigby/Window.h"

