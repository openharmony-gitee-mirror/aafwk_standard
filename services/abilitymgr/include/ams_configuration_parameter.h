/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef OHOS_AAFWK_AMS_CONFIGURATION_PARAMETER_H
#define OHOS_AAFWK_AMS_CONFIGURATION_PARAMETER_H

#include <fstream>
#include <nlohmann/json.hpp>

namespace OHOS {
namespace AAFwk {
namespace AmsConfig {
namespace MemThreshold {
const std::string HOME_APP("home_application");
}
const std::string AMS_CONFIG_FILE_PATH {"/system/etc/ams_service_config.json"};
const std::string SERVICE_ITEM_AMS {"service_startup_config"};
const std::string STARTUP_LAUNCHER {"startup_launcher"};
const std::string STARTUP_STATUS_BAR {"startup_system_ui_status_bar"};
const std::string STARTUP_NAVIGATION_BAR {"startup_system_ui_navigation_bar"};
const std::string STARTUP_PHONE_SERVICE {"startup_phone_service"};
const std::string MISSION_SAVE_TIME {"mission_save_time"};
}  // namespace AmsConfig

enum class SatrtUiMode { STATUSBAR = 1, NAVIGATIONBAR = 2, STARTUIBOTH = 3 };

class AmsConfigurationParameter final {
public:
    AmsConfigurationParameter() = default;
    ~AmsConfigurationParameter() = default;
    /**
     * return true : ams no config file
     * return false : ams have config file
     */
    bool NonConfigFile() const;
    /**
     * return true : ams can start launcher
     * return false : ams do not start launcher
     */
    bool GetStartLauncherState() const;
    /**
     * return true : ams can start system ui status bar
     * return false : ams do not start system ui status bar
     */
    bool GetStatusBarState() const;
    /**
     * return true : ams can start system ui navigation bar
     * return false : ams do not start system ui navigation bar
     */
    bool GetNavigationBarState() const;
    /**
     * return true : ams can start phone service
     * return false : ams do not start phone service
     */
    bool GetPhoneServiceState() const;
    /**
     * Get profile information
     */
    void Parse();

    /**
     * The low memory threshold under which the system will kill background processes
     */
    int GetMemThreshold(const std::string &key);

    int GetMissionSaveTime() const;

    enum { READ_OK = 0, READ_FAIL = 1, READ_JSON_FAIL = 2 };

private:
    /**
     * Read the configuration file of ams
     *
     */
    int LoadAmsConfiguration(const std::string &filePath);
    int LoadAppConfigurationForStartUpService(nlohmann::json& Object);
    int LoadAppConfigurationForMemoryThreshold(nlohmann::json& Object);

private:
    bool nonConfigFile_ {false};
    bool canStartLauncher_ {false};
    bool canStartUiStatusBar_ {false};
    bool canStartUiNavigationBar_ {false};
    bool canStartPhoneService_ {false};
    int missionSaveTime_ {12 * 60 * 60 * 1000};
    std::map<std::string, std::string> memThreshold_;
};
}  // namespace AAFwk
}  // namespace OHOS
#endif  // OHOS_AAFWK_AMS_CONFIGURATION_PARAMETER_H
