#pragma once

#include <windows.h>

#include <string>
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <deque>
#include <mutex>
#include <shared_mutex>
#include <any>
#include <array>
#include <chrono>
#include <directxmath.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "../../Dependencies/imgui/imgui.h"
#include "../../Dependencies/imgui/imgui_internal.h"
#include "../../Dependencies/imgui/imgui_impl_dx9.h"
#include "../../Dependencies/imgui/imgui_impl_win32.h"

#include "../../Utilities/Memory.hpp"
#include "../../Utilities/Print.hpp"

using namespace std::chrono_literals;