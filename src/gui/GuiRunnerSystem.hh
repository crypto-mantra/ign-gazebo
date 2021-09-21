/*
 * Copyright (C) 2019 Open Source Robotics Foundation
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
 *
 */

#ifndef IGNITION_GAZEBO_GUI_GUIRUNNERSYSTEM_HH_
#define IGNITION_GAZEBO_GUI_GUIRUNNERSYSTEM_HH_

#include <memory>
#include <set>
#include <string>

#include <ignition/utils/ImplPtr.hh>

#include "ignition/gazebo/config.hh"
#include "ignition/gazebo/EntityComponentManager.hh"
#include "ignition/gazebo/EventManager.hh"
#include "ignition/gazebo/gui/Export.hh"
#include "ignition/gazebo/System.hh"

namespace ignition
{
namespace gazebo
{

class GuiRunnerSystem:
  public System,
  public ISystemConfigure,
  public ISystemPreUpdate,
  public ISystemPostUpdate
{
  public: GuiRunnerSystem();

  public: ~GuiRunnerSystem();

  public: void WorldName(const std::string &_worldName);

  public: std::string WorldName() const;

  public: void OnPluginAdded(const std::string &_objectName);

  // Documentation inherited
  public: void Configure(const Entity &_entity,
                         const std::shared_ptr<const sdf::Element> &_sdf,
                         EntityComponentManager &_ecm,
                         EventManager &_eventMgr) final;

  // Documentation inherited
  public: void PreUpdate(const UpdateInfo &_info,
                         EntityComponentManager &_ecm) final;

  // Documentation inherited
  public: void PostUpdate(const UpdateInfo &_info,
              const EntityComponentManager &_ecm) final;

  /// \brief Pointer to private data.
  IGN_UTILS_UNIQUE_IMPL_PTR(dataPtr)

};
}  // namespace gazebo
}  // namespace ignition
#endif  // IGNITION_GAZEBO_GUI_GUIRUNNERSYSTEM_HH_