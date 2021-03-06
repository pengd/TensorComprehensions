/**
 * Copyright (c) 2017-present, Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <string>
#include <vector>

#include <ATen/ATen.h>
#include <ATen/DLConvertor.h>
namespace tc {
namespace {
inline std::pair<std::vector<DLTensor*>, std::vector<DLManagedTensor*>>
toDlpackTensors(const std::vector<at::Tensor>& tensors) {
  std::vector<DLTensor*> dlTensors;
  std::vector<DLManagedTensor*> dlMTensors;
  for (auto tensor : tensors) {
    auto dlMTensor = at::toDLPack(tensor);
    dlTensors.push_back(&(dlMTensor->dl_tensor));
    dlMTensors.push_back(dlMTensor);
  }
  return make_pair(dlTensors, dlMTensors);
}

inline std::pair<std::vector<const DLTensor*>, std::vector<DLManagedTensor*>>
toConstDlpackTensors(const std::vector<at::Tensor>& tensors) {
  std::vector<const DLTensor*> dlTensors;
  std::vector<DLManagedTensor*> dlMTensors;
  for (auto tensor : tensors) {
    auto dlMTensor = at::toDLPack(tensor);
    dlTensors.push_back(&(dlMTensor->dl_tensor));
    dlMTensors.push_back(dlMTensor);
  }
  return make_pair(dlTensors, dlMTensors);
}

inline void deleteDlmTensors(std::vector<DLManagedTensor*>& tensors) {
  for (auto& tensor : tensors) {
    tensor->deleter(tensor);
  }
}
} // namespace
} // namespace tc
