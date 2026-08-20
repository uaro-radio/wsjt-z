# WSJT-Z — UaHamAward fork

A fork of WSJT-Z carrying the same two features as this project's WSJT-X fork
— a DXCC country filter and a direct connection to
[uahamaward.com](https://uahamaward.com) — plus a Ukrainian interface.
Everything else is upstream WSJT-Z, unchanged.

**Read this before touching anything.** Most of it was learned the expensive
way.

---

## The three repositories, and how they relate

| | What it is | Where |
|---|---|---|
| **This repo** | Fork of WSJT-Z (WSJT-X 3.0.0 base + mod 2.0.18) | `uaro-radio/wsjt-z` |
| **WSJT-X fork** | The same features on upstream WSJT-X 3.0.2 | `uaro-radio/wsjtx` |
| **The platform** | The award site the two talk to | `PetroOstapuk/UaHamAward` |

The two forks are **siblings, not a chain.** `UaHam/` is almost identical in
both; a change there usually belongs in the other one too. **The WSJT-X fork
is where a feature is written first** — it has the fuller documentation, and
`../wsjtx/AGENTS.md` is worth reading alongside this file.

Upstream here is `sq9fve/wsjt-z`. WSJT-Z is itself a fork of WSJT-X, so this
tree carries WSJT-X code that upstream WSJT-X has since changed — see the
gotchas.

**Upstream ships Windows only.** `sq9fve/wsjt-z` publishes `win32` and `win64`
installers and nothing else. That is why Windows is the platform that matters
here, and why an AppImage was not worth fighting for (below).

---

## What the fork adds

In `UaHam/`, which upstream will never touch:

| File | Responsibility |
|---|---|
| `UaHam/CountryFilter.hpp` | Header-only. Off / Block / Only, on a DXCC primary prefix |
| `UaHam/SiteServer.{hpp,cpp}` | The WebSocket endpoint the site connects to |
| `UaHam/QsoPayload.{hpp,cpp}` | Logged ADIF → the JSON the site expects |
| `UaHam/SettingsTabs.{hpp,cpp}` | The Settings tabs, built in code |
| `UaHam/StatusWidget.{hpp,cpp}` | The «UaHam» tab in the main window |

The QRZ.com lookup (`UaHam/QrzLookup`, `UaHam/CallInfoWidget`) exists **only in
the WSJT-X fork**, because WSJT-Z already has its own QRZ integration inline in
`mainwindow.cpp`. Do not port it back here; port bug fixes between them
instead.

### Contact points outside `UaHam/`

| File | Why it is touched |
|---|---|
| `CMakeLists.txt` | `WSJT_FORK_TAG`; `UaHam/*.cpp`; `uk` in `LANGUAGES`; the MinGW `-Werror` exception |
| `Configuration.hpp` / `.cpp` | Settings storage and accessors |
| `widgets/mainwindow.h` / `.cpp` | The filter check, the tabs, the `acceptQSO` hook, the title |
| `logbook/AD1CCty.hpp` / `.cpp` | `entities()` — the cty.dat table for the picker |
| `widgets/about.cpp` | The modified-build notice GPLv3 §5(a) asks for |
| `main.cpp` | Reads the saved UI language before translators are installed |
| `lib/decoder.f90`, `lib/map65_mmdec.f90` | A dead include removed — see gotchas |
| `translations/wsjtx_uk.ts` | The Ukrainian translation |
| `.github/workflows/*` | The whole CI, which upstream does not have |

**Settings tabs are added from code, never to `Configuration.ui`** — that file
is generated XML upstream edits often, and a tab written into it is a conflict
in every future merge.

---

## How the filter integrates here — different from WSJT-X

WSJT-Z funnels its own filtering through `callsignFiltered()`, and every gate
reads the result: the Band Activity gate, auto-sequencing, Auto CQ, and the
UDP feed when the operator ticks "Apply filtering to UDP messages". Feeding
the country verdict into `isFiltered` therefore gets all of that for free.

But WSJT-Z's filtering is **deliberately overridable in two places the country
filter must survive**:

- `for_us` lets a station calling you through — being called directly by a
  country the operator asked to hide is precisely the case they asked about;
- the Rx Frequency window takes `isFiltered` only as a colouring hint, never
  as a gate.

So the country verdict is kept as its own flag, `uahamHidden`, and both places
test it. Do not "simplify" that into `isFiltered`.

---

## Building

```sh
.uaham/docker/build.sh            # configure if needed, then build
.uaham/docker/build.sh --fresh
```

Ubuntu 24.04, Qt5, Hamlib 4.7.0 static. First run builds the image (~15 min);
after that incremental builds are seconds. Output in `build/linux/`.

---

## Releasing

**Bumping the version is the release.** Put a new `WSJT_FORK_TAG` (or
`VERSION_Z`) in the commit that should ship, push it to master, and a green CI
publishes it: `auto-release.yml` waits for CI, checks whether that version is
already tagged, and dispatches `release.yml` when it is not. Push anything
without a bump and it is a no-op, because the version is already released.
Nothing decides when to release except the release commit.

To release without waiting for CI, or to re-run one by hand:

```sh
gh workflow run release.yml --repo uaro-radio/wsjt-z --ref master
```

**CI runs on master.** It used to name `feat/uaham-integration`, the
integration branch, which has been merged since — so it fired for nobody. Auto
release depends on it firing.

**Do not tag by hand.** The tag is what a green build earns, not what starts
one: the workflow builds all five installers first and only then creates
`build/v<version>` on the commit it built, and publishes. A run that fails half
way leaves no tag to clean up and no version number burned on a build nobody
can download. Add `-f dry_run=true` to build everything and stop just before
the tag.

The version has **three parts**: the WSJT-X base (`Versions.cmake`), WSJT-Z's
own mod version (`VERSION_Z` in `CMakeLists.txt`), and the fork marker
(`WSJT_FORK_TAG`). It is read from those files, never typed — a file whose name
promises one version while its binary reports another is the kind of thing
nobody notices until they are debugging something else. **Bump
`WSJT_FORK_TAG` and commit it before dispatching**; the run refuses a version
that is already tagged, and refuses release notes that are missing or have no
`# English` section, both before any build starts.

Nothing is published unless every platform produced an installer. The
description comes from `.uaham/release-notes.md`; edit that, not the workflow.

**Release notes are written in both languages, in full.** Ukrainian first, then
an `# English` section carrying the same sections with the same headings — not
a summary paragraph, which is what this file used to end with. Whoever
downloads a WSJT-Z fork is as likely to read English as Ukrainian, and a
release page that explains a country filter in one language and waves at it in
the other gets misunderstood in exactly the half nobody checks. A section added
to one language and not the other is a review comment.

Notes are read from the commit being released, so editing `release-notes.md`
afterwards changes nothing on the page. Fix a published release with
`gh release edit <tag> --notes-file .uaham/release-notes.md` **and** commit the
file, or the next release repeats the omission.

---

## Gotchas that cost real time

**Windows: `.tls_common` from the Fortran OpenMP build.** `decoder.f90` and
`map65_mmdec.f90` carried `include 'timer_common.inc'`, which declares
`!$omp threadprivate(/timer_private/)`. With `-fopenmp` gfortran emits a
`.tls_common` directive the PE/COFF assembler does not know:

    Error: unknown pseudo-op: `.tls_common'

Linux never saw it because ELF supports the directive. Neither file used
`level` or `onlevel` — the only things that include defines — and upstream
WSJT-X removed the same lines long ago. **If a future merge brings them back,
remove them again.**

**Windows: `-Werror=maybe-uninitialized` on `HRDMessage`.** A false positive
from MinGW gcc 16 on a placement-new'd flexible-array struct. Demoted to a
warning for Windows + gcc 16 or newer only, exactly as upstream WSJT-X scopes
it; every other platform keeps `-Werror`.

**Linux: no AppImage.** `linuxdeploy` rejects this tree's AppDir with
"Could not find suitable icon for Icon entry: wsjtx_icon" while accepting one
built the same way from WSJT-X — same linuxdeploy build, byte-identical
`wsjtx.desktop`, the icon in the same place, the same command line.
Reproduced locally: it fails with WSJT-X's own icon too, and with the icon
stripped of its colour profile, so it is neither the icon nor the desktop
file. A defect in linuxdeploy. `.deb` and `.rpm` come from CPack and do not
involve it, and upstream WSJT-Z ships no Linux build at all, so this was not
worth more time. If you return to it, the difference to chase is that WSJT-X
warns "icon size could not be determined" and carries on where this tree gives
up.

**`filtered` was reset per batch, not per decode** — the same bug as in
WSJT-X, but note WSJT-Z reads its lines into a batch first, so the reset
belongs at the top of the processing loop rather than beside `blockUDP`.

**`qrzlookup.cpp` is dead code.** Not in `CMakeLists.txt`, no object file,
nothing constructs it. The working QRZ implementation is inline in
`mainwindow.cpp`. Do not "fix" the dead one.

**`rcc` compresses the translation resource.** Verifying a translation by
searching the binary for Ukrainian text proves nothing past about 23 kB — no
language is visible that way. Use `lconvert -i build/linux/wsjtx_uk.qm -o
/tmp/back.ts` instead.

**`WSJT_FORK_TAG` is a CMake cache variable, so editing `CMakeLists.txt` does
not move it.** `.uaham/docker/build.sh` configures only when `CMakeCache.txt` is
absent, which means a local build keeps reporting whatever marker the very first
configure wrote — a binary claiming `uaham1` long after the source says
otherwise. Releases are unaffected: CI configures from a clean checkout. To
check a local build, ask the binary rather than the source:

```sh
strings build/linux/wsjtx | grep -m1 -- -uaham
```

and if it disagrees, re-point the cache without a full rebuild:

```sh
docker run --rm -v "$PWD:/src" -u "$(id -u):$(id -g)" -e HOME=/tmp -w /src \
  uaham/wsjtx-build cmake -S /src -B /src/build/linux -DWSJT_FORK_TAG=uahamN
```

**cty.dat entity ids are line numbers** and are renumbered by every update, so
settings store the primary prefix (`UR`, `JA`, `K`), never the id.

---

## Translating

`translations/wsjtx_uk.ts`, about 1160 of 1550 strings. Most came from the
WSJT-X fork by merge; the rest are WSJT-Z's own settings and windows.

```sh
.uaham/tools/uk_merge.py  ../wsjtx/translations/wsjtx_uk.ts translations/wsjtx_uk.ts
.uaham/tools/uk_merge2.py ../wsjtx/translations/wsjtx_uk.ts translations/wsjtx_uk.ts
.uaham/tools/uk_list.py   translations/wsjtx_uk.ts MainWindow 1 40
.uaham/tools/uk_apply.py  translations/wsjtx_uk.ts MainWindow batch.txt
```

`uk_merge` matches full source text; `uk_merge2` matches sources differing only
by whitespace or Qt's rich-text wrapper, and reshapes the translation to fit.
Both skip ambiguous matches rather than guess — which is why `Troposheric
ducting`, a typo this tree carries and WSJT-X does not, was translated by hand.

`uk_apply.py` verifies a hash of each source before writing anything. That
guard exists because a shifted list once put ninety-one translations onto
their neighbours, producing valid XML and nonsense text.

---

## Commits

- **No AI co-author trailers.** Nothing in a commit message credits an
  assistant — no `Co-Authored-By:` for Claude or any other tool, no generated-by
  footer. The person who decided the change owns it; the tooling that typed it
  is no more a co-author than the editor is.
- **Commit as an address GitHub can resolve.** GitHub links a commit to an
  account by matching the author email against the verified addresses on that
  account, and nothing else. An address that is not on the account makes the
  commit authorless on the web view and invisible to the contributor graph —
  the work lands, the name does not. Check with:

  ```sh
  gh api repos/uaro-radio/wsjt-z/commits/HEAD --jq '.author.login // "NOT LINKED"'
  ```

  If that prints `NOT LINKED`, the address in `git config user.email` is
  missing from https://github.com/settings/emails. Adding and verifying it
  there fixes every past commit at once — GitHub re-links history, so there is
  never a reason to rewrite commits over this.

---

## Boundaries

- **Never push this fork to `sq9fve/wsjt-z`.** Contributions go upstream as
  pull requests. Two facts make this easy to get wrong. The only git remote
  here is `origin`, which is ours — so no push can reach upstream by accident.
  But this repository **is** a GitHub fork of `sq9fve/wsjt-z`, and `gh pr
  create` in a fork defaults its base to the **parent's** default branch. A
  pull request meant for our own `master` will be aimed at upstream unless
  `--repo uaro-radio/wsjt-z` is given. Merge locally and push to `origin`
  instead; the CI publishes nothing anywhere else, and nothing under
  `.github/workflows/` names another repository.
- Keep `UaHam/` in step with the WSJT-X fork; write the feature there first.
- QRZ data is shown to the operator and goes nowhere else.
- Ask before changing the site protocol, the tag format, or anything under
  `.github/workflows/` that publishes.

---

See `.uaham/CHANGELOG.md` for what changed and why. The WSJT-X fork's
`AGENTS.md` carries the full protocol contract with the site.

Last updated: 2026-08-20
