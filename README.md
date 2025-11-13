# ZMK Config for Cornix TB (Trackball)

Cornixとモジュール型トラックボールを連携させ、一つのキーボードとして利用できるようにするZMKファームウェアです。

## モジュール型トラックボール

 ![トラックボールモジュール搭載例](docs/images/trackball_mount.jpg)
 親指キーの一番外側のキースイッチの箇所にマウントすることを想定
 一応左でも実装可能と思うが調整が必要

 ### 必要部品
 - **PAW3222ブレイクアウトボード**: https://nogikes.booth.pm/items/6520217
 - **FFCコネクタ変換基板**: 上記からセット購入推奨
 - **FFCケーブル**: 15cm以上で取り回ししやすくなります
 - **XIAO BLE nrf52840**: 
 - **上記配線用ケーブル**:
 - **トラックボールケース**: https://github.com/sekigon-gonnoc/torabo-tsuki-lp/blob/master/3d-models/STL/trackball-case-19mm-Body.stl
 - **トラックボールケース用マウント台**: https://github.com/t-ogura/zmk-config-cornix-tb/tree/master/3dmodel/cornix_trackball_case_mount.step
 - **19mmトラックボール**: PTFE球がおすすめ 

  ### 配線： PAW3222センサー ⇔ Seeeduino XIAO nRF52840

  | ピン番号 | PAW3222信号 | 機能 | XIAO nRF52840ピン | 備考 |
  |---------|------------|------|------------------|------|
  | 1 | 3.3V | 電源 | 3V3 | 3.3V電源 |
  | 2 | CS | Chip Select | D10 | SPI通信 |
  | 3 | MOTION | モーション検出 | D9 | 割り込み信号 |
  | 4 | SDIO | SPI Data I/O | D8 | 双方向データ |
  | 5 | SCLK | SPI Clock | D7 | クロック |
  | 6 | GND | グランド | GND | グランド |

  バッテリーを配線してもいいと思います。
  現段階ではUSB給電を想定しています。

  配線例
 ![配線例](docs/images/trackball_wiring.jpg)

## Cornix TBの構成
- **Left Cornix**: Central
- **Right Cornix**: Peripheral
- **Trackball module**: Peripheral

Peripheralが2台になる3台構成になります。

## Prospectorについて

現段階でProspectorを使用するように設定されていますが不要であればconfig/west.ymlとconfig/cornix_left.confを編集してください。

## 参考資料
下記情報を大いに活用させていただきました。ありがとうございます。
- https://github.com/hitsmaxft/zmk-keyboard-cornix/
- https://zenn.dev/kot149/articles/zmk-workspace
- https://zenn.dev/kot149/articles/zmk-input-processor-cheat-sheet
- https://zenn.dev/kot149/articles/zmk-auto-mouse-layer
- https://note.com/pooh_polo/n/n133ad59486ea
- https://github.com/sekigon-gonnoc/small-mouse-sensor-module

## ライセンス

このプロジェクトはMITライセンスの下で公開されています。

```
MIT License

Copyright (c) 2025 Cornix TB Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
