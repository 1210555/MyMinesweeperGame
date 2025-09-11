# マイマインスイーパー

##　このプロジェクトについて
c++を用いて初めてゲーム制作を行いました。enum class を用いた状態管理や UI 配置などにこだわりました。個人開発ながら保守性や可読性を意識して実装しました。

## 動作動画（YouTube）

https://www.youtube.com/watch?v=iHsHOCTpz-M

## 概要

C++と SFML を用いて作成した 2D マインスイーパー風ゲームです。  
難易度を選んで開始し、左クリックでマスを開き、右クリックで旗を立てることができます。

## 使用技術

- **言語**：C++
- **開発環境**：Visual Studio Code（MSYS2 + UCRT64 環境）
- **ライブラリ**：SFML（Simple and Fast Multimedia Library）

## ビルド方法（MSYS2 UCRT64 環境で実行）

```bash
g++ src/main.cpp src/Game.cpp src/Field.cpp src/GameUI.cpp src/GameRenderer.cpp src/SoundManager.cpp -o MyMinesweeper -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
実行方法
bash
./MyMinesweeper.exe
※ .exe をダブルクリックしても動作しない場合があります。MSYS2のターミナルから実行してください。

操作方法
左クリック：マスを開く
右クリック：旗を立てる

ボタン説明
Easy,Normal,Hard：メインメニュー画面でそれぞれのボタンに応じた難易度のボタンを押すことでゲーム開始

Menu：プレイ時にウィンドウ右上の「Menu」ボタンを押すことでメニュー画面に移動

Continue、Finish：メニュー画面時にContinueボタンで元の状態に戻り、Finishボタンでメインメニュー画面に移動

GoTitle：ゲームオーバー時やクリア時にウィンドウ右上の「GoTitle」を押すことでタイトル画面に移動

```
