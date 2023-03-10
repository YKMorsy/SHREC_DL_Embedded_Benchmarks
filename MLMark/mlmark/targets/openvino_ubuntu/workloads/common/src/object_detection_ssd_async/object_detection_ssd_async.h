/*
// Copyright (c) 2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#pragma once

#include <string>
#include <vector>
#include <gflags/gflags.h>
#include <iostream>

#ifdef _WIN32
#include <os/windows/w_dirent.h>
#else
#include <dirent.h>
#endif

/// @brief message for help argument
static const char help_message[] = "Print a usage message.";

/// @brief message for images argument
static const char image_message[] = "Required. Path to an .bmp image.";

/// @brief message for plugin_path argument
static const char plugin_path_message[] = "Path to a plugin folder.";

/// @brief message for model argument
static const char model_message[] = "Required. Path to an .xml file with a trained model.";

/// @brief message for plugin argument
static const char plugin_message[] = "Plugin name. For example MKLDNNPlugin. If this parameter is pointed, " \
"the sample will look for this plugin only";

/// @brief message for assigning cnn calculation to device
static const char target_device_message[] = "Specify the target device to infer on; CPU, GPU, FPGA or MYRIAD is acceptable. " \
"Sample will look for a suitable plugin for device specified";

/// @brief message for performance counters
static const char performance_counter_message[] = "Enables per-layer performance report";

/// @brief message for iterations count
static const char iterations_count_message[] = "Number of iterations (default 1)";

/// @brief message for #threads for CPU inference
static const char infer_num_threads_message[] = "Optional. Number of threads to use for inference on the CPU "
                                                "(including Hetero cases).";

/// @brief message for clDNN custom kernels desc
static const char custom_cldnn_message[] = "Required for clDNN (GPU)-targeted custom kernels. "\
"Absolute path to the xml file with the kernels desc.";

/// @brief message for user library argument
static const char custom_cpu_library_message[] = "Required for MKLDNN (CPU)-targeted custom layers. " \
"Absolute path to a shared library with the kernels impl.";

// @brief message for CPU threads pinning option
static const char cpu_threads_pinning_message[] = "Optional. Enable (\"YES\"default) or disable (\"NO\")" \
                                                  "CPU threads pinning for CPU-involved inference.";
/// @brief message for plugin messages
static const char plugin_err_message[] = "Enables messages from a plugin";

/// @brief message for requests count
static const char ninfer_request_message[] = "Number of infer request for pipelined mode (default 1)";


/// \brief Define flag for showing help message <br>
DEFINE_bool(h, false, help_message);

/// \brief Define parameter for set image file <br>
/// It is a required parameter
DEFINE_string(i, "", image_message);

/// \brief Define parameter for set model file <br>
/// It is a required parameter
DEFINE_string(m, "", model_message);

/// \brief Define parameter for set path to plugins <br>
/// Default is ./lib
DEFINE_string(pp, "", plugin_path_message);

/// \brief device the target device to infer on <br>
DEFINE_string(d, "CPU", target_device_message);

/// \brief Enable per-layer performance report
DEFINE_bool(pc, false, performance_counter_message);

/// @brief Define parameter for clDNN custom kernels path <br>
/// Default is ./lib
DEFINE_string(c, "", custom_cldnn_message);

/// @brief Absolute path to CPU library with user layers <br>
/// It is a optional parameter
DEFINE_string(l, "", custom_cpu_library_message);

/// @brief Iterations count (default 1)
DEFINE_int32(ni, 1, iterations_count_message);

/// @brief Enable plugin messages
DEFINE_bool(p_msg, false, plugin_err_message);

/// @brief Enable plugin messages
DEFINE_string(pin, "YES", cpu_threads_pinning_message);

/// @brief Number of threads to use for inference on the CPU (also affects Hetero cases)
DEFINE_int32(nthreads, 0, infer_num_threads_message);

DEFINE_string(a, "", "Model name");
DEFINE_int32(b, 0, "Batch size");
DEFINE_string(aarch, "", "Architecture");
DEFINE_string(dir, "", "output_dir");
DEFINE_string(prec, "", "Precision");
DEFINE_string(r, "results.txt", "path to write latencies over iterations");

/// @brief Number of infer requests
DEFINE_int32(nireq, 1, ninfer_request_message);

/**
* \brief This function show a help message
*/
static void showUsage() {
    std::cout << std::endl;
    std::cout << "object_detection_sample_ssd [OPTION]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << std::endl;
    std::cout << "    -h                      " << help_message << std::endl;
    std::cout << "    -i \"<path>\"             " << image_message << std::endl;
    std::cout << "    -m \"<path>\"             " << model_message << std::endl;
    std::cout << "      -l \"<absolute_path>\"    " << custom_cpu_library_message << std::endl;
    std::cout << "          Or" << std::endl;
    std::cout << "      -c \"<absolute_path>\"    " << custom_cldnn_message << std::endl;
    std::cout << "    -pp \"<path>\"            " << plugin_path_message << std::endl;
    std::cout << "    -d \"<device>\"           " << target_device_message << std::endl;
    std::cout << "    -pc                     " << performance_counter_message << std::endl;
    std::cout << "    -ni \"<integer>\"         " << iterations_count_message << std::endl;
    std::cout << "    -p_msg                  " << plugin_err_message << std::endl;
    std::cout << "    -nireq \"<integer>\"      " << ninfer_request_message << std::endl;
    std::cout << "    Some CPU-specific performance options" << std::endl;
    std::cout << "    -nthreads \"<integer>\"   " << infer_num_threads_message << std::endl;
    std::cout << "    -pin \"YES\"/\"NO\"       " << cpu_threads_pinning_message << std::endl;
}
