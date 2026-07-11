#include "test_framework.hpp"

#include "sony_head_tracker/macos_support.hpp"

using namespace sony;

TEST(macos_report_interval_uses_smallest_nonzero_valid_raw_value) {
    DescriptorField field;
    field.logicalMin = 0;
    field.logicalMax = 63;
    field.physicalMin = 10;
    field.physicalMax = 100;
    field.unitExponent = -3;
    const auto choice = chooseReportInterval(field);
    CHECK(choice.has_value());
    CHECK(choice->raw == 1);
    CHECK(choice->seconds >= 0.010);
    CHECK(choice->seconds <= 0.020);
}

TEST(macos_report_interval_rejects_degenerate_ranges) {
    DescriptorField field;
    CHECK(!chooseReportInterval(field).has_value());
    field.logicalMax = 10;
    field.physicalMin = 10;
    field.physicalMax = 10;
    CHECK(!chooseReportInterval(field).has_value());
}

TEST(macos_verified_device_selection_requires_usage_and_marker) {
    DeviceInfo device;
    device.usagePage = 0x20;
    device.usage = 0xE1;
    CHECK(!isVerifiedAndroidTracker(device));
    device.androidHeadTracker = true;
    CHECK(isVerifiedAndroidTracker(device));
    device.usage = 0xE2;
    CHECK(!isVerifiedAndroidTracker(device));
}

TEST(macos_reconnect_backoff_is_bounded) {
    CHECK(reconnectBackoffSeconds(0) == 1);
    CHECK(reconnectBackoffSeconds(1) == 2);
    CHECK(reconnectBackoffSeconds(2) == 5);
    CHECK(reconnectBackoffSeconds(3) == 10);
    CHECK(reconnectBackoffSeconds(4) == 30);
    CHECK(reconnectBackoffSeconds(1000) == 30);
}

TEST(macos_stream_recovery_never_forces_a_baseband_reconnect) {
    CHECK(streamRecoveryAction(1) == StreamRecoveryAction::refreshServices);
    CHECK(streamRecoveryAction(2) == StreamRecoveryAction::reopenHid);
    CHECK(streamRecoveryAction(1000) == StreamRecoveryAction::reopenHid);
}

TEST(macos_stream_reconnect_backoff_stays_short) {
    CHECK(streamReconnectBackoffSeconds(0) == 1);
    CHECK(streamReconnectBackoffSeconds(1) == 2);
    CHECK(streamReconnectBackoffSeconds(1000) == 2);
}

TEST(macos_reconnect_wait_wakes_on_bluetooth_or_hid_transition) {
    CHECK(trackerAvailabilityBecameReady(false, false, true, false));
    CHECK(trackerAvailabilityBecameReady(false, false, false, true));
    CHECK(trackerAvailabilityBecameReady(true, false, true, true));
    CHECK(!trackerAvailabilityBecameReady(true, true, true, true));
    CHECK(!trackerAvailabilityBecameReady(false, false, false, false));
}
