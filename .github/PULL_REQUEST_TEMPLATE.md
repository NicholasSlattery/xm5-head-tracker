## Summary

<!-- What does this PR change, and why? -->

## How tested

<!-- This project talks to real Bluetooth hardware; describe how you verified the
     change. e.g. probe/dump output, GUI screen capture, OpenTrack behaviour. -->

## Checklist

- [ ] Builds warning-clean at `/W3` with MSVC (`build.cmd`)
- [ ] Stays within scope: no device spoofing, identity changes, or firmware edits
- [ ] Updated `docs/PROTOCOL.md` if the UDP/JSON output changed
- [ ] Bumped the JSON `version` if the change is not backward-compatible
- [ ] Added a line to the **Unreleased** section of `CHANGELOG.md`
