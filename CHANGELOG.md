# Changelog

All notable changes to this project are documented here. The format is based on
[Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and the project aims to
follow [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- **Accelerometer exposure.** Input reports are parsed for the standard HID
  sensor-page acceleration usages (`0x0452`–`0x0455`); when present they are
  emitted as the JSON `accelerometer` array and shown live in the GUI.
- **Explicit gyroscope field.** Angular velocity is now also parsed from the
  standard sensor-page usages (`0x0456`–`0x0459`) and emitted as `gyroscope`
  (rad/s). `angularVelocity` is retained as a deprecated alias.
- Bridge startup and the GUI now state exactly which UDP ports the data goes to.
- `docs/PROTOCOL.md` documenting the full UDP/JSON wire format.
- Open-source project scaffolding: contributing guide, code of conduct, issue
  and PR templates, `.editorconfig`, and a CI build workflow.

### Fixed
- **OpenTrack head rotation now works.** The OpenTrack UDP packet was sending the
  head angles in the translation slots (`yaw, pitch, roll, 0, 0, 0`); OpenTrack
  reads six doubles as `x, y, z, yaw, pitch, roll`, so rotation (including roll /
  head tilt) was being fed into translation and the rotation axes stayed zero.
  The angles are now sent in the correct last three slots.

### Changed
- Default axis convention is now **YXZ with X and Z inverted** (previously Z
  only); the GUI's Invert X and Invert Z checkboxes both start checked.
- **GUI no longer flickers.** The live graph is now double-buffered, the window
  clips its children, background erase is suppressed, and only the graph
  rectangle is invalidated per sample. Child controls are dark-themed for a
  cohesive look, and the graph gained a degree grid, legend, and axis labels.
- JSON telemetry schema bumped to `version: 2`.
- The configured axis convention is now applied to the accelerometer vector too,
  so all streams share one coordinate frame.

## [0.1.0]

### Added
- Initial single-file bridge: HID + Windows Sensor API backends, orientation
  filtering with recenter and drift correction, OpenTrack + JSON UDP output,
  diagnostics GUI, and one-click driver-only "Repair Tracker" recovery.

[Unreleased]: https://github.com/OWNER/xm5-head-tracker/compare/v0.1.0...HEAD
[0.1.0]: https://github.com/OWNER/xm5-head-tracker/releases/tag/v0.1.0
