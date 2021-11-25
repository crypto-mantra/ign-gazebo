/*
 * Copyright (C) 2021 Open Source Robotics Foundation
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
#include <pybind11/pybind11.h>

#include <memory>

#include "destroyable.hh"
#include "exceptions.hh"

namespace ignition
{
namespace gazebo
{
namespace python
{
Destroyable::Destroyable(const Destroyable &)
{
  // When a destroyable is copied, it does not matter if someone asked
  // to destroy the original. The copy has its own lifetime.
  use_count = 0;
  please_destroy_ = false;
}

void
Destroyable::Enter()
{
  if (please_destroy_) {
    throw InvalidHandle("cannot use Destroyable because destruction was requested");
  }
  ++use_count;
}

void
Destroyable::Exit(pybind11::object, pybind11::object, pybind11::object)
{
  if (0u == use_count) {
    throw std::runtime_error("Internal error: "
      "Destroyable use_count would be negative");
  }

  --use_count;
  if (please_destroy_ && 0u == use_count) {
    Destroy();
  }
}

void
Destroyable::Destroy()
{
  // Normally would be pure virtual, but then pybind11 can't
  // create bindings for this class
  throw std::runtime_error("Internal error : "
    "Destroyable subclass didn't override destroy()");
}

void
Destroyable::DestroyWhenNotInUse()
{
  if (please_destroy_) {
    // already asked to destroy
    return;
  }
  please_destroy_ = true;
  if (0u == use_count) {
    Destroy();
  }
}

void
define_destroyable(pybind11::object module)
{
  pybind11::class_<Destroyable, std::shared_ptr<Destroyable>>(
    module, "Destroyable")
  .def("__enter__", &Destroyable::Enter)
  .def("__exit__", &Destroyable::Exit)
  .def(
    "destroy_when_not_in_use",
    &Destroyable::DestroyWhenNotInUse,
    "Forcefully destroy the rcl object as soon as it's not actively "
    "being used");
}
}  // namespace python
}  // namespace utils
}  // namespace ignition
