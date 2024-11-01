/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

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
#include "log_scale.h"

#include "log_scale_util.h"
#include "tensorflow/lite/micro/testing/micro_test.h"

namespace {

const int kScaleShift = 6;
const int kCorrectionBits = -1;

} // namespace

TF_LITE_MICRO_TESTS_BEGIN

TF_LITE_MICRO_TEST(LogScaleTest_CheckOutputValues) {
  struct LogScaleState state;
  state.enable_log = true;
  state.scale_shift = kScaleShift;

  uint32_t fake_signal[] = {3578, 1533};
  uint16_t *output = LogScaleApply(&state, fake_signal,
                                   sizeof(fake_signal) / sizeof(fake_signal[0]),
                                   kCorrectionBits);

  const uint16_t expected[] = {479, 425};
  for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i) {
    TF_LITE_MICRO_EXPECT_EQ(output[i], expected[i]);
  }
}

TF_LITE_MICRO_TEST(LogScaleTest_CheckOutputValuesNoLog) {
  struct LogScaleState state;
  state.enable_log = false;
  state.scale_shift = kScaleShift;

  uint32_t fake_signal[] = {85964, 45998};
  uint16_t *output = LogScaleApply(&state, fake_signal,
                                   sizeof(fake_signal) / sizeof(fake_signal[0]),
                                   kCorrectionBits);

  const uint16_t expected[] = {65535, 45998};
  for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i) {
    TF_LITE_MICRO_EXPECT_EQ(output[i], expected[i]);
  }
}

TF_LITE_MICRO_TESTS_END
