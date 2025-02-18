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
#include "frontend.h"

#include "frontend_util.h"
#include "tensorflow/lite/micro/testing/micro_test.h"

namespace {

const int kSampleRate = 1000;
const int kWindowSamples = 25;
const int kStepSamples = 10;
const int16_t kFakeAudioData[] = {
    0, 32767, 0, -32768, 0, 32767, 0, -32768, 0, 32767, 0, -32768,
    0, 32767, 0, -32768, 0, 32767, 0, -32768, 0, 32767, 0, -32768,
    0, 32767, 0, -32768, 0, 32767, 0, -32768, 0, 32767, 0, -32768};

// Test end-to-end frontend behaviors.
class FrontendTestConfig {
public:
  FrontendTestConfig() {
    config_.window.size_ms = 25;
    config_.window.step_size_ms = 10;
    config_.noise_reduction.smoothing_bits = 10;
    config_.filterbank.num_channels = 2;
    config_.filterbank.lower_band_limit = 8.0;
    config_.filterbank.upper_band_limit = 450.0;
    config_.noise_reduction.smoothing_bits = 10;
    config_.noise_reduction.even_smoothing = 0.025;
    config_.noise_reduction.odd_smoothing = 0.06;
    config_.noise_reduction.min_signal_remaining = 0.05;
    config_.pcan_gain_control.enable_pcan = true;
    config_.pcan_gain_control.strength = 0.95;
    config_.pcan_gain_control.offset = 80.0;
    config_.pcan_gain_control.gain_bits = 21;
    config_.log_scale.enable_log = true;
    config_.log_scale.scale_shift = 6;
  }

  struct FrontendConfig config_;
};

} // namespace

TF_LITE_MICRO_TESTS_BEGIN

TF_LITE_MICRO_TEST(FrontendTest_CheckOutputValues) {
  FrontendTestConfig config;
  struct FrontendState state;
  TF_LITE_MICRO_EXPECT(
      FrontendPopulateState(&config.config_, &state, kSampleRate));
  size_t num_samples_read;

  struct FrontendOutput output = FrontendProcessSamples(
      &state, kFakeAudioData,
      sizeof(kFakeAudioData) / sizeof(kFakeAudioData[0]), &num_samples_read);

  const uint16_t expected[] = {479, 425};
  TF_LITE_MICRO_EXPECT_EQ(output.size, sizeof(expected) / sizeof(expected[0]));
  for (size_t i = 0; i < output.size; ++i) {
    TF_LITE_MICRO_EXPECT_EQ(output.values[i], expected[i]);
  }

  FrontendFreeStateContents(&state);
}

TF_LITE_MICRO_TEST(FrontendTest_CheckConsecutiveWindow) {
  FrontendTestConfig config;
  struct FrontendState state;
  TF_LITE_MICRO_EXPECT(
      FrontendPopulateState(&config.config_, &state, kSampleRate));
  size_t num_samples_read;

  FrontendProcessSamples(&state, kFakeAudioData,
                         sizeof(kFakeAudioData) / sizeof(kFakeAudioData[0]),
                         &num_samples_read);
  struct FrontendOutput output = FrontendProcessSamples(
      &state, kFakeAudioData + kWindowSamples,
      sizeof(kFakeAudioData) / sizeof(kFakeAudioData[0]) - kWindowSamples,
      &num_samples_read);

  const int16_t expected[] = {436, 378};
  TF_LITE_MICRO_EXPECT_EQ(output.size, sizeof(expected) / sizeof(expected[0]));
  for (size_t i = 0; i < output.size; ++i) {
    TF_LITE_MICRO_EXPECT_EQ(output.values[i], expected[i]);
  }

  FrontendFreeStateContents(&state);
}

TF_LITE_MICRO_TEST(FrontendTest_CheckNotEnoughSamples) {
  FrontendTestConfig config;
  struct FrontendState state;
  TF_LITE_MICRO_EXPECT(
      FrontendPopulateState(&config.config_, &state, kSampleRate));
  size_t num_samples_read;

  FrontendProcessSamples(&state, kFakeAudioData,
                         sizeof(kFakeAudioData) / sizeof(kFakeAudioData[0]),
                         &num_samples_read);
  FrontendProcessSamples(&state, kFakeAudioData + kWindowSamples,
                         sizeof(kFakeAudioData) / sizeof(kFakeAudioData[0]) -
                             kWindowSamples,
                         &num_samples_read);
  struct FrontendOutput output = FrontendProcessSamples(
      &state, kFakeAudioData + kWindowSamples + kStepSamples,
      sizeof(kFakeAudioData) / sizeof(kFakeAudioData[0]) - kWindowSamples -
          kStepSamples,
      &num_samples_read);

  TF_LITE_MICRO_EXPECT_EQ(output.size, 0u);
  TF_LITE_MICRO_EXPECT(output.values == nullptr);

  FrontendFreeStateContents(&state);
}

TF_LITE_MICRO_TESTS_END
