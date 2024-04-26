#pragma once

const double kPI = 3.1415926;

const wchar_t kWindowClassName[] = L"Renderer Window Class";
const wchar_t kWindowTitle[] = L"Seaotter Renderer";

const unsigned int kInputBufferLimit = 16u;

const unsigned int kMainWindowWidth = 1366u;
const unsigned int kMainWindowHeight = 768u;
constexpr float kRenderRatio = static_cast<float>(kMainWindowWidth) / static_cast<float>(kMainWindowHeight);

const unsigned int kVSync = 0u;

const float kNearZ = 0.01f, kFarZ = 200.0f;

const unsigned int kMaxLight = 4u;