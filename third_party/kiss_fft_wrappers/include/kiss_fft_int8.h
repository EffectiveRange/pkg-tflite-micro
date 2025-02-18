/* Copyright 2023 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#pragma once

#include "kiss_fft_common.h"
// Wrap floating point kiss fft in its own namespace. Enables us to link an
// application with different kiss fft resolutions
// (16/32 bit integer, float, double) without getting a linker error.
#define FIXED_POINT 8
namespace kiss_fft_fixed8 {
#include "kiss_fft.h"
#include "tools/kiss_fftr.h"
} // namespace kiss_fft_fixed8
#undef FIXED_POINT
