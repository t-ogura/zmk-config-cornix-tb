# zmk-keyboard-cornix local patches

These patches are applied to the `zmk-keyboard-cornix/` workspace clone
after `west update`. Like the patches in `../zmk/`, they get wiped by
`west update` and must be re-applied (CI handles this via
`.github/workflows/build.yml`; locally, run `git apply` from inside
`zmk-keyboard-cornix/`).

## Files

- `0001-role-defaults-swappable.patch`
  Removes the `default y` clauses for `ZMK_SPLIT_ROLE_CENTRAL`,
  `ZMK_SPLIT_BLE_ROLE_CENTRAL`, and the two battery-proxy/fetching
  symbols from the `BOARD_CORNIX_LEFT` block of `Kconfig.defconfig`.
  Without this, the left board's defconfig hard-selects
  `ZMK_SPLIT_ROLE_CENTRAL` (via the prompt-less
  `ZMK_SPLIT_BLE_ROLE_CENTRAL` -> `select ZMK_SPLIT_ROLE_CENTRAL` chain)
  and the application config cannot disable it -- breaking the
  `feature/right-as-central` experiment that needs to swap the central
  to the right half.

  After the patch, both boards default to peripheral, and the
  application `config/cornix_*.conf` decides which side is central by
  explicitly setting `CONFIG_ZMK_SPLIT_ROLE_CENTRAL=y` on the chosen
  side.

## Local apply

```sh
cd zmk-keyboard-cornix
for p in ../patches/zmk-keyboard-cornix/*.patch; do git apply "$p"; done
```
