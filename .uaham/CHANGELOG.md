# Changelog — UaHamAward fork of WSJT-Z

Only this fork's changes. Upstream WSJT-Z's own history is in its commit log
and release notes.

Written for whoever picks this up next, including an agent in a fresh session:
each entry says what changed and, where it matters, why it is that way rather
than the obvious alternative.

---

## Unreleased — first build

Not yet tagged. The tag will be `build/v3.0.0-2.0.18-uaham1`; the version has
three parts and the release job refuses a tag that disagrees with any of them.

### Country filter

Settings → UaHam Filter. Any number of DXCC entities, in two modes: hide the
chosen ones, or show only those. A hidden station is hidden from Band
Activity, Rx Frequency and Active Stations, and auto-sequencing will not
answer it even when it calls directly. ALL.TXT stays complete, and the UDP
feed other programs read is only filtered if the operator has ticked WSJT-Z's
own "Apply filtering to UDP messages".

WSJT-Z made this easier and harder at once. Easier because it already funnels
its filtering through `callsignFiltered()`, so feeding the country verdict into
`isFiltered` reaches every gate at once. Harder because WSJT-Z's filtering is
deliberately overridable in two places the country filter must survive: a
message addressed to us passes via `for_us`, and the Rx Frequency window takes
`isFiltered` as a colouring hint rather than a gate. Hence the separate
`uahamHidden` flag — do not fold it into `isFiltered`.

### Direct connection to uahamaward.com

Settings → UaHam Site. A WebSocket on 127.0.0.1 hands every logged contact to
the site as it is logged, whether the operator logged it or auto-sequencing
did. This replaces `uaham-bridge`, the separate program the site used to
require. The protocol is the bridge's exactly, so the site needed no change.

### Ukrainian interface

About 1160 of 1550 strings, plus a Language tab. 736 came from the WSJT-X fork
by merge — the two trees share most of their text — and the rest are WSJT-Z's
own: the permanent ignore list, the filtering panel, alert commands, mode
switching, Auto CQ, the PSK Reporter window.

The merge refuses ambiguous matches rather than guessing. `Troposheric
ducting` — a typo this tree carries and WSJT-X does not — was therefore
translated by hand rather than matched to the correctly spelled string.

### Fixed while in there

`filtered` was cleared once per call to `readFromStdout` rather than per
decode, so one filtered decode hid every later decode in the same period and
suppressed auto-sequencing with it. The same bug exists in WSJT-X and is fixed
in that fork too. Note WSJT-Z reads its lines into a batch first, so the reset
belongs at the top of the processing loop.

### Windows build fixes

Both in inherited code, both already solved upstream in WSJT-X, neither picked
up by WSJT-Z:

- **`.tls_common`**: `decoder.f90` and `map65_mmdec.f90` still included
  `timer_common.inc`, whose `!$omp threadprivate(/timer_private/)` makes
  gfortran emit a directive the PE/COFF assembler does not know. Neither file
  used anything that include defines. Removed, as upstream did.
- **`-Werror=maybe-uninitialized`** on the placement-new'd `HRDMessage` struct,
  a false positive from MinGW gcc 16. Demoted to a warning for Windows +
  gcc 16 or newer only, scoped exactly as upstream scopes it.

### CI, which upstream does not have

Windows (`.exe`) and Linux x86_64/aarch64 (`.deb`, `.rpm`), plus a release
workflow driven by one pushed tag. Two checks earn their lines: the build
fails if the fork marker is missing from the binary, and nothing is published
unless every platform produced an installer.

**No AppImage.** `linuxdeploy` rejects this tree's AppDir with "Could not find
suitable icon for Icon entry: wsjtx_icon" while accepting one built the same
way from WSJT-X. Reproduced locally: it fails with WSJT-X's own icon too, and
with the icon stripped of its colour profile, so it is neither the icon nor
the desktop file — a defect in linuxdeploy. Upstream WSJT-Z ships no Linux
build at all, so this was not worth more time; `.deb` and `.rpm` come from
CPack and do not involve linuxdeploy.

### Fork marking

`WSJT_FORK_TAG` appends the marker to the version, the About box names the
build and its author, and the window title reads
`WSJT-Z MOD by SQ9FVE 2.0.18 · UaHamAward by UR3PKI`. GPLv3 §5(a) asks for the
notice; the practical reason is that a bug report about the country filter
must reach neither the WSJT-Z author nor the WSJT-X team.

---

## Base

Forked from `sq9fve/wsjt-z` at `695bd51` (2026-08-06), which is WSJT-X 3.0.0
plus WSJT-Z mod 2.0.18.
