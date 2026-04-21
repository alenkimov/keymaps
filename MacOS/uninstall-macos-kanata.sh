#!/usr/bin/env bash
set -euo pipefail

info() {
  printf '==> %s\n' "$*"
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

INSTALL_BIN_DIR="${INSTALL_BIN_DIR:-$(default_install_bin_dir)}"
CONFIG_DEST="${CONFIG_DEST:-/etc/kanata/kanata.kbd}"
KANATA_LABEL="${KANATA_LABEL:-com.alenkimov.kanata}"
HELPER_LABEL="${HELPER_LABEL:-com.alenkimov.kanata-input-source-helper}"
KANATA_LOG="${KANATA_LOG:-/tmp/kanata.log}"
HELPER_LOG="${HELPER_LOG:-/tmp/kanata-input-source-helper.log}"

OLD_KANATA_LABEL="dev.kanata.kanata"
OLD_HELPER_LABEL="dev.kanata.input-source-helper"

KANATA_BIN="$INSTALL_BIN_DIR/kanata"
HELPER_BIN="$INSTALL_BIN_DIR/kanata-input-source-helper"
KANATA_PLIST="/Library/LaunchDaemons/$KANATA_LABEL.plist"
HELPER_PLIST="$HOME/Library/LaunchAgents/$HELPER_LABEL.plist"
OLD_KANATA_PLIST="/Library/LaunchDaemons/$OLD_KANATA_LABEL.plist"
OLD_HELPER_PLIST="$HOME/Library/LaunchAgents/$OLD_HELPER_LABEL.plist"

if [[ "$(uname -s)" != "Darwin" ]]; then
  printf 'error: this uninstaller only supports macOS\n' >&2
  exit 1
fi

if [[ "$(id -u)" == "0" ]]; then
  printf 'error: run this as your normal macOS user, not with sudo\n' >&2
  exit 1
fi

USER_ID="$(id -u)"

info "stopping Kanata LaunchDaemon"
sudo launchctl bootout "system/$KANATA_LABEL" >/dev/null 2>&1 || true
sudo launchctl bootout "system/$OLD_KANATA_LABEL" >/dev/null 2>&1 || true
sudo rm -f "$KANATA_PLIST" "$OLD_KANATA_PLIST"

info "stopping input-source helper LaunchAgent"
launchctl bootout "gui/$USER_ID/$HELPER_LABEL" >/dev/null 2>&1 || true
launchctl bootout "gui/$USER_ID/$OLD_HELPER_LABEL" >/dev/null 2>&1 || true
rm -f "$HELPER_PLIST" "$OLD_HELPER_PLIST"

if [[ "${REMOVE_BINARIES:-0}" == "1" ]]; then
  info "removing installed binaries"
  sudo rm -f "$KANATA_BIN" "$HELPER_BIN"
else
  info "keeping binaries; set REMOVE_BINARIES=1 to remove them"
fi

if [[ "${REMOVE_CONFIG:-0}" == "1" ]]; then
  info "removing installed config"
  sudo rm -f "$CONFIG_DEST"
else
  info "keeping config; set REMOVE_CONFIG=1 to remove it"
fi

if [[ "${REMOVE_LOGS:-0}" == "1" ]]; then
  info "removing logs"
  sudo rm -f "$KANATA_LOG"
  rm -f "$HELPER_LOG"
else
  info "keeping logs; set REMOVE_LOGS=1 to remove them"
fi

info "uninstalled launchd services"
