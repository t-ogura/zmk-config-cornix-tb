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

- `0003-central-resilient-scanning.patch` (v2)
  Split-central hardening: (1) set `is_scanning=true` only after
  `bt_le_scan_start` succeeds, (2) continuous passive scan (30 ms window ==
  interval, 100% duty) instead of the default 50%-duty scan so a contending
  peripheral's ~100-150 ms adv window is not missed, (3) scan WITHOUT
  duplicate filtering so the controller's dup-adv filter can never latch a
  peripheral as "already seen" after a failed CONNECT_REQ, (4) a 5 s
  recovery watchdog that restarts scanning ONLY when the scan is not
  running, a peripheral slot is open, and no connection attempt is in
  flight, and (5) re-trigger `start_scanning()` on transitions back to
  `ZMK_ACTIVITY_ACTIVE`. Eliminates the "second peripheral never
  reconnects" symptom on Cornix TB without requiring a hard reset.

  v2 note: v1's watchdog stop-and-started the scan every 5 s while any
  slot was unconnected. Those unsynchronized scan commands raced ZMK's
  own scan/initiator handover (`split_central_eir_found` gives the LL
  scanner to the initiator for up to `BT_CREATE_CONN_TIMEOUT`), wedging
  the host and permanently blocking the system workqueue — a reproducible
  total freeze at wake+5 s on the xiao-as-central build. Removing
  duplicate filtering makes the churn unnecessary, and the watchdog now
  never touches a live scan or a pending connect.

## Local apply

```sh
cd zmk
for p in ../patches/zmk/*.patch; do git apply "$p"; done
```

Patches apply against the zmk root (paths start with `app/...`).
