# ZMK local patches

These patches are applied to the `zmk/` workspace clone after `west update`,
both in CI (see `.github/workflows/build.yml`) and locally (apply manually with
`git apply` from the zmk dir).

Kept in this repo rather than upstreamed — small private use only.

## Files

- `0001-nice_view-Kconfig-add-int-type.patch`
  Workaround for ZMK upstream regression in `3538843a`: `LS0XX_VCOM_THREAD_PRIO`
  defined without a type aborts Kconfig parsing on Zephyr 4.1+. Adds `int`.

- `0002-peripheral-undirected-adv-only.patch`
  Skip directed advertising in split-peripheral role; always use undirected
  `BT_LE_ADV_CONN_FAST_2`. Eliminates the BLE-spec 1.28s timeout that loses
  the race when the central is busy connecting to another peripheral. Greatly
  improves multi-peripheral reconnect reliability on Cornix TB.

## Local apply

```sh
cd zmk
for p in ../patches/zmk/*.patch; do git apply "$p"; done
```

Patches apply against the zmk root (paths start with `app/...`).
