#!/usr/bin/env bash
set -euo pipefail

die() {
  printf 'error: %s\n' "$*" >&2
  exit 1
}

info() {
  printf '==> %s\n' "$*"
}

require_command() {
  command -v "$1" >/dev/null 2>&1 || die "missing command: $1"
}

require_app_bundle_path() {
  case "$1" in
    /*.app) ;;
    *) die "KANATA_APP_DIR must be an absolute .app path, got: $1" ;;
  esac
}

wait_for_user() {
  local prompt="$1"
  local reply

  if [[ ! -t 0 ]]; then
    die "macOS privacy permissions must be approved interactively. Re-run this installer from Terminal."
  fi

  read -r -p "$prompt" reply
  if [[ "$reply" == "q" || "$reply" == "Q" ]]; then
    die "installation cancelled"
  fi
}

request_macos_privacy_permissions() {
  info "requesting macOS Accessibility registration for Kanata"
  open -n "$KANATA_APP_DIR" --args --macos-request-permissions >/dev/null 2>&1 || true

  cat <<EOF

Action needed:
  Enable Kanata.app in System Settings -> Privacy & Security -> Accessibility.
  If Kanata.app is not listed, add this application with the + button:
    $KANATA_APP_DIR

  After the toggle is enabled, return to this terminal.
EOF

  if [[ "$OPEN_PRIVACY_SETTINGS" == "1" ]]; then
    info "opening Accessibility settings"
    open "$ACCESSIBILITY_SETTINGS_URL" >/dev/null 2>&1 || true
  fi
  wait_for_user "Enable Kanata.app in Accessibility, then press Enter to start services, or type q to quit: "
}

default_install_bin_dir() {
  local brew_prefix

  if command -v brew >/dev/null 2>&1; then
    brew_prefix="$(brew --prefix 2>/dev/null || true)"
    if [[ -n "$brew_prefix" ]]; then
      printf '%s/bin\n' "$brew_prefix"
      return
    fi
  fi

  if [[ "$(uname -m)" == "arm64" ]]; then
    printf '/opt/homebrew/bin\n'
  else
    printf '/usr/local/bin\n'
  fi
}

default_config_source() {
  local candidate

  for candidate in \
    "$SCRIPT_DIR/kanata.kbd" \
    "$SCRIPT_DIR/v2/kanata.kbd" \
    "$SCRIPT_DIR/v1/kanata.kbd"
  do
    if [[ -f "$candidate" ]]; then
      printf '%s\n' "$candidate"
      return
    fi
  done

  printf '%s\n' "$SCRIPT_DIR/v2/kanata.kbd"
}

xml_escape() {
  sed \
    -e 's/&/\&amp;/g' \
    -e 's/</\&lt;/g' \
    -e 's/>/\&gt;/g' \
    -e 's/"/\&quot;/g' \
    -e "s/'/\&apos;/g" \
    <<<"$1"
}

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"

KANATA_GIT_URL="${KANATA_GIT_URL:-https://github.com/alenkimov/kanata}"
KANATA_GIT_BRANCH="${KANATA_GIT_BRANCH:-main}"
INSTALL_BIN_DIR="${INSTALL_BIN_DIR:-$(default_install_bin_dir)}"
KANATA_APP_DIR="${KANATA_APP_DIR:-/Applications/Kanata.app}"
KANATA_BUNDLE_ID="${KANATA_BUNDLE_ID:-com.alenkimov.Kanata}"
CONFIG_SOURCE="${CONFIG_SOURCE:-$(default_config_source)}"
CONFIG_DEST="${CONFIG_DEST:-/etc/kanata/kanata.kbd}"
KANATA_LABEL="${KANATA_LABEL:-com.alenkimov.kanata}"
HELPER_LABEL="${HELPER_LABEL:-com.alenkimov.kanata-input-source-helper}"
KANATA_LOG="${KANATA_LOG:-/tmp/kanata.log}"
HELPER_LOG="${HELPER_LOG:-/tmp/kanata-input-source-helper.log}"
ACCESSIBILITY_SETTINGS_URL="x-apple.systempreferences:com.apple.preference.security?Privacy_Accessibility"
OPEN_PRIVACY_SETTINGS="${OPEN_PRIVACY_SETTINGS:-1}"

OLD_KANATA_LABEL="dev.kanata.kanata"
OLD_HELPER_LABEL="dev.kanata.input-source-helper"

KANATA_BIN="$KANATA_APP_DIR/Contents/MacOS/kanata"
HELPER_BIN="$INSTALL_BIN_DIR/kanata-input-source-helper"
KANATA_PLIST="/Library/LaunchDaemons/$KANATA_LABEL.plist"
HELPER_PLIST="$HOME/Library/LaunchAgents/$HELPER_LABEL.plist"
OLD_KANATA_PLIST="/Library/LaunchDaemons/$OLD_KANATA_LABEL.plist"
OLD_HELPER_PLIST="$HOME/Library/LaunchAgents/$OLD_HELPER_LABEL.plist"

if [[ "$(uname -s)" != "Darwin" ]]; then
  die "this installer only supports macOS"
fi

if [[ "$(id -u)" == "0" ]]; then
  die "run this as your normal macOS user, not with sudo; the script will ask for sudo when needed"
fi

require_app_bundle_path "$KANATA_APP_DIR"

require_command cargo
require_command git
require_command launchctl
require_command plutil

[[ -f "$CONFIG_SOURCE" ]] || die "config not found: $CONFIG_SOURCE. Keep a layout at MacOS/v2/kanata.kbd or set CONFIG_SOURCE=/path/to/kanata.kbd"

USER_ID="$(id -u)"
TMP_DIR="$(mktemp -d)"
trap 'rm -rf "$TMP_DIR"' EXIT

info "building Kanata from $KANATA_GIT_URL branch $KANATA_GIT_BRANCH"
git clone --depth 1 --branch "$KANATA_GIT_BRANCH" "$KANATA_GIT_URL" "$TMP_DIR/kanata"
(
  cd "$TMP_DIR/kanata"
  cargo build --release --bin kanata --bin kanata-input-source-helper
)

info "installing input-source helper to $INSTALL_BIN_DIR"
sudo mkdir -p "$INSTALL_BIN_DIR"
sudo install -m 755 "$TMP_DIR/kanata/target/release/kanata-input-source-helper" "$HELPER_BIN"

info "installing config to $CONFIG_DEST"
sudo mkdir -p "$(dirname "$CONFIG_DEST")"
sudo install -m 644 "$CONFIG_SOURCE" "$CONFIG_DEST"

KANATA_BIN_XML="$(xml_escape "$KANATA_BIN")"
HELPER_BIN_XML="$(xml_escape "$HELPER_BIN")"
CONFIG_DEST_XML="$(xml_escape "$CONFIG_DEST")"
KANATA_LOG_XML="$(xml_escape "$KANATA_LOG")"
HELPER_LOG_XML="$(xml_escape "$HELPER_LOG")"
KANATA_LABEL_XML="$(xml_escape "$KANATA_LABEL")"
HELPER_LABEL_XML="$(xml_escape "$HELPER_LABEL")"
KANATA_BUNDLE_ID_XML="$(xml_escape "$KANATA_BUNDLE_ID")"

cat >"$TMP_DIR/$KANATA_LABEL.plist" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN"
  "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>Label</key>
  <string>$KANATA_LABEL_XML</string>

  <key>ProgramArguments</key>
  <array>
    <string>$KANATA_BIN_XML</string>
    <string>--cfg</string>
    <string>$CONFIG_DEST_XML</string>
  </array>

  <key>UserName</key>
  <string>root</string>

  <key>RunAtLoad</key>
  <true/>

  <key>KeepAlive</key>
  <dict>
    <key>SuccessfulExit</key>
    <false/>
  </dict>

  <key>StandardOutPath</key>
  <string>$KANATA_LOG_XML</string>

  <key>StandardErrorPath</key>
  <string>$KANATA_LOG_XML</string>
</dict>
</plist>
EOF

cat >"$TMP_DIR/Kanata-Info.plist" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN"
  "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>CFBundleDevelopmentRegion</key>
  <string>en</string>

  <key>CFBundleDisplayName</key>
  <string>Kanata</string>

  <key>CFBundleExecutable</key>
  <string>kanata</string>

  <key>CFBundleIdentifier</key>
  <string>$KANATA_BUNDLE_ID_XML</string>

  <key>CFBundleInfoDictionaryVersion</key>
  <string>6.0</string>

  <key>CFBundleName</key>
  <string>Kanata</string>

  <key>CFBundlePackageType</key>
  <string>APPL</string>

  <key>CFBundleShortVersionString</key>
  <string>1.0</string>

  <key>CFBundleVersion</key>
  <string>1</string>

  <key>LSUIElement</key>
  <true/>
</dict>
</plist>
EOF

cat >"$TMP_DIR/$HELPER_LABEL.plist" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN"
  "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>Label</key>
  <string>$HELPER_LABEL_XML</string>

  <key>ProgramArguments</key>
  <array>
    <string>$HELPER_BIN_XML</string>
  </array>

  <key>LimitLoadToSessionType</key>
  <string>Aqua</string>

  <key>RunAtLoad</key>
  <true/>

  <key>KeepAlive</key>
  <dict>
    <key>SuccessfulExit</key>
    <false/>
  </dict>

  <key>StandardOutPath</key>
  <string>$HELPER_LOG_XML</string>

  <key>StandardErrorPath</key>
  <string>$HELPER_LOG_XML</string>
</dict>
</plist>
EOF

plutil -lint "$TMP_DIR/$KANATA_LABEL.plist" "$TMP_DIR/$HELPER_LABEL.plist" "$TMP_DIR/Kanata-Info.plist" >/dev/null

info "stopping any previous Kanata launchd jobs"
sudo launchctl bootout "system/$KANATA_LABEL" >/dev/null 2>&1 || true
sudo launchctl bootout "system/$OLD_KANATA_LABEL" >/dev/null 2>&1 || true
launchctl bootout "gui/$USER_ID/$HELPER_LABEL" >/dev/null 2>&1 || true
launchctl bootout "gui/$USER_ID/$OLD_HELPER_LABEL" >/dev/null 2>&1 || true
sudo rm -f "$KANATA_PLIST" "$OLD_KANATA_PLIST"
rm -f "$HELPER_PLIST" "$OLD_HELPER_PLIST"

info "installing Kanata.app to $KANATA_APP_DIR"
sudo rm -rf "$KANATA_APP_DIR"
sudo mkdir -p "$KANATA_APP_DIR/Contents/MacOS"
sudo install -m 644 "$TMP_DIR/Kanata-Info.plist" "$KANATA_APP_DIR/Contents/Info.plist"
sudo install -m 755 "$TMP_DIR/kanata/target/release/kanata" "$KANATA_BIN"

info "installing LaunchDaemon file for Kanata"
sudo install -m 644 -o root -g wheel "$TMP_DIR/$KANATA_LABEL.plist" "$KANATA_PLIST"

info "installing LaunchAgent file for kanata-input-source-helper"
mkdir -p "$HOME/Library/LaunchAgents"
install -m 644 "$TMP_DIR/$HELPER_LABEL.plist" "$HELPER_PLIST"

request_macos_privacy_permissions

info "loading launchd services"
sudo launchctl bootstrap system "$KANATA_PLIST"
sudo launchctl enable "system/$KANATA_LABEL"
launchctl bootstrap "gui/$USER_ID" "$HELPER_PLIST"
launchctl enable "gui/$USER_ID/$HELPER_LABEL"

info "starting services"
launchctl kickstart -k "gui/$USER_ID/$HELPER_LABEL"
sudo launchctl kickstart -k "system/$KANATA_LABEL"

cat <<EOF

Installed.

Kanata:
  app: $KANATA_APP_DIR
  binary: $KANATA_BIN
  config: $CONFIG_DEST
  service: system/$KANATA_LABEL
  log: $KANATA_LOG

Input-source helper:
  binary: $HELPER_BIN
  service: gui/$USER_ID/$HELPER_LABEL
  log: $HELPER_LOG

Verify:
  sudo launchctl print system/$KANATA_LABEL
  launchctl print gui/$USER_ID/$HELPER_LABEL
  tail -f "$KANATA_LOG"
  tail -f "$HELPER_LOG"

Prerequisites that cannot be fully automated:
  - Karabiner-Elements / Karabiner VirtualHIDDevice must be installed and approved.
  - macOS input sources used by the config, for example U.S. and Russian - PC,
    must be added in System Settings.
EOF
