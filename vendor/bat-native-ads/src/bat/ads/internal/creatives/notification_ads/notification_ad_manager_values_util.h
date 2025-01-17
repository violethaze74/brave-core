/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_MANAGER_VALUES_UTIL_H_
#define BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_MANAGER_VALUES_UTIL_H_

#include "base/containers/circular_deque.h"
#include "base/values.h"

namespace ads {

struct NotificationAdInfo;

base::circular_deque<NotificationAdInfo> NotificationAdsFromValue(
    const base::Value::List& list);
base::Value::List NotificationAdsToValue(
    const base::circular_deque<NotificationAdInfo>& ads);

}  // namespace ads

#endif  // BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_CREATIVES_NOTIFICATION_ADS_NOTIFICATION_AD_MANAGER_VALUES_UTIL_H_
